#include <espr.h>
#include <stddef.h>
#include <stdio.h>

int eval(nodo* n)
{
    if(n->left == NULL && n->right == NULL) {
        return *(int*)n->mytype;
    }
    return eval(n->left) + eval(n->right);
}

int temp[10] = {}; // conserva i valori temporanei
int evallist(coda* c)
{

    int* q = temp;
    pila* p = create_pila();
    while(c->size > 0) {
        char* e = remove_el(c);
        if(*e >= '0' && *e <= '9') {
            *q = *e - '0';
        } else {
            int* e1 = pop(p);
            int* e2 = pop(p);
            switch(*e) {
            case '+':
                *q = *e1 + *e2;
                break;
            case '*':
                *q = *e1 * *e2;
                break;
            case '-':
                *q = *e1 - *e2;
                break;
            case '/':
                *q = *e1 / (*e2);
                break;
            default:
                break;
            }
        }
        push(p, q);
        q++;
    }
    int* val = pop(p);
    return *val;
}
void addele(coda* c, nodo* n)
{
    if(n->left != NULL) {
        addele(c, n->left);
        append_el(c, n->left->mytype);
    }
    if(n->right != NULL) {
        addele(c, n->right);
        append_el(c, n->right->mytype);
    }
}

coda* convert(nodo* n)
{
    coda* c = create_coda();
    addele(c, n);
    append_el(c, n->mytype);
    return c;
}
