<<<<<<< HEAD
//  Created by Malcolm Williams on 3/10/19.
=======
//  Created by Malcolm H. Williams on 3/10/19.
>>>>>>> 4133f2b3a1ac4c6fdac1aff5d18ea6f5e296a93f
//  Copyright (c) 2019 Malcolm Williams. All rights reserved.
//

#ifndef __TESTCV__BTree__
#define __TESTCV__BTree__

#include <iostream>
#include <string.h>
using namespace std;

struct ColorScheme{
    double rgb1[3];
    double rgb2[3];
    double rgb3[3];
    double rgb4[3];
    double hsv1[3];
    double hsv2[3];
    double hsv3[3];
    double hsv4[3];


};
struct TreeNode
{
    ColorScheme color;
    string hex;
    TreeNode *left;
    TreeNode *right;
    TreeNode *parent;
};
class BTree{
private:
    TreeNode *root;

public:
    TreeNode* lookUp(TreeNode *node, string hex);
    TreeNode* leftMost(TreeNode *node);
    TreeNode *newTreeNode(ColorScheme &color,string hex);
    TreeNode* insertTreeNode(TreeNode *node, ColorScheme &color,string hex);
    int treeSize(TreeNode *node);
    int maxDepth(TreeNode *node);
    int minDepth(TreeNode *node);
    bool isBalanced(TreeNode *node);
    TreeNode* minTree(TreeNode *node);
    TreeNode* maxTree(TreeNode *node);
    TreeNode *succesorInOrder(TreeNode *node);
    TreeNode *predecessorInOrder(TreeNode *node);
    void reverseOrderPrint(TreeNode *node);
    TreeNode *lowestCommonAncestor(TreeNode *node, TreeNode *p, TreeNode *q);
    void clear(TreeNode *node);
    void printTreeNodeInOrder(TreeNode *node);
    void printTreeNodePostOrder(TreeNode *node);
    void printTreeNodePreOrder(TreeNode *node);
    void printTreeNodeReverseOrder(TreeNode *node);



private:
  };
#endif /* defined(__TESTCV__BTree__) */
