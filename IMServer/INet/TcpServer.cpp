#include "TcpServer.h"
#include "../mediator/TcpServerMediator.h"
#include <iostream>
namespace net {
	TcpServer::TcpServer(INetMediator* pMediator) : m_socket(INVALID_SOCKET), m_isStop(false)
	{
		m_pMediator = pMediator;
	}
	TcpServer::~TcpServer()
	{
		UnInitNet();
	}
	bool TcpServer::InitNet()
	{
		/*���ؿ�*/
		WORD wVersionRequested;
		WSADATA wsaData;
		int err;

		/* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
		wVersionRequested = MAKEWORD(2, 2);

		err = WSAStartup(wVersionRequested, &wsaData);
		if (err != 0) {
			/* Tell the user that we could not find a usable */
			/* Winsock DLL.                                  */
			printf("WSAStartup failed with error: %d\n", err);
			return false;
		}

		/* Confirm that the WinSock DLL supports 2.2.*/
		/* Note that if the DLL supports versions greater    */
		/* than 2.2 in addition to 2.2, it will still return */
		/* 2.2 in wVersion since that is the version we      */
		/* requested.                                        */

		if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
			/* Tell the user that we could not find a usable */
			/* WinSock DLL.                                  */
			printf("Could not find a usable version of Winsock.dll\n");
			WSACleanup();
			return false;
		}
		else
			printf("The Winsock 2.2 dll was found okay\n");
		/*�����׽���*/
		if ((m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
			WSACleanup();
			return false;
		}
		/*��IP��ַ*/
		sockaddr_in server_addr;
		server_addr.sin_family = AF_INET;
		server_addr.sin_addr.S_un.S_addr = INADDR_ANY;
		server_addr.sin_port = htons(_DEF_TCP_PORT);
		if (bind(m_socket, (const sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
			UnInitNet();
			return false;
		}
		/*���׽��ָ�Ϊ�����׽���*/
		if (listen(m_socket, SOMAXCONN) == SOCKET_ERROR) {
			UnInitNet();
			return false;
		}
		/*���������߳�*/
		HANDLE handle = (HANDLE)_beginthreadex(NULL, 0, &AcceptThread, this, 0, NULL);
		if (handle) {
			m_hThreadHandleLst.emplace_back(handle);
		}
		return true;
	}
	void TcpServer::UnInitNet()
	{
		m_isStop = true; // �����˳��߳�ѭ��
		for (auto& it : m_hThreadHandleLst) { // �����߳�
			if (it) {
				if (WaitForSingleObject(it, 100) == WAIT_TIMEOUT) {
					TerminateThread(it, -1);
				}
				CloseHandle(it);
				it = NULL;
			}
		}
		if (m_socket && m_socket != INVALID_SOCKET) {
			closesocket(m_socket);
		}
		for (auto& it : m_mapThreadIdToSocket) {
			if (it.second && it.second != INVALID_SOCKET) {
				closesocket(it.second);
			}
		}
		WSACleanup();
	}
	bool TcpServer::SendData(unsigned long lSendIP, const char* buf, int nLen)
	{
		if (!buf || nLen <= 0) return false;
		// TODO: ��ֹճ��, ����취: �ȷ�����С, �ٷ����ݰ�
		send(lSendIP, (char*)&nLen, sizeof(int), 0);
		if (send(lSendIP, buf, nLen, 0) <= 0) return false;

		return true;
	}
	void TcpServer::RecvData()
	{
		Sleep(100);
		SOCKET sockWaiter = m_mapThreadIdToSocket[GetCurrentThreadId()];
		if (!sockWaiter || sockWaiter == INVALID_SOCKET) return;
		int nPackSize = 0; // �洢����С
		
		int iResult = 0;
		while (!m_isStop) {
			// �Ƚ��ܰ���С �ٽ������ݰ�
			iResult = recv(sockWaiter, (char*)&nPackSize, sizeof(int), 0);
			if (iResult <= 0) break;
			int offset = 0; //��buf��ʼ��ʼƫ�ƶ���
			char* recvbuf = new char[nPackSize];
			while (nPackSize) {
				if ((iResult = recv(sockWaiter, recvbuf + offset, sizeof(recvbuf), 0)) > 0) {
					// TODO: ��������
					nPackSize -= iResult;
					offset += iResult;
					//sockaddr_in client_addr;
					//int addrSize = sizeof(client_addr);
					//getpeername(sockWaiter, (sockaddr*)&client_addr, &addrSize);
					//std::cout << "ip[" << inet_ntoa(client_addr.sin_addr) << "] says: " << recvbuf << std::endl;
				}
			}
			m_pMediator->DealData(sockWaiter, recvbuf, offset);
		}
	}
	unsigned int __stdcall TcpServer::AcceptThread(LPVOID lpParameter)
	{
		TcpServer* pthis = (TcpServer*)lpParameter;
		sockaddr_in client_addr;
		int nSize = sizeof(client_addr);
		while (!pthis->m_isStop) {
			SOCKET sockWaiter = accept(pthis->m_socket, (sockaddr*)&client_addr, &nSize);
			std::cout << "IP[" << inet_ntoa(client_addr.sin_addr) << "] connect." << std::endl;
			unsigned int threadId = 0;
			HANDLE handle = (HANDLE)_beginthreadex(NULL, 0, &RecvThread, pthis, 0, &threadId);
			pthis->m_hThreadHandleLst.emplace_back(handle);
			pthis->m_mapThreadIdToSocket[threadId] = sockWaiter;
		}
		return 0;
	}
	unsigned int __stdcall TcpServer::RecvThread(LPVOID lpParameter)
	{
		TcpServer* pthis = (TcpServer*)lpParameter;
		pthis->RecvData();
		return 0;
	}
}

