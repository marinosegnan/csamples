#include <has.h>
#include <stdio.h>
#include <stringa.h>
#include <tempi.h>

#define MAX_LINE_LENGTH 1000

void trim(char* s)
{
    while(*s != '\0' && *s != '\r' && *s != '\n' && *s != ' ') {
        s++;
    }
    *s = '\0';
}
int teststringa()
{
    FILE* textfile;
    char line[MAX_LINE_LENGTH];
    char* diz[65000];

    textfile = fopen("./words.italian.txt", "r");
    if(textfile == NULL)
        return 1;

    miotempo("");
    int i = 0;
    while(fgets(line, MAX_LINE_LENGTH, textfile)) {
        trim(line);
        diz[i++] = strdup(line);
    }
    diz[i] = "";
    fclose(textfile);
    miotempo("files");
    miotempo(NULL);
    for(char** p = diz; **p != '\0'; p++) {
        addh(*p);
    }
    miotempo("tabella");
    stats();
    //    for (char **p = diz; **p != '\0'; *p++) {
    //    sorta(*p);
    //  }
    //    miotempo("search");
    printf("remove %d\n", remh("abte"));
    return 0;
}
