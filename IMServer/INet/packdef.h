#pragma once
#include <stdint.h>
#include <cstdio>
#include <memory.h>

#define _DEF_TCP_PORT (43232)
#define _DEF_SERVER_IP ("10.56.60.144")

#define _MAX_SIZE	(40)
#define _DEF_CONTENT_SIZE (1024)

// Э��ͷ
#define _DEF_PROTOCOL_BASE (100)
#define _DEF_PROTOCOL_COUNT (100)

// ע��
#define _DEF_PACK_REGISTER_RQ	(_DEF_PROTOCOL_BASE + 0 )
#define _DEF_PACK_REGISTER_RS	(_DEF_PROTOCOL_BASE + 1 )
//��¼
#define _DEF_PACK_LOGIN_RQ	(_DEF_PROTOCOL_BASE + 2 )
#define _DEF_PACK_LOGIN_RS	(_DEF_PROTOCOL_BASE + 3 )
//������Ϣ
#define _DEF_PACK_FRIEND_INFO	(_DEF_PROTOCOL_BASE + 4 )
//��Ӻ���
#define _DEF_PACK_ADDFRIEND_RQ	(_DEF_PROTOCOL_BASE + 5 )
#define _DEF_PACK_ADDFRIEND_RS	(_DEF_PROTOCOL_BASE + 6 )
//����
#define _DEF_PACK_CHAT_RQ	(_DEF_PROTOCOL_BASE + 7 )
#define _DEF_PACK_CHAT_RS	(_DEF_PROTOCOL_BASE + 8 )
//����
#define _DEF_PACK_OFFLINE_RQ	(_DEF_PROTOCOL_BASE + 9 )
/*�ļ�����*/ 
// �ļ���Ϣ
#define _DEF_PROTOCOL_FILE_INFO_RQ (_DEF_PROTOCOL_BASE + 10)
#define _DEF_PROTOCOL_FILE_INFO_RS (_DEF_PROTOCOL_BASE + 11)
// �ļ���
#define _DEF_PROTOCOL_FILE_BLOCK_RQ (_DEF_PROTOCOL_BASE + 12)
#define _DEF_PROTOCOL_FILE_BLOCK_RS (_DEF_PROTOCOL_BASE + 13)
// ����ļ�·������
#define _MAX_FILE_PATH_SIZE (512)
// ����ļ���С
#define _DEF_FILE_CONTENT_SIZE (8*1024)

//���صĽ��
//ע������Ľ��
#define user_is_exist		(0)
#define register_success	(1)
//��¼����Ľ��
#define user_not_exist		(0)
#define password_error		(1)
#define login_success		(2)
//��Ӻ��ѵĽ��
#define no_this_user		(0)
#define user_refuse			(1)
#define user_offline		(2)
#define add_success			(3)

//Э��ṹ
//ע��
typedef struct STRU_REGISTER_RQ
{
    typedef int PackType;
    STRU_REGISTER_RQ() :type(_DEF_PACK_REGISTER_RQ)
    {
        memset(tel, 0, sizeof(tel));
        memset(username, 0, sizeof(username));
        memset(password, 0, sizeof(password));
    }
    //��Ҫ�ֻ����� , ����, �ǳ�
    PackType type;
    char tel[_MAX_SIZE];
    char username[_MAX_SIZE];
    char password[_MAX_SIZE];

}STRU_REGISTER_RQ;

typedef struct STRU_REGISTER_RS
{
    typedef int PackType;
    //�ظ����
    STRU_REGISTER_RS() : type(_DEF_PACK_REGISTER_RS), result(register_success)
    {
    }
    PackType type;
    int result;

}STRU_REGISTER_RS;

//��¼
typedef struct STRU_LOGIN_RQ
{
    typedef int PackType;
    //��¼��Ҫ: �ֻ��� ����
    STRU_LOGIN_RQ() :type(_DEF_PACK_LOGIN_RQ)
    {
        memset(tel, 0, sizeof(tel));
        memset(password, 0, sizeof(password));
    }
    PackType type;
    char tel[_MAX_SIZE];
    char username[_MAX_SIZE];
    char password[_MAX_SIZE];

}STRU_LOGIN_RQ;

typedef struct STRU_LOGIN_RS
{
    typedef int PackType;
    // ��Ҫ ��� , �û���id
    STRU_LOGIN_RS() : type(_DEF_PACK_LOGIN_RS), result(login_success), userid(0)
    {
    }
    PackType type;
    int result;
    int userid;

}STRU_LOGIN_RS;

//������Ϣ
typedef struct STRU_FRIEND_INFO
{
    typedef int PackType;
    STRU_FRIEND_INFO() :type(_DEF_PACK_FRIEND_INFO), uuid(0), iconid(0), state(0)
    {
        memset(username, 0, sizeof(username));
        memset(feeling, 0, sizeof(feeling));
    }
    //��Ҫ �û�id ͷ��id �ǳ� ǩ�� ״̬--�Ƿ�����
    PackType type;
    int uuid;
    int iconid;
    int state;
    char username[_MAX_SIZE];
    char feeling[_MAX_SIZE];

}STRU_FRIEND_INFO;

