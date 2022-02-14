#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>
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


/// definition ::= 'def' prototype expression

static std::unique_ptr<FunctionAST> ParseDefinition() {
    getNextToken();
    auto Proto = ParsePrototype();
    if(!Proto) {
        return nullptr;
    }
    if(auto E = ParseExpression()){
        return std::make_unique<FunctionAST>(std::move(Proto), std::move(E));
    }
    return nullptr;
}

/// external ::= 'extern' prototype

static std::unique_ptr<PrototypeAST> ParseExtern() {
    getNextToken();
    return ParsePrototype();
}

/// toplevelexpr ::= expression

static std::unique_ptr<FunctionAST> ParseTopLevelExpr() {
    if(auto E = ParseExpression()) {
         // Make an anonymous proto
        auto Proto = std::make_unique<PrototypeAST> ("", std::vector<std::string>());
        return std::make_unique<FunctionAST>(std::move(Proto), std::move(E));
    }
    return nullptr;
}

//===----------------------------------------------------------------------===//
// Top-Level parsing
//===----------------------------------------------------------------------===//

static void HandleDefinition() {
    if(ParseDefinition()) {
        fprintf(stderr, "Parsed a function definition\n");
    }
    else {
        // Skip token for error recovery.
        getNextToken();
    }
}

static void HandleExtern() {
    if(ParseExern()) {
        fprintf(stderr, "Parsed an extern\n");
    }
    else {
        // Skip token for error recovery.
        getNextToken();
    }
}

static void MainLoop() {
    while(true) {
        fprintf(sdterr, "Ready >  ");
        switch(Curtok) {
            case tok_eof:
                return;
            case ';':    // ignore top-level semicolons.
                getNextToken();
                break;
            case tok_def:
                HandleDefinition();
                break;
            case tok_extern:
                HandleExtern();
                break;
            default:
                HandleTopLevelExpression();
                break;
        }
    }
}


int main() {
     // Install standard binary operators.
     // 1 is lowest precedence.
     BinopPrecedence['<'] = 10;
     BinopPrecedence['+'] = 20;
     BinopPrecedence['-'] = 30;
     BinopPrecedence['*'] = 40;  // highest

    // Prime the first token.
    fprintf(stderr, "ready> ");
    getNextToken();

    // Run the main "interpreter loop" now.
    MainLoop();

    return 0;
}
