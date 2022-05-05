#include <iostream>

using namespace std;

struct Node {
    int d;
    int bal;
    Node* left;
    Node* right;

    Node(int d) { this->d = d; this->right = this->left = NULL; this->bal = 0; }
};

void fileInput(Node*& tr, const char* filename);

Node* rightRotate(Node* a);
Node* leftRotate(Node* a);
int fixBalance(Node* N);

Node* insertNode(Node* node, int d);
Node* insertBalance(Node* node);

Node* deleteMaxValueNode(Node* p, Node* t);
Node* deleteNode(Node* root, int d);
Node* balanceDelete(Node* root);

void printPreOrder(Node* root);

int main() {
    Node* root = NULL;

    const char* filename = "text.txt";
    fileInput(root, filename);

    printPreOrder(root);

    return 0;
}

void fileInput(Node*& p, const char* filename) {
    FILE* f;
    
    if (!(f = fopen(filename, "r"))) {
        cout << "File wasn't opened";
        return;
    }

    int a;

    while (fscanf(f, "%d", &a) && a)
        p = a > 0 ? insertNode(p, a) : deleteNode(p, -a);

    fclose(f);
}

int fixBalance(Node* N) {
    if (!N) return 0;

    int bal_l = N->left ? N->left->bal : -1;
    int bal_r = N->right ? N->right->bal : -1;

    return  bal_l - bal_r;
}
Node* rightRotate(Node* a) {
    Node* b = a->left;
    Node* T1 = b->right;

    b->right = a;
    a->left = T1;

    a->bal = fixBalance(a);
    b->bal = fixBalance(b);

    return b;
}
Node* leftRotate(Node* a) {
    Node* b = a->right;
    Node* T1 = b->left;

    b->left = a;
    a->right = T1;

    a->bal = fixBalance(a);
    b->bal = fixBalance(b);

    return b;
}

Node* insertNode(Node* node, int d) {
    if (!node) return new Node(d);

    if (d < node->d)
        node->left = insertNode(node->left, d);
    else if (d > node->d)
        node->right = insertNode(node->right, d);
    else
        return node;

    return insertBalance(node);
}
Node* insertBalance(Node* node) {
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

Node* deleteMaxValueNode(Node* p, Node* t) {
    Node* q;

    if (p->right) p->right = deleteMaxValueNode(p->right, t);
    else {
        t->d = p->d;
        q = p; p = p->left;
        delete q;
    }

    return p;
}
Node* deleteNode(Node* root, int d) {
    if (root == NULL) return root;
    if (d < root->d) root->left = deleteNode(root->left, d);
    else if (d > root->d) root->right = deleteNode(root->right, d);
    else if (root->left) root->left = deleteMaxValueNode(root->left, root);
    else {
        Node* q = root; root = root->right;
        delete q;
    }

    if (root == NULL) return root;

    return root ? balanceDelete(root) : root;
}
Node* balanceDelete(Node* root) {
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

void printPreOrder(Node* root) {
    if (root) {
        printf("%d ", root->d);
        printPreOrder(root->left);
        printPreOrder(root->right);
    }
}