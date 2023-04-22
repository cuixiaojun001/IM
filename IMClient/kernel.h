#ifndef __KERNEL_H__
#define __KERNEL_H__

#include <QObject>

#include <map>
#include <functional>
#include <list>
#include <string>

#include "INetMediator.h"
#include "packdef.h"
#include "logindialog.h"
#include "contactlistdialog.h"
#include "chatdialog.h"

class Kernel : public QObject
{
    Q_OBJECT
public:
    Kernel();
    ~Kernel();
public:
//    static Kernel& getInstance() {
//        return kernel;
//    }
public:
    /**
     * @brief 开启服务器
     * @return 成功返回true; 失败返回false
    */
    bool startServer();
    /**
     * @brief 关闭服务器
    */
    void closeServer();
    /**
     * @brief 处理数据
     * @param lSendIP
     * @param buf
     * @param nLen
    */
 public slots:
    void slot_DealData(unsigned long lSendIP, const char* buf, int nLen);
    /**
     * @brief 处理登录回复
     * @param lSendIP
     * @param buf
     * @param nLen
    */
    void slot_LoginRs(unsigned long lSendIP, const char* buf, int nLen);
    /**
     * @brief 处理注册回复
     * @param lSendIP
     * @param buf
     * @param nLen
    */
    void slot_RegisterRs(unsigned long lSendIP, const char* buf, int nLen);
    /**
     * @brief slot_FriendInfoRq 获取好友信息请求
     * @param lSendIP
     * @param buf
     * @param nLen
     */
    void slot_FriendInfoRs(unsigned long lSendIP, const char* buf, int nLen);
    /**
     * @brief slot_ChatRq 好友发来聊天请求
     * @param lSendIP
     * @param buf
     * @param nLen
     */
    void slot_ChatRq(unsigned long lSendIP, const char *buf, int nLen);
    /**
     * @brief slot_ChatRs 自己发出的聊天内容的回复
     * @param lSendIP
     * @param buf
     * @param nLen
     */
    void slot_ChatRs(unsigned long lSendIP, const char *buf, int nLen);
    /**
     * @brief slot_addFriendRq 有其他用户发起添加好友声请
     * @param lSendIP
     * @param buf
     * @param nLen
     */
    void slot_addFriendRq(unsigned long lSendIP, const char* buf, int nLen);
    /**
     * @brief slot_addFriendRs 用户发起添加好友申请，服务器响应结果
     * @param lSendIP
     * @param buf
     * @param nLen
     */
    void slot_addFriendRs(unsigned long lSendIP, const char* buf, int nLen);

    void slot_DealFileInfoRq(unsigned long lSendIP, const char* buf, int nLen);

    void slot_DealFileInfoRs(unsigned long lSendIP, const char* buf, int nLen);

    void slot_DealFileBlockRq(unsigned long lSendIP, const char* buf, int nLen);

    void slot_DealFileBlockRs(unsigned long lSendIP, const char* buf, int nLen);
    /**
     * @brief slot_LoginCommit 登录提交事件
     * @param username 用户名
     * @param password 密码
     */
    void slot_LoginCommit(QString username, QString password);
    /**
     * @brief slot_RegisterCommit 注册提交事件
     * @param username 用户名
     * @param tel 电话号码
     * @param password 密码
     */
    void slot_RegisterCommit(QString username, QString tel, QString password);
    /**
     * @brief slot_userItemClicked 好友头像点击事件
     * @param uuid 好友唯一id
     */
    void slot_userItemClicked(int uuid);
    /**
     * @brief slot_SendChatMsg 聊天信息发送按钮点击事件
     * @param id
     * @param content
     */
    void slot_SendChatMsg(int id, QString content);
    /**
     * @brief slot_addFriendClicked 添加好友点击事件
     */
    void slot_addFriendClicked();
    /**
     * @brief slot_SendFile 发送文件
     * @param id 要发送给的好友id
     * @param filename 文件名，包括文件路径
     * @param filesize 文件大小
     */
    void slot_SendFile(int id, QString filename, uint64_t filesize);
    /**
     * @brief slot_DealOffineRq 处理好友下线请求
     * @param lSendIP
     * @param buf
     * @param nLen
     */
    void slot_DealOffineRq(unsigned long lSendIP, const char* buf, int nLen);
    /**
     * @brief slot_SendOffline 发送离线请求
     */
    void slot_SendOffline();
private:
    /**
     * @brief 设置函数映射
    */
    void setProtocolMap();
    /**
     * @brief Utf8字符集转GB2312
     * @param utf8 QString字符串
     * @param gbbuf char*字符串
     * @param nLen gbbuf大小
     */
    void Utf8ToGB2312(QString &utf8, char* gbbuf, int nLen);
    /**
     * @brief GB2312字符集转Utf8
     * @param gbbuf char* 字符串
     * @return QString字符串
     */
    QString GB2312ToUtf8(char* gbbuf);
    /**
     * @brief GetFileName 从文件路径中获取文件名
     * @param path 文件绝对路径
     * @return
     */
    std::string GetFileName(const char* path);

    /**
     * @brief DestroyInstance
     */
    void DestroyInstance();

private:
//    static Kernel kernel;
    std::map<int, std::function<void(unsigned long, const char*, int)> > m_deal_items;
    net::INetMediator* m_pClient;

    // UI对象指针
    LoginDialog *m_loginDialog;
    ContactListDialog* m_mainWnd;

    // 个人信息
    int m_uuid;
    QString m_username;
    int m_state;
    QString m_feeling;

    // 用户id与item的映射map
    std::map<int, UserItem*> m_mapIdToUserItem;
    /**
     * @brief m_mapIdToChatDialog 好友id与聊天dialog的映射map
     */
    std::map<int, ChatDialog*> m_mapIdToChatDialog;

    std::map<std::string, FileInfo*> m_mapFileIdToFileInfo;
};

#endif // !__KERNEL_H__



