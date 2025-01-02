#include <stdio.h>
#include "fileread.h"
#include "optflags.h"

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

	printf("CONTENT: %s\n", file_contents);

	return 0;
}
