#include "wowclip.h"
#include "MyGlobalShortCut.h"
#include <QApplication>

//#include<cstring>


int main(int argc, char *argv[])
{

//    HWND hWnd = NULL;
//    OpenClipboard(hWnd);//打开剪贴板
//    qDebug()<<IsClipboardFormatAvailable(CF_BITMAP);
//    if ( IsClipboardFormatAvailable(CF_TEXT) )
//    {
//    HANDLE h = GetClipboardData(CF_TEXT);//获取剪切板数据

//    qDebug()<<CountClipboardFormats();
//    char* p = (char*)GlobalLock(h);

//    GlobalUnlock(h);
//    }
//    CloseClipboard();//关闭剪贴板

//    QString str = "abc";
//    std::string s = str.toStdString();
//    qDebug()<<s.find("7");
//    qDebug()<<s.npos;
    QApplication a(argc, argv);
    a.setStyleSheet("QListView{"
                    "border:1px solid #00BFFF;"
                    "outline:0;"
                    "}"
                    "QListView::item{"
                    "border:0px;"
                    "padding:5px 5px;"
                    "}"
                    "QListView::item:hover{"
                    "background:#DEF7FF;"
                    "border:1px solid #DC143C;"
                    "}"
                    "QListView::item:selected{"
                    "background:#00ACE6;"
                    "color:white;"
                    "}");
    WowClip w;
    w.hide();

    MyGlobalShortCut *shortcut_Ctrlq = new MyGlobalShortCut("Ctrl+q",&w);
    QObject::connect(shortcut_Ctrlq,SIGNAL(activated()),&w,SLOT(hotKey_Ctrlq()));
    w.setWindowIcon(QIcon("://mlogo5"));
//    w.hide();
    qDebug()<<"curr work dir:"+QCoreApplication::applicationDirPath();
    return a.exec();
}
