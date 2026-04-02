#include "konwersje.h"

#define NULL '\0'

void UIntToHexStr(unsigned int uiValue, char pcStr[]) {
    
    unsigned char ucTetradCounter;
    unsigned char ucTetradValue;

    pcStr[0] = '0';
    pcStr[1] = 'x';

    for(ucTetradCounter = 0; ucTetradCounter < 4; ucTetradCounter++) {
        ucTetradValue = (uiValue >> (4 * ucTetradCounter)) & 0x000F; 

        if(10 > ucTetradValue) {
            pcStr[5 - ucTetradCounter] = ucTetradValue + '0';
        } else {
            pcStr[5 - ucTetradCounter] = (ucTetradValue - 10) + 'A';
        }
    }

    pcStr[6] = NULL;
}

// enum Result { OK, ERROR };
enum Result eHexStringToUInt(char pcStr[], unsigned int *puiValue) {

    unsigned char ucCharCounter;
    unsigned char ucCharValue;

    *puiValue = 0;

    if(('0' != pcStr[0]) || ('x' != pcStr[1]) || (NULL == pcStr[2])) {
        return ERROR;
    }

    for(ucCharCounter = 2; NULL != pcStr[ucCharCounter]; ucCharCounter++) {
        ucCharValue = pcStr[ucCharCounter];
        
        if(6 == ucCharCounter) {
            return ERROR;
        }

        *puiValue = *puiValue << 4;

        if(('0' <= ucCharValue) && ('9' >= ucCharValue)) {
            *puiValue = *puiValue + (ucCharValue - '0');
        } else if(('A' <= ucCharValue) && ('F' >= ucCharValue)) {
            *puiValue = *puiValue + ((ucCharValue + 10) - 'A');
        } else {
            return ERROR;
        }
    }

    return OK;
}

void AppendUIntToString (unsigned int uiValue, char pcDestinationStr[]) {
    unsigned char ucCharCounter;

    for(ucCharCounter = 0; NULL != pcDestinationStr[ucCharCounter]; ucCharCounter++) {}
    UIntToHexStr(uiValue, pcDestinationStr + ucCharCounter);
}

/*

char cCorrectHex[] = "0xFFEE";
char cIncorrectHex[] = "0xFHE";
enum Result eResult;
unsigned int value;

int main() {

    eResult = ERROR;

    eResult = eHexStringToUInt(cCorrectHex, &value);
    eResult = eHexStringToUInt(cIncorrectHex, &value);

    return 0;
}
    
*/
