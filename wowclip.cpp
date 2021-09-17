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
    //系统托盘事件
    connect(system_tray,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this,SLOT(on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason)));

    ui->listWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget->setVerticalScrollBar(new AnimatedScrollBar(ui->listWidget));
ui->listWidget->setStyleSheet(
            "QScrollBar:vertical"
            "{"
               "width:22px;"
               "background:rgba(0,0,0,0%);"
               "margin:5px,0px,5px,0px;"
               "padding-top:9px;"
               "padding-bottom:9px;"
            "}"
            "QScrollBar::handle:vertical"
            "{"
            "width:5px;"
            "background:rgba(0,0,0,25%);"
            " border-radius:4px;"
            "min-height:40px;"
            "}"
            "QScrollBar::handle:vertical:hover"
            "{"
            "width:15px;"
            "background:rgba(0,0,0,50%);"
            " border-radius:4px;"
            "min-height:40;"
            "}"
           "QScrollBar::add-line:vertical,"
           "QScrollBar::sub-line:vertical{"
           "height:0px;"
           "}"
           "QScrollBar::add-line,"
           "QScrollBar::add-page{"
           "}"
           "QScrollBar::sub-line,"
           "QScrollBar::sub-page{"
           "}"
           "QAbstractScrollArea::corner{"
           "background: transparent;"
           "border: none;"
           "}"
           "AnimatedScrollBar{"
           "qproperty-expandedWidth:15;"
           "}"
         );
    //    ui->listWidget->verticalScrollBar()->setStyleSheet("QScrollBar"
//                                                   "{"
//                                                   "width:22px;"
//                                                   "background:rgba(0,0,0,0%);"
//                                                   "margin:5px,0px,5px,0px;"
//                                                   "padding-top:9px;"
//                                                   "padding-bottom:9px;"
//                                                   "}"
//                                                   "QScrollBar::handle:vertical"
//                                                   "{"
//                                                   "width:5px;"
//                                                   "background:rgba(0,0,0,25%);"
//                                                   " border-radius:4px;"
//                                                   "min-height:40px;"
//                                                   "}"
//                                                   "QScrollBar::handle:vertical:hover"
//                                                   "{"
//                                                   "width:15px;"
//                                                   "background:rgba(0,0,0,50%);"
//                                                   " border-radius:4px;"
//                                                   "min-height:40;"
//                                                   "}"
//                                                   "QScrollBar::add-line:vertical"
//                                                   "{"
//                                                   "height:16px;width:15px;"

//                                                   "subcontrol-position:bottom;"
//                                                   "}"
//                                                   "QScrollBar::sub-line:vertical"
//                                                   "{"
//                                                   "height:16px;width:15px;"

//                                                   "subcontrol-position:top;"
//                                                   "}"
//                                                   "QScrollBar::add-line:vertical:hover"
//                                                   "{"
//                                                   "height:16px;width:15px;"

//                                                   "subcontrol-position:bottom;"
//                                                   "}"
//                                                   "QScrollBar::sub-line:vertical:hover"
//                                                   "{"
//                                                   "height:16px;width:15px;"

//                                                   "subcontrol-position:top;"
//                                                   "}"
//                                                   "QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical"
//                                                   "{"
//                                                   "background:rgba(0,0,0,10%);"
//                                                   "border-radius:4px;"
//                                                   "}");


