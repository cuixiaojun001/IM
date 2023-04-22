#include "chatdialog.h"
#include "ui_chatdialog.h"
#include <QTime>
#include <QFileDialog>

void ChatDialog::slot_setInfo(int id, const QString &name)
{
    m_friendId = id;
    m_friendName = name;
    setWindowTitle( QString("与[%1]的聊天").arg(name) );
}

void ChatDialog::slot_setUserOffline()
{
    ui->textBrowser_chat->append(QString("[%1] %2用户不在线").arg(m_friendName).arg(QTime::currentTime().toString("hh:mm:ss")));
}

void ChatDialog::slot_setChatMsg(QString content)
{
    ui->textBrowser_chat->append(QString("[%1] %2").arg(m_friendName).arg(QTime::currentTime().toString("hh:mm:ss")));
    ui->textBrowser_chat->append(content);
}

ChatDialog::ChatDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChatDialog)
{
    ui->setupUi(this);
}

ChatDialog::~ChatDialog()
{
    delete ui;
}

void ChatDialog::on_qb_sendMsg_clicked()
{
    // 获取发送框信息
    QString content = ui->textEdit_chat->toPlainText(); // 不带格式纯文本
    if (content.isEmpty()) return;
    content = ui->textEdit_chat->toHtml(); // 附带文本格式
    ui->textEdit_chat->clear(); // 清除发送框信息
    // 将自己的聊天信息显示到Browser上
    ui->textBrowser_chat->append(QString("[我] %1").arg(QTime::currentTime().toString("hh:mm:ss")));
    ui->textBrowser_chat->append(content);
    Q_EMIT SIG_SendChatMsg(m_friendId, content);
}


void ChatDialog::on_pb_sendFile_clicked()
{
    qDebug() << __func__;
    QString fileName = QFileDialog::getOpenFileName(this, "打开文件");
    if(!fileName.isEmpty()) { // 用户选择了某个文件
        // ui->pb_sendFile->setEnabled(true); // 可以按下发送
        // 可以发送
        QFile* selectedFile = new QFile(fileName);
        if( !selectedFile->open(QFile::ReadOnly)) {
            qDebug() << "打开用户想要传输的文件失败";
            return;
        }
        uint64_t filesize = selectedFile->size();
        Q_EMIT SIG_SendFile(m_friendId, fileName, filesize);
    }
}

