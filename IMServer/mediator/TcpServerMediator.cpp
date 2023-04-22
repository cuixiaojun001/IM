#include "TcpServerMediator.h"
#include "../INet/TcpServer.h"
#include "../Kernel.h"
#include <iostream>
namespace net {
	TcpServerMediator::TcpServerMediator()
	{
		m_pNet = new TcpServer(this);
	}
	TcpServerMediator::~TcpServerMediator()
	{
		if (m_pNet) {
			delete m_pNet;
			m_pNet = nullptr;
		}
	}
	bool TcpServerMediator::OpenNet()
	{
		if (m_pNet->InitNet()) return true;
		return false;
	}
	void TcpServerMediator::CloseNet()
	{
		m_pNet->UnInitNet();
	}
	bool TcpServerMediator::SendData(unsigned long lSendIP, const char* buf, int nLen)
	{
		if (m_pNet->SendData(lSendIP, buf, nLen)) return true;
		return false;
	}
	void TcpServerMediator::DealData(unsigned long lSendIP, const char* buf, int nLen)
	{
		Kernel::getInstance().DealData(lSendIP, buf, nLen);
	}
}

