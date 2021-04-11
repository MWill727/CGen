//  Created by Malcolm Williams on 3/10/19.
//  Copyright (c) 2019 Malcolm Williams. All rights reserved.
//
#include "dialog.h"
#include "ui_dialog.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/types_c.h"
#include <iostream>
#include "stdio.h"
#include <string.h>
#include "Tree.h"
#include <qlabel.h>
#include <QPushButton>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QTextCodec>
#include <QDir>
double Hue; //Global Hue
double Saturation;//Global Saturation
double Value;// Global Value
using namespace cv;
Dialog::Dialog(QWidget *parent) :QDialog(parent), ui(new Ui::Dialog)
{

      ui->setupUi(this);//Setup UI

      this->setWindowTitle("C-GEN \t \t \t \t \t \t \t \t \t \t (c) Malcolm H. Williams");
      key=0;//Global key equals zero
      theTree = 0;//Set Binary Tree to NULL
      theTree=new Tree();
      ui->lblOriginal->setScaledContents(true);//Scale Image to fit Qlabel dimensions

      /* For each image inside of folder assign path to Qstring then process and cluster image
      and add to binary tree*/
      foreach( const QString &imageName, QDir("/Users/378b/Documents/CGen/images").entryList(QDir::NoDotAndDotDot | QDir::Files))
      {
          ColorScheme nodeScheme[4];
           QString r ;

         r= QDir("/Users/378b/Documents/CGen/images").absolutePath()+"/"+imageName;//Concatenate absoulte path with relitive path inorder to get correct path of images   (MAY HAVE TO CHANGE PATH FOR CERATIN COMPUTERS THEN COMPILE)

        Mat src = imread(r.toStdString().c_str(),1);//load image into OpenCV matrix
         QPixmap pic= cvMatToQPixmap(src);//Convert CV image to QPIXMAP assign to variable

        //convert CV image into 3
        Mat samples(src.rows * src.cols, 3, CV_32F);
        for( int y = 0; y < src.rows; y++ )
            for( int x = 0; x < src.cols; x++ )
                for( int z = 0; z < 3; z++)
                    samples.at<float>(y + x*src.rows, z) = src.at<Vec3b>(y,x)[z];
        int clusterCount = 4; // number of clusters
        Mat labels;//data labels
        int attempts = 4; //number of attemps to cluster
        Mat centers; //centroids
        kmeans(samples, clusterCount, labels, TermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 10000, 0.0001), attempts, KMEANS_PP_CENTERS, centers );
        for (int i=0; i<=3; i++)
        {
        cv::Mat dominantColor = centers.row(i);//CENTER OF CLUSTER
          cv::Vec3d dominantColorVec1;//INTINILIZE 3D VECTOR
           dominantColorVec1[0] = (int)dominantColor.col(0).at<float>(0);//B
           dominantColorVec1[1] = (int)dominantColor.col(1).at<float>(0);//G
           dominantColorVec1[2] = (int)dominantColor.col(2).at<float>(0);//R

           nodeScheme[i].rgb[0]=dominantColorVec1[2];//R
           nodeScheme[i].rgb[1]=dominantColorVec1[1];//G
           nodeScheme[i].rgb[2]=dominantColorVec1[0];//B
            RGBtoHSV(nodeScheme[i].rgb);//Convert each rgb color space in binary node into HSV color space
           nodeScheme[i].hsv[0]=Hue; //H
           nodeScheme[i].hsv[1]=Saturation;//S
           nodeScheme[i].hsv[1]=Value;//V
           nodeScheme[i].hex=RGBtoHEX(nodeScheme[i].rgb[0],nodeScheme[i].rgb[1],nodeScheme[i].rgb[2]);//GET HEX CODE OF EACH COLOR SCHEME
        }
        ++key;//increment global key
       // cout<<key<<endl;
        theTree->Insert(nodeScheme,pic,key);//INSERT NODE INTO BINARY TREE
       // cout<<key<<endl;
  }
    key=2;
    setPixMap(theTree->getRoot());//SET UI WINDOW
}
Dialog::~Dialog()
{
    delete ui;
}



