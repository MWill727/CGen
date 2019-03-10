//  Created by Malcolm H. Williams on 3/10/19.
//  Copyright (c) 2019 Malcolm Williams. All rights reserved.
//
#include "dialog.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   Dialog w;

    w.show();

    return a.exec();
}
