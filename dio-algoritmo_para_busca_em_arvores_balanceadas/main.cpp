#include <iostream>

using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;
    int height;
};

Node* createNode(int value) {
    Node* newNode = new Node();
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

int getHeight(Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

int getBalanceFactor(Node* node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

Node* insert(Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }

    if (value < root->value) {
        root->left = insert(root->left, value);
    }
    else if (value > root->value) {
        root->right = insert(root->right, value);
    }
    else {
        return root;
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balance = getBalanceFactor(root);

    if (balance > 1 && value < root->left->value) {
        return rotateRight(root);
    }
    if (balance < -1 && value > root->right->value) {
        return rotateLeft(root);
    }
    if (balance > 1 && value > root->left->value) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (balance < -1 && value < root->right->value) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

void inOrder(Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        cout << root->value << " ";
        inOrder(root->right);
    }
}

int main() {

    Node* node = createNode(182);
    insert(node, 192);
    insert(node, 69);
    insert(node, 832);
    insert(node, 1372);
    insert(node, 102);
    insert(node, 1032);
    insert(node, 821);
    insert(node, 178);
    insert(node, 1923);

    inOrder(node);
}