#ifndef __TCPCLIENT_H__
#define __TCPCLIENT_H__
#include "INet.h"
namespace net {
    class TcpClient : public INet
    {
    public:
        TcpClient(INetMediator* mediator);
        ~TcpClient();
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
             * @param lSendIP �����ֽ���IP��ַ
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
             * @brief ������Ϣ�̺߳���
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
             * @brief ���������Ϣ���߳̾��
            */
        HANDLE m_hThreadHandle;
        /**
             * @brief �����жϱ�־
            */
        bool m_isStop;
    };
}
#endif // !__TCPCLIENT_H__



