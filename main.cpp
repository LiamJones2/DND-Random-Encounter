#include "Main.h"
#include <QtWidgets/QApplication>

namespace Window {
    DNDRandomEncounter* windowDNDRandomEncounter;
    QWindow* mainWindow;
}

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    DNDRandomEncounter w;
    w.show();
    Window::windowDNDRandomEncounter = &w;
    Window::mainWindow = w.windowHandle();
    return a.exec();
}