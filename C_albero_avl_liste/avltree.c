// AVL tree implementation in C

#include <assert.h>
#include <binario.h>
#include <stdio.h>
#include <stdlib.h>
#include <tempi.h>

/* Create Node
struct Node {
  int key;
  struct Node *left;
  struct Node *right;
  int height;
};
  */

int max(int a, int b);

// Calculate height
int height(node* N)
{
    if(N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b) { return (a > b) ? a : b; }

// Create a node
node* newNode(adt* key, node* parent) { return createnode(key, parent); }

// Right rotate
node* rightRotate(node* y)
{
    node* x = y->left;
    node* T2 = x->right;

    x->right = y;
    //    assert(y != NULL);
    if(y != NULL)
        y->up = x;
    y->left = T2;
    if(T2 != NULL)
        T2->up = y;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Left rotate
node* leftRotate(node* x)
{
    node* y = x->right;
    node* T2 = y->left;

    y->left = x;
    if(x != NULL)
        x->up = y;
    x->right = T2;
    if(T2 != NULL)
        T2->up = x;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Get the balance factor
int getBalance(node* N)
{
    if(N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Insert node
node* insertNode(node* node, adt* key)
{
    // Find the correct position to insertNode the node and insertNode it
    if(node == NULL)
        return (newNode(key, NULL));
    int res = compare(key, node->elem);

    if(res < 0) {
        node->left = insertNode(node->left, key);
        if(node->left != NULL)
            node->left->up = node;
    } else if(res > 0) {
        node->right = insertNode(node->right, key);
        if(node->right != NULL)
            node->right->up = node;
    } else
        return node;

    // Update the balance factor of each node and
    // Balance the tree
    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);
    if(balance > 1 && compare(key, node->left->elem) < 0)
        return rightRotate(node);

    if(balance < -1 && compare(key, node->right->elem) > 0)
        return leftRotate(node);

    if(balance > 1 && compare(key, node->left->elem) > 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if(balance < -1 && compare(key, node->right->elem) < 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

node* minValueNode(node* n)
{
    node* current = n;

    while(current->left != NULL)
        current = current->left;

    return current;
}

// Delete a nodes
node* deleteNode(node* root, adt* key)
{
    // Find the node and delete it
    if(root == NULL)
        return root;
    int res = compare(key, root->elem);
    if(res < 0) {
        root->left = deleteNode(root->left, key);
        if(root->left != NULL)
            root->left->up = root;
    }

    else if(res > 0) {
        root->right = deleteNode(root->right, key);
        if(root->right != NULL)
            root->right->up = root;
    }

    else {
        if((root->left == NULL) || (root->right == NULL)) {
            node* temp = root->left ? root->left : root->right;

            if(temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;
            free(temp);
        } else {
            node* temp = minValueNode(root->right);

            root->elem = temp->elem;

            root->right = deleteNode(root->right, temp->elem);
            if(root->right != NULL)
                root->right->up = root;
        }
    }

    if(root == NULL)
        return root;

    // Update the balance factor of each node and
    // balance the tree
    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);
    if(balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if(balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if(balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if(balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Print the tree
void printPreOrder(node* root)
{
    if(root != NULL) {
        printf("%s ", tostr(root->elem));
        printPreOrder(root->left);
        printPreOrder(root->right);
    }
}

int testavl()
{
    node* root = NULL;

    root = insertNode(root, createadt("", 2));
    root = insertNode(root, createadt("", 1));
    root = insertNode(root, createadt("", 7));
    root = insertNode(root, createadt("", 4));
    root = insertNode(root, createadt("", 5));
    root = insertNode(root, createadt("", 3));
    root = insertNode(root, createadt("", 8));

    printPreOrder(root);

    root = deleteNode(root, createadt("", 3));

    printf("\nAfter deletion: ");
    printPreOrder(root);
    checkTree(root);
    printf("\nTree seems OK\n");
    return 0;
}

int testavlinsertrandom()
{
    char buf[24];
    adt* linea[SZ];
    srand(1000);
    for(int count = 0; count < SZ; count++) {
        int cur = rand() % 1000000;
        sprintf(buf, "%d", cur);
        linea[count] = createadt(buf, cur);
    }
    miotempo(NULL);
    node* root = NULL;
    for(adt** iniz = linea + SZ - 1; iniz > linea; iniz--) {
        root = insertNode(root, *iniz);
    }

    // prova a reinserire i nodi, ovviamente non succedera' NULLA
    // serve a vedere quanto ci va a cercarli
    for(int aa = 0; aa < 10; aa++)
        for(adt** iniz = linea + SZ - 1; iniz > linea; iniz--) {
            root = insertNode(root, *iniz);
        }
    miotempo(" crea avl random quasi bilanciato 100000");
    printf("TREESIZE %ld\n", treeSize(root));
    printf("TREEHEIGHT avl %ld\n", treeHeight(root));
    checkTree(root);
    return 0;
}