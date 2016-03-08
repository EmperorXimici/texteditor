
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "devmode.h"

//This function processes the dev Commands
void GoInDevMode(doc *fileBuffer, char *command)
{
  /*
  TODO: - error checking if ParseCommand fails
        - maybe merge RemoveEnter() and CleanCommand?
  */
    RemoveEnter(command); //remove enter
    CleanCommand(command); //remove spaces in front of command and at end of command

    int numberOfCommands = CountCharacter(command, ' ') + 1; //because command is clean, spaces + 1 = #commands
    char **commandlist = ParseCommand(command);

    if(strcmp(commandlist[0], "save") == SAME_STRING)
    {
        SaveDocument(fileBuffer);
    }
    else if(strcmp(commandlist[0], "print") == SAME_STRING)
    {
        PrintDoc(fileBuffer);
    }
    else if(strcmp(commandlist[0], "movey") == SAME_STRING)
    {
        if (isNum(commandlist[1]))
          MoveCursorY(fileBuffer, atoi(commandlist[1]));
        else
          printf("Invallid syntax");
    }
    else if(strcmp(commandlist[0], "exit") == SAME_STRING)
    {
        ExitProgram();
    }
    else
    {
        printf("Command not found.\n");
    }

    //free heap commandlist
    for (int i = 0; i < numberOfCommands; i++)
      free(commandlist[i]);

    free(commandlist);
}

//This function creates a list of words mentioned in the command. list = [COMMAND, PARAM1, PARAM2, ...]
//Assumed the command is cleaned from spaces and enters with the respective functions
char **ParseCommand(char* command)
{
  //Copy the command in a fixed array, prevent segmentation fault on strtok()
  char tempCommand[MAX_STR_LEN];
  strcpy(tempCommand, command);

  //Initialise variables
  char *tempArgument;
  int commandCounter = 0;

  //Allocate the list on heap so we can return the pointer later in this function
  char** commandlist = malloc((CountCharacter(command, ' ')+1) * sizeof(char*)); //The list will have #spaces+1 elements in it in an ideal command input

  if (commandlist == NULL)
    return NULL;

  //Tokenize the string
  tempArgument = strtok(command, " ");
  while( tempArgument != NULL )
  {
    commandlist[commandCounter] = malloc(strlen(tempArgument)+1);
    strcpy(commandlist[commandCounter], tempArgument);

    tempArgument = strtok(NULL, " ");
    commandCounter += 1;
  }

  return commandlist;
}

//This function will save a document based on the name in the doc struct
int SaveDocument(const doc* fileBuffer)
{
    //Ope the file to write to
    FILE *saveFile = fopen(fileBuffer->name, "w");
    rewind(saveFile);

    //Write the data into the file
    node* listIterator = fileBuffer->HEAD;
    for(int i = 0; listIterator != NULL; i++)
    {
        fputs(listIterator->content, saveFile);
        listIterator->isEdited = FALSE;
        listIterator = listIterator->next;
    }

    fclose(saveFile);

    return 0;
}

//This function exits the program
int ExitProgram()
{
    //TODO: Free document
    exit(0);

    return 0;
}

//This function prints out the text in our document
void PrintDoc(const doc *fileBuffer)
{
    //Print name of file
    printf("%s\n", fileBuffer->name);

    //Print out the document itself
    node* listIterator = fileBuffer->HEAD;
    while(listIterator != NULL)
    {
        printf("%s", listIterator->content);
        listIterator = listIterator->next;
    }
}

//Move the CURRENT pointer
int MoveCursorY(doc *fileBuffer, int y)
{
    node* listIterator = fileBuffer->HEAD;
    for(int i = 0; listIterator != NULL; i++)
    {
        if(i == y)
        {
            fileBuffer->CURRENT = listIterator;
            return 0;
        }
        listIterator = listIterator->next;
    }
    return 1;
}

//This function counts the given symbol (character) in a given string
int CountCharacter(const char* string, const char symbol)
{
  int CharCounter = 0;
  for (unsigned int i = 0; i < strlen(string); i++)
  {
    if (string[i] == symbol)
    {
      CharCounter += 1;
    }
  }
  return CharCounter;
}

//Removes unnessesary spaces at the beginning and end of a command
void CleanCommand(char* command)
{
  char tempCommand[MAX_STR_LEN];

  int beginCounter = 0;
  int endCounter = 0;


  for (unsigned int i = 0; i < strlen(command); i++)
  {
    if (command[i] != ' ')
    {
      break;
    }
    beginCounter++;
  }
  for (unsigned int i = 0; i < strlen(command); i++)
  {
    if (command[strlen(command) - i - 1] != ' ')
    {
      break;
    }
    endCounter++;
  }

  memcpy(tempCommand, command + beginCounter, strlen(command) - beginCounter - endCounter);
  tempCommand[strlen(command) -endCounter -beginCounter] = '\0';

  strcpy(command, tempCommand);
}

//Checks if string is a number
int isNum(char* string)
{
  for (unsigned int i = 0; i < strlen(string); i++)
  {
    if ((string[i] < 48) || string[i] > 57)
    {
      return FALSE;
    }
  }

  return TRUE;
}

//This function removes end-line enters
void RemoveEnter(char*string)
{
    int len = strlen(string);
    string[len-1] = '\0';
}
