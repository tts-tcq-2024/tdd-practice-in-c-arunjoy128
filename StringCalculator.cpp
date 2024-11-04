#include <stdlib.h>
#include <string.h>
#include <cctype>
#include <iostream>
#include "StringCalculator.h"

/* Function Prototypes */
void replaceNewLineDelimiterWithCommaDelimiter(char *tempInputString);
int addNumbersFromInputString(char *inputString);
void removeNonDigitCharactersFromString(char *inputString);
void deleteCharFromStringByIndex(char *inputString, int charIndex);
void removeNumbersGreaterThanThousand(char *numString);
void checkAndReplaceCustomDelimiterWithCommaDelimiter(char *inputString);
void replaceCustomDelimiterWithCommaDelimiter(char *inputString, char* customDelimiter);
void checkForNegativeNumbersInInputString(char *inputString);
void throwExceptionForNegativeNumber(char *listOfNegativeNumbers);
int isCustomDelimiterFormatStarterPresent(char *inputString);
int isCustomDelimiterFormatEnderPresent(char *inputString);

/* Function Description: calculate the sum of numbers in a given string */
/* Parameters:
      inputString - the string of numbers whose sum is to be calculated 
*/
int calculateStringSum(const char *inputString) {
  int stringSum = 0;

  if(strlen(inputString) != 0) {
    /* temporary input string */
    char tempInputString[strlen(inputString)];
    strcpy(tempInputString, inputString);

    /* process and simplify the input string (copy) */    
    checkAndReplaceCustomDelimiterWithCommaDelimiter(tempInputString);
    replaceNewLineDelimiterWithCommaDelimiter(tempInputString);
    checkForNegativeNumbersInInputString(tempInputString);

    /* get the sum from the processed input string */
    stringSum = addNumbersFromInputString(tempInputString);
  }

  return stringSum;
}

/* Function Description: sets the exception message and throws the exception once a negative number has been detected*/
/* Parameters:
      listOfNegativeNumbers - string in which the negative numbers have been listed so that they can be included in the exception message
*/
void throwExceptionForNegativeNumber(char *listOfNegativeNumbers) {
  if(strlen(listOfNegativeNumbers) != 0) {
    char errorMessage[strlen(listOfNegativeNumbers) + 35];
    strcpy(errorMessage,"negative numbers not allowed: ");
    strcat(errorMessage, listOfNegativeNumbers);
    errorMessage[strlen(errorMessage)-1] = '\0';
    throw std::runtime_error(errorMessage);
  }
}

/* Function Description: checks for the presence of negative numbers in the given input string */
/* Parameters:
      inputString - string inside which presence of negative numbers is to be checked
*/
void checkForNegativeNumbersInInputString(char *inputString) {
  /* create a copy of input string to be used with strtok() */
  char tempInputString[strlen(inputString)];
  strcpy(tempInputString,inputString);
  
  /* create a string to store the negative numbers */
  char listOfNegativeNumbers[strlen(inputString)];
  strcpy(listOfNegativeNumbers,"");

  /* get the sub-string before the delimiter and loop through all such sub-strings */
  char* token = strtok(tempInputString,",");
  while (token != NULL) {
    if(atoi(token) < 0) {
      strcat(listOfNegativeNumbers,token);
      strcat(listOfNegativeNumbers,",");
    }
    token = strtok(NULL,",");
  }
  throwExceptionForNegativeNumber(listOfNegativeNumbers);
}

/* Function Description: add up all the numbers in the given input string and return the sum */
/* Parameters:
      inputString - the string of numbers whose sum is to be calculated 
*/
int addNumbersFromInputString(char *inputString) {
  int stringSum = 0;
  
  /* get the sub-string before the delimiter and loop through all such sub-strings */
  char* token = strtok(inputString,",");  
  while (token != NULL) {
    removeNonDigitCharactersFromString(token);
    removeNumbersGreaterThanThousand(token);
    stringSum += atoi(token);
    token = strtok(NULL,",");
  }

  return stringSum;
}

/* Function Description: delete the character at the given index from the given string */
/* Parameters:
      inputString - string from which a character is to be deleted
      charIndex - index of the character which is to be deleted
*/
void deleteCharFromStringByIndex(char *inputString, int charIndex) {        
    int len = strlen(inputString); /* len - length of the input string */
    int i;
    for(i = charIndex; i < len-1; ++i) {
        inputString[i] = inputString[i+1];
    }
    inputString[i] = '\0';
}

