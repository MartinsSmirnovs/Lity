#include <QApplication>
#include <lity/logic/LityLogic.h>
#include <lity/widgets/MainWindow.h>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    MainWindow w;
    w.show();

    const int returnCode = app.exec();

    return returnCode;
}
