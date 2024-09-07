#include "binplorer.h"

#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    BinPlorer w;
    w.setWindowTitle("BinPlorer");

    QIcon icon(":/bp_icon_img/BIN.png");
    w.setWindowIcon(icon);

    w.show();
    return a.exec();
}
