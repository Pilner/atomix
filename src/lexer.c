#include "lexer.h"
#include "tokens.h"
#include "utils.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Lexer *initializeLexer(const char *contents) {
	Lexer *lexer = calloc(1, sizeof(Lexer));
	lexer->contents = contents;
	lexer->index = 0;
	lexer->length = strlen(contents);
	lexer->ch = lexer->contents[lexer->index];

	return lexer;
}

// Peek to the next character index of content
char peekNextChar(Lexer* currentLexer) {
	if (currentLexer->index + 1 >= currentLexer->length) {
		return '\0';
	} else {
		return currentLexer->contents[currentLexer->index + 1];
	}
}

// Get the next character and shift index by +1
void readNextChar(Lexer* currentLexer) {
	currentLexer->index += 1;

	if (currentLexer->index >= currentLexer->length) {
		currentLexer->ch = '\0';
	} else {
		currentLexer->ch = currentLexer->contents[currentLexer->index];
	}
}

// Debug: For showing the current character
void showCurrChar(Lexer* currentLexer) {
	printf("-> %c\n", currentLexer->ch);
}

// Skip White Spaces and Comments
void skipWhiteSpace(Lexer *currentLexer) {
	while (
		currentLexer->ch == ' ' ||
		currentLexer->ch == '\t' ||
		currentLexer->ch == '\n' ||
		currentLexer->ch == '\r' ||
		currentLexer->ch == '#'
	) {

		// Comments
		if (currentLexer->ch == '#') {
			// Block Line Comments (##)
			if (peekNextChar(currentLexer) == '#') {
				readNextChar(currentLexer);
				readNextChar(currentLexer);
				while ((currentLexer->ch != '#' &&
					peekNextChar(currentLexer) != '#') &&
					peekNextChar(currentLexer) != '\0')
				{
					readNextChar(currentLexer);
				}
				readNextChar(currentLexer);
				readNextChar(currentLexer);
			} else { // Single Line Comments (#)
				while (currentLexer->ch != '\n' && currentLexer->ch != '\0') {
					readNextChar(currentLexer);
				}
			}
		}

		readNextChar(currentLexer);
	}
}


// Convert character/s into a string
char *lexerReadAsString(Lexer *currentLexer) {

	// Set Initial Index
	size_t initialIndex = currentLexer->index;

	// If lexeme is ASCII
	if (isascii(currentLexer->ch)) {

		// If lexeme is a character or string literal
		if (currentLexer->ch == '\'' || currentLexer->ch == '"') {
			if (currentLexer->ch == '\'') {
				readNextChar(currentLexer);
				while (currentLexer->ch != '\'' && currentLexer->ch != '\0') {
					readNextChar(currentLexer);
				}
			}

			if (currentLexer->ch == '"') {
				readNextChar(currentLexer);
				while (currentLexer->ch != '"' && currentLexer->ch != '\0') {
					readNextChar(currentLexer);
				}
			}
			readNextChar(currentLexer);

		} else { // Default

			// If lexeme is a keyword/identifier
			if (isalnum(currentLexer->ch)) {
				while (currentLexer->ch != '\0' &&
						(isalnum(currentLexer->ch) || currentLexer->ch == '.') &&
						(isalnum(peekNextChar(currentLexer)) || peekNextChar(currentLexer) == '.'))
				{
					readNextChar(currentLexer);
				}
				readNextChar(currentLexer);
			} else { // If lexeme is an operator
				if (peekNextChar(currentLexer) == '=' || currentLexer->ch == peekNextChar(currentLexer)) {
					readNextChar(currentLexer);
				}
				readNextChar(currentLexer);
			}
		}
	} else { // If lexeme is non-ASCII (Foreign Characters)
		while (!isascii(currentLexer->ch)) {
			readNextChar(currentLexer);
		}
	}

	size_t lexeme_length = currentLexer->index - initialIndex;

	char *string = strndup(currentLexer->contents + initialIndex, lexeme_length);

	return string;
}

