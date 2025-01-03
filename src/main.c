#include <stdio.h>
#include <string.h>
#include "fileread.h"
#include "optflags.h"
#include "lexer.h"

int main(int argc, char *argv[]) {

	/* printf("count: %d - command: %s", argc, argv[1]); */
	int flag = parseOptionFlags(argc, argv);

	if (flag == 1) {
		return 1;
	}

	if (inputFile) {
		if (readATXFile(inputFile)) {
			printf("Error Reading File\n");
			return 1;
		}
	}

	Lexer *lexer = initializeLexer(file_contents);

	Token* tokenArray[100];

	int idx = 0;
	Token* currToken;

	do {
		currToken = getCurrentToken(lexer);
		if (tk_map[currToken->type]) {
			printf("%s:\t\t|%s|\n", tk_map[currToken->type], currToken->lexeme);
		}

	} while (currToken->type != TK_EOF);

	return 0;
}
