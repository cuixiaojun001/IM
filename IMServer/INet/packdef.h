#pragma once
#include <stdint.h>
#include <cstdio>
#include <memory.h>

#define _DEF_TCP_PORT (43232)
#define _DEF_SERVER_IP ("10.56.60.144")

#define _MAX_SIZE	(40)
#define _DEF_CONTENT_SIZE (1024)

// 协议头
#define _DEF_PROTOCOL_BASE (100)
#define _DEF_PROTOCOL_COUNT (100)

// 注册
#define _DEF_PACK_REGISTER_RQ	(_DEF_PROTOCOL_BASE + 0 )
#define _DEF_PACK_REGISTER_RS	(_DEF_PROTOCOL_BASE + 1 )
//登录
#define _DEF_PACK_LOGIN_RQ	(_DEF_PROTOCOL_BASE + 2 )
#define _DEF_PACK_LOGIN_RS	(_DEF_PROTOCOL_BASE + 3 )
//好友信息
#define _DEF_PACK_FRIEND_INFO	(_DEF_PROTOCOL_BASE + 4 )
//添加好友
#define _DEF_PACK_ADDFRIEND_RQ	(_DEF_PROTOCOL_BASE + 5 )
#define _DEF_PACK_ADDFRIEND_RS	(_DEF_PROTOCOL_BASE + 6 )
//聊天
#define _DEF_PACK_CHAT_RQ	(_DEF_PROTOCOL_BASE + 7 )
#define _DEF_PACK_CHAT_RS	(_DEF_PROTOCOL_BASE + 8 )
//离线
#define _DEF_PACK_OFFLINE_RQ	(_DEF_PROTOCOL_BASE + 9 )
/*文件传输*/ 
// 文件信息
#define _DEF_PROTOCOL_FILE_INFO_RQ (_DEF_PROTOCOL_BASE + 10)
#define _DEF_PROTOCOL_FILE_INFO_RS (_DEF_PROTOCOL_BASE + 11)
// 文件块
#define _DEF_PROTOCOL_FILE_BLOCK_RQ (_DEF_PROTOCOL_BASE + 12)
#define _DEF_PROTOCOL_FILE_BLOCK_RS (_DEF_PROTOCOL_BASE + 13)
// 最大文件路径长度
#define _MAX_FILE_PATH_SIZE (512)
// 最大文件大小
#define _DEF_FILE_CONTENT_SIZE (8*1024)

//返回的结果
//注册请求的结果
#define user_is_exist		(0)
#define register_success	(1)
//登录请求的结果
#define user_not_exist		(0)
#define password_error		(1)
#define login_success		(2)
//添加好友的结果
#define no_this_user		(0)
#define user_refuse			(1)
#define user_offline		(2)
#define add_success			(3)

//协议结构


/**
 * @brief 注册请求块
*/
typedef struct STRU_REGISTER_RQ
{
    typedef int PackType;
    STRU_REGISTER_RQ() :type(_DEF_PACK_REGISTER_RQ)
    {
        memset(tel, 0, sizeof(tel));
        memset(username, 0, sizeof(username));
        memset(password, 0, sizeof(password));
    }
    //需要手机号码 , 密码, 昵称

    /**
     * @brief 数据包类型：_DEF_PACK_REGISTER_RQ
    */
    PackType type;
    /**
     * @brief 电话号码
    */
    char tel[_MAX_SIZE];
    /**
     * @brief 用户名
    */
    char username[_MAX_SIZE];
    /**
     * @brief 用户密码
    */
    char password[_MAX_SIZE];

}STRU_REGISTER_RQ;

/**
 * @brief 注册回复块
*/
typedef struct STRU_REGISTER_RS
{
    typedef int PackType;
    //回复结果
    STRU_REGISTER_RS() : type(_DEF_PACK_REGISTER_RS), result(register_success)
    {
    }
    /**
     * @brief 数据包类型：_DEF_PACK_REGISTER_RS
    */
    PackType type;
    /**
     * @brief 回复结果
    */
    int result;

}STRU_REGISTER_RS;


/**
 * @brief 登录请求块
*/
typedef struct STRU_LOGIN_RQ
{
    typedef int PackType;
    //登录需要: 手机号 密码
    STRU_LOGIN_RQ() :type(_DEF_PACK_LOGIN_RQ)
    {
        memset(tel, 0, sizeof(tel));
        memset(password, 0, sizeof(password));
    }
    /**
     * @brief 数据包类型：_DEF_PACK_LOGIN_RQ
    */
    PackType type;
    /**
     * @brief 电话号码
    */
    char tel[_MAX_SIZE];
    /**
     * @brief 用户名
    */
    char username[_MAX_SIZE];
    /**
     * @brief 用户密码
    */
    char password[_MAX_SIZE];

}STRU_LOGIN_RQ;

