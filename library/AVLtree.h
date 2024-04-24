#ifndef AVLtree_H
#define AVLtree_H

#include "User.h"

struct User;

typedef struct AVL_node{
    User user;
    int height;
    struct AVL_node *left;
    struct AVL_node *right;
}AVL_node;
//declaratins
int max(int a,int b);
struct AVL_node* AVL_tree_create_node(struct User *entity);
struct AVL_node* AVL_tree_insert(struct AVL_node *root,User *entity);
int AVL_tree_height(struct AVL_node *node);
int AVL_tree_balance_factor(struct AVL_node *root);
struct AVL_node* AVL_tree_right_rotate(struct AVL_node* y);
struct AVL_node* AVL_tree_left_rotate(struct AVL_node* x);
void AVL_tree_inorder_traverse(struct AVL_node* root);
struct AVL_node* AVL_tree_delete_node(struct AVL_node* root,User *entity);
struct AVL_node* AVL_tree_search_node_by_id(struct AVL_node *root,int query);
struct AVL_node* AVL_tree_search_by_email(struct AVL_node* root,char* email);
/**********************definitions************************/
int max(int a, int b) {
    return (a > b) ? a : b;
}
//allocate memory for the structure and return a pointer
struct AVL_node* AVL_tree_create_node(struct User *entity) {
    struct AVL_node* newNode = (struct AVL_node*)malloc(sizeof(struct AVL_node));
    if (!newNode) {
        // Handle memory allocation failure
        return NULL;
    }
    
    // Allocate memory for User and copy the data
    newNode->user = (*entity);  // Copy the User data
    
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;

    return newNode;
}

//getting the height of the node
int AVL_tree_height(struct AVL_node *node){
    if(node==NULL)return 0;
    return (node->height);
}
//finding balance factor of the node . left node's height - right node's height
int AVL_tree_balance_factor(struct AVL_node *root){
    return (AVL_tree_height(root->left) - AVL_tree_height(root->right));
}
/* if you don't understand how these two works , i recommend you to read blog or watch videos about this subject*/
//rotate to right
struct AVL_node* AVL_tree_right_rotate(struct AVL_node* y){
    struct AVL_node* x = y->left;
    struct AVL_node* T2 = x->right;

    //perform rotation
    x->right = y;
    y->left = T2;

    //calculate the height
    y->height = 1 + (AVL_tree_height(y->left) > AVL_tree_height(y->right) ? AVL_tree_height(y->left) : AVL_tree_height(y->right) );
    x->height = 1 + (AVL_tree_height(x->left) > AVL_tree_height(x->right) ? AVL_tree_height(x->left) : AVL_tree_height(x->right) );

    return x;
}
//rotate to left
struct AVL_node* AVL_tree_left_rotate(struct AVL_node* x){
    struct AVL_node* y = x->right;
    struct AVL_node* T2 = y->left;

    //perform rotation
    y->left = x;
    x->right = T2;

    //calculate the height 
    y->height = 1 + (AVL_tree_height(y->left) > AVL_tree_height(y->right) ? AVL_tree_height(y->left) : AVL_tree_height(y->right) );
    x->height = 1 + (AVL_tree_height(x->left) > AVL_tree_height(x->right) ? AVL_tree_height(x->left) : AVL_tree_height(x->right) );

    return y;
}

struct AVL_node* AVL_tree_insert(struct AVL_node *root,User *entity){
    if(root == NULL){
        root = AVL_tree_create_node(entity);
        return root;
    }
    //to the left
    if((entity->id) < (root->user.id)){
        root->left = AVL_tree_insert(root->left,entity);
    //to the right
    }else if(entity->id > (root->user.id)){
        root->right = AVL_tree_insert(root->right,entity);
    }else{
        //no duplicate nodes
        printf("You can't add same data twice!\n");
        return root;
    }
    //find the biggest height of the two children and add ONE
    root->height = 1+max(AVL_tree_height(root->left), AVL_tree_height(root->right));
    
    //get the balance factor of the tree
    int balance = AVL_tree_balance_factor(root);
    //left rotate
    //do when tree is right heavy and data is greater than right node
    if(balance < -1 && (entity->id > root->right->user.id)){
        return AVL_tree_left_rotate(root);
    //right rotate
    //do when tree is left heavy and data is smaller than left node
    }else if(balance > 1 && (entity->id < root->left->user.id)){
        return AVL_tree_right_rotate(root);
    //left right rotate
    //do when tree is left heavy and data is greater than the right node
    }else if(balance > 1 && (entity->id > root->right->user.id)){
        root->left  = AVL_tree_left_rotate(root->left);   
        return AVL_tree_right_rotate(root);
    //right left rotate
    //do when tree is right heavy and data is smaller than left node
    }else if(balance < -1 && (entity->id < root->left-> user.id)){
        root->right  = AVL_tree_right_rotate(root->right);   
        return AVL_tree_left_rotate(root);
    }

