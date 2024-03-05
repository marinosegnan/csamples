typedef struct {
    char* content;
    int capacity;
    int last;
} dynstring, *dynstringptr;

dynstringptr createstring(int capacity);

void append(dynstringptr s, char* s2);

char* tocharstar(dynstringptr p);

void cancelladynstr(dynstringptr p);

void reset(dynstringptr p);

int testdynstring();
