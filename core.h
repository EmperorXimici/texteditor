/** @file core.h */
#ifndef CORE_H
#define CORE_H

/** \def MAX_STR_LEN This is the maximum length a single line is allowed to be.*/
#define MAX_STR_LEN 128
/** \def MAX_NAME_LEN This is the maximum length a file name is allowed to be.*/
#define MAX_NAME_LEN 30
/** \def SAME_STRING The strcmp fucntion returns 0 if the strings are the same.*/
#define SAME_STRING 0
/** \def DEV_CHAR This is the character that indecates a command is comming.*/
#define DEV_CHAR '~'

/**Commands:*/
/** \def CMD_EDIT means the file is being edited.*/
#define CMD_EDIT 'a'
/** \def CMD_NONE means the command was exicuted in*/
#define CMD_NONE '\0'


//Thse defines are obvious and dont need explenation
#define TRUE 1;
#define FALSE 0;

/** \struct node core.h "core.h"
    \brief This struct represents a single text line.

    This struct is basicly the node of a single linked list.
    It has been typedef'd to "node" and the size of content made fixed.
    Since it really doesnt matter because every modern computer has 4GB or more of system memory.
    When the file is saved we will worry about file size.

    This struct has a:
    \var char array: content which holds the string itself.
    \var char(used as bool): So it can hold TRUE or FALSE.
    \var node pointer: next which is a pointer to the next node in the list.
    \var node pointer: previous which is a pointer to the previous node in the list.
*/
typedef struct node{
    char content[MAX_STR_LEN];
    _Bool isEdited;
    struct node *next;
    struct node *previous;
}node;

/** \struct doc core.h "core.h"
    \brief This struct holds all the information about the document

    This struct like said before holds all the information you would need in a data structure like this one.
    Since this is a single linked list we need to keep track of the head and current node.

    This struct has a:
    \var node pointer: HEAD which holds first node in the list.
    \var node pointer: CURRENT which is the node that has the current focus of the user.
    \var char array: name which just hold the name of the file(this will be used for saving the document).
*/
typedef struct doc{
    node *HEAD;
    node *CURRENT;
    char name[MAX_NAME_LEN];
}doc;


/** \brief This function puts a new line at the end of the document

    TODO: add detailed description of the function

    @param struct doc: The document we want to add a line to at the end.
    @param const char pointer: The new line we want to add.
    @return int: This is used for error handling 0: everything OK, -1: failed to allocate memory.
*/
int ReadIn(doc *fileBuffer, const char *s);


/** \brief This function will process the input

    TODO: add detailed description of the function

    @param struct doc: The document we want to edit.
    @return int: This is used for error handling 0: everything OK.
*/
int GetInput(doc *fileBuffer);


/** \brief This function prints out the text in our document

    TODO: add detailed description of the function

    @param const struct doc: The document we want to print out.
    @return void.
*/
void PrintDoc(const doc *fileBuffer);


/** \brief This function reads the file into the system

    TODO: add detailed description of the function

    @param const char pointer: Name of the file we want to read.
    @return doc pointer: Returns the document we generated based on the input file.
*/
doc* ReadDocument(const char *filename);


int SaveDocument(const doc* fileBuffer);


void StartEditor();


int MoveCursorY(doc *fileBuffer, int y);


doc* NewDocument();


void GoInDevMode(doc *fileBuffer, char *command);


int ExitProgram();


void RemoveEnter(char* string);


int GetParameter(char* command);


#endif
