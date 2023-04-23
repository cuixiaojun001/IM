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
	void DealData(unsigned long lSendIP, const char* buf, int nLen);
	/**
	 * @brief 处理登录请求
	 * @param lSendIP
	 * @param buf
	 * @param nLen
	*/
	void dealLoginRq(unsigned long lSendIP, const char* buf, int nLen);
	/**
	 * @brief 处理注册请求
	 * @param lSendIP
	 * @param buf
	 * @param nLen
	*/
	void dealRegisterRq(unsigned long lSendIP, const char* buf, int nLen);
	/**
	 * @brief 获得好友列表
	 * @param lSendIP
	 * @param buf
	 * @param nLen
	*/
	void getFriendList(unsigned long lSendIP, const char* buf, int nLen);
	/**
	 * @brief 处理聊天信息
	 * @param lSendIP
	 * @param buf
	 * @param nLen
	*/
	void dealChatRq(unsigned long lSendIP, const char* buf, int nLen);
	/**
	 * @brief 处理添加好友请求
	 * @param lSendIP 
	 * @param buf 
	 * @param nLen 
	*/
	void dealAddFriendRq(unsigned long lSendIP, const char* buf, int nLen);
	/**
	 * @brief 对方(好友)回复申请
	 * @param lSendIP 
	 * @param buf 
	 * @param nLen 
	*/
	void dealAddFriendRs(unsigned long lSendIP, const char* buf, int nLen);
	/**
	 * @brief 从数据库中查询用户信息
	 * @param uuid 用户id
	 * @param info 输出参数, 信息结构体
	*/
	void getFriendInfoFromSql(int uuid, STRU_FRIEND_INFO* info);

	/**
	 * @brief 处理文件传输信息请求
	 * @param lSendIP 
	 * @param buf 
	 * @param nLen 
	*/
	void DealFileInfoRq(unsigned long lSendIP, const char* buf, int nLen);
	/**
	 * @brief 处理文件传输信息回复
	 * @param lSendIP 
	 * @param buf 
	 * @param nLen 
	*/
	void DealFileInfoRs(unsigned long lSendIP, const char* buf, int nLen);
	/**
	 * @brief 处理文件块请求
	 * @param lSendIP 
	 * @param buf 
	 * @param nLen 
	*/
	void DealFileBlockRq(unsigned long lSendIP, const char* buf, int nLen);
	/**
	 * @brief 处理文件块回复
	 * @param lSendIP 
	 * @param buf 
	 * @param nLen 
	*/
	void DealFileBlockRs(unsigned long lSendIP, const char* buf, int nLen);

	/**
	 * @brief 处理下线请求
	 * @param lSendIP 
	 * @param buf 
	 * @param nLen 
	*/
	void DealOfflineRq(unsigned long lSendIP, const char* buf, int nLen);
public:
	/**
	 * @brief 设置函数映射
	*/
	void setProtocolMap();
private:
	/**
	 * @brief Kernel类唯一实例
	*/
	static Kernel kernel;
	/**
	 * @brief 协议头与处理函数的映射
	*/
	static std::map<int, std::function<void(unsigned long, const char*, int)> > m_deal_items;
	/**
	 * @brief 用户id与套接字的映射
	*/
	std::map<int, unsigned long> m_mapIdToSock;

	/**
	 * @brief 数据库接口
	*/
	mysql::CMySql m_sql;
	/**
	 * @brief 中介者接口指针, 用于将网络数据向类内传输和将Kernel处理结果发送到网络中
	*/
	net::INetMediator* m_pServer;
	/**
	 * @brief 文件id与文件信息的映射, 方便跨函数传输文件块
	*/
	std::map<std::string, FileInfo*> m_mapFileIdToFileInfo;
};

#endif // !__KERNEL_H__



