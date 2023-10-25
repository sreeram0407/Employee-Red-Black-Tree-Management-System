//************************************************************************
// ASU CSE310 Assignment #6 Spring 2023
// Author: Sreeram Kondapalli
// ASU ID: 1221440298
// Description: Red black tree implementation. See RedBlackTree.h
//              for the Red Black Tree definition
//************************************************************************

//include the relevant header file
#include "RedBlackTree.h"

using namespace std;

//*******************************************************************
//constructor
RedBlackTree::RedBlackTree()
{
    root = nullptr;
}

//*******************************************************************
//destructor
RedBlackTree::~RedBlackTree()
{
    int nodeSize = 0;
    nodeSize = deleteNode(this->root);
    cout << "The number of deleted nodes: " << nodeSize << endl;
}

//**************************************************************
//Finish all other functions according to re-black tree definition
//put proper comments for each of the functions. I recommend that you
//design each function in order

Node* RedBlackTree::getRoot()
{
    return this->root;
}

int RedBlackTree::deleteNode(Node* node)
{
    int deleted = 0;
    // If the node exists
    if(node != nullptr)
    {
        // Recursively delete the left and right subtrees and
        // add the number of deleted nodes to the counter
        deleted = deleted + deleteNode(node->leftChild);
        deleted = deleted + deleteNode(node->rightChild);
        // Delete the node
        delete node;
        deleted++;
    }
    // Return the number of deleted nodes
    return deleted;
}
// This function inserts a new node z into the red-black tree.
// It first searches for the appropriate place to insert z and sets its parent as the last node visited during the search.
// It then checks whether z's parent is null, meaning the tree is empty, and sets z as the root of the tree.
// If z's parent is not null, it checks whether z should be inserted as a left or right child of its parent based on its id.
// It then sets z's color to red and calls the fixUp function to balance the tree.
void RedBlackTree::insertNode(Node *z)
{
    Node* uncle = nullptr;
    Node* temp = this->root;
    while(temp != nullptr)
    {
        uncle = temp;
        if(z->id < temp->id)
        {
            temp = temp->leftChild;
        }
        else
        {
            temp = temp->rightChild;
        }
    }
    z->parent = uncle;
    if(uncle == nullptr)
    {
        this->root = z;
        this->root->color = "BLACK";
    }
    else if(z->id < uncle->id)
    {
        uncle->leftChild = z;
    }
    else
    {
        uncle->rightChild = z;
    }
    z->leftChild = nullptr;
    z->rightChild = nullptr;
    z->color = "RED";
    fixUp(z);
}

void RedBlackTree::fixUp(Node *z)
{
    while(this->root != z && (z->parent->color == "RED"))
    {
        //if z's uncle is red, recolor parent, uncle and grandparent and move z to its grandparent
        if(z->parent->parent->leftChild == z->parent)
        {
            Node* uncle = z->parent->parent->rightChild;
            if((uncle != nullptr) && (uncle->color == "RED"))
            {
                z->parent->color = "BLACK";
                uncle->color = "BLACK";
                z->parent->parent->color = "RED";
                z = z->parent->parent;
            }
            else
            {
                //z's uncle is black and z is a right child. In this case, we left rotate at parent of z
                if(z->parent->rightChild == z)
                {
                    z = z->parent;
                    leftRotate(z);
                }
                //z's uncle is black and z is a left child. In this case, we recolor and right rotate at grandparent of z
                z->parent->color = "BLACK";
                z->parent->parent->color = "RED";
                rightRotate(z->parent->parent);
            }
        }
        else // z's parent is the right child of its parent
        {
            // Get z's uncle node
            Node* uncle = z->parent->parent->leftChild;
            if((uncle != nullptr) && (uncle->color == "RED"))
            {
                z->parent->color = "BLACK";
                uncle->color = "BLACK";
                z->parent->parent->color = "RED";
                z = z->parent->parent;
            }
            else
            {
                if(z->parent->leftChild == z)
                {
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->color = "BLACK";
                z->parent->parent->color = "RED";
                leftRotate(z->parent->parent);
            }
        }
    }
    this->root->color = "BLACK";
}
// Perform a pre-order traversal of the Red-Black Tree, starting from the given node
void RedBlackTree::preOrderTraversal(Node *node)
{
    // Check if the given node is not null
    if(node != nullptr)
    {
        // Print the information of the current node by calling the print function
        print(node);
        // Recursively call the preOrderTraversal function for the left child of the current node
        preOrderTraversal(node->leftChild);
        // Recursively call the preOrderTraversal function for the right child of the current node
        preOrderTraversal(node->rightChild);
    }
}

void RedBlackTree::inorderTraversal(Node *node)
{
    if(node != nullptr)
    {
        inorderTraversal(node->leftChild);
        print(node);
        inorderTraversal(node->rightChild);
    }
}

void RedBlackTree::postOrderTraversal(Node *node)
{
    if(node != nullptr)
    {
        postOrderTraversal(node->leftChild);
        postOrderTraversal(node->rightChild);
        print(node);
    }
}
// finds the minimum node
Node* RedBlackTree::findMinimumNode(Node *node)
{
    // If the tree is empty, return nullptr.
    if (root == nullptr)
    {
        return nullptr;
    }
    // If the root node has no left child, it is the minimum node.
    if (root->leftChild == nullptr)
    {
        return root;
    }
    // Otherwise, traverse left from the given node until the minimum node is found.
    while(node->leftChild != nullptr)
    {
        node = node->leftChild;
    }
    return node;
}
//finds the maximum node
Node* RedBlackTree::findMaximumNode(Node *node)
{
    if (root == nullptr)
    {
        return nullptr;
    }
    if (root->rightChild == nullptr)
    {
        return root;
    }
    while(node->rightChild != nullptr)
    {
        node = node->rightChild;
    }
    return node;
}

Node* RedBlackTree::treeSearch(int id, string firstName, string lastName)
{
    Node* temp = root;
    // Traverse the tree until the node is found or the end is reached
    while(temp != nullptr)
    {

        if((id == temp->id && firstName == temp->firstName && lastName == temp->lastName) || temp == nullptr)
        {
            return temp;
        }

        if(id < temp->id)
        {
            temp = temp->leftChild;
        }
        else
        {
            temp = temp->rightChild;
        }
    }
    return nullptr;
}

void RedBlackTree::leftRotate(Node *node)
{
    // Save the right child of the node
    Node *y = node->rightChild;
    // Set the left child of the right child of the node as the right child of the node
    node->rightChild = y->leftChild;
    // Update the parent pointer of the left child of the right child of the node
    if (y->leftChild != nullptr)
    {
        y->leftChild->parent = node;
    }
    // Update the parent pointer of the right child of the node
    y->parent = node->parent;
    // Update the root of the tree if the node is the root
    if (node->parent == nullptr)
    {
        root = y;
    }
    // Update the parent pointer of the node's parent
    else if (node == node->parent->leftChild)
    {
        node->parent->leftChild = y;
    }
    else
    {
        node->parent->rightChild = y;
    }
    // Set the node as the left child of the right child of the node
    y->leftChild = node;
    // Update the parent pointer of the node
    node->parent = y;
}

void RedBlackTree::rightRotate(Node *node)
{
    Node *y = node->leftChild;
    node->leftChild = y->rightChild;
    if (y->rightChild != nullptr)
    {
        y->rightChild->parent = node;
    }
    y->parent = node->parent;
    if (node->parent == nullptr)
    {
        root = y;
    }
    else if (node == node->parent->rightChild)
    {
        node->parent->rightChild = y;
    }
    else
    {
        node->parent->leftChild = y;
    }
    y->rightChild = node;
    node->parent = y;
}

Node* RedBlackTree::findPredecessorNode(Node *node)
{
    // If the left subtree is non-empty, then the predecessor
    // is the rightmost node in the left subtree
    if (node->leftChild != nullptr)
    {
        Node *temp = node->leftChild;
        while (temp->rightChild != nullptr)
        {
            temp = temp->rightChild;
        }
        return temp;
    }
    // If the left subtree is empty, then the predecessor is the
    // closest ancestor whose right child is also an ancestor of
    // the node
    else
    {
        Node *temp = node->parent;
        while (temp != nullptr && node == temp->leftChild)
        {
            node = temp;
            temp = temp->parent;
        }
        return temp;
    }
}
// This function finds the successor node of the given node in the Red-Black Tree
Node* RedBlackTree::findSuccessorNode(Node *node)
{
    // If the right subtree of the node is not null, find the leftmost node in the right subtree
    if (node->rightChild != nullptr)
    {
        Node *temp = node->rightChild;
        while (temp->leftChild != nullptr)
        {
            temp = temp->leftChild;
        }
        return temp;
    }
    // If the right subtree of the node is null, find the first right ancestor of the node
    else
    {
        Node *temp = node->parent;
        while (temp != nullptr && node == temp->rightChild)
        {
            node = temp;
            temp = temp->parent;
        }
        return temp;
    }
}

void RedBlackTree::treeMinimum()
{
    if(this->root != nullptr)
    {
        Node *minumumNode = findMinimumNode(this->root);
        cout << "The MINIMUM is: " << endl;
        print(minumumNode);
    }
    else
    {
        cout << "tree is empty" << endl;
    }
}

void RedBlackTree::treeMaximum()
{
    if(this->root != nullptr)
    {
        Node *maximumNode = findMaximumNode(this->root);
        cout << "The MAXIMUM is: " << endl;
        print(maximumNode);
    }
    else
    {
        cout << "tree is empty" << endl;
    }
}

void RedBlackTree::treePreorder()
{
    if(this->root != nullptr)
    {
        preOrderTraversal(this->root);
    }
    else
    {
        cout << "tree is empty" << endl;
    }
}

void RedBlackTree::treeInorder()
{
    if (this->root != nullptr)
    {
        inorderTraversal(this->root);
    }
    else
    {
        cout << "tree is empty" << endl;
    }
}

void RedBlackTree::treePostorder()
{
    if (this->root != nullptr)
    {
        postOrderTraversal(this->root);
    }
    else
    {
        cout << "\ntree is empty" << endl;
    }
}

void RedBlackTree::treePredecessor(int id, string firstName, string lastName)
{
    Node *search = treeSearch(id,firstName,lastName);

    if(search != nullptr)
    {
        cout << left;
        cout << setw(8)  << id << setw(12) << firstName << setw(12) << lastName << " is found." << endl;
        Node* predecessorNode = findPredecessorNode(search);
        if(search == root || predecessorNode == nullptr){
            cout << "Its Predecessor does NOT exist" << endl;
        }
        else{
            cout << "Its Predecessor is: " << endl;
            print(predecessorNode);
        }
    }
    else
    {
        cout << left;
        cout << setw(8)  << id << setw(12) << firstName << setw(12) << lastName << " is NOT found." << "\nIts Predecessor does NOT exist" << endl;
    }
}

void RedBlackTree::treeSucessor(int id, string firstName, string lastName)
{
    // Search for the node with the specified id, first name, and last name
    Node *search = treeSearch(id,firstName,lastName);

    if(search != nullptr)
    {
        // If the node is found, print a message and find its successor
        cout << left;
        cout << setw(8)  << id << setw(12) << firstName << setw(12) << lastName << " is found." << endl;
        Node* successerNode = findSuccessorNode(search);
        if(successerNode == nullptr){
            // If the successor node does not exist, print a message
            cout << "Its Successor does NOT exist" << endl;
        }
        else{
            // If the successor node exists, print the node's details
            cout << "Its Successor is: " << endl;
            print(successerNode);
        }
    }
    else
    {
        // If the node is not found, print a message indicating that the node and its successor do not exist
        cout << left;
        cout << setw(8)  << id << setw(12) << firstName << setw(12) << lastName << " is NOT found." << "\nIts Successor does NOT exist" << endl;
    }
}

void RedBlackTree::treeInsert(int id, string firstName, string lastName, double salary)
{
    Node* newEmployee = new Node();
    newEmployee->firstName = firstName;
    newEmployee->lastName = lastName;
    newEmployee->id = id;
    newEmployee->salary = salary;
    insertNode(newEmployee);
}

//******************************************************************
//Given a 'node', this function prints all the node information on screen
void RedBlackTree::print(Node *node)
{
    cout << left;
    cout << setw(8)  << node->id
         << setw(12) << node->firstName
         << setw(12) << node->lastName
         << setw(10) << fixed << setprecision(2) << node->salary;
    cout << right << setw(7) << node->color << endl;
}