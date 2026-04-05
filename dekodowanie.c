#include "dekodowanie.h"
#include "lancuchy.h"
#include "konwersje.h"

enum State { TOKEN, DELIMITER };

struct Keyword asKeywordList[MAX_KEYWORD_NR] = {
{RST, "reset"},
{LD, "load" },
{ST, "store"}
};

struct Token asToken[MAX_TOKEN_NR];
unsigned char ucTokenNr;

unsigned char ucFindTokensInString (char *pcString) {

    enum State eState = DELIMITER; 
    unsigned char ucCharValue;
    unsigned char ucCharCounter;

    ucTokenNr = 0;

    for(ucCharCounter = 0;; ucCharCounter++) {
        ucCharValue = pcString[ucCharCounter];

        switch (eState) {
            case DELIMITER:
                if(NULL == ucCharValue) {
                    return ucTokenNr;
                } else if(' ' == ucCharValue) {} 
                else if(MAX_TOKEN_NR == ucTokenNr) {
                    return ucTokenNr;
                } else {
                    eState = TOKEN;
                    asToken[ucTokenNr].uValue.pcString = &pcString[ucCharCounter];
                    ucTokenNr++;
                }

                break;
            case TOKEN:
                if(NULL == ucCharValue) {
                    return ucTokenNr;
                } else if(' ' == ucCharValue) {
                    eState = DELIMITER;
                } else {};

                break;
        }
    }
}

// enum Result { OK, ERROR };
enum Result eStringToKeyword (char pcStr[], enum KeywordCode *peKeywordCode) {

    unsigned char ucKeywordCounter;

    for(ucKeywordCounter = 0; ucKeywordCounter < MAX_KEYWORD_NR; ucKeywordCounter++) {
        if(EQUAL == eCompareString(pcStr, asKeywordList[ucKeywordCounter].cString)) {
            *peKeywordCode = asKeywordList[ucKeywordCounter].eCode;
            return OK;
        }
    }

    return ERROR;
}

void DecodeTokens(void) {

    unsigned char ucTokenCounter;
    struct Token *psToken;
    enum KeywordCode eKeyword;
    unsigned int uiNumber;

    for(ucTokenCounter = 0; ucTokenCounter < ucTokenNr; ucTokenCounter++) {
        psToken = &asToken[ucTokenCounter];

        if(OK == eStringToKeyword(psToken->uValue.pcString, &eKeyword)) {
            psToken->eType = KEYWORD;
            psToken->uValue.eKeyword = eKeyword;
            
        } else if (OK == eHexStringToUInt(psToken->uValue.pcString, &uiNumber)) {
            psToken->eType = NUMBER;
            psToken->uValue.uiNumber = uiNumber; 
            
        } else {
            psToken->eType = STRING;
        }
    }
}

void DecodeMsg(char *pcString) {

    ucTokenNr = ucFindTokensInString(pcString);
    ReplaceCharactersInString(pcString, ' ', NULL);
    DecodeTokens();
}
