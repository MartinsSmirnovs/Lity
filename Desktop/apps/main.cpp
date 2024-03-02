#include <QApplication>
#include <lity/DynamicSettings.h>
#include <lity/LityLogic.h>
#include <lity/widgets/MainWindow.h>

int main( int argc, char* argv[] )
{
    QApplication app( argc, argv );

    DynamicSettings::instance( QApplication::applicationDirPath() + "/settings.ini", QCoreApplication::instance() );

    MainWindow w;
    w.show();

    const int returnCode = app.exec();

    return returnCode;
}