/**
 * @brief 登录回复块
*/
typedef struct STRU_LOGIN_RS
{
    typedef int PackType;
    // 需要 结果 , 用户的id
    STRU_LOGIN_RS() : type(_DEF_PACK_LOGIN_RS), result(login_success), userid(0)
    {
    }
    /**
     * @brief 数据包类型：_DEF_PACK_REGISTER_RS
    */
    PackType type;
    /**
     * @brief 回复结果
    */
    int result;
    /**
     * @brief 登录用户的uuid
    */
    int userid;

}STRU_LOGIN_RS;

/**
 * @brief 好友信息块
 * @details 包括自身
*/
typedef struct STRU_FRIEND_INFO
{
    typedef int PackType;
    STRU_FRIEND_INFO() :type(_DEF_PACK_FRIEND_INFO), uuid(0), iconid(0), state(0)
    {
        memset(username, 0, sizeof(username));
        memset(feeling, 0, sizeof(feeling));
    }
    //需要 用户id 头像id 昵称 签名 状态--是否在线
    /**
     * @brief 数据包类型：_DEF_PACK_FRIEND_INFO
    */
    PackType type;
    /**
     * @brief 用户唯一id
    */
    int uuid;
    /**
     * @brief 头像id
    */
    int iconid;
    /**
     * @brief 用户状态(在线|离线)
    */
    int state;
    /**
     * @brief 用户名
    */
    char username[_MAX_SIZE];
    /**
     * @brief 个性签名
    */
    char feeling[_MAX_SIZE];

}STRU_FRIEND_INFO;


/**
 * @brief 添加好友请求块
*/
typedef struct STRU_ADD_FRIEND_RQ
{
    typedef int PackType;
    // 如果用户1 添加用户2 为好友 需要 用户1 id 用户1 名字 ,用户2的名字
    STRU_ADD_FRIEND_RQ() :type(_DEF_PACK_ADDFRIEND_RQ), userid(0)
    {
        memset(userName, 0, sizeof(userName));
        memset(friendName, 0, sizeof(friendName));
    }
    /**
     * @brief 数据包类型: _DEF_PACK_ADDFRIEND_RQ
    */
    PackType type;
    /**
     * @brief 用户唯一id
    */
    int userid;
    /**
     * @brief 用户名
    */
    char userName[_MAX_SIZE];
    /**
     * @brief 好友名
    */
    char friendName[_MAX_SIZE];

}STRU_ADD_FRIEND_RQ;

/**
 * @brief 添加好友回复块
*/
typedef struct STRU_ADD_FRIEND_RS
{
    typedef int PackType;
    STRU_ADD_FRIEND_RS() :type(_DEF_PACK_ADDFRIEND_RS), userid(0), friendid(0), result(add_success)
    {
        memset(friendName, 0, sizeof(friendName));
    }
    //如果用户1 添加用户2 需要 用户1id  用户2 id 用户2的名字 结果
    /**
     * @brief 数据包类型: _DEF_PACK_ADDFRIEND_RS
    */
    PackType type;
    /**
     * @brief 用户唯一id
    */
    int userid; // 用户1
    /**
     * @brief 好友id
    */
    int friendid; // 用户2
    /**
     * @brief 回复结果
    */
    int result;
    /**
     * @brief 好友用户名
    */
    char friendName[_MAX_SIZE];

}STRU_ADD_FRIEND_RS;

/**
 * @brief 聊天内容请求块
*/
typedef struct STRU_CHAT_RQ
{
    typedef int PackType;
    STRU_CHAT_RQ() :type(_DEF_PACK_CHAT_RQ), userid(0), friendid(0)
    {
        memset(content, 0, _DEF_CONTENT_SIZE);
    }
    // 谁发给谁 服务器转发  用户1 id 用户2 id 发的内容
    /**
     * @brief 数据包类型: _DEF_PACK_CHAT_RQ
    */
    PackType type;
    /**
     * @brief 用户唯一id
    */
    int userid;
    /**
     * @brief 好友id
    */
    int friendid;
    /**
     * @brief 聊天内容
    */
    char content[_DEF_CONTENT_SIZE];

}STRU_CHAT_RQ;

/**
 * @brief 聊天内容回复块
*/
typedef struct STRU_CHAT_RS
{
    typedef int PackType;
    STRU_CHAT_RS() :type(_DEF_PACK_CHAT_RS), userid(0), friendid(0), result(0) {}
    /**
     * @brief 数据包类型: _DEF_PACK_CHAT_RS
    */
    PackType type;
    /**
     * @brief 用户唯一id
    */
    int userid;
    /**
     * @brief 好友id
    */
    int friendid; //方便找是哪个人不在线
    /**
     * @brief 回复结果
    */
    int result;

}STRU_CHAT_RS;

/**
 * @brief 离线通知块
*/
typedef struct STRU_OFFLINE {
    typedef int PackType;
    STRU_OFFLINE() : type(_DEF_PACK_OFFLINE_RQ) {}
    /**
     * @brief 数据包类型: _DEF_PACK_OFFLINE_RQ
    */
    PackType type;
    /**
     * @brief 用户唯一id
    */
    int uuid;
}STRU_OFFLINE;

