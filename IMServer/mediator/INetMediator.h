#pragma once
namespace net {
	class INet;
	class INetMediator
	{
	public:
		INetMediator() {}
		virtual ~INetMediator() {}
		/**
		 * @brief 打开网络
		 * @return 成功返回true; 失败返回false
		*/
		virtual bool OpenNet() = 0;
		/**
		 * @brief 关闭网络
		*/
		virtual void CloseNet() = 0;
		/**
		 * @brief 发送数据
		 * @param lSendIP 处理客户端请求套接字
		 * @param buf 数据缓冲区指针
		 * @param nLen 数据大小
		 * @return 成功返回true; 失败返回false
		*/
		virtual bool SendData(unsigned long lSendIP, const char* buf, int nLen) = 0;
		/**
		 * @brief 处理数据
		 * @param lSendIP 处理客户端请求套接字
		 * @param buf 数据缓冲区指针
		 * @param nLen 数据大小
		*/
		virtual void DealData(unsigned long lSendIP, const char* buf, int nLen) = 0;
	protected:
		INet* m_pNet;
	};
}