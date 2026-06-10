#include <iostream>
#include <string>
using namespace std;

// =======================================
//  LINKED LIST
// =======================================
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;
    int size;
public:
    LinkedList() : head(nullptr), size(0) {}

    void push_front(int val) {
        Node* newNode = new Node(val);
        newNode->next = head;
        head = newNode;
        size++;
    }

    void push_back(int val) {
        Node* newNode = new Node(val);
        if (!head) { head = newNode; size++; return; }
        Node* curr = head;
        while (curr->next) curr = curr->next;
        curr->next = newNode;
        size++;
    }

    void remove(int val) {
        if (!head) return;
        if (head->data == val) {
            Node* tmp = head;
            head = head->next;
            delete tmp; size--; return;
        }
        Node* curr = head;
        while (curr->next && curr->next->data != val)
            curr = curr->next;
        if (curr->next) {
            Node* tmp = curr->next;
            curr->next = tmp->next;
            delete tmp; size--;
        }
    }

    void print() {
        Node* curr = head;
        cout << "LinkedList [" << size << "]: ";
        while (curr) {
            cout << curr->data;
            if (curr->next) cout << " -> ";
            curr = curr->next;
        }
        cout << endl;
    }

    ~LinkedList() {
        while (head) { Node* tmp = head; head = head->next; delete tmp; }
    }
};

// =======================================
//  STACK
// =======================================
class Stack {
private:
    Node* top;
    int size;
public:
    Stack() : top(nullptr), size(0) {}

    void push(int val) {
        Node* newNode = new Node(val);
        newNode->next = top;
        top = newNode;
        size++;
    }

    int pop() {
        if (!top) throw runtime_error("Stack vazia!");
        int val = top->data;
        Node* tmp = top;
        top = top->next;
        delete tmp; size--;
        return val;
    }

    int peek() {
        if (!top) throw runtime_error("Stack vazia!");
        return top->data;
    }

    bool empty() { return top == nullptr; }
    int getSize() { return size; }

    void print() {
        Node* curr = top;
        cout << "Stack [" << size << "] (top->bottom): ";
        while (curr) {
            cout << curr->data;
            if (curr->next) cout << " -> ";
            curr = curr->next;
        }
        cout << endl;
    }

    ~Stack() {
        while (top) { Node* tmp = top; top = top->next; delete tmp; }
    }
};

// =======================================
//  HASH TABLE
// =======================================
class HashTable {
private:
    static const int SIZE = 10;
    struct Entry {
        string key;
        int value;
        bool occupied;
        Entry() : key(""), value(0), occupied(false) {}
    };
    Entry table[SIZE];

    int hash(const string& key) {
        int h = 0;
        for (char c : key) h = (h * 31 + c) % SIZE;
        return h;
    }

public:
    void insert(const string& key, int value) {
        int idx = hash(key);
        int original = idx;
        while (table[idx].occupied && table[idx].key != key) {
            idx = (idx + 1) % SIZE;
            if (idx == original) { cout << "HashTable cheia!\n"; return; }
        }
        table[idx].key = key;
        table[idx].value = value;
        table[idx].occupied = true;
    }

    int get(const string& key) {
        int idx = hash(key);
        int original = idx;
        while (table[idx].occupied) {
            if (table[idx].key == key) return table[idx].value;
            idx = (idx + 1) % SIZE;
            if (idx == original) break;
        }
        throw runtime_error("Chave nao encontrada: " + key);
    }

    void print() {
        cout << "HashTable:" << endl;
        for (int i = 0; i < SIZE; i++)
            if (table[i].occupied)
                cout << "  [" << i << "] " << table[i].key << " => " << table[i].value << endl;
    }
};

// =======================================
//  AVL TREE
// =======================================
struct AVLNode {
    int data, height;
    AVLNode *left, *right;
    AVLNode(int val) : data(val), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
private:
    AVLNode* root;

    int height(AVLNode* n) { return n ? n->height : 0; }
    int balance(AVLNode* n) { return n ? height(n->left) - height(n->right) : 0; }
    void updateHeight(AVLNode* n) {
        if (n) n->height = 1 + max(height(n->left), height(n->right));
    }

    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T = x->right;
        x->right = y;
        y->left = T;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T = y->left;
        y->left = x;
        x->right = T;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    AVLNode* insert(AVLNode* node, int val) {
        if (!node) return new AVLNode(val);
        if (val < node->data) node->left = insert(node->left, val);
        else if (val > node->data) node->right = insert(node->right, val);
        else return node;

        updateHeight(node);
        int b = balance(node);

        if (b > 1 && val < node->left->data)
            return rotateRight(node);
        if (b < -1 && val > node->right->data)
            return rotateLeft(node);
        if (b > 1 && val > node->left->data) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (b < -1 && val < node->right->data) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

    void inorder(AVLNode* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

public:
    AVLTree() : root(nullptr) {}
    void insert(int val) { root = insert(root, val); }
    void print() { cout << "AVL Inorder: "; inorder(root); cout << endl; }
};

// =======================================
//  MAIN
// =======================================
int main() {
    cout << "=== DATA STRUCTURES IN C++ ===" << endl << endl;

    cout << "--- Linked List ---" << endl;
    LinkedList list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.push_front(5);
    list.print();
    list.remove(20);
    list.print();

    cout << "\n--- Stack ---" << endl;
    Stack stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.print();
    cout << "Pop: " << stack.pop() << endl;
    stack.print();

    cout << "\n--- Hash Table ---" << endl;
    HashTable ht;
    ht.insert("java", 1);
    ht.insert("python", 2);
    ht.insert("cpp", 3);
    ht.print();
    cout << "java => " << ht.get("java") << endl;

    cout << "\n--- AVL Tree ---" << endl;
    AVLTree avl;
    avl.insert(10);
    avl.insert(20);
    avl.insert(30);
    avl.insert(40);
    avl.insert(50);
    avl.insert(25);
    avl.print();

    cout << "\n=== DONE ===" << endl;
    return 0;
}