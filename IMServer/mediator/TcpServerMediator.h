#ifndef __TCPSERVERMEDIATOR_H__
#define __TCPSERVERMEDIATOR_H__
#include "INetMediator.h"
namespace net {
	class TcpServerMediator : public INetMediator {
	public:
		TcpServerMediator();
		~TcpServerMediator();
	public:
		/**
		 * @brief 打开网络
		 * @return 成功返回true; 失败返回false
		*/
		bool OpenNet() override;
		/**
		 * @brief 关闭网络
		*/
		void CloseNet() override;
		/**
		 * @brief 发送数据
		 * @param lSendIP 处理客户端请求套接字
		 * @param buf 数据缓冲区指针
		 * @param nLen 数据大小
		 * @return 成功返回true; 失败返回false
		*/
		bool SendData(unsigned long lSendIP, const char* buf, int nLen) override;
		/**
		 * @brief 处理数据
		 * @param lSendIP 处理客户端请求套接字
		 * @param buf 数据缓冲区指针
		 * @param nLen 数据大小
		*/
		void DealData(unsigned long lSendIP, const char* buf, int nLen) override;
	};
}
#endif // !__TCPSERVERMEDIATOR_H__