void Dialog::setPixMap(TreeNode *node)
{

   //Update and clear UI old contents
    ui->scheme1->update();
    ui->scheme2->update();
    ui->scheme3->update();
    ui->scheme4->update();
    ui->sText1->clear();
    ui->sText2->clear();
    ui->sText3->clear();
    ui->sText4->clear();
    ui->lblOriginal->setPixmap(node->qtPic);//get Image of binary tree node and set image to Qlabael
    //new GraphicsScene
    scheme1 = new QGraphicsScene(this);
    scheme2= new QGraphicsScene(this);
    scheme3= new QGraphicsScene(this);
    scheme4= new QGraphicsScene(this);
    ui->scheme1->setScene(scheme1);
    ui->scheme2->setScene(scheme2);
    ui->scheme3->setScene(scheme3);
    ui->scheme4->setScene(scheme4);

    QColor c1;
    QColor c2;
    QColor c3;
    QColor c4;
    // Get color scheme hex codes from binary tree node
    QString hex1 = QString::fromStdString(node->color[0].hex);
    QString hex2 = QString::fromStdString(node->color[1].hex);
    QString hex3 = QString::fromStdString(node->color[2].hex);
    QString hex4 = QString::fromStdString(node->color[3].hex);

   c1.setNamedColor(hex1);
   c2.setNamedColor(hex2);
   c3.setNamedColor(hex3);
   c4.setNamedColor(hex4);
   //make text background transparent
   ui->sText1->viewport()->setAutoFillBackground(false);
   ui->sText2->viewport()->setAutoFillBackground(false);
   ui->sText3->viewport()->setAutoFillBackground(false);
   ui->sText4->viewport()->setAutoFillBackground(false);
   //load hex string to text boxes
   ui->sText1->appendPlainText(hex1);
   ui->sText2->appendPlainText(hex2);
   ui->sText3->appendPlainText(hex3);
   ui->sText4->appendPlainText(hex4);
   //set colors scheme of binary tree node
   ui->scheme1->setBackgroundBrush(QBrush(c1, Qt::SolidPattern));
   ui->scheme2->setBackgroundBrush(QBrush(c2, Qt::SolidPattern));
   ui->scheme3->setBackgroundBrush(QBrush(c3, Qt::SolidPattern));
   ui->scheme4->setBackgroundBrush(QBrush(c4, Qt::SolidPattern));

}



void Dialog::on_prevBtn_clicked()
{
    if(key>1)//check if global key is greator than one
    {
    --key;//pre-decrement key
    TreeNode *nodee=0;//intizilize new node
    nodee=theTree->lookUp(key);//lookup previous node
    setPixMap(nodee);//setup UI based on inserted node
    }

}

void Dialog::on_nextBtn_clicked()
{
    if(key<=theTree->BTreeSize(theTree->getRoot()))//Check if key is greater than Tree size
    {
    TreeNode *nodee=0;//initilize new node
    nodee=theTree->lookUp(key);//lookup next node and assign to new node
    setPixMap(nodee);//setup new Ui based on new inserted node
    key++;//increment global key
    }
}


string Dialog::RGBtoHEX(int rNum, int gNum, int bNum)
{

    string result;
    result.append("#");// add # to beginning of hex string
    char r[255];//
    sprintf(r, "%.2X", rNum);//Compute #RR
    result.append(r );//Append RR to string

    char g[255];
    sprintf(g, "%.2X", gNum);//Compute #GG
    result.append(g );//Append GG to string

    char b[255];
    sprintf(b, "%.2X", bNum);// Computer #BB
    result.append(b );//Append BB to string

    return result;//return Hex
}

void Dialog::RGBtoHSV(int rgb[])
{

    int R = rgb[0];
    int G = rgb[1];
    int B = rgb[2];

    int MAX = max((max(R,G)),B);//Min. value of RGB
    int MIN = min((min(R,G)),B);//Max value of RGB
    Value = MAX/256*100; // Value of HSV is computed by getting max of rgb and mutiplying amount of colors by 100

    if(MAX==MIN){ // No color
        Hue = 0;
        Saturation = 0;
    }
    else{
        if(MAX == R) Hue = 60.0*(G-B)/(MAX-MIN) + 0; // between yellow & magenta
        else if(MAX == G) Hue = 60.0*(B-R)/(MAX-MIN) + 120.0;// between cyan & yellow
        else if(MAX == B) Hue = 60.0*(R-G)/(MAX-MIN) + 240.0;//between magenta & cyan
        if(Hue > 360.0) Hue = Hue - 360.0; // degrees
        else if(Hue < 0) Hue = Hue + 360.0; // degrees
        Saturation = (MAX-MIN)/MAX*100.0;  // degrees
    }
}


//CONVERION FUNCTIONS BELOW REFERENCED FROM http://asmaloney.com/2013/11/code/converting-between-cvmat-and-qimage-or-qpixmap
 QImage Dialog::cvMatToQImage( const cv::Mat &inMat )
  {
     switch ( inMat.type() )
     {
        // 8-bit, 4 channel
        case CV_8UC4:
        {
           QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB32 );

           return image;
        }

        // 8-bit, 3 channel
        case CV_8UC3:
        {
           QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB888 );

           return image.rgbSwapped();
        }

        // 8-bit, 1 channel
        case CV_8UC1:
        {
           static QVector<QRgb>  sColorTable;

           // only create our color table once
           if ( sColorTable.isEmpty() )
           {
              for ( int i = 0; i < 256; ++i )
                 sColorTable.push_back( qRgb( i, i, i ) );
           }

           QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_Indexed8 );

           image.setColorTable( sColorTable );

           return image;
        }

        default:
           qWarning() << "ASM::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
           break;
     }

     return QImage();
  }

  inline QPixmap Dialog::cvMatToQPixmap( const cv::Mat &inMat )
  {
     return QPixmap::fromImage( cvMatToQImage( inMat ) );
  }