// 文件传输协议
/**
 * @brief 文件信息请求
*/
struct STRU_FILE_INFO_RQ {
    typedef int PackType;
    STRU_FILE_INFO_RQ() : nType(_DEF_PROTOCOL_FILE_INFO_RQ), nFileSize(0), uuid(0), friendid(0) {
        memset(szFileId, 0, _MAX_FILE_PATH_SIZE);
        memset(szFileName, 0, _MAX_FILE_PATH_SIZE);
    }
    /**
     * @brief 数据包类型: _DEF_PROTOCOL_FILE_INFO_RQ
    */
    PackType nType;
    /**
     * @brief 文件唯一id
    */
    char szFileId[_MAX_FILE_PATH_SIZE];
    /**
     * @brief 文件名
    */
    char szFileName[_MAX_FILE_PATH_SIZE];
    /**
     * @brief 文件大小
    */
    uint64_t nFileSize;
    /**
     * @brief 用户唯一id
    */
    int uuid;
    /**
     * @brief 好友id
    */
    int friendid;
};

#define _file_accept (0)
#define _file_refuse (1)
/**
 * @brief 文件信息回复
*/
struct STRU_FILE_INFO_RS 
{
    typedef int PackType;
    STRU_FILE_INFO_RS() : nType(_DEF_PROTOCOL_FILE_INFO_RS), nResult(_file_accept), uuid(0), friendid(0) {
        memset(szFileId, 0, _MAX_FILE_PATH_SIZE);
    }
    /**
     * @brief 数据包类型: _DEF_PROTOCOL_FILE_INFO_RS
    */
    PackType nType;
    /**
     * @brief 文件唯一id
    */
    char szFileId[_MAX_FILE_PATH_SIZE];
    /**
     * @brief 回复结果
    */
    int nResult;
    /**
     * @brief 用户唯一id
    */
    int uuid;
    /**
     * @brief 好友id
    */
    int friendid;
};

/**
 * @brief 文件块请求
*/
struct STRU_FILE_BLOCK_RQ
{
    typedef int PackType;
    STRU_FILE_BLOCK_RQ() : nType(_DEF_PROTOCOL_FILE_BLOCK_RQ), nBlockSize(0), uuid(0), friendid(0) {
        memset(szFileId, 0, _MAX_FILE_PATH_SIZE);
        memset(szFileContent, 0, _DEF_FILE_CONTENT_SIZE);
    }
    /**
     * @brief 数据包类型: _DEF_PROTOCOL_FILE_BLOCK_RQ
    */
    PackType nType;
    /**
     * @brief 文件唯一id
    */
    char szFileId[_MAX_FILE_PATH_SIZE];
    /**
     * @brief 文件块内容
    */
    char szFileContent[_DEF_FILE_CONTENT_SIZE];
    /**
     * @brief 文件块大小
    */
    uint64_t nBlockSize;
    /**
     * @brief 用户唯一id
    */
    int uuid;
    /**
     * @brief 好友id
    */
    int friendid;
};

#define _file_block_recv_success (0)
#define _file_block_recv_fail    (1)
/**
 * @brief 文件块接受回复
*/
struct STRU_FILE_BLOCK_RS
{
    typedef int PackType;
    STRU_FILE_BLOCK_RS() :nType(_DEF_PROTOCOL_FILE_BLOCK_RS), nResult(_file_block_recv_success), uuid(0), friendid(0) {
        memset(szFileId, 0, _MAX_FILE_PATH_SIZE);
    }
    /**
     * @brief 数据包类型: _DEF_PROTOCOL_FILE_BLOCK_RS
    */
    PackType nType;
    /**
     * @brief 文件唯一id
    */
    char szFileId[_MAX_FILE_PATH_SIZE];
    /**
     * @brief 回复结果
    */
    int nResult;
    /**
     * @brief 用户唯一id
    */
    int uuid;
    /**
     * @brief 好友id
    */
    int friendid;
};

/**
 * @brief 文件信息
*/
struct FileInfo
{
    FileInfo() : nPos(0), nFileSize(0), pFile(nullptr) {
        memset(szFileId, 0, _MAX_FILE_PATH_SIZE);
        memset(szFileName, 0, _MAX_FILE_PATH_SIZE);
        memset(szFilePath, 0, _MAX_FILE_PATH_SIZE);
    }
    /**
     * @brief 文件唯一id
    */
    char szFileId[_MAX_FILE_PATH_SIZE];
    /**
     * @brief 文件名
    */
    char szFileName[_MAX_FILE_PATH_SIZE];
    /**
     * @brief 文件所在路径
    */
    char szFilePath[_MAX_FILE_PATH_SIZE];
    /**
     * @brief 文件已经接受的字节数
    */
    uint64_t nPos;
    /**
     * @brief 文件大小
    */
    uint64_t nFileSize;
    /**
     * @brief 文件指针
    */
    FILE* pFile;
};