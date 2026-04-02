#ifndef DEKODOWANIE
#define DEKODOWANIE

#include "konwersje.h"

#define NULL '\0'
#define MAX_TOKEN_NR 3
#define MAX_KEYWORD_STRING_LTH 10
#define MAX_KEYWORD_NR 3

enum TokenType { KEYWORD, NUMBER, STRING };
enum KeywordCode { LD, ST, RST };

union TokenValue {
    enum KeywordCode eKeyword; 
    unsigned int uiNumber; 
    char *pcString; 
};

struct Token {
    enum TokenType eType; 
    union TokenValue uValue; 
};

struct Keyword {
    enum KeywordCode eCode;
    char cString[MAX_KEYWORD_STRING_LTH + 1];
};

extern struct Keyword asKeywordList[MAX_KEYWORD_NR];
extern struct Token asToken[MAX_TOKEN_NR];
extern unsigned char ucTokenNr;

unsigned char ucFindTokensInString (char *pcString);

enum Result eSringToKeyword (char pcStr[], enum KeywordCode *peKeywordCode);

void DecodeTokens(void);

void DecodeMsg(char *pcString);

#endif