//��Ӻ���
typedef struct STRU_ADD_FRIEND_RQ
{
    typedef int PackType;
    // ����û�1 ����û�2 Ϊ���� ��Ҫ �û�1 id �û�1 ���� ,�û�2������
    STRU_ADD_FRIEND_RQ() :type(_DEF_PACK_ADDFRIEND_RQ), userid(0)
    {
        memset(userName, 0, sizeof(userName));
        memset(friendName, 0, sizeof(friendName));
    }
    PackType type;
    int userid;
    char userName[_MAX_SIZE];
    char friendName[_MAX_SIZE];

}STRU_ADD_FRIEND_RQ;

typedef struct STRU_ADD_FRIEND_RS
{
    typedef int PackType;
    STRU_ADD_FRIEND_RS() :type(_DEF_PACK_ADDFRIEND_RS), userid(0), friendid(0), result(add_success)
    {
        memset(friendName, 0, sizeof(friendName));
    }
    //����û�1 ����û�2 ��Ҫ �û�1id  �û�2 id �û�2������ ���
    PackType type;
    int userid; // �û�1
    int friendid; // �û�2
    int result;
    char friendName[_MAX_SIZE];

}STRU_ADD_FRIEND_RS;

//����
typedef struct STRU_CHAT_RQ
{
    typedef int PackType;
    STRU_CHAT_RQ() :type(_DEF_PACK_CHAT_RQ), userid(0), friendid(0)
    {
        memset(content, 0, _DEF_CONTENT_SIZE);
    }
    // ˭����˭ ������ת��  �û�1 id �û�2 id ��������
    PackType type;
    int userid;
    int friendid;
    char content[_DEF_CONTENT_SIZE];

}STRU_CHAT_RQ;

typedef struct STRU_CHAT_RS
{
    typedef int PackType;
    STRU_CHAT_RS() :type(_DEF_PACK_CHAT_RS), userid(0), friendid(0), result(0)
    {
    }
    PackType type;
    int userid;
    int friendid; //���������ĸ��˲�����
    int result;

}STRU_CHAT_RS;

typedef struct STRU_OFFLINE {
    typedef int PackType;
    STRU_OFFLINE() : type(_DEF_PACK_OFFLINE_RQ) {}
    PackType type;
    int uuid;
}STRU_OFFLINE;

// �ļ�����Э��
/**
 * @brief �ļ���Ϣ����
*/
struct STRU_FILE_INFO_RQ {
    typedef int PackType;
    STRU_FILE_INFO_RQ() : nType(_DEF_PROTOCOL_FILE_INFO_RQ), nFileSize(0), uuid(0), friendid(0) {
        memset(szFileId, 0, _MAX_FILE_PATH_SIZE);
        memset(szFileName, 0, _MAX_FILE_PATH_SIZE);
    }
    PackType nType;
    char szFileId[_MAX_FILE_PATH_SIZE];
    char szFileName[_MAX_FILE_PATH_SIZE];
    uint64_t nFileSize;
    int uuid;
    int friendid;
};
/**
 * @brief �ļ���Ϣ�ظ�
*/
#define _file_accept (0)
#define _file_refuse (1)
struct STRU_FILE_INFO_RS 
{
    typedef int PackType;
    STRU_FILE_INFO_RS() : nType(_DEF_PROTOCOL_FILE_INFO_RS), nResult(_file_accept), uuid(0), friendid(0) {
        memset(szFileId, 0, _MAX_FILE_PATH_SIZE);
    }
    PackType nType;
    char szFileId[_MAX_FILE_PATH_SIZE];
    int nResult;
    int uuid;
    int friendid;
};

/**
 * @brief �ļ�������
*/
struct STRU_FILE_BLOCK_RQ
{
    typedef int PackType;
    STRU_FILE_BLOCK_RQ() : nType(_DEF_PROTOCOL_FILE_BLOCK_RQ), nBlockSize(0), uuid(0), friendid(0) {
        memset(szFileId, 0, _MAX_FILE_PATH_SIZE);
        memset(szFileContent, 0, _DEF_FILE_CONTENT_SIZE);
    }
    PackType nType;
    char szFileId[_MAX_FILE_PATH_SIZE];
    char szFileContent[_DEF_FILE_CONTENT_SIZE];
    uint64_t nBlockSize;
    int uuid;
    int friendid;
};

/**
 * @brief �ļ�����ܻظ�
*/
#define _file_block_recv_success (0)
#define _file_block_recv_fail    (1)
struct STRU_FILE_BLOCK_RS
{
    typedef int PackType;
    STRU_FILE_BLOCK_RS() :nType(_DEF_PROTOCOL_FILE_BLOCK_RS), nResult(_file_block_recv_success), uuid(0), friendid(0) {
        memset(szFileId, 0, _MAX_FILE_PATH_SIZE);
    }
    PackType nType;
    char szFileId[_MAX_FILE_PATH_SIZE];
    int nResult;
    int uuid;
    int friendid;
};

/**
 * @brief �ļ���Ϣ
*/
struct FileInfo
{
    FileInfo() : nPos(0), nFileSize(0), pFile(nullptr) {
        memset(szFileId, 0, _MAX_FILE_PATH_SIZE);
        memset(szFileName, 0, _MAX_FILE_PATH_SIZE);
        memset(szFilePath, 0, _MAX_FILE_PATH_SIZE);
    }
    char szFileId[_MAX_FILE_PATH_SIZE];
    char szFileName[_MAX_FILE_PATH_SIZE];
    char szFilePath[_MAX_FILE_PATH_SIZE];
    uint64_t nPos;
    uint64_t nFileSize;
    FILE* pFile;
};