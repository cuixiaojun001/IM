#ifndef __KERNEL_H__
#define __KERNEL_H__
#include <map>
#include <functional>
#include <list>
#include <string>

#include "MySQL/CMySql.h"
#include "mediator/TcpServerMediator.h"
#include "INet/packdef.h"

class Kernel
{
public:
	Kernel();
	~Kernel();
public:
	static Kernel& getInstance() {
		return kernel;
	}
public:
	/**
	 * @brief ����������
	 * @return �ɹ�����true; ʧ�ܷ���false
	*/
	bool startServer();
	/**
	 * @brief �رշ�����
	*/
	void closeServer();
	/**
	 * @brief ��������
	 * @param lSendIP
	 * @param buf
	 * @param nLen
	*/
	void DealData(unsigned long lSendIP, const char* buf, int nLen);
	/**
	 * @brief �����¼����
	 * @param lSendIP
	 * @param buf
	 * @param nLen
	*/
	void dealLoginRq(unsigned long lSendIP, const char* buf, int nLen);
	/**
	 * @brief ����ע������
	 * @param lSendIP
	 * @param buf
	 * @param nLen
	*/
	void dealRegisterRq(unsigned long lSendIP, const char* buf, int nLen);
	/**
	 * @brief ��ú����б�
	 * @param lSendIP
	 * @param buf
	 * @param nLen
	*/
	void getFriendList(unsigned long lSendIP, const char* buf, int nLen);
	/**
	 * @brief ����������Ϣ
	 * @param lSendIP
	 * @param buf
	 * @param nLen
	*/
	void dealChatRq(unsigned long lSendIP, const char* buf, int nLen);
	/**
	 * @brief ������Ӻ�������
	 * @param lSendIP 
	 * @param buf 
	 * @param nLen 
	*/
	void dealAddFriendRq(unsigned long lSendIP, const char* buf, int nLen);
	/**
	 * @brief �Է�(����)�ظ�����
	 * @param lSendIP 
	 * @param buf 
	 * @param nLen 
	*/
	void dealAddFriendRs(unsigned long lSendIP, const char* buf, int nLen);
	/**
	 * @brief �����ݿ��в�ѯ�û���Ϣ
	 * @param uuid �û�id
	 * @param info �������, ��Ϣ�ṹ��
	*/
	void getFriendInfoFromSql(int uuid, STRU_FRIEND_INFO* info);

	/**
	 * @brief �����ļ�������Ϣ����
	 * @param lSendIP 
	 * @param buf 
	 * @param nLen 
	*/
	void DealFileInfoRq(unsigned long lSendIP, const char* buf, int nLen);
	/**
	 * @brief �����ļ�������Ϣ�ظ�
	 * @param lSendIP 
	 * @param buf 
	 * @param nLen 
	*/
	void DealFileInfoRs(unsigned long lSendIP, const char* buf, int nLen);
	/**
	 * @brief �����ļ�������
	 * @param lSendIP 
	 * @param buf 
	 * @param nLen 
	*/
	void DealFileBlockRq(unsigned long lSendIP, const char* buf, int nLen);
	/**
	 * @brief �����ļ���ظ�
	 * @param lSendIP 
	 * @param buf 
	 * @param nLen 
	*/
	void DealFileBlockRs(unsigned long lSendIP, const char* buf, int nLen);

	/**
	 * @brief ������������
	 * @param lSendIP 
	 * @param buf 
	 * @param nLen 
	*/
	void DealOfflineRq(unsigned long lSendIP, const char* buf, int nLen);
public:
	/**
	 * @brief ���ú���ӳ��
	*/
	void setProtocolMap();
private:
	static Kernel kernel;
	static std::map<int, std::function<void(unsigned long, const char*, int)> > m_deal_items;
	std::map<int, unsigned long> m_mapIdToSock;

	mysql::CMySql m_sql;
	net::INetMediator* m_pServer;
	/**
	 * @brief �ļ�id���ļ���Ϣ��ӳ��, ����纯�������ļ���
	*/
	std::map<std::string, FileInfo*> m_mapFileIdToFileInfo;
};

#endif // !__KERNEL_H__



