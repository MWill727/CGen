//  Created by Malcolm Williams on 3/10/19.
//  Copyright (c) 2019 Malcolm Williams. All rights reserved.
//

#include "BTree.h"
#include <string.h>
#include <iostream>
using namespace std;

TreeNode *BTree:: lookUp(struct TreeNode *node, string hex)
{
    if(node == NULL) return node;

    if(node->hex == hex) return node;
    else {
        if(node->hex < hex)
            return lookUp(node->right, hex) ;
        else
            return lookUp(node->left, hex);
    }
}

TreeNode *BTree:: leftMost(struct TreeNode *node)
{
    if(node == NULL) return NULL;
    while(node->left != NULL)
        node = node->left;
    return node;
}

struct TreeNode *newTreeNode(ColorScheme &color,string hex)
{
    TreeNode *node = new TreeNode;
    node->color = color;
    node->hex=hex;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;

    return node;
}

struct TreeNode *BTree:: insertTreeNode(struct TreeNode *node, ColorScheme &color,string hex)
{
    static TreeNode *p;
    TreeNode *retNode;

    //if(node != NULL) p = node;

    if(node == NULL)  {
        retNode = newTreeNode(color,hex);
        retNode->parent = p;
        return retNode;
    }
    if(color.hsv1[0] >= node->color.hsv1[0] ) {
        p = node;
        node->left = insertTreeNode(node->left,color,hex);
    }
    else {
        p = node;
        node->right = insertTreeNode(node->right,color,hex);
    }
    return node;
}


int BTree::treeSize(struct TreeNode *node)
{
    if(node == NULL) return 0;
    else
        return treeSize(node->left) + 1 + treeSize(node->right);
}

int BTree::maxDepth(struct TreeNode *node)
{
    if(node == NULL || (node->left == NULL && node->right == NULL))
        return 0;

    int leftDepth = maxDepth(node->left);
    int rightDepth = maxDepth(node->right);

    return leftDepth > rightDepth ?
    leftDepth + 1 : rightDepth + 1;
}

int BTree::minDepth(struct TreeNode *node)
{
    if(node == NULL || (node->left == NULL && node->right == NULL))
        return 0;

    int leftDepth = minDepth(node->left);
    int rightDepth = minDepth(node->right);

    return leftDepth < rightDepth ?
    leftDepth + 1 : rightDepth + 1;
}

bool BTree::isBalanced(struct TreeNode *node)
{
    if(maxDepth(node)-minDepth(node) <= 1)
        return true;
    else
        return false;
}

/* TreeNode Minimum */
TreeNode *BTree:: minTree(struct TreeNode *node)
{
    if(node == NULL) return NULL;
    while(node->left)
        node = node -> left;
    return node;
}

/* TreeNode Maximum */
TreeNode *BTree:: maxTree(struct TreeNode *node)
{
    while(node->right)
        node = node -> right;
    return node;
}

/* In Order Successor - a node which has the next higher key */
TreeNode *BTree::succesorInOrder(struct TreeNode *node)
{
    /* if the node has right child, seccessor is TreeNode-Minimum */
    if(node->right != NULL) return minTree(node->right);

    TreeNode *y = node->parent;
    while(y != NULL && node == y->right) {
        node = y;
        y = y->parent;
    }
    return y;
}

/* In Order Predecessor - a node which has the next lower key */
TreeNode *BTree::predecessorInOrder(struct TreeNode *node)
{
    /* if the node has left child, predecessor is TreeNode-Maximum */
    if(node->left != NULL) return maxTree(node->left);

    TreeNode *y = node->parent;
    /* if it does not have a left child,
     predecessor is its first left ancestor */
    while(y != NULL && node == y->left) {
        node = y;
        y = y->parent;
    }
    return y;
}

void reverseOrderPrint(struct TreeNode *node)
{
    if(node == NULL) return;
    if(node->left == NULL && node->right == NULL) {
        cout<< ""<<endl;
        return;
    }

    reverseOrderPrint(node->right);
    //cout << node->data << " ";
    reverseOrderPrint(node->left);
}

TreeNode *lowestCommonAncestor(TreeNode *node, TreeNode *p, TreeNode *q)
{
    TreeNode *left, *right;
    if(node == NULL) return NULL;
    if(node->left == p || node->left == q
       || node->right == p || node->right == q) return node;

    left = lowestCommonAncestor(node->left,p,q);
    right = lowestCommonAncestor(node->right, p,q);
    if(left && right)
        return node;
    else
        return (left) ? left : right;
}

void clear(struct TreeNode *node)
{
    if(node != NULL) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}
/* print TreeNode in order */
/* 1. Traverse the left subTreeNode.
 2. Visit the root.
 3. Traverse the right subTreeNode.
 */

void printTreeNodeInOrder(struct TreeNode *node)
{
    if(node == NULL) return;

    printTreeNodeInOrder(node->left);
    cout << node->color.hsv1[0] << " "<<endl;
    // cout<< node->hex<<endl;
    printTreeNodeInOrder(node->right);
}

/* print TreeNode in postorder*/
/* 1. Traverse the left subTreeNode.
 2. Traverse the right subTreeNode.
 3. Visit the root.
 */
void printTreeNodePostOrder(struct TreeNode *node)
{
    if(node == NULL) return;

    printTreeNodePostOrder(node->left);
    printTreeNodePostOrder(node->right);
    //cout << node->data << " ";
}

/* print in preorder */
/* 1. Visit the root.
 2. Traverse the left subTreeNode.
 3. Traverse the right subTreeNode.
 */
void printTreeNodePreOrder(struct TreeNode *node)
{
    if(node == NULL) return;

    //cout << node->data << " ";
    printTreeNodePreOrder(node->left);
    printTreeNodePreOrder(node->right);
}

/* In reverse of printTreeNodeInOrder() */
void printTreeNodeReverseOrder(struct TreeNode *node)
{
    if(node == NULL) return;
    if(node->left == NULL && node->right == NULL) {
        //   cout << node->data << " ";
        return;
    }

    printTreeNodeReverseOrder(node->right);
    cout << node->color.hsv1[0] << " "<<endl;
    printTreeNodeReverseOrder(node->left);

}





