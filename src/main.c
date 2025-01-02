#include <stdio.h>
#include "optflags.h"

int main(int argc, char *argv[]) {

	/* printf("count: %d - command: %s", argc, argv[1]); */
	int flag = parseOptionFlags(argc, argv);

	if (flag == 1) {
		return 1;
	}

	return 0;
}
