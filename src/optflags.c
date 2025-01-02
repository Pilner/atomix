#include "optflags.h"
#include <stdio.h>
#include <getopt.h>

const char *inputFile = NULL;
const char *outputFile = NULL;

int parseOptionFlags(const int argc, char *argv[]) {

	// Remove default getopt() error
	opterr = 0;

	// Loop all the written flags
	while (1) { 
		int flag = getopt(argc, argv, "o:vh");

		// If there are no flags
		if (flag == -1) {
			break;
		}

		switch (flag) {
			case 'o': // Output file
				outputFile = optarg;
				break;
			case 'v': // Version
				printAtomixVersionInfo();
				return 0;
			case 'h': // Help
				printAtomixHelpGuide();
				return 0;
			default: // Error
				printAtomixFlagError();
				return 1;
		}
	}


	// If unspecified output (-o), default to "a.out"
	if (outputFile == NULL) {
		outputFile = "a.out";
	}

	// If unspecified input file, throw an error
	if (optind > argc - 1) {
		printf("ERROR: input file not found in arguments [UNSPECIFIED_FILE_ERROR]\n");
		printAtomixHelpGuide();
		return 1;
	}

	// If more than 1 file argument
	if (optind < argc - 1) {
		printf("ERROR: too many argument/s: ");
		for (int i = optind + 1; i < argc; i++) {
			printf("%s ", argv[i]);
		}
		printf("[UNPARSED_ARGUMENTS_ERROR]\n");
		return 1;
	}

	// If option flag is incomplete (only dash -)
	if (argv[optind][0] == '-') {
		printf("ERROR: incomplete option flag '%s' on argument %d [INCOMPLETE_FLAG_ERROR]\n", argv[optind], optind);
	}

	// Assign remaining unparsed argument to inputFile
	if (inputFile == NULL) {
		inputFile = argv[optind];
		return 0;
	}

	printf("ERROR: uncaught error [UNCAUGHT_ERROR]\n");
	return 1;

}

void printAtomixVersionInfo() {
	printf("Atomix Compiler Version 0.1.0\n");
}

void printAtomixHelpGuide() {
	printf("Usage: atomix [option...] [file...].atx\n"
			"-o <filename>\t\twrite output to file\n"
			"-h\t\t\tPrint Help Guide\n"
			"-v\t\t\tPrint Atomix Version\n"
			"\n"
		  );
}

void printAtomixFlagError() {
	printf("ERROR: option or flag '-%c' is undefined [UNKNOWN_OPTION_FLAG_ERROR]\n", optopt);
}

