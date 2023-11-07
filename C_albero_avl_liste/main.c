#include <adt.h>
#include <avltree.h>
#include <binario.h>
#include <limits.h>
#include <listadt.h>
#include <stdio.h>
#include <stringa.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    char cwd[PATH_MAX];
    if(getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working dir: %s\n", cwd);
    } else {
        perror("getcwd() error");
        return 1;
    }
    printf("hello listadt\n");
    //  testlistadt();

    //  teststringa();
    //    testbinariolist();
    //  testbinario();

    testlistatempiinsertremove();
    testbinarioinsertremove();
    //   testlistatempi();
    testavl();
    testbinarioinsertrandom();
    testavlinsertrandom();
    return 0;
}
