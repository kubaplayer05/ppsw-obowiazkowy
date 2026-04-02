#include "lancuchy.h"

#define NULL '\0'

void CopyString(char pcSource[], char pcDestination[]) {

    unsigned char ucSourceIndex;

    for(ucSourceIndex = 0; NULL != pcSource[ucSourceIndex]; ucSourceIndex++) {
        pcDestination[ucSourceIndex] = pcSource[ucSourceIndex];
    }

    pcDestination[ucSourceIndex] = NULL;
}

// enum CompResult { DIFFERENT , EQUAL };
enum CompResult eCompareString(char pcStr1[], char pcStr2[]) {

    unsigned char ucStringIndex;

    for(ucStringIndex = 0; NULL != pcStr1[ucStringIndex] || NULL != pcStr2[ucStringIndex]; ucStringIndex++) {
        if(pcStr1[ucStringIndex] != pcStr2[ucStringIndex]) {
            return DIFFERENT;
        }
    }

    return EQUAL;
}

void AppendString(char pcSourceStr[],char pcDestinationStr[]) {

    unsigned char ucStringIndex;

    for(ucStringIndex = 0; NULL != pcDestinationStr[ucStringIndex]; ucStringIndex++) {}
    CopyString(pcSourceStr, &pcDestinationStr[ucStringIndex]);
}

void ReplaceCharactersInString(char pcString[], char cOldChar, char cNewChar) {

    unsigned char ucStringIndex;

    for(ucStringIndex = 0; NULL != pcString[ucStringIndex]; ucStringIndex++) {
        if(cOldChar == pcString[ucStringIndex]) {
            pcString[ucStringIndex] = cNewChar;
        }
    }
}