// Tokenizer
Token *getCurrentToken(Lexer *currentLexer) {
	skipWhiteSpace(currentLexer);

	switch (currentLexer->ch) {

		// Syntax Operators
		case '{':
			return createToken(TK_LCURLY, lexerReadAsString(currentLexer));
		case '}':
			return createToken(TK_RCURLY, lexerReadAsString(currentLexer));
		case '[':
			return createToken(TK_LBRACKET, lexerReadAsString(currentLexer));
		case ']':
			return createToken(TK_RBRACKET, lexerReadAsString(currentLexer));
		case '(':
			return createToken(TK_LPAREN, lexerReadAsString(currentLexer));
		case ')':
			return createToken(TK_RPAREN, lexerReadAsString(currentLexer));
		case ',':
			return createToken(TK_COMMA, lexerReadAsString(currentLexer));
		case '.':
			return createToken(TK_DOT, lexerReadAsString(currentLexer));
		case ';':
			return createToken(TK_SEMICOLON, lexerReadAsString(currentLexer));
		case ':':
			return createToken(TK_COLON, lexerReadAsString(currentLexer));

		// Arithmetic Operators
		case '%':
			if (peekNextChar(currentLexer) == '=') {
				return createToken(TK_ASSIGNMOD, lexerReadAsString(currentLexer));
			}
			return createToken(TK_MODULO, lexerReadAsString(currentLexer));
		case '+':
			if (peekNextChar(currentLexer) == '+') {
				return createToken(TK_INCREMENT, lexerReadAsString(currentLexer));
			}
			if (peekNextChar(currentLexer) == '=') {
				return createToken(TK_ASSIGNINC, lexerReadAsString(currentLexer));
			}
			return createToken(TK_PLUS, lexerReadAsString(currentLexer));
		case '-':
			if (peekNextChar(currentLexer) == '-') {
				return createToken(TK_DECREMENT, lexerReadAsString(currentLexer));
			}
			if (peekNextChar(currentLexer) == '=') {
				return createToken(TK_ASSIGNDEC, lexerReadAsString(currentLexer));
			}
			return createToken(TK_MINUS, lexerReadAsString(currentLexer));
		case '*':
			if (peekNextChar(currentLexer) == '*') {
				return createToken(TK_EXPONENT, lexerReadAsString(currentLexer));
			}
			if (peekNextChar(currentLexer) == '=') {
				return createToken(TK_ASSIGNMUL, lexerReadAsString(currentLexer));
			}
			return createToken(TK_ASTERISK, lexerReadAsString(currentLexer));
		case '/':
			if (peekNextChar(currentLexer) == '/') {
				return createToken(TK_FLOORDIV, lexerReadAsString(currentLexer));
			}
			if (peekNextChar(currentLexer) == '=') {
				return createToken(TK_ASSIGNDIV, lexerReadAsString(currentLexer));
			}
			return createToken(TK_SLASH, lexerReadAsString(currentLexer));
		case '=':
			if (peekNextChar(currentLexer) == '=') {
				return createToken(TK_EQUAL, lexerReadAsString(currentLexer));
			}
			return createToken(TK_ASSIGN, lexerReadAsString(currentLexer));

		// Conditional Operators
		case '!':
			if (peekNextChar(currentLexer) == '=') {
				return createToken(TK_NOTEQUAL, lexerReadAsString(currentLexer));
			}
			return createToken(TK_BANG, lexerReadAsString(currentLexer));
		case '>':
			if (peekNextChar(currentLexer) == '=') {
				return createToken(TK_GEQUAL, lexerReadAsString(currentLexer));
			}
			return createToken(TK_GT, lexerReadAsString(currentLexer));
		case '<':
			if (peekNextChar(currentLexer) == '=') {
				return createToken(TK_LEQUAL, lexerReadAsString(currentLexer));
			}
			return createToken(TK_LT, lexerReadAsString(currentLexer));
		case '&':
			if (peekNextChar(currentLexer) == '&') {
				return createToken(TK_AND, lexerReadAsString(currentLexer));
			}
			return createToken(TK_AMPERSAND, lexerReadAsString(currentLexer));
		case '|':
			if (peekNextChar(currentLexer) == '|') {
				return createToken(TK_OR, lexerReadAsString(currentLexer));
			}

		// Terminator Operator
		case '\0':
			return createToken(TK_EOF, "\0");

		default:
			break;
	}

	// If lexeme starts with single quotation mark
	if (currentLexer->ch == '\'') {
		size_t initialIndex = currentLexer->index;

		readNextChar(currentLexer);

		// If lexeme is an empty char
		if (currentLexer->ch == '\'') {
			return createToken(TK_EMPTYCHERR, "");
		}

		while (currentLexer->ch != '\0' && currentLexer->ch != '\'') {
			readNextChar(currentLexer);
		}

		if (currentLexer->ch == '\'') { // If it completes the pair

			currentLexer->index = initialIndex;
			return createToken(TK_CHARLIT, lexerReadAsString(currentLexer));

		} else if (currentLexer->ch != '\0') { // If it has more than one char

			currentLexer->index = initialIndex;
			return createToken(TK_MULTICHERR, lexerReadAsString(currentLexer));

		}

		// If the pair of quotation marks is not completed
		currentLexer->index = initialIndex;
		return createToken(TK_CHOFERR, lexerReadAsString(currentLexer));
	}

	// If lexeme starts with double quotation mark
	if (currentLexer->ch == '"') {
		size_t initialIndex = currentLexer->index;

		readNextChar(currentLexer);

		while (currentLexer->ch != '\0' && currentLexer->ch != '"') {
			readNextChar(currentLexer);
		}

		if (currentLexer->ch == '"') { // If it completes the pair
			currentLexer->index = initialIndex;
			return createToken(TK_STRINGLIT, lexerReadAsString(currentLexer));
		}

		// If the pair of quotation marks is not completed
		currentLexer->index = initialIndex;
		return createToken(TK_STROFERR, lexerReadAsString(currentLexer));
	}

	// If lexeme starts with an alphabet or number
	if (isalnum(currentLexer->ch) ||
		currentLexer->ch == '_')
	{
		// Check if lexeme starts to be an keyword/identifier
		if (isValidIdentifier(currentLexer->ch)) {
			char *lexeme = lexerReadAsString(currentLexer);

			TokenType type = ReservedKeywords(lexeme);
			return createToken(type, lexeme);
		}

		// Check if lexeme starts to be a number;
		if (isValidNumber(currentLexer->ch)) {
			short dotExists = 0;
			short isDecimal = 0;
			char *floatOrDouble = "f";

			char *lexeme = lexerReadAsString(currentLexer);

			// If there are unnecessary characters in the number literal
			short invalidChars = 0;
			for (int i = 0; i < strlen(lexeme); i++)  {
				if (!isValidNumber(lexeme[i]) && lexeme[i] != '.') {
					invalidChars++;
				}
				if (invalidChars == 3) {
					return createToken(TK_INVALIDNUM, lexeme);
				}
			}
			if (invalidChars >= 1 && invalidChars <= 2) {
				if (lexeme[strlen(lexeme) - 1] != 'f') {
					return createToken(TK_INVALIDNUM, lexeme);
				}
				if (invalidChars == 2) {
					if (lexeme[strlen(lexeme) - 2] != 'l') {
						return createToken(TK_INVALIDNUM, lexeme);
					}
				}
			}

			// If there is a dot in the number
			if (strstr(lexeme, ".") != NULL) {
				dotExists = 1;
				if (lexeme[strlen(lexeme) - 1] == '.') {
					return createToken(TK_FLOATERR, lexeme);
				}

				// If there are more than one dot
				short dotCount = 0;
				for (int i = 0; i < strlen(lexeme) - 1; i++) {
					if (lexeme[i] == '.') {
						dotCount++;
						if (dotCount >= 2) {
							return createToken(TK_FLOATERR, lexeme);
						}
					}
				}
			}

			// If the data type is explicitly defined (-f & -lf)
			if (lexeme[strlen(lexeme) - 1] == 'f') {
				isDecimal = 1;
				if (lexeme[strlen(lexeme) - 2] == 'l') {
					floatOrDouble = "lf";
				}
			}

			// If number literal has a decimal
			if (dotExists) {
				if (strcmp(floatOrDouble, "f") == 0) {
					return createToken(TK_FLTLIT, lexeme);
				}
				if (strcmp(floatOrDouble, "lf") == 0) {
					return createToken(TK_DOUBLELIT, lexeme);
				}
			} else { // If number literal does not have a decimal
				if (isDecimal) {
					if (strcmp(floatOrDouble, "f") == 0) {
						return createToken(TK_FLTLIT, lexeme);
					}
					if (strcmp(floatOrDouble, "lf") == 0) {
						return createToken(TK_DOUBLELIT, lexeme);
					}
				}
				return createToken(TK_INTLIT, lexeme);
			}
		}
	}

	return createToken(TK_ILLEGALCHR, lexerReadAsString(currentLexer));
}

