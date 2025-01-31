#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#define SEPARATOR "#<ab@17943918#@>#"
#include "contactOpq.h"

#include <mcheck.h>
#include <signal.h>
#include <setjmp.h>

jmp_buf env;
int passed;

{{ STUDENT_ANSWER }}

/*
struct contact {
   char* name;   
   char* surname;
   char* mobile;
   char* url;
};
*/

void on_sigabrt (int signum)
{
  signal(signum, SIG_DFL);
  // printf("Ciao, ho catturato SIGABRT\n");
  passed = 1;
  longjmp(env, 1);
}
void try_and_catch_abort (void (*func)(void))
{
  if (setjmp (env) == 0) {
    signal(SIGABRT, &on_sigabrt);
    (*func)();
    signal (SIGABRT, SIG_DFL);
  }
  else {
    // printf("called after longjmp\n");
  }
}   

ContactPtr mymk(char* name, char* surname, char* mobile, char* url) {
      ContactPtr cnt;
      if(name == NULL || surname == NULL) return NULL; 
      cnt = malloc(sizeof(Contact));
      cnt->name = name;
      cnt->surname = surname;
      cnt->mobile = mobile;
      cnt->url = url;
      return cnt;
}

void checkmk(char* name, char* surname, char* mobile, char* url) {
    ContactPtr cnt;
    passed = 1;
    cnt = mkContact(name,surname,mobile,url);
    //if(!cnt) { passed = 0; return; }
    if ((name == NULL) || (surname == NULL)) {
        if(cnt != NULL) passed = 0; 
    } else {
        if(name) passed = passed && cnt->name && strcmp(name,cnt->name)==0; else passed = passed && !cnt->name;
        if(surname) passed = passed && cnt->surname && strcmp(surname,cnt->surname)==0; else passed = passed && !cnt->surname;
        if(mobile) passed = passed && cnt->mobile && strcmp(mobile,cnt->mobile)==0; else passed = passed && !cnt->mobile;
        if(url) passed = passed && cnt->url && strcmp(url,cnt->url)==0; else passed = passed && !cnt->url;
    }
    return;
}

void no_op(enum mcheck_status status) { 
   if(status == 2) passed = 1;
   //  printf("called noop with status %d\n",status); 
}    

void checkds1() {
    ContactPtr cnt, save;
    passed = 0;
    save = cnt = malloc(sizeof(Contact));
    dsContact(&cnt);
    free(save);    
    return;
}

void checkds2() {
    ContactPtr cnt;
    cnt = mymk("name","surname","mobile","url");
    dsContact(&cnt);
    passed = (cnt==NULL);    
    return;
}

void checkmobile() {
    ContactPtr cnt;
    cnt = mymk("name","surname","mobile","url");
    updateMobile(cnt,"newmobile");
    passed = (strcmp("newmobile",cnt->mobile)==0);
    updateMobile(cnt,NULL);
    passed = passed && !cnt->mobile;    
    return;
}

void checkurl() {
    ContactPtr cnt;
    cnt = mymk("name","surname","mobile","url");
    updateUrl(cnt,"newurl");
    passed = (strcmp("newurl",cnt->url)==0);
    updateUrl(cnt,NULL);
    passed = passed && !cnt->url;    
    return;
}

void checkgets() {
    ContactPtr cnt;
    char *test;
    cnt = mymk("name","surname","mobile",NULL);
    test = getName(cnt);
    passed = test? (strcmp("name",test)==0) : 0;
    test = getSurname(cnt);
    passed = passed && test? (strcmp("surname",test)==0) : 0;
    test = getMobile(cnt);
    passed = passed && test? (strcmp("mobile",test)==0) : 0;
    test = getUrl(cnt);
    passed = passed && !test;   
    return;
}

void checkeq() {
    ContactPtr cnt1,cnt2;
    cnt1 = mymk("gian paolo","rossi",NULL,NULL);
    cnt2 = mymk("gian paolo","rossi",NULL,NULL);
    passed = equalsContact(cnt1, cnt2) == 1;
    free(cnt2);
    cnt2 = mymk("","rossi",NULL,NULL);
    passed = passed && equalsContact(cnt1, cnt2) == 0;
    free(cnt2);
    cnt2 = mymk("","",NULL,NULL);
    passed = passed && equalsContact(cnt2, cnt2) == 1; 
    return;
}

void checkcmp() {
    ContactPtr cnt1,cnt2;
    cnt1 = mymk("vladimir","",NULL,NULL);
    cnt2 = mymk("vladimiro","",NULL,NULL);
    passed = cmpContact(cnt1, cnt2) == -1; 
    passed = passed && cmpContact(cnt1, cnt1) == 0; 
    passed = passed && cmpContact(cnt2, cnt1) == 1;
    free(cnt2);
    cnt2 = mymk("","Rossi",NULL,NULL);
    passed = passed && cmpContact(cnt2, cnt2) == 0; 
    return;
}

int main() {
    
// printf("calling first mcheck\n");
mcheck(&no_op);    
    return 0;
}
