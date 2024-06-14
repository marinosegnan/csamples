#include "scan.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* tokentypestring[] = { "OPENP", "CLOSEP", "LONG", "STR", "DOUBLE", "IDENT", "COMMA", "EMPTY", "END" };

int starters[128];

void initstarters()
{
    for(int i = 'A'; i <= 'Z'; i++) {
        starters[i] = IDENT;
    }
    for(int i = 'a'; i <= 'z'; i++) {
        starters[i] = IDENT;
    }
    for(int i = '0'; i <= '9'; i++) {
        starters[i] = LONG;
    }
    starters[','] = COMMA;
    starters['"'] = STR;
    starters[' '] = EMPTY;
    starters['\0'] = END;
}

token* create_token(enum tokentype type, char* val, long length)
{
    token* ret = malloc(sizeof(token));
    if(ret == NULL) {
        fprintf(stderr, "malloc error\n");
        exit(1);
    }
    ret->tokentype = type;
    char save;
    switch(type) {
    case LONG:
        save = val[length];
        val[length] = '\0';
        ret->lval = atoll(val);
        val[length] = save;
        break;
    case DOUBLE:
        save = val[length];
        val[length] = '\0';
        ret->dval = atof(val);
        val[length] = save;
        break;
    case STR:
    case IDENT:
        ret->sval = malloc(sizeof(length + 1));
        strncpy(ret->sval, val, length);
        ret->sval[length] = '\0';
        break;
    case END:
        break;
    default:
        break;
    }
    return ret;
}

char outb[64];

char* tostring(token* t)
{

    switch(t->tokentype) {
    case LONG:
        sprintf(outb, "%ld (%s)", t->lval, tokentypestring[t->tokentype]);
        break;
    case DOUBLE:
        sprintf(outb, "%f (%s)", t->dval, tokentypestring[t->tokentype]);
        break;
    case END:
        break;
    case STR:
    case IDENT:
        sprintf(outb, "%s (%s)", t->sval, tokentypestring[t->tokentype]);
        break;
    case COMMA:
        sprintf(outb, ", (%s)", tokentypestring[t->tokentype]);
    default:
        break;
    }
    return outb;
}

scanner* create_scanner(char* s)
{
    scanner* ret = malloc(sizeof(token));
    if(ret == NULL) {
        fprintf(stderr, "malloc error\n");
        exit(1);
    }
    ret->input = s;
    ret->pos = 0;
    initstarters();
    return ret;
}
token* next(scanner* sc)
{
    char ch;
    long pos = sc->pos;
    int start = pos;
    token* ret = NULL;
    // trova partenza prossimo token
    for(;;) {
        ch = sc->input[pos];
        switch(starters[(long)ch]) {
        case EMPTY:
            pos++;
            continue;

        case COMMA:
            pos++;
            ret = create_token(COMMA, NULL, 0);
            break;

        case IDENT: // inizia ident
            start = pos;
            while((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')) { // intero o float
                ch = sc->input[++pos];
            }
            ret = create_token(IDENT, sc->input + start, pos - start);
            break;

        case LONG: // inizia numero
            int punto = 0;
            start = pos;
            while((ch >= '0' && ch <= '9') || ch == '.') { // intero o float
                ch = sc->input[++pos];
                if(ch == '.') {
                    punto++;
                }
            }
            if(punto) {
                ret = create_token(DOUBLE, sc->input + start, pos - start);
            } else {
                ret = create_token(LONG, sc->input + start, pos - start);
            }
            break;

        case STR: // inizia stringa
            ch = sc->input[++pos];
            char tmp[64];
            int tpos = 0;
            while(ch != '"') {
                if(ch == '\\') { // salta uno
                    ch = sc->input[++pos];
                    if(ch != '\0') { /// etc etc
                        tmp[tpos++] = ch;
                    } else {
                        // errore
                    }
                } else {
                    tmp[tpos++] = ch;
                }
                ch = sc->input[++pos];
            }
            ret = create_token(STR, tmp, tpos);
            pos++;
            break;
        case END:
            return NULL;
        default:
            fprintf(stderr, "unexpected char at position %ld: '%c'\n", pos, ch);
            exit(1);
        }
        sc->pos = pos;
        return ret;
    }
}

token* create_token1(enum tokentype type, char* val)
{
    token* ret = malloc(sizeof(token));
    if(ret == NULL) {
        fprintf(stderr, "malloc error\n");
        exit(1);
    }
    ret->tokentype = type;
    switch(type) {
    case LONG:
        ret->lval = atoll(val);
        break;
    case DOUBLE:
        ret->dval = atof(val);
        break;
    case STR:
    case IDENT:
        ret->sval = malloc(sizeof(strlen(val) + 1));
        strcpy(ret->sval, val);
        break;
    case END:
        break;
    default:
        break;
    }
    return ret;
}

token* next1(scanner* sc)
{
    char ch;
    long pos = sc->pos;
    token* ret = NULL;
    // trova partenza prossimo token
    while((ch = sc->input[pos]) != '\0') {
        if(ch == ' ') {
            pos++;
            continue;
        }
        if(ch == ',') {
            pos++;
            ret = create_token1(COMMA, NULL);
            break;
        }
        if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) { // inizia ident
            int start = pos;
            while((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')) { // intero o float
                ch = sc->input[++pos];
            }
            char buf[64];
            strncpy(buf, sc->input + start, pos - start);
            buf[pos - start + 1] = '\0';
            ret = create_token1(IDENT, buf);
            break;
        }
        if(ch >= '0' && ch <= '9') { // inizia numero
            int start = pos;
            int punto = 0;
            while((ch >= '0' && ch <= '9') || ch == '.') { // intero o float
                ch = sc->input[++pos];
                if(ch == '.') {
                    punto++;
                }
            }
            char buf[64];
            strncpy(buf, sc->input + start, pos - start);
            buf[pos - start + 1] = '\0';
            if(punto) {
                ret = create_token1(DOUBLE, buf);
            } else {
                ret = create_token1(LONG, buf);
            }
            break;
        }
        if(ch == '"') { // inizia stringa
            ch = sc->input[++pos];
            char tmp[64];
            int tpos = 0;
            while(ch != '"') {
                if(ch == '\\') { // salta uno
                    ch = sc->input[++pos];
                    if(ch != '\0') { /// etc etc
                        tmp[tpos++] = ch;
                    } else {
                        // errore
                    }
                } else {
                    tmp[tpos++] = ch;
                }
                ch = sc->input[++pos];
            }
            tmp[tpos + 1] = '\0';
            ret = create_token1(STR, tmp);
            pos++;
            break;
        }
        fprintf(stderr, "unexpected char at position %ld: '%c'\n", pos, ch);
        exit(1);
    }
    sc->pos = pos;
    return ret;
}