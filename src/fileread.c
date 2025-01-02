#include "fileread.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *file_contents;

int readATXFile(const char *filename) {
	// Check if file ends with ".atx"
	if (!strstr(filename, ".atx")) {
		printf("ERROR: unrecognized file extension '%s' [FILE_EXTENSION_ERROR]\n", filename);
		return 1;
	}

	// Open given file
	FILE *file_ptr = fopen(filename, "r");

	// If file cannot be opened
	if (file_ptr == NULL) {
		printf("ERROR: the file '%s' can't be opened\n", filename);
		fclose(file_ptr); // Close the file pointer to avoid memory leaks
		return 1;
	}

	// Get the length of the File Content
	fseek(file_ptr, 0, SEEK_END);
	unsigned long file_length = ftell(file_ptr);

	fseek(file_ptr, 0, SEEK_SET);

	file_contents = (char *)malloc(file_length + 1);

	// If file has an error in allocating memory
	if (file_contents == NULL) {
		printf("ERROR: file contents memory allocation failure [CONTENT_ALLOCATION_ERROR]\n");
		fclose(file_ptr); // Close the file pointer to avoid memory leaks
		return 1;
	}

	// Insert contents of file to the array;
	fread(file_contents, 1, file_length, file_ptr);
	file_contents[file_length] = '\0';

	fclose(file_ptr);
	return 0;
}
