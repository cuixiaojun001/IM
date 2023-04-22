#include "useritem.h"
#include "ui_useritem.h"

UserItem::UserItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserItem)
{
    ui->setupUi(this);
}

UserItem::~UserItem()
{
    delete ui;
}
#include<QIcon>
#include<QBitmap>
void UserItem::slot_setInfo(int id, QString name, int state, int iconid, QString feeling)
{
    //设置变量
    m_id        = id;
    m_name      = name;
    m_state     = state;
    m_iconid    = iconid;
    m_feeling   = feeling;
        //设置ui
    ui->label_username->setText( m_name );
    ui->label_feeling->setText( m_feeling );
        //引入资源文件 以:起始
    QString path = QString(":/icon/%1.png").arg(m_iconid);
    //根据状态 不在为灰色
    //ui->pb_icon
    if( m_state )
    {
        ui->pb_icon->setIcon( QIcon( path ) );
    }else{
        QBitmap bmp;
        bmp.load( path );
        ui->pb_icon->setIcon( bmp ); // 添加位图是黑白的
    }
    this-> repaint(); // 立即重绘
}

void UserItem::slot_setOffline()
{
    m_state = 0;
    QString path = QString(":/tx/%1.png").arg(m_iconid);
    QBitmap bmp;
    bmp.load( path );
    ui->pb_icon->setIcon( bmp ); // 添加位图是黑白的

    this-> repaint(); // 立即重绘
}

void UserItem::on_pb_icon_clicked()
{
    Q_EMIT SIG_userItemClicked(m_id);
}

