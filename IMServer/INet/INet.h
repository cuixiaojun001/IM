#ifndef __INET_H__
#define __INET_H__
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <process.h>
#include "packdef.h"
#include "../mediator/INetMediator.h"
#pragma comment (lib, "ws2_32.lib")

namespace net {
	/**
	 * @brief 接口类，TCP和UDP的Socket实现INet成员方法
	*/
	class INet
	{
	public:
		INet() {}
		virtual ~INet() {}
		virtual bool InitNet() = 0;
		virtual void UnInitNet() = 0;
		virtual bool SendData(unsigned long lSendIP, const char* buf, int nLen) = 0;
	protected:
		virtual void RecvData() = 0;
		/**
		 * @brief 中介者接口指针, 用于将网络数据向类外传输
		*/
		INetMediator* m_pMediator;
	};
}
#endif // !__INET_H__