//    this->move ((QApplication::desktop()->width() - this->width())/2+100,(QApplication::desktop()->height() - this->height())/2);
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
    if(mimeData->hasUrls()){
        qDebug()<<"url:"<<mimeData->urls()<<endl;
    }
    if(mimeData->hasImage()){
        qDebug()<<mimeData->imageData()<<endl;
        Dosth *widget = new Dosth(this);

        QPixmap pix = qvariant_cast<QPixmap>(mimeData->imageData());
        QString timeformat = QDateTime::currentDateTime().toString("yyyyMMddHHmmsszzz");

//        QString path = "D:/prj/my/qtobj/wowclip/save/";
        QString fn = workdir+timeformat+".jpg";
        pix.save(fn);
        widget->setText("<img src=\""+fn+"\">");
        QListWidgetItem *item_ui = new QListWidgetItem("",ui->listWidget);
        ui->listWidget->addItem(item_ui);
        ui->listWidget->setItemWidget(item_ui, widget);
        qDebug()<<"widget width"<<widget->width()<<"widget height"<<widget->height();
        item_ui->setSizeHint(QSize(widget->width(),widget->height()));
    }else if(mimeData->hasHtml()){
        QString res = dealImgUrl(mimeData->html());

//        saveData(res);
        Dosth *widget = new Dosth(this);
        widget->setText(res);
        QListWidgetItem *item_ui = new QListWidgetItem("",ui->listWidget);
        ui->listWidget->addItem(item_ui);
        ui->listWidget->setItemWidget(item_ui, widget);
//        ui->listWidget->setStyleSheet("QListWidget::Item:hover{border:1px solid #2A333C;}");
        qDebug()<<"widget width"<<widget->width()<<"widget height"<<widget->height();
//        qDebug()<<widget->styleSheet();
        item_ui->setSizeHint(QSize(widget->width(),widget->height()));
    }else /*if(mimeData->hasText())*/{
        qDebug()<<mimeData->text()<<endl;
        Dosth *widget = new Dosth(this);
        widget->setText(mimeData->text());
        QListWidgetItem *item_ui = new QListWidgetItem("",ui->listWidget);
        ui->listWidget->addItem(item_ui);
        ui->listWidget->setItemWidget(item_ui, widget);
        qDebug()<<"widget width"<<widget->width()<<"widget height"<<widget->height();
        item_ui->setSizeHint(QSize(widget->width(),widget->height()));
    }

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
         //必须前面空格，否则可能有其他属性比如 data-src=""
         std::string::size_type srcindex = stemp.find(" src=\"") ;
         if(srcindex==s.npos||srcindex>=endFlagIndex){
             continue;
         }
         std::string::size_type start = temp+4+srcindex+6;
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
             if(end>=temp+4+endFlagIndex) {
                 continue;
             }

             std::string result = s.substr(start,endFlagDbqte);
             QString resultq = QString::fromStdString(result);
             qDebug()<<resultq<<endl;

             QEventLoop loop ;
             QNetworkAccessManager *qManager = new QNetworkAccessManager(this);
             QNetworkRequest request;
//             resultq = "https://upload-images.jianshu.io/upload_images/4469129-fa3f54aecf6ef8a2.jpg";
             request.setUrl(QUrl(resultq));
             QNetworkReply *reply = qManager->get(request);
             connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
             loop.exec();

             QPixmap pix;
             QByteArray data = reply->readAll();
             pix.loadFromData(data);

//             QDateTime time = QDateTime::currentDateTime();   //获取当前时间
//             ulong timeT = time.toTime_t();   //将当前时间转为时间戳,有问题，精度丢失
             QString timeformat = QDateTime::currentDateTime().toString("yyyyMMddHHmmsszzz");
//             QString path = "D:/prj/my/qtobj/wowclip/save/";
             QString fn = workdir+timeformat+".jpg";
             qDebug()<<fn<<endl;
//             pix.save(fn, "JPG", 100);

             QDir  *folder=new QDir;

             bool exist = folder->exists(workdir);
             if(!exist){
                 bool ok = folder->mkpath(workdir);
                 if(ok){
                     qDebug()<<"save picture:create dir success";
                     pix.save(fn);
                 }else{
                     qDebug()<<"save picture:create dir error";
                 }
             }else{
                 pix.save(fn);
             }

             //替换
             s.replace(start,endFlagDbqte,fn.toStdString());

             //替换为本地路径后，重新算endFlagIndex
             stemp = s.substr(start);
             std::string::size_type endFlagIndex = stemp.find(">") ;

             position = start+endFlagIndex+1;
             qDebug()<<position<<endl;
          }else{
             position = start+endFlagIndex+1;
          }
    }
    return QString::fromStdString(s);
}

