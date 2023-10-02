#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

// C++ has implicit "typdef"
// tree node structure
struct node{
    int key;
    struct node* left;
    struct node* right;
    struct node* p;
}*root = NULL;

// follow the rule of BST to find the address of key
node* Search(node* x, int k){
    if(x == NULL || k == x->key)
        return x;
    if(k < x->key)
        return Search(x->left, k);
    return Search(x->right, k);
}

// not using recursive has better efficiency(because no stack structure)
// right-most leaf is the max
node* Max(node* x){
    while(x->right != NULL){
        x = x->right;
    }
    return x;
}

// left-most leaf is the max
node* Min(node* x){
    while(x->left != NULL){
        x = x->left;
    }
    return x;
}

// find who is itself parent's left, and the return its parent
node* Successor(node* x){
    if(x->right != NULL)
        return Min(x->right);
    node* y = x->p;
    while(y != NULL && x == y->right){
        x = y;
        y = y->p;
    }
    return y;
}

// same as above(right becomes left)
node* Predecessor(node* x){
    if(x->left != NULL)
        return Max(x->left);
    node* y = x->p;
    while(y != NULL && x == y->left){
        x = y;
        y = y->p;
    }
    return y;
}

// being used to initialize the node structure
node* newNode(int x){
    node* p;
    //p = malloc(sizeof(node));
    p = new node;
    p->key = x;
    p->left = NULL;
    p->right = NULL;
    return p;
}

// First, find the patent of the inserting node
// then insert the node to the left(or right) of it
void Insert(node* z){
    node* y = NULL;
    node* x = root;
    while (x != NULL){
        y = x; // holds the parent of x
        if (z->key < x->key)
            x = x->left;
        else x = x->right;
    }
    z->p = y; // we are sure that y is the parent of z
    if (y == NULL)
        root = z;
    else if (z->key < y->key)
        y->left = z;
    else y->right = z;
}


// replace u with v
void Transplant(node* u, node* v){
    if (u->p == NULL)
        root = v;
    else if (u == u->p->left)
        u->p->left = v;
    else u->p->right = v;
    if(v != NULL)
        v->p = u->p;
}

// to avoid being the same with memory delete, use "TreeDelete" instead
void TreeDelete(node* z){
    if(z->left == NULL)
        Transplant(z, z->right);
    else if(z->right == NULL)
        Transplant(z, z->left);
    else{
        node* y = Min(z->right);
        if (y->p != z){ // to avoid y to point to itself(when y == z->right)
            Transplant(y, y->right);
            y->right = z->right;
            y->right->p = y;
        }
        Transplant(z, y);
        y->left = z->left;
        y->left->p = y;
    }
}

// traverse the BST
void PrintInorder(node *x){
    if(x != NULL){
        PrintInorder(x->left);
        cout << x->key << " ";
        PrintInorder(x->right);
    }
}

int main(){
    vector<node*> vec;
    int key;
    int size=0;
    cout << "1.Insert" << endl;
    cout << "2.Search" << endl;
    cout << "3.Print Max & Min" << endl;
    cout << "4.Find Successor & Predecessor" << endl;
    cout << "5.Delete" << endl;
    cout << "6.Print the tree(inorder)" << endl;
    cout << "Choose action:";
    while(1){
        int a;
        cin >> a;
        switch(a){ // uses switch to judge what an action is user wanted
            case 1:{
                cout << "Enter the key: ";
                cin >> key;
                vec.push_back(newNode(key)); // save each node to vec
                Insert(vec[size]);
                // note that size in here is used to record the number of inserted nodes
                // and will not going to reduce during deletion
                size++; 
                cout << "The tree becomes (inorder):" << endl;
                PrintInorder(root); // print the results of BST
                cout << endl;
                break;
            }
            case 2:{ // check whether the key exist
                cout << "Enter the key: ";
                cin >> key;
                if(Search(root, key) != NULL)
                    cout << "key " << key << " can be found" << endl;
                else cout << "key " << key << " can not be found" << endl;
                break;
            }
            case 3:{ // output the max & min
                cout << "Max key is " << Max(root)->key << endl;
                cout << "Min key is " << Min(root)->key << endl;
                break;
            }
            case 4:{ // output Successor & Predecessor. We should check whether input key is the biggest or smallest
                cout << "Enter the key: ";
                cin >> key;
                if(Search(root, key) == NULL)
                    cout << "key " << key << " can not be found" << endl;
                else{
                    if (Search(root, key) == Max(root)){
                        cout << "It's biggest key, no successor" << endl;
                    }
                    else{
                    cout << "Seccessor of "<< key << " is " << Successor(Search(root, key))->key << endl;
                    }
                    if (Search(root, key) == Min(root)){
                        cout << "It's smallest key, no predecessor" << endl;
                    }
                    else{
                    cout << "Predecessor of "<< key << " is " << Predecessor(Search(root, key))->key << endl;
                    }
                }
                break;
            }
            case 5:{ // delete a node by key
                cout << "Enter the key: ";
                cin >> key;
                if(Search(root, key) == NULL)
                    cout << "key " << key << " can not be found" << endl;
                else{
                    TreeDelete(Search(root, key));
                    cout << "After deletion, tree is now:" << endl;
                    PrintInorder(root);
                    cout << endl;
                }
                break;
            }
            case 6:{ // print the tree
                cout << "The tree is (inorder):" << endl;
                PrintInorder(root);
                cout << endl;
                break;
            }
        }
        cout << endl << "Choose action:";
    }
    return 0;
}


