#ifndef ATOMIX_TOKEN_H
#define ATOMIX_TOKEN_H

// Token Types
typedef enum {
	TK_ILLEGALCHR,
    TK_EMPTYCHERR,
    TK_MULTICHERR,
	TK_FLOATERR,
    TK_CHOFERR,
    TK_STROFERR,
	TK_INVALIDNUM,
	TK_EOF,
	TK_IDENTIFIER,
	TK_CHARLIT,
	TK_STRINGLIT,
	TK_INTLIT,
	TK_FLTLIT,
	TK_DOUBLELIT,
	TK_AMPERSAND,
    TK_AND,
    TK_OR,
    TK_BANG,
    TK_PLUS,
    TK_MINUS,
    TK_ASTERISK,
    TK_EXPONENT,
    TK_SLASH,
    TK_FLOORDIV,
    TK_MODULO,
    TK_ASSIGN,
    TK_ASSIGNINC,
    TK_ASSIGNDEC,
    TK_ASSIGNMUL,
    TK_ASSIGNDIV,
    TK_ASSIGNMOD,
    TK_INCREMENT,
    TK_DECREMENT,
    TK_EQUAL,
    TK_GT,
    TK_GEQUAL,
    TK_LT,
    TK_LEQUAL,
    TK_NOTEQUAL,
    TK_COMMA,
    TK_DOT,
	TK_SEMICOLON,
	TK_COLON,
	TK_LPAREN,
	TK_RPAREN,
	TK_LBRACKET,
    TK_RBRACKET,
    TK_LCURLY,
    TK_RCURLY,
	TK_INT,
	TK_CHAR,
	TK_FLOAT,
	TK_DOUBLE,
	TK_BOOL,
	TK_VOID,
	TK_OUTPUT,
	TK_INPUT,
	TK_FUNCTION,
	TK_TRUE,
	TK_FALSE,
	TK_IF,
	TK_ELSE,
	TK_WHILE,
	TK_FOR,
	TK_CONTINUE,
	TK_RETURN,

} TokenType;

static const char *const tk_map[] = {
	"TK_ILLEGALCHR",
    "TK_EMPTYCHERR",
    "TK_MULTICHERR",
	"TK_FLOATERR",
	"TK_CHOFERR",
    "TK_STROFERR",
	"TK_INVALIDNUM",
	"TK_EOF",
	"TK_IDENTIFIER",
	"TK_CHARLIT",
	"TK_STRINGLIT",
	"TK_INTLIT",
	"TK_FLTLIT",
	"TK_DOUBLELIT",
	"TK_AMPERSAND",
    "TK_AND",
    "TK_OR",
    "TK_BANG",
    "TK_PLUS",
    "TK_MINUS",
    "TK_ASTERISK",
    "TK_EXPONENT",
    "TK_SLASH",
    "TK_FLOORDIV",
    "TK_MODULO",
    "TK_ASSIGN",
    "TK_ASSIGNINC",
    "TK_ASSIGNDEC",
    "TK_ASSIGNMUL",
    "TK_ASSIGNDIV",
    "TK_ASSIGNMOD",
    "TK_INCREMENT",
    "TK_DECREMENT",
    "TK_EQUAL",
    "TK_GT",
    "TK_GEQUAL",
    "TK_LT",
    "TK_LEQUAL",
    "TK_NOTEQUAL",
    "TK_COMMA",
    "TK_DOT",
	"TK_SEMICOLON",
	"TK_COLON",
	"TK_LPAREN",
	"TK_RPAREN",
	"TK_LBRACKET",
    "TK_RBRACKET",
    "TK_LCURLY",
    "TK_RCURLY",
	"TK_INT",
	"TK_CHAR",
	"TK_FLOAT",
	"TK_DOUBLE",
	"TK_BOOL",
	"TK_VOID",
	"TK_OUTPUT",
	"TK_INPUT",
	"TK_FUNCTION",
	"TK_TRUE",
	"TK_FALSE",
	"TK_IF",
	"TK_ELSE",
	"TK_WHILE",
	"TK_FOR",
	"TK_CONTINUE",
	"TK_RETURN",
};

typedef struct TokenStruct {
	TokenType type;
	char *lexeme;
} Token;

Token *createToken(TokenType type, char* lexeme);

TokenType ReservedKeywords(const char *ident);


#endif
