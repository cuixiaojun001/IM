#ifndef __TCPSERVER_H__
#define __TCPSERVER_H__

#include <map>
#include <list>
#include "INet.h"
#include "../mediator/INetMediator.h"

namespace net {
	/**
	 * @brief TCP服务器 Socket
	*/
	class TcpServer : public INet
	{
	public:
		TcpServer(INetMediator* pMediator);
		~TcpServer();
		/**
		 * @brief 初始化网络
		 * @return 成功返回true, 失败返回false
		*/
		bool InitNet() override;
		/**
		 * @brief 关闭网络
		*/
		void UnInitNet() override;
		/**
		 * @brief 发送信息: 同时兼容TCP和UDP
		 * @param lSendIP 处理客户端请求套接字
		 * @param buf 传输数据缓冲区的指针
		 * @param nLen 数据长度
		 * @return 成功返回true, 失败返回false
		*/
		bool SendData(unsigned long lSendIP, const char* buf, int nLen) override;
	protected:
		/**
		 * @brief 接受信息
		*/
		void RecvData() override;
	private:
		/**
		 * @brief 接受客户端连接请求线程, 仅此一个
		 * @param lpParameter
		 * @return
		*/
		static unsigned int __stdcall AcceptThread(LPVOID lpParameter);
		/**
		 * @brief 与客户端交互的线程, 每个客户端对应一个
		 * @param lpParameter
		 * @return
		*/
		static unsigned int __stdcall RecvThread(LPVOID lpParameter);
	private:
		/**
		 * @brief 主套接字
		*/
		SOCKET m_socket;
		/**
		 * @brief 线程列表
		*/
		std::list<HANDLE> m_hThreadHandleLst;
		/**
		 * @brief key为线程id, value为socket描述符的map
		*/
		std::map<unsigned int, SOCKET> m_mapThreadIdToSocket;
		/**
		 * @brief 结束判断标志
		*/
		bool m_isStop;

	};
}

#endif // !__TCPSERVER_H__



