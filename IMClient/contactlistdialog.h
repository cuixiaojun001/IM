#ifndef CONTACTLISTDIALOG_H
#define CONTACTLISTDIALOG_H

#include <QDialog>
#include <QMenu>
#include <QAction>
#include <QVBoxLayout>
#include "useritem.h"
namespace Ui {
class ContactListDialog;
}

class ContactListDialog : public QDialog
{
    Q_OBJECT
signals:
    void SIG_addFriend();
    void SIG_offLine();
public:
    explicit ContactListDialog(QWidget *parent = nullptr);
    ~ContactListDialog();

    /**
     * @brief closeEvent 重写父类虚函数, 窗口关闭事件
     * @param event
     */
    void closeEvent(QCloseEvent* event) override;
public slots:
    void slot_addFriend(UserItem* item);
    void slot_setInfo(QString username, int iconid, QString feeling);

private slots:
    void on_pb_menu_clicked();
    void slot_dealMenu(QAction* action);
private:
    Ui::ContactListDialog *ui;
    QVBoxLayout* m_layout;
    QMenu* m_menu;
};

#endif // CONTACTLISTDIALOG_H