/* Function Description: if the value of the number string is greater than 1000, it is "removed" by replacing it with 0 */
/* Parameters:
      numString - number string whose value is to be checked
*/
void removeNumbersGreaterThanThousand(char *numString) {
  if(atoi(numString) > 1000) {
    /* if the number is greater than 1000, it is replaced with zero so that 0 is added to the string sum */
    strcpy(numString,"0");
  }
}

/* Function Description: removes all non-digit characters from a given string */
/* Parameters:
      inputString - string from which all non-digit characters are to be removed
*/
void removeNonDigitCharactersFromString(char *inputString) {
  int i = 0;
  while(inputString[i] != '\0') { /* loop through every character in the token to check if it is a digit or not */
    if(!isdigit(inputString[i])) {
      deleteCharFromStringByIndex(inputString,i);
    } else {
        ++i;
    }
  }
}

/* Function Description: checks if the given input string starts with the format starter for a custom delimiter i.e., "//" */
/* Parameters:
      inputString - string inside whcih custom delimiter starter needs to be checked
*/
int isCustomDelimiterFormatStarterPresent(char *inputString) {
    return (((inputString[0] - '/') + (inputString[1] - '/')) == 0);
}

/* Function Description: checks if the given input string contains the format ender for a custom delimiter i.e., '\n' after the format starter */
/* Parameters:
      inputString - string inside whcih custom delimiter starter needs to be checked
*/
int isCustomDelimiterFormatEnderPresent(char *inputString) {
    return (strstr(inputString+2,"\n") != NULL);
}

/* Function Description: check if a custom delimiter has been specified in the input string and replace it with comma characters */
/* Parameters:
      inputString - string inside whcih custom delimiter characters need to be checked and replaced 
*/
void checkAndReplaceCustomDelimiterWithCommaDelimiter(char *inputString) {
  /* if a custom delimiter is present, both it's format starter (//) and ender (/n) must be present at the beginning of the string */
  if((isCustomDelimiterFormatStarterPresent(inputString) + isCustomDelimiterFormatEnderPresent(inputString)) == 2) {
    char tempInputString[strlen(inputString)];
    strcpy(tempInputString,inputString);
    
    /* extract the custom delimiter */
    char* customDelimiter = strtok(tempInputString+2,"\n");
    /* remove the delimiter and consider only the contents of the string */    
    char* contentOfInputString = inputString + 2 + strlen(customDelimiter) + 1;
    
    replaceCustomDelimiterWithCommaDelimiter(contentOfInputString, customDelimiter);    
    strcpy(inputString,contentOfInputString);
  }
}

/* Function Description: replaces custom delimiter characters with comma characters so that there is only one delimiter to handle */
/* Parameters:
      inputString - string inside whcih custom delimiter characters need to be checked and replaced
      customDelimiter - the character (or string) that needs to be replaced
*/
void replaceCustomDelimiterWithCommaDelimiter(char *inputString, char* customDelimiter) {
  int lenInputString = strlen(inputString);
  char tempString[lenInputString];
  char tempString2[lenInputString];
  int lenCustomDelimiter = strlen(customDelimiter);
  
  /* set initial values for the temporary strings */
  strcpy(tempString2,"");
  strcpy(tempString,inputString);

  /* get the sub-string with and after the custom delimiter and loop through all such sub-strings */    
  char* token = strstr(tempString,customDelimiter);    
  while(token != NULL) {
    /* copy the characters that occur before the custom delimiter */
    strncpy(tempString2,tempString,(token-tempString));    
    tempString2[(token-tempString)] = '\0';

    /* add the comma delimiter */
    strcat(tempString2,",");
    
    /* add the rest of the string after the custom delimiter */
    strcat(tempString2, (token+lenCustomDelimiter));
    
    /* prepare for next iteration of the while loop */
    strcpy(tempString,tempString2);    
    token = strstr(tempString,customDelimiter);    
    strcpy(tempString2,"");
  }

  /* finally copy the modified string into the input string */
  strcpy(inputString,tempString);
}

/* Function Description: replaces new line characters with comma characters so that there is only one delimiter to handle */
/* Parameters:
      inputString - string inside whcih new line characters need to be checked and replaced
*/
void replaceNewLineDelimiterWithCommaDelimiter(char *inputString) {
  for(int i = 0; inputString[i] != '\0'; ++i) {
    if(inputString[i] == '\n') {
      inputString[i] = ',';
    }
  }
}
