/// ExprAST - Base class for all expression nodes.

class ExprAST {
    public:
    virtual ~ExprAST() {}
};

/// NumberExprAST - Expression class for numeric literals like "1.0".

class NumberExprAST : public ExprAST {
    double Val;

    public:
    NumberExprAST(double Val) : Val(Val) {}
};

/// VariableExprAST - Expression class for referencing a variable, like "a".

class VariableExprAST : public ExprAST {
    std::string Name;
    public:
    VariableExprAST(const std::string &Name) : Name(Name) {}

}
/// BinaryExprAST - Expression class for a binary operator.

class BinaryExprAST : public ExprAST{
    char Op;
    std::unique_ptr<ExprAST> LHS, RHS;

    pubilc:
    BinaryExprAST(char Op, std::unique_ptr<ExprAST> LHS, std::unique_ptr<ExprAST> RHS) : Op(Op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}
};

/// CallExprAST - Expression class for function calls.

class CallExprAST : public ExprAST {
    std::string Callee;
    std::vector<std::unique_ptr<ExprAST>> Args;
    public:
    CallExprAST(const std::string &Callee, std::vector<std::unique_ptr<ExprAST>> Args) : Callee(Callee), Args(std::move(Args)) {}
};


/// PrototypeAST - This class represents the "prototype" for a function,
/// which captures its name, and its argument names (thus implicitly the number
/// of arguments the function takes).

class PrototypeASt {
    std::string Name;
    std::vector<std::string> Args;

    public:
    PrototypeASt(const std::string &name, std::vector<std::string> Args) : Name(name), Args(std::move(Args)) {}
};

/// FunctionAST - This class represents a function definition itself.

class FunctionASt {
    std::unique_ptr<PrototypeASt> Proto;
    std::unique_ptr<ExprAST> Body;

    public:
    FunctionASt(Std::unique_ptr<PrototypeASt> Proto, std::unique_ptr<ExprAST> Body) : Proto(std::move(Proto)), Body(std::move(Body)) {}
};


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
