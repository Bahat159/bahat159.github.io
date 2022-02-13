
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
