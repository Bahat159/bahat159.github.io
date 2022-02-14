#include <cctype>
#include "lexer.h"

/// CurTok/getNextToken - Provide a simple token buffer.  CurTok is the current
/// token the parser is looking at.  getNextToken reads another token from the
/// lexer and updates CurTok with its results.

static int Curtok;
static int getNextToken() {
    return Curtok = gettok();
}

/// LogError* - These are little helper functions for error handling.

std::unique_ptr<ExprAST> LogError(const char *Str) {
    fprintf(stderr, "LogError: %s\n", Str);
    return nullptr;
}

std::unique_ptr<PrototypeASt> LogError(const char *Str) {
    LogError(Str);
    return nullptr;
}

/// Basic Expression Parsing

/// numberexpr ::= number

static std::unique_ptr<ExprAST> ParseNumberExpr() {
    auto Result = std::make_unique<NumberExprAST> (NumVal);
    getNextToken();  /// consume the number
    return std::move(Result);
}


/// parenexpr ::= '(' expression ')'

static std::unique_ptr<ExprAST> ParseParenExpr() {
    getNextToken();
    auto V = ParseExpression();
     
    if(!V){
        return nullptr;
    }
    if (Curtok != ')'){
        return LogError("Expected ')'");
    }
    getNextToken();
    return V;
}

/// identifierexpr
///   ::= identifier
///   ::= identifier '(' expression* ')'

static std::unique_ptr<ExprASt> ParseIdentifierExpr() {
    std::string IdName = IdentifierStr;

    getNextToken();

    if(Curtok != '('){
        return std::make_unique<VariableExprAST>(IdName);
    }
    getNextToken();
    std::vector<std::unique_ptr<ExprAST>> Args;
    if (Curtok != ')'){
        while (1){
            if (auto Arg = ParseExpression()){
                Args.push_back(std::move(Args))
            }
            else {
                return nullptr;
            }
            if (Curtok == ')'){
                break;
            }
            if (Curtok != ','){
                return LogError("Expected ')' or ',' in argument list");
            }
            getNextToken();
        }
    }
    getNextToken();
    return std::make_unique<CallExprAST>(Idname, std::move(Args));
}

/// primary
///   ::= identifierexpr
///   ::= numberexpr
///   ::= parenexpr

static std::unique_ptr<ExprAST> ParsePrimary() {
    switch (Curtok){
        default:
            return LogError("unknown token when expecting an expression");
        case tok_identifier:
            return ParseIdentifierExpr();
        case tok_number:
            return ParseNumberExpr();
        case '(':
            return ParseParenExpr();
    }
}


/// Binary Expression Parsing

/// BinopPrecedence - This holds the precedence for each binary operator that is
/// defined.

static std::map<char, int> BinopPrecedence;

static int GetTokPrecedence() {
    if (!isascii(Curtok)) {
        return -1;
    }
    int TokPrec = BinopPrecedence[Curtok];
    if (TokPrec <= 0) {
        return -1;
    }
}


int parser_main() {
    BinopPrecedence['<'] = 10;
    BinopPrecedence['+'] = 20;
    BinopPrecedence['-'] = 30;
    BinopPrecedence['='] = 40; // highest
}

/// expression
///   ::= primary binoprhs
///

static std::unique_ptr<ExprAST> ParseExpression() {
    auto LHS = ParsePrimary();
    if(!LHS){
        return nullptr;
    }
    return ParseBinOpRHS(0, std::move(LHS));
}

/// binoprhs
///   ::= ('+' primary)*

static std::unique_ptr<ExprAST> ParseBinOpRHS(int ExprPrec, std::unique_ptr<ExprAST> LHS) {
    // If this is a binop, find its precedence.
    while(1) {
        int TokPrec = GetTokPrecedence();
        // If this is a binop that binds at least as tightly as the current binop,
        // consume it, otherwise we are done.

        if(TokPrec < ExprPrec){
            return LHS;
        }
        // Okay, we know this is a binop.
        int BinOp = Curtok;
        getNextToken();
        // Parse the primary expression after the binary operator.
        auto RHS = ParsePrimary();
        if(!RHS) {
            return nullptr;
        }
        // If BinOp binds less tightly with RHS than the operator after RHS, let
        // the pending operator take RHS as its LHS.
        int NextPrec = GetTokPrecedence();
        if (TokPrec < NextPrec) {
            RHS = ParseBinOpRHS (TokPrec + 1, std::move(RHS));
            if(!RHS) {
                return nullptr;
            }
        }
        LHS = std::make_unique<BinaryExprAST>(BinOp, std::move(LHS), std::move(RHS));
    }
}

/// prototype
///   ::= id '(' id* ')'

static std::unique)ptr<PrototpyeAST> ParsePrototype() {
    if(Curtok != tok_identifier) {
        return LogError("Expected function name in prototype");
    }
    std::string FnName = IdentifierStr;
    getNextToken();

    if(Curtok != '('){
        return LogErrorP("Expected '(' in prototype");
    }
    // Read the list of argument names.
    std::vector<std::string> ArgNames;
    while(getNextToken() == tok_identifier){
        ArgNames.push_back() == tok_identifier;
    }
    if(Curtok != ')'){
        return LogErrorP("Expected ')' in prototype");
    }
     // success.
    getNextToken();
    return std::make_unique<PrototypeAST>(FnName, std::move(ArgNames));
}
