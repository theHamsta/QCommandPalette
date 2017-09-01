#include <QtGui/QApplication>
#include "QCommandPalette.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QCommandPalette qcommandpalette;
    qcommandpalette.show();
    return app.exec();
}
