#include "Main.h"
#include <QtWidgets/QApplication>
#include <qsplashscreen.h>

namespace Window {
    DNDRandomEncounter* windowDNDRandomEncounter;
    QWindow* mainWindow;
}

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    QPixmap splashPixmap("DNDRandomEncountersLogo.png");
    QSplashScreen splash(splashPixmap);
    splash.show();
    DNDRandomEncounter w;
    w.show();

    QIcon appIcon("DNDRandomEncountersLogo.png");
    a.setWindowIcon(appIcon);
    Window::windowDNDRandomEncounter = &w;
    Window::mainWindow = w.windowHandle();
    splash.hide();
    
    return a.exec();
}