#include "wowclip.h"
#include "ui_wowclip.h"

WowClip::WowClip(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WowClip)
{

    ui->setupUi(this);
    connect(board, SIGNAL(changed(QClipboard::Mode)), this, SLOT(listenClipChanged(QClipboard::Mode)));
    setWindowFlags(
                Qt::Tool|
                Qt::NoDropShadowWindowHint
                |Qt::WindowStaysOnTopHint
                |Qt::WindowTitleHint
                |Qt::WindowSystemMenuHint
                |Qt::WindowCloseButtonHint
                |Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

//    setWindowOpacity(0.85);
    if(!QSystemTrayIcon::isSystemTrayAvailable())
        return;
    createSysTrayActions();
    system_tray ->setToolTip(tr("WowClip 1.0"));
    system_tray ->setIcon(QIcon("://mlogo5"));
    system_tray->setContextMenu(menu_tray);

    system_tray->show();

//    addItem();
//    system_tray->showMessage(tr("wowclip"),QString(tr("wowclip已启动")));
}
/**
 * @brief WowClip::listenClipChanged
 * 监听剪贴板变化
 */
void WowClip::listenClipChanged(QClipboard::Mode mode_){
    if(mode_!=mode)return;
    qDebug()<<"clip change";
    mimeData = board->mimeData();
    qDebug()<<mimeData;

    if(mimeData->hasText()){
        qDebug()<<mimeData->text()<<endl;
    }
    if(mimeData->hasImage()){
        qDebug()<<mimeData->imageData()<<endl;
    }
    if(mimeData->hasUrls()){
        qDebug()<<"url:"<<mimeData->urls()<<endl;
    }
    if(mimeData->hasHtml()){
        qDebug()<<"html:"<<mimeData->html()<<endl;
        dealImgUrl(mimeData->html());
//        saveData(mimeData->html());
        Dosth *widget = new Dosth(this);
        widget->setText(mimeData->html());
        QListWidgetItem *item_ui = new QListWidgetItem("",ui->listWidget);
        ui->listWidget->addItem(item_ui);
        ui->listWidget->setItemWidget(item_ui, widget);
        qDebug()<<"widget width"<<widget->width()<<"widget height"<<widget->height();
        item_ui->setSizeHint(QSize(widget->width(),widget->height()));
    }
//    QImage image = qvariant_cast<QImage>(mimeData->imageData());
//    qDebug()<<"image:"<<image;
}

void WowClip:: addItem(){
    Dosth *widget = new Dosth(this);
    QListWidgetItem *item_ui = new QListWidgetItem("",ui->listWidget);
    ui->listWidget->addItem(item_ui);
    ui->listWidget->setItemWidget(item_ui, widget);
    qDebug()<<"widget宽度"<<widget->width()<<"widget高度"<<widget->height();
    item_ui->setSizeHint(QSize(widget->width(),widget->height()));
}
void WowClip::slot_replyFinished(QNetworkReply* reply)
{
    QPixmap pix;
    QByteArray data = reply->readAll();
    pix.loadFromData(data, "JPG");

    QDateTime time = QDateTime::currentDateTime();   //获取当前时间
    int timeT = time.toTime_t();   //将当前时间转为时间戳
    QString path = "C:/Users/Administrator/Desktop/wowclip/save/";
    QString fn = path+timeT+".jpg";
    pix.save(fn, "JPG", 100);
    //ui->textEdit->append(" src=c://tmp1.jpg>");
}


//void WowClip::setNetworkPic(const QString &szUrl)
//{
//    QUrl url(szUrl);
//    QNetworkAccessManager manager;
//    QEventLoop loop;

//    // qDebug() << "Reading picture form " << url;
//    QNetworkReply *reply = manager.get(QNetworkRequest(url));
//    //请求结束并下载完成后，退出子事件循环
//    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
//    //开启子事件循环
//    loop.exec();

//    QByteArray jpegData = reply->readAll();
//    QPixmap pixmap;
//    pixmap.loadFromData(jpegData);
//    setPixmap(pixmap); // 你在QLabel显示图片
//}



QString WowClip::dealImgUrl(const QString &str){

        std::string s = str.toStdString();
    std::string::size_type position=0;
//    std::string s = "<img alt=\"enter\"src=\"https://1.png\"     loading=\"lazy\" style=\"margin: 0px; padding: 0px; border: 0px; max-width: 700px; height: auto;\"></p>";
    std::string des = "<img";
    int idx=1;
    while ((position=s.find(des,position))!=s.npos) {
        qDebug()<<" '<img' position "<<idx<<" : "<<position<<endl;
        std::string::size_type temp = position;
         std::string stemp = s.substr(temp+4);
         std::string::size_type endFlagIndex = stemp.find(">") ;
         if(endFlagIndex==s.npos){
             //找不到img标签结束符号
             break;
         }
         std::string::size_type srcindex = stemp.find("src=\"") ;
         if(srcindex==s.npos||srcindex>=endFlagIndex){
             continue;
         }
         std::string::size_type start = temp+4+srcindex+5;
         std::string ftp = "ftp://";
          std::string ftps = "ftps://";
          std::string http = "http://";
          std::string https = "https://";
          stemp = s.substr(start,8);
          if(stemp.find(ftp)!=stemp.npos||stemp.find(ftps)!=stemp.npos
                  ||stemp.find(http)!=stemp.npos||stemp.find(https)!=stemp.npos){
             stemp = s.substr(start);
             std::string::size_type endFlagDbqte = stemp.find("\"");
             if(endFlagDbqte==stemp.npos){
                 break;
             }
             std::string::size_type end = start + endFlagDbqte;
             if(end>=endFlagIndex) {
                 continue;
             }

             std::string result = s.substr(start,endFlagDbqte);
             QString resultq = QString::fromStdString(result);
             qDebug()<<resultq<<endl;

             QUrl url(resultq);
             QNetworkAccessManager *manager = new QNetworkAccessManager(this);
             QEventLoop loop;
             QNetworkReply *reply = manager->get(QNetworkRequest(url));
             //请求结束并下载完成后，退出子事件循环
             QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
             //开启子事件循环
             loop.exec();

             QPixmap pix;
             QByteArray data = reply->readAll();
             pix.loadFromData(data, "JPG");

             QDateTime time = QDateTime::currentDateTime();   //获取当前时间
             int timeT = time.toTime_t();   //将当前时间转为时间戳
             QString path = "C:/Users/Administrator/Desktop/wowclip/save/";
             QString fn = path+timeT+".jpg";
             pix.save(fn, "JPG", 100);

             //替换
             s.replace(start,endFlagDbqte,fn.toStdString());

             //替换为本地路径后，重新算endFlagIndex


             position = temp+4+endFlagIndex+1;
             qDebug()<<position<<endl;
          }else{
             position = temp+4+endFlagIndex+1;
          }
    }
}

void WowClip:: saveData(const QString & data){
    //保存为TXT文件
    bool exist;
    QString fileName;
    QDir *folder = new QDir;
    exist = folder->exists("C:/Users/Administrator/Desktop/wowclip/save");

    if(!exist){//不存在就创建
        bool ok = folder->mkdir("C:/Users/Administrator/Desktop/wowclip/save");
        if(ok){
            qDebug()<<"创建目录,创建成功";
//            QMessageBox::warning(this,tr("创建目录"),tr("创建成功!"));//添加提示方便查看是否成功创建
        }else{
            qDebug()<<"创建目录,创建失败";
//            QMessageBox::warning(this,tr("创建目录"),tr("创建失败"));
        }
    }

    QDateTime time = QDateTime::currentDateTime();   //获取当前时间
    int timeT = time.toTime_t();   //将当前时间转为时间戳
    fileName = tr("C:/Users/Administrator/Desktop/wowclip/save/%1.jpg").arg(timeT);

    QFile f(fileName);
    if(!f.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text)){//追加写入 添加结束符\r\n
//         QMessageBox::warning(this,tr("错误"),tr("打开文件失败,数据保存失败"));
        qDebug()<<"错误,打开文件失败,数据保存失败";
        return ;
    }else{
        QTextStream stream(&f);
           stream<<data<<"\n";
    }
    f.close();
}


