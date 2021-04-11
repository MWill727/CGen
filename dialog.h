//  Created by Malcolm Williams on 3/10/19.
//  Copyright (c) 2019 Malcolm Williams. All rights reserved.
//
#ifndef DIALOG_H
#define DIALOG_H
#include <iostream>
#include "stdio.h"
#include <string.h>
#include <qlabel.h>
#include <QDialog>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QImage>
#include <QPixmap>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "tree.h"
using namespace cv;
namespace Ui {
class Dialog;
}
class Dialog : public QDialog
{
    Q_OBJECT
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    struct menu{

    };

private slots:
    void on_prevBtn_clicked();
    void on_nextBtn_clicked();
private:
    Ui::Dialog *ui;
    QGraphicsScene *scheme1;
    QGraphicsScene *scheme2;
    QGraphicsScene *scheme3;
    QGraphicsScene *scheme4;
    QGraphicsTextItem *stxt1;
    QGraphicsTextItem *stxt2;
    QGraphicsTextItem *stxt3;
    QGraphicsTextItem *stxt4;
    QGraphicsEllipseItem *ellipse;
    QGraphicsRectItem *rectangle;
    QGraphicsRectItem *rectangle2;
    QGraphicsRectItem *rectangle3;
    QGraphicsTextItem *text;
    int key;
    Tree *theTree;
    void getImageArt();
    void setPixMap(TreeNode *node);
    void nextScheme();
    String RGBtoHEX(int rNum, int gNum, int bNum);
    void RGBtoHSV(int rgb[]);
    void setSchemes(String hex1,String hex2, String hex3, String hex4);
    QImage cvMatToQImage( const cv::Mat &inMat );
    QPixmap cvMatToQPixmap( const cv::Mat &inMat );
    inline cv::Mat QImageToCvMat( const QImage &inImage, bool inCloneImageData = true );
    inline cv::Mat QPixmapToCvMat( const QPixmap &inPixmap, bool inCloneImageData = true );
    void outputNode(TreeNode& node);
};
#endif // DIALOG_H
