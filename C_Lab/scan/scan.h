#ifndef _SCAN_H
#define _SCAN_H

enum tokentype { OPENP, CLOSEP, LONG, STR, DOUBLE, IDENT, COMMA, EMPTY, END };

typedef struct {
    enum tokentype tokentype;
    union {
        char* sval;
        double dval;
        long lval;
        char cval;
        void* pval;
    };
} token;

typedef struct {
    char* input;
    long pos;
} scanner;

token* create_token(enum tokentype type, char* val, long length);
token* create_token1(enum tokentype type, char* val);
char* tostring(token* t);

scanner* create_scanner(char* s);
token* next(scanner* sc);
token* next1(scanner* sc);
#endif
