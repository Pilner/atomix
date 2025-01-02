#ifndef ATOMIX_OPTFLAG_H
#define ATOMIX_OPTFLAG_H

extern const char *inputFile;
extern const char *outputFile;

extern int parseOptionFlags(int argc, char *argv[]);

extern void printAtomixVersionInfo();

extern void printAtomixFlagError();

extern void printAtomixHelpGuide();

#endif