void WowClip:: saveData(const QString & data){
    //保存为TXT文件
    bool exist;
    QString fileName;
//     QString path = "D:/prj/my/qtobj/wowclip/save";
    QDir  *folder=new QDir;

    exist = folder->exists(workdir);

    if(!exist){
        bool ok = folder->mkpath(workdir);
        if(ok){
            qDebug()<<"create dir success";
//            QMessageBox::warning(this,tr("创建目录"),tr("创建成功!"));//添加提示方便查看是否成功创建
        }else{
            qDebug()<<"create dir error";
//            QMessageBox::warning(this,tr("创建目录"),tr("创建失败"));
        }
    }

    QDateTime time = QDateTime::currentDateTime();   //获取当前时间
    uint timeT = time.toTime_t();   //将当前时间转为时间戳
//    fileName = tr("C:/Users/Administrator/Desktop/wowclip/save/%1.txt").arg("数据");
    fileName = workdir+tr("%1.txt").arg("数据");

    QFile f(fileName);
    if(!f.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text)){//追加写入 添加结束符\r\n
//         QMessageBox::warning(this,tr("错误"),tr("打开文件失败,数据保存失败"));
        qDebug()<<"error,open file fail,data save fail";
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
    action_quit->setIcon(QIcon("://shutdown"));
    action_quit->setText(tr("退出"));
    menu_tray->addAction(action_quit);
    connect(action_quit, SIGNAL(triggered(bool)), qApp, SLOT(quit()));
    QAction *action_home = new QAction(this);
    action_home->setIcon(QIcon("://home"));
    action_home->setText(tr("主页"));
    menu_tray->addAction(action_home);
    connect(action_home, SIGNAL(triggered(bool)), this, SLOT(showHome()));
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
        qDebug()<<"color:"<<current->backgroundColor().rgb();
    }
    if(previous){
        qDebug()<<previous->backgroundColor();
    }
}

/**
 * @brief WowClip::on_closeButton_clicked
 */
void WowClip::on_closeButton_clicked()
{
    this->hide();
    isShow = false;
}
/**
 * @brief WowClip::showHome
 */
void WowClip:: showHome(){
    if(!isShow){
        this->show();
        isShow = true;
    }
}
/**
 * @brief 系统托盘点击事件
 * @param reason
 */
void WowClip::on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason){
    case QSystemTrayIcon::DoubleClick:
        this->showHome();
        break;
    default:
        break;
    }
}
//varAnima: 变量动画
//preferWidth: 临时记录动态的滚动条宽度
//_expandedWidth: 滚动条变粗后的宽度
AnimatedScrollBar::AnimatedScrollBar(QWidget *parent):
    QScrollBar(parent)
{
    varAnima = new QVariantAnimation(this); //创建动画
    varAnima->setDuration(150);
    connect(varAnima, &QVariantAnimation::valueChanged, this, [this](const QVariant &val){
        //valueChanged时，动画不一定在运行,需要约束
        if(varAnima->state() == QAbstractAnimation::Running)
        {
            preferWidth = val.toInt();
            updateGeometry();
        }
    });
}

QSize AnimatedScrollBar::sizeHint() const
{
    QSize tmp = QScrollBar::sizeHint(); //样式指定的宽度值，可以通过默认的sizeHint获取
    if(this->orientation() == Qt::Horizontal)
    {
        return QSize(tmp.width(), preferWidth); //仅改变宽度,实际由于布局的存在，长度值并不重要
    }
    return QSize(preferWidth, tmp.height());
}

void AnimatedScrollBar::setExpandedWidth(int val)
{
    _expandedWidth = val;
}

bool AnimatedScrollBar::event(QEvent *e)
{
    if(e->type() == QEvent::Polish)
    {
        //初始化preferWidth，也可以在第一次sizeHint()被调用时初始化
        QSize tmp = QScrollBar::sizeHint();
        preferWidth = 12;
//        preferWidth = this->orientation() == Qt::Horizontal ? tmp.height() : tmp.width();
    }
    else if(e->type() == QEvent::HoverEnter)
    {
        if(varAnima->state() == QAbstractAnimation::Running)
            varAnima->stop();

//        varAnima->setStartValue(preferWidth);
//        varAnima->setEndValue(_expandedWidth);
        varAnima->setStartValue(12);
        varAnima->setEndValue(22);
        varAnima->start();
    }
    else if(e->type() == QEvent::HoverLeave)
    {
        if(varAnima->state() == QAbstractAnimation::Running)
            varAnima->stop();

        QSize tmp = QScrollBar::sizeHint();
        int  normalWidth = this->orientation() == Qt::Horizontal ? tmp.height() : tmp.width();
//        varAnima->setStartValue(preferWidth);
//        varAnima->setEndValue(normalWidth);
        varAnima->setStartValue(22);
        varAnima->setEndValue(12);
        varAnima->start();
    }
    return QScrollBar::event(e);
}