Token *createToken(TokenType type, char* lexeme) {
	Token *token = calloc(1, sizeof(Token));

	token->lexeme = lexeme;
	token->type = type;

	return token;
}

TokenType ReservedKeywords(const char *ident) {

	/* // Data Types */
	if (strcmp(ident, "int") == 0) {
		return TK_INT;
	}
	if (strcmp(ident, "char") == 0) {
		return TK_CHAR;
	}
	if (strcmp(ident, "float") == 0) {
		return TK_FLOAT;
	}
	if (strcmp(ident, "double") == 0) {
		return TK_DOUBLE;
	}
	if (strcmp(ident, "bool") == 0) {
		return TK_BOOL;
	}
	if (strcmp(ident, "void") == 0) {
		return TK_VOID;
	}
	if (strcmp(ident, "print") == 0) {
		return TK_OUTPUT;
	}
	if (strcmp(ident, "input") == 0) {
		return TK_INPUT;
	}
	if (strcmp(ident, "func") == 0) {
		return TK_FUNCTION;
	}
	if (strcmp(ident, "TRUE") == 0) {
		return TK_TRUE;
	}
	if (strcmp(ident, "FALSE") == 0) {
		return TK_FALSE;
	}
	if (strcmp(ident, "if") == 0) {
		return TK_IF;
	}
	if (strcmp(ident, "else") == 0) {
		return TK_ELSE;
	}
	if (strcmp(ident, "while") == 0) {
		return TK_WHILE;
	}
	if (strcmp(ident, "for") == 0) {
		return TK_FOR;
	}
	if (strcmp(ident, "continue") == 0) {
		return TK_CONTINUE;
	}
	if (strcmp(ident, "return") == 0) {
		return TK_RETURN;
	}


	return TK_IDENTIFIER;
}