    //if the balanced factor is -1 , 0 , 1
    return root;

}
//print the data from left to right
void AVL_tree_inorder_traverse(struct AVL_node* root){
        if(root == NULL) return;
        printf("hello");
        AVL_tree_inorder_traverse(root->left);
        printf(" %d ",root->user.id);
        AVL_tree_inorder_traverse(root->right);

}
//for further details comment , you should go read the binary Search Tree file .
//these two are basically the same
struct AVL_node* AVL_tree_delete_node(struct AVL_node* root,User* entity){
    if(root == NULL){
        return root;
    }
//traverse the tree according to BST logic
    //go to left
    if(entity->id < root->user.id){
        //after the recursive is done this will return a new sub tree with the data we want deleted
        root->left = AVL_tree_delete_node(root->left,entity);
    }else if(entity->id > root->user.id){
        root->right = AVL_tree_delete_node(root->right,entity);
    }else{
    //we have found the node 
        //Case 1: no child node
        if((!root->left)&&(!root->right)){
            free(root);
            return NULL;
        //Case 2: only one child node
            //sub case : left child is empty
        }else if(!(root->left)){
            struct AVL_node* temp = root->right;
            root = temp;
            free(temp);
            return root;
            //sub case : right child is empty
        }else if(!(root->right)){
            struct AVL_node* temp = root->left;
            root=temp;
            free(temp);
            return root;
        //Case 3: has both children
        }else if((root->left)&&(root->right)){
            struct AVL_node* parent = root;
            //we are gonna search the smallest child in the right sub-tree
            struct AVL_node* child = root->right;
            while(child->left){
                parent = child;
                child = child->left;
            }
            //we have to assume we have found the smallest child with NO LEFT NODE
                //if the sub-tree doesn't have a left child which insist current child is the smallest
            if(parent == root){
                //skip the child node link it to its child
                parent->right = child->right;
            }else{
                parent->left = child->right;
            }

            //change the data of the root now
            root->user = child->user;
            free(child);
        } 
    }
    root->height = 1+max(AVL_tree_height(root->left),AVL_tree_height(root->right));

    // Balance the tree
    int balance = AVL_tree_balance_factor(root);
    /*  
    the balance the root will be determine whether the final rotation will be left or right
    the balance factor of the sub-tree will determine whether we have to rotate it seprately or not
    and we will only check the balanced factor of a sub-tree that is heavy (more than 1 or less than -1)
    */
    // right rotate
    if(balance > 1 && AVL_tree_balance_factor(root->left) >= 0){
        return AVL_tree_right_rotate(root);
    }

    // Left Right Case
    if(balance > 1 && AVL_tree_balance_factor(root->left) < 0){
        root->left = AVL_tree_left_rotate(root->left);
        return AVL_tree_right_rotate(root);
    }

    // left rotate
    if(balance < -1 && AVL_tree_balance_factor(root->right) <= 0){
        return AVL_tree_left_rotate(root);
    }

    // Right Left Case
    if(balance < -1 && AVL_tree_balance_factor(root->right) > 0){
        root->right = AVL_tree_right_rotate(root->right);
        return AVL_tree_left_rotate(root);
    }

    return root;
}

struct AVL_node* AVL_tree_search_node_by_id(struct AVL_node *root,int query){
    if(root == NULL || query == root->user.id){
        return root;
    }
    if(query < (root->user.id)){
        return AVL_tree_search_node_by_id(root->left,query);
    }else if(query > (root->user.id)){
        return AVL_tree_search_node_by_id(root->right,query);
    }
}
struct AVL_node* AVL_tree_search_by_email(struct AVL_node* root,char* email) {
    if (root == NULL) {
        return NULL;  // Email not found
    }

    // Search in the left subtree
    struct AVL_node* leftResult = AVL_tree_search_by_email(root->left, email);
    if (leftResult != NULL) {
        return leftResult;  // Found in left subtree
    }

    // Check current node
    if (strcmp(root->user.email, email) == 0) {
        return root;  // Found current node
    }

    // Search in the right subtree
    return AVL_tree_search_by_email(root->right, email);
}

#endif