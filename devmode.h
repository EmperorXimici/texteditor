#include "core.h"

#ifndef DEVMODE_H
#define DEVMODE_H
#define MAX_STR_LEN 128

void GoInDevMode(doc *fileBuffer, char *command);

char **ParseCommand(char* command);

int ExitProgram();

void CleanCommand(char* command);

int isNum(char* string);

void RemoveEnter(char* string);

int CountCharacter(const char* string, const char symbol);

int MoveCursorY(doc *fileBuffer, int y);

int SaveDocument(const doc* fileBuffer);

void PrintDoc(const doc *fileBuffer);

#endif
