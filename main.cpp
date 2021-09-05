#include "wowclip.h"
#include "MyGlobalShortCut.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WowClip w;
    w.show();

    MyGlobalShortCut *shortcut_Ctrlq = new MyGlobalShortCut("Ctrl+q",&w);
    QObject::connect(shortcut_Ctrlq,SIGNAL(activated()),&w,SLOT(hotKey_Ctrlq()));
//    w.hide();
    return a.exec();
}
