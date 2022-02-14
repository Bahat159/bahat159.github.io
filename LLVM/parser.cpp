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


/// Binary Expression PArsing

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
    return PArseBinOpRHS(0, std::move(LHS));
}

/// binoprhs
///   ::= ('+' primary)*

