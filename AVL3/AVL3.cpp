// AVL tree implementation in C

#include <stdio.h>
#include <stdlib.h>

// Create Node
struct Node {
    int d;
    int bal;
    Node* left;
    Node* right;
};


int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(Node* N) {
    if (!N) return 0;

    return  max( height(N->left), height(N->right) ) + 1 ;
}

int fixBalance(Node* N) {
    if (!N) return 0;
    return  height(N->left) - height(N->right);
}

Node* newNode(int d) {
    Node* node = new Node;
    node->d = d;
    node->left = node->right = NULL;
    node->bal = 0;
    return (node);
}

Node* rightRotate(Node*& y) {
    Node* x = y->left;
    Node* T1 = x->right;

    x->right = y;
    y->left = T1;

    y->bal = fixBalance(y);
    x->bal = fixBalance(x);

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T1 = y->left;

    y->left = x;
    x->right = T1;

    x->bal = fixBalance(x);
    y->bal = fixBalance(y);

    return y;
}

Node* insertNode(Node* node, int d) {
    if (!node) return newNode(d);

    if (d < node->d)
        node->left = insertNode(node->left, d);
    else if (d > node->d)
        node->right = insertNode(node->right, d);
    else
        return node;

    node->bal = fixBalance(node);

    if (node->bal > 1 && node->left->bal > 0) 
        return rightRotate(node);

    if (node->bal < -1 && node->right->bal < 0)
        return leftRotate(node);

    if (node->bal > 1 && node->left->bal < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (node->bal < -1 && node->right->bal > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

Node* maxValueNode(Node* node) {
    Node* current = node;

    while (current->right)
        current = current->right;

    return current;
}

Node* deleteNode(Node* root, int d) {
    if (root == NULL)
        return root;

    if (d < root->d)
        root->left = deleteNode(root->left, d);

    else if (d > root->d)
        root->right = deleteNode(root->right, d);

    else {
        if (!root->left || !root->right) {
            
            Node* temp = root->left ? root->left : root->right;

            if (!temp) {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
            
            delete temp;
        }
        else {
            Node* temp = maxValueNode(root->left);

            root->d = temp->d;

            root->left = deleteNode(root->left, temp->d);
        }
    }

    if (root == NULL)
        return root;

    root->bal = fixBalance(root);

    if (root->bal > 1 && root->left->bal >= 0)
        return rightRotate(root);

    if (root->bal > 1 && root->left->bal < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (root->bal < -1 && root->right->bal <= 0)
        return leftRotate(root);

    if (root->bal < -1 && root->right->bal > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Print the tree
void printPreOrder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->d);
        printPreOrder(root->left);
        printPreOrder(root->right);
    }
}

int main() {
    Node* root = NULL;

    root = insertNode(root, 2);
    root = insertNode(root, 1);
    root = insertNode(root, 7);
    root = insertNode(root, 4);
    root = insertNode(root, 5);
    root = insertNode(root, 3);
    root = insertNode(root, 8);


    root = deleteNode(root, 3);

    printPreOrder(root);

    return 0;
}