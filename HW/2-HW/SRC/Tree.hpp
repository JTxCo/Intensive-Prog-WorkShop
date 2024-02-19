/*
Instructions for Tree.hpp:
Binary Search tree - using linked lists  
Below are the interfaces for the classes you will implement. You may include additional functions as needed.  Note: it is your job to determine which parameters and methods should be const!

Function Signatures	Description
Tree(T val)	Initialize the root node for the Tree
~Tree()	Should delete the entire tree.

void insertElement(T val)	Insert an element at the appropriate position in the Binary Search Tree

bool search(T val)	Returns if the element is found in the Binary Search Tree
void deleteElement (T val)	Delete the element from the Tree

std::ostream& operator<<(std::ostream& os, const Tree<U> &t);	overload the << operator for Tree<T>. This should print out the contents of the Tree in the format: {T, T, T, T}. You will use inorder traversal for this function. Hint: using a helper function may be helpful.



*/

#include <iostream>
#include <string>
#include <utility>

using std::string;
using std::pair;
using std::cout;



template <typename T>
class Tree{
    private:
        struct Node {
            T data;
            Node* left;
            Node* right;
        };
        Node* root;

        // delete the tree
        void deleteTree(Node* &node) {
            if (node == nullptr) {
                return;
            }
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
            node = nullptr;
        }
        void insertElement(Node* &node, T val) {
            if (node == nullptr) {
                node = new Node;
                node->data = val;
                node->left = nullptr;
                node->right = nullptr;
            } else if (val < node->data) {
                insertElement(node->left, val);
            } else {
                insertElement(node->right, val);
            }
        }

        void printTree(Node* node)const {
            if (node == nullptr) {
                return;
            }
            printTree(node->left);
            std::cout << node->data << " ";
            printTree(node->right);
        }
        bool search(Node* node, T val)const {
            if (node == nullptr) {
                return false;
            } else if (node->data == val) {
                return true;
            } else if (val < node->data) {
                return search(node->left, val);
            } else {
                return search(node->right, val);
            }
        }
       void deleteElement(Node* &node, T val) {
            if (node == nullptr) {
                return;
            } else if (val < node->data) {
                deleteElement(node->left, val);
            } else if (val > node->data) {
                deleteElement(node->right, val);
            } else {
                if (node->left == nullptr && node->right == nullptr) {
                    delete node;
                    node = nullptr;
                } else if (node->left == nullptr) {
                    Node* temp = node;
                    node = node->right;
                    delete temp;
                } else if (node->right == nullptr) {
                    Node* temp = node;
                    node = node->left;
                    delete temp;
                } else {
                    Node* temp = node->right;
                    while (temp->left != nullptr) {
                        temp = temp->left;
                    }
                    node->data = temp->data;
                    deleteElement(node->right, temp->data);
                }
            }
        }
    public:
        // constructor
        Tree(T val) {
            root = new Node;
            root->data = val;
            root->left = nullptr;
            root->right = nullptr;
        }

        // destructor
        ~Tree(){
            deleteTree(root);
        }


        // get the root value
        const Node* getRoot() const{
            return root;
        }
        // insertElement
        void insertElement(T val){
            insertElement(root, val);
        }
        // search for element in the tree, returns true if found, else false
        bool search( T val)const {
            return search(root, val);
        }
        // delete element from the tree
        void deleteElement(T val) {
            deleteElement(root, val);
        }
        // print the tree
        void printTree() const {
            printTree(root);
        }

        // overload the << operator for Tree<T>
        friend std::ostream& operator<<(std::ostream& os, const Tree<T> &t) {
            os << "{";
            t.printTree();
            os << "}";
            return os;
        }
};