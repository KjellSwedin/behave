#include "behave_qt_main_window.h"

#ifdef _MSC_VER
#pragma warning(push, 3)
#endif
#include <QtWidgets/QApplication>
#ifdef _MSC_VER
#pragma warning(pop)
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BehaveQtMainWindow mainWindow;
    mainWindow.show();
    return a.exec();
}
