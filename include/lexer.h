#ifndef ATOMIX_LEXER_H
#define ATOMIX_LEXER_H

#include "tokens.h"

typedef struct LexerStruct {
	const char *contents;
	unsigned long index;
	unsigned long length;
	char ch;
} Lexer;

Lexer *initializeLexer(const char *contents);

char peekNextChar(Lexer* currentLexer);

void readNextChar(Lexer* currentLexer);

void showCurrChar(Lexer* currentLexer);

void skipWhiteSpace(Lexer *currentLexer);

char *lexerReadAsString(Lexer* currentLexer);

Token *getCurrentToken(Lexer *currentLexer);

#endif
