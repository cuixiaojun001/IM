#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QDialog>

namespace Ui {
class ChatDialog;
}

class ChatDialog : public QDialog
{
    Q_OBJECT
signals:
    /**
     * @brief SIG_SendChatMsg 向好友发送聊天内容
     * @param id 好友的id
     * @param content 聊天内容buffer
     */
    void SIG_SendChatMsg(int id, QString content);
    /**
     * @brief SIG_SendFile 点击发送文件按钮向kernel发送文件信息信号
     * @param id    要发送给的好友的id
     * @param filename 文件名，包括路径
     * @param filesize 文件大小
     */
    void SIG_SendFile(int id, QString filename, uint64_t filesize);
public slots:
    void slot_setInfo(int id, const QString& name);
    void slot_setUserOffline();
    void slot_setChatMsg(QString content);
public:
    explicit ChatDialog(QWidget *parent = nullptr);
    ~ChatDialog();
private slots:
    void on_qb_sendMsg_clicked();
    void on_pb_sendFile_clicked();

private:
    Ui::ChatDialog *ui;
    int m_friendId;
    QString m_friendName;
};

#endif // CHATDIALOG_H
