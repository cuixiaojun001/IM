#include "contactlistdialog.h"
#include "ui_contactlistdialog.h"
#include <QIcon>
#include "QDebug"
#include "QMessageBox"
ContactListDialog::ContactListDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ContactListDialog)
{
    ui->setupUi(this);
    setWindowTitle( "IM");
//    /*设置窗口最大化和最小化*/
//    Qt::WindowFlags windowFlag = this;
//    windowFlag |= Qt::WindowMinimizeButtonHint;
//    windowFlag |= Qt::WindowMaximizeButtonHint;
//    windowFlag |= Qt::WindowCloseButtonHint;
//    this.window
//    setWindowFlag();
    /*---------------------------------------*/
    m_layout = new QVBoxLayout; // 垂直布局的层
    m_layout->setContentsMargins( 0 , 0, 0 ,0 ); //左下右上距离外边框多远
    m_layout->setSpacing( 3 );//每个控件彼此的距离
    ui->widget_frienditem->setLayout(m_layout);
    m_menu = new QMenu(this);
    m_menu->addAction("添加好友");
    m_menu->addAction("系统设置");
    connect(m_menu, SIGNAL(triggered(QAction*)), this, SLOT(slot_dealMenu(QAction*)));

}

ContactListDialog::~ContactListDialog()
{
    delete ui;
}

void ContactListDialog::closeEvent(QCloseEvent *event)
{
    if (QMessageBox::question(this, "提示", "是否要退出?") == QMessageBox::Yes) {
        Q_EMIT SIG_offLine();
    }
}

void ContactListDialog::slot_addFriend(UserItem *item)
{
    m_layout->addWidget(item);
}

void ContactListDialog::slot_setInfo(QString username, int iconid = 1, QString feeling = "比较懒, 什么也没写")
{
    ui->label_username->setText(username);
    ui->lineEdit_feeling->setText(feeling);
    ui->pb_icon->setIcon(QIcon(QString(":/icon/%1.png").arg(iconid)));
}

void ContactListDialog::slot_dealMenu(QAction *action)
{
    qDebug() << __func__;
    if( action->text() == "添加好友" )
    {
        Q_EMIT SIG_addFriend();
    }else if( action->text() == "系统设置" )
    {
        //
    }
}

void ContactListDialog::on_pb_menu_clicked()
{
    qDebug() << __func__;
    QPoint p = QCursor::pos();
    QSize size = m_menu->sizeHint(); //菜单的绝对高度 -- 所有的项都弹出之后的高

    m_menu->exec( QPoint( p.x() , p.y() - size.height() )  );
}

