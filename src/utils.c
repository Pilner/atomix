#include "utils.h"

int isValidIdentifier(const char chr) {
	return 'a' <= chr && chr <= 'z' || 'A' <= chr && chr <= 'Z' || chr == '_';
}

int isValidNumber(const char chr) { return '0' <= chr && '9' >= chr; }
