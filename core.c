/** @file core.c */

/** @brief This is the core file, All the main code will be in this file.

    Detailed description follows here.
    @author Lasse Jacobs
    @date February 2016
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "core.h"
#include "devmode.h"

void StartEditor()
{
    doc *CurrentDocument = NewDocument();
    while(1)
    {
        GetInput(CurrentDocument);
    }
}

//This function puts a new line at the end of the document
int ReadIn(doc *fileBuffer, const char *s)
{
    //Allocate new store for our new line
    node *newNode = malloc(sizeof(*newNode));
    if(newNode == NULL)
        return -1;

    //Copy the string into the node
    strcpy(newNode->content, s);
    newNode->isEdited = FALSE;

    //If this is our first line we have to set it as head aswell
    if(fileBuffer->HEAD == NULL)
    {
        fileBuffer->HEAD = newNode;
        fileBuffer->CURRENT = newNode;

        fileBuffer->CURRENT->previous = NULL;
        fileBuffer->CURRENT->next = NULL;

        //everything went fine, let the caller know
        return 0;
    }
    else
    {
        newNode->previous = fileBuffer->CURRENT;
        if(fileBuffer->CURRENT->next == NULL)
            newNode->next = NULL;
        else
        {
            newNode->next = fileBuffer->CURRENT->next;
        }

        fileBuffer->CURRENT->next = newNode;
        fileBuffer->CURRENT = fileBuffer->CURRENT->next;

        //everything went fine, let the caller know
        return 0;
    }
}

//This function will process the input
int GetInput(doc *fileBuffer)
{
    //Our buffer to temporarily store
    char buffer[MAX_STR_LEN];

    printf(">");
    fgets(buffer, MAX_STR_LEN, stdin);

    //If the first character of the string is a DEV_CHAR
    //then the second char is a command
    if(buffer[0] == DEV_CHAR)
    {
        GoInDevMode(fileBuffer, &buffer[1]);
    }
    else
    {
        ReadIn(fileBuffer, buffer);
    }

    return 0;
}

//This function reads the file into the system
doc* ReadDocument(const char *filename)
{
    //First we need to open the file
    FILE *f = fopen(filename, "r");
    if(f == NULL)
        return NULL;

    //2: We need to create a new document
    doc *newDoc = malloc(sizeof(*newDoc));

    //3: We read the file into the document
    char buffer[MAX_STR_LEN];
    while(fgets(buffer, sizeof(buffer), f) != NULL){
        ReadIn(newDoc, buffer);
    }

    //4:Close the file
    fclose(f);

    //5: Return the result
    return newDoc;
}

//This function creates a new empty document and returns it.
doc* NewDocument()
{
    doc *newDoc = malloc(sizeof(*newDoc));
    char *NEW_FILE_NAME = "newdocument.txt";

    newDoc->HEAD = NULL;
    newDoc->CURRENT = NULL;
    strcpy(newDoc->name, NEW_FILE_NAME);

    return newDoc;
}


/*
//This function returns the parameter and removes it from the command
int GetParameter(char* command)
{
    for(int i = 0; command[i] != '\0'; i++)
    {
        if(command[i] == ' ')
            return atoi(&command[i]);
    }
    return 0;
}
*/
