//  Created by Malcolm H. Williams on 3/10/19.
//  Copyright (c) 2019 Malcolm Williams. All rights reserved.
//
#include "Tree.h"

using namespace std;

//Class Constructor
Tree::Tree()
{
    root = NULL;
    return;
}


// Class destructor
Tree::~Tree()
{
    clear(root);
    return;
}

//Destory all node recursivly
void Tree::clear(TreeNode *T)
{
    if(T==NULL) return;  // No nodes to clear
    if(T->left != NULL) clear(T->left); // Clear left sub-tree
    if(T->right != NULL) clear(T->right); // Clear right sub-tree
    delete T;    // Destroy current node
    return;
}

//returns whether the binary tree is empty
bool Tree::isEmpty()
{
    return(root==NULL);
}


//Look up Binary Tree Node recursively.
TreeNode *Tree:: lookUp(TreeNode *node, int key)
{

    if( node == NULL ) // If no node return Null
        return NULL;
    if( node->key == key )// If node key equals referenced key reuturn node
        return node;
    if( node->key > key ) // If node greater than referenced key call function again to look up recursively
        return lookUp( node->left, key );
    else
        return lookUp( node->right, key );// If node les than referenced key call function again to look up recursively
}

TreeNode *Tree::lookUp(int key)
{
    return lookUp(root,key);//Call first look up function
}

//Inserts node into Tree
int Tree::Insert(TreeNode *newNode)
{
    TreeNode *temp=0;//temp node
    TreeNode *back;//back node

    temp = root;//root equals temp node
    back = NULL;

    while(temp != NULL) // Loop until temp is done
    {
        back = temp;
        if(newNode->key < temp->key)
            temp = temp->left;
        else
            temp = temp->right;
    }
    // attach the new node to the node that back points to
    if(back == NULL) // Attach as root node in a new tree
    {

        root = newNode;

    }
    else
    {
        if(newNode->key < back->key)
            back->left = newNode;
        else
            back->right = newNode;
    }
    return(true);
}


//Inserts node into Tree
int Tree::Insert(ColorScheme c[4], QPixmap qtP, int key)
{
    TreeNode *newNode;

    // Create new node and copy referenced data into it
    newNode = new TreeNode();
    newNode->color[0]=c[0];
    newNode->color[1]=c[1];
    newNode->color[2]=c[2];
    newNode->color[3]=c[3];
    newNode->qtPic=qtP;
    newNode->key=key;
    newNode->left = newNode->right = NULL;

    // Call other Insert() to do the actual insertion
    return(Insert(newNode));
}

//get root node of tree
TreeNode *Tree:: getRoot()
{
    return root;
}



//Print data of one node
void Tree::print(TreeNode *T)
{
    for(int i=0;i<=3;i++)
    {
        cout<<i<<endl;
        cout<<"R:"<<T->color[i].rgb[0]<<" G:"<<T->color[i].rgb[1]<<" B:"<<T->color[i].rgb[2]<<endl;
        cout<<endl;
        cout<<"H:"<<T->color[i].hsv[0]<<" S:"<<T->color[i].hsv[1]<<" V:"<<T->color[i].hsv[2]<<endl;
        cout<<endl;
        cout<<"HEX "<<T->color[i].hex<<endl;
        cout<<"KEY "<<T->key<<endl;
    }
}

//Print using recursive traversal
void Tree::PrintAll(TreeNode *T)
{
    if(T != NULL)
    {
        PrintAll(T->left);
        print(T);
        PrintAll(T->right);
    }
}

//Print using recursive traversal
void Tree::PrintTree()
{
    PrintAll(root);
}


//get size of Binary tree
int Tree::BTreeSize(TreeNode *node)
{
    if(node == NULL) return 0;//if tree has no nodes return 0
    else
        return BTreeSize(node->left) + 1 + BTreeSize(node->right);//if not iterate through tree recursitley while incremting count
}
