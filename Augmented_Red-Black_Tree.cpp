#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
 Propertyies of RBT
(1) A node is either red or black
(2) The root is black
(3) All leaves (NULL) are black
(4) Both children of every red node are black
(5) Every simple path from root to leaves contains the same number of black nodes.
*/

// each node has key, left, right, parent, color
struct node{
    int key;
    node *left, *right, *parent;
    int size;
    string color;
};

// use vector to store nodes, makes debug to be easier
// size is initially = 0
// nil is not only NULL, it should be set to black, size=0
struct Tree{
    vector<node *> tree;
    int size = 0;
    node *root;
    node *nil;
};

// to implement left rotate
// y to x's left child
// y's left child to x's right child
// x's parent to y's parent
void Left_Rotate(Tree *T, node *x){
    node *y = x->right;
    x->right = y->left;
    if (y->left != T->nil)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == T->nil)
        T->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
    y->size = x->size; // textbook pseudo code error?
    x->size = x->left->size + x->right->size + 1;
}

// to implement right rotate, exactly the inverse of left rotate
void Right_Rotate(Tree *T, node *x){
    node *y = x->left;
    x->left = y->right;
    if (y->right != T->nil)
        y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == T->nil)
        T->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->right = x;
    x->parent = y;
    y->size = x->size;
    x->size = x->left->size + x->right->size + 1;
}

// fixup the RBT to maintain properties
void RB_Insert_Fixup(Tree *T, node *z){
    while (z->parent->color == "red"){ // while parent is red, there is a violation of property(4)
        // if parent is left child
        if (z->parent->parent != T->nil && z->parent == z->parent->parent->left){
            node *y = z->parent->parent->right; // y is uncle
            // if uncle is red, change the color of parent and uncle to black, grandparent to red
            if (y->color == "red"){
                z->parent->color = "black";
                y->color = "black";
                z->parent->parent->color = "red";
                z = z->parent->parent;
            }
            // if uncle is black, consider LR, LL case
            else{
                // for LR case, use left & right totate
                if (z == z->parent->right){
                    z = z->parent;
                    Left_Rotate(T, z);
                }
                // for LL case, use right rotate, set parent to black, grandparent to red
                z->parent->color = "black";
                z->parent->parent->color = "red";
                Right_Rotate(T, z->parent->parent);
                
            }
        }
        else{
            node *y = z->parent->parent->left;
            // if uncle is red, change the color of parent and uncle to black, grandparent to red
            if (y->color == "red"){
                z->parent->color = "black";
                y->color = "black";
                z->parent->parent->color = "red";
                z = z->parent->parent;
            }
            // if uncle is black, consider RL, RR case
            else{
                // for RL case, use right & left totate
                if (z == z->parent->left){
                    z = z->parent;
                    Right_Rotate(T, z);
                }
                // for RR case, use left rotate, set parent to black, grandparent to red
                z->parent->color = "black";
                z->parent->parent->color = "red";
                Left_Rotate(T, z->parent->parent);
            }
        }
    }
    T->root->color = "black";
}

// insert the new node, and then call fixup to maintain RBT property
void RB_Insert(Tree *T, node *z){
    node *y = T->nil;
    node *x = T->root;
    while (x != T->nil){
        y = x;
        if (z->key < x->key){ // smaller key goes to left
            x = x->left;
        }
        else{ // larger key goes to left
            x = x->right;
        }
        y->size++;
    }
    z->parent = y;
    if (y == T->nil) // y is NIL => x is NIL => Tree is empty
        T->root = z;
    else if (z->key < y->key) // otherwise add the node
        y->left = z;
    else
        y->right = z;
    RB_Insert_Fixup(T, z);
}

// return the ith smallest key
node *OS_Select(node *x, int i){
    int r = x->left->size + 1;
    if (i == r)
        return x;
    else if (i < r)
        return OS_Select(x->left, i);
    else
        return OS_Select(x->right, i - r);
}

// return the rank(ith smallest) of an node
int OS_Rank(Tree *T, node *x){
    int r = x->left->size + 1;
    node *y = x;
    while (y != T->root){
        if (y == y->parent->right)
            r = r + y->parent->left->size + 1;
        y = y->parent;
    }
    return r;
}

// find the position for a node to be inserted
node *Search(node *x, int key, Tree *T){
    if (x == T->nil || key == x->key)
        return x;
    if (key < x->key)
        return Search(x->left, key, T);
    else
        return Search(x->right, key, T);
}

// initialize any inserted node
node *newNode(int key, Tree *T){
    node *temp = new node;
    temp->key = key;
    temp->left = T->nil;
    temp->right = T->nil;
    temp->size = 1;
    temp->color = "red";
    return temp;
}

// to print preorder traverse
void Preorder(node *x, Tree *T){
    if (x == T->nil)
        return;
    cout << "Key: " << x->key << "  Color: " << x->color << "  Size: " << x->size << endl;
    Preorder(x->left, T);
    Preorder(x->right, T);
}

int main(){
    Tree *RBT = new Tree;
    RBT->nil = new node; // nil is black, size = 0
    RBT->nil->color = "black";
    RBT->nil->size = 0;
    RBT->root = RBT->nil; // root is equal to nil at first
    
    cout << endl << "1.Insert" << endl;
    cout << "2.OS-SELECT" << endl;
    cout << "3.OS-RANK" << endl;
    cout << "4.Pre-Order Traversal" << endl;
    cout << "Choose an action:";
    
    while (1){
        int choice;
        cin >> choice;
        switch (choice){
            case 1:{ // insert
                int key;
                cout << "Enter a key for insertion: ";
                cin >> key;
                if (RBT->size == 0){ // if size=0, insert directly
                    node *insert = newNode(key, RBT);
                    RB_Insert(RBT, insert);
                    RBT->size++;
                    RBT->tree.push_back(insert);
                    break;
                }
                // otherwise, insertion will only be done if the key is not existed
                node *found = Search(RBT->root, key, RBT);
                if (found == RBT->nil){
                    node *insert = newNode(key, RBT);
                    RB_Insert(RBT, insert);
                    RBT->size++;
                    RBT->tree.push_back(insert);
                }
                else
                    cout << endl << "The key is already existed!" << endl ;
                break;
            }
                
            case 2:{ // select
                int select;
                cout << "Enter ith smallest key to select: ";
                cin >> select;
                if (select > RBT->size || select <= 0)
                    cout << endl << "The number exceeds the size of the tree." << endl;
                else{
                    node *S = OS_Select(RBT->root, select);
                    cout << endl << "Select: " << select << "-th element" << endl;
                    cout << "key: " << S->key << "  color: " << S->color << "  size: " << S->size << endl;
                }
                cout << endl;
                break;
            }
                
            case 3:{ // OS-rank
                int rank;
                cout << "Enter a key for OS-rank: ";
                cin >> rank;
                node *rank1 = Search(RBT->root, rank, RBT);
                if (rank1 == RBT->nil)
                    cout << "The node doesn't exist." << endl;
                else{
                    int rank2 = OS_Rank(RBT, rank1);
                    cout << "The rank of the node = " << rank2 << endl;
                }
                cout << endl;
                break;
            }
                
            case 4:{ // Print preorder traverse
                if (RBT->size == 0)
                    cout << "The tree is empty!!" << endl;
                else{
                    cout << endl << "The Pre-order Traversal is: " << endl;
                    Preorder(RBT->root, RBT);
                }
                cout << endl;
                break;
            }
                
            default:
                cout << endl << "Invalid input!" << endl << endl;
                break;
        }
        cout  << endl << "Choose an action:";
    }
    return 0;
}
