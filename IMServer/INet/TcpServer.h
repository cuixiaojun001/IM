#ifndef __TCPSERVER_H__
#define __TCPSERVER_H__

#include <map>
#include <list>
#include "INet.h"
#include "../mediator/INetMediator.h"

namespace net {
	class TcpServer : public INet
	{
	public:
		TcpServer(INetMediator* pMediator);
		~TcpServer();
		/**
		 * @brief ��ʼ������
		 * @return �ɹ�����true, ʧ�ܷ���false
		*/
		bool InitNet() override;
		/**
		 * @brief �ر�����
		*/
		void UnInitNet() override;
		/**
		 * @brief ������Ϣ: ͬʱ����TCP��UDP
		 * @param lSendIP ����ͻ��������׽���
		 * @param buf �������ݻ�������ָ��
		 * @param nLen ���ݳ���
		 * @return �ɹ�����true, ʧ�ܷ���false
		*/
		bool SendData(unsigned long lSendIP, const char* buf, int nLen) override;
	protected:
		/**
		 * @brief ������Ϣ
		*/
		void RecvData() override;
	private:
		/**
		 * @brief ���ܿͻ������������߳�, ����һ��
		 * @param lpParameter
		 * @return
		*/
		static unsigned int __stdcall AcceptThread(LPVOID lpParameter);
		/**
		 * @brief ��ͻ��˽������߳�, ÿ���ͻ��˶�Ӧһ��
		 * @param lpParameter
		 * @return
		*/
		static unsigned int __stdcall RecvThread(LPVOID lpParameter);
	private:
		/**
		 * @brief ���׽���
		*/
		SOCKET m_socket;
		/**
		 * @brief �߳��б�
		*/
		std::list<HANDLE> m_hThreadHandleLst;
		/**
		 * @brief keyΪ�߳�id, valueΪsocket��������map
		*/
		std::map<unsigned int, SOCKET> m_mapThreadIdToSocket;
		/**
		 * @brief �����жϱ�־
		*/
		bool m_isStop;

	};
	//bool TcpServer::m_isStop = false;
	//SOCKET TcpServer::m_socket = NULL;
}

#endif // !__TCPSERVER_H__



