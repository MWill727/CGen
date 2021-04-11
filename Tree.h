//  Created by Malcolm Williams on 3/10/19.
//  Copyright (c) 2019 Malcolm Williams. All rights reserved.
//
#ifndef TREE_H
#define TREE_H
#include <iostream>
#include "stdio.h"
#include <string.h>
#include <QPixmap>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace std;
using namespace cv;
//Struct that holds one color scheme for picture
struct ColorScheme{
    int rgb[3];
    int hsv[3];
    string hex;



};
//Tree node
struct TreeNode
{
    ColorScheme color[4];
    TreeNode *left;
    TreeNode *right;
    TreeNode *parent;
    QPixmap qtPic;
    int key;
};
class Tree
{
private:
    TreeNode *root;

public:
    Tree();
    ~Tree();
    bool isEmpty();
    int Insert(TreeNode *newNode);
    int Insert(ColorScheme c[4], QPixmap qtPic,int key);
    int Delete(int Key);
    TreeNode *lookUp(TreeNode *node, int key);
    TreeNode *lookUp(int key);
    void print(TreeNode *T);
    TreeNode *getRoot();
    int BTreeSize(TreeNode *node);
    void PrintTree();
    int count;

private:
    void clear(TreeNode *T);
    void PrintAll(TreeNode *T);
};
#endif