/**
创建系统托盘菜单动作*/
void WowClip::createSysTrayActions()
{

    QAction *action_quit = new QAction(this);

    action_quit->setIcon(QIcon("://out"));

    action_quit->setText(tr("退出"));

    menu_tray->addAction(action_quit);

    connect(action_quit, SIGNAL(triggered(bool)), qApp, SLOT(quit()));
}
void WowClip:: hotKey_Ctrlq( ){
    if  (isShow){
        this->hide();
        isShow = false;
    }else{
        this->show();
        isShow = true;
    }
    emit ;
}


WowClip::~WowClip()
{
    delete ui;
}
void WowClip::mousePressEvent(QMouseEvent *event)
{
    mMoveing = true;
    mMovePosition = event->globalPos() - pos();
    event->accept();
}

void WowClip::mouseMoveEvent(QMouseEvent *event)
{
    if (mMoveing && (event->buttons() && Qt::LeftButton)
            && (event->globalPos()-mMovePosition).manhattanLength() > QApplication::startDragDistance())
    {
        move(event->globalPos()-mMovePosition);
        mMovePosition = event->globalPos() - pos();
    }
    event->accept();
}

void WowClip::mouseReleaseEvent(QMouseEvent *event)
{
    mMoveing = false;
}

void WowClip::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if(current){
        qDebug()<<"颜色"<<current->backgroundColor().rgb();
    }
    if(previous){
        qDebug()<<previous->backgroundColor();
    }
}

