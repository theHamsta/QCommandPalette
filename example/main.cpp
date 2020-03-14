#include <QApplication>
#include <QCommandLineParser>

#include "MainWindow.hpp"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription(QCoreApplication::applicationName());
    parser.addHelpOption();
    parser.addVersionOption();
    // 	parser.addPositionalArgument( "file", QApplication::translate( "main.cpp", "Video file to open" ) );
    parser.process(app);

    MainWindow form;
    form.show();

    return app.exec();
}
