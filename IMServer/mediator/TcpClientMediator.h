#ifndef __TCPCLIENTMEDIATOR_H__
#define __TCPCLIENTMEDIATOR_H__
#include "INetMediator.h"
namespace net {
	class TcpClientMediator : public INetMediator
	{
	public:
		TcpClientMediator();
		~TcpClientMediator();
	public:
		/**
		 * @brief ������
		 * @return �ɹ�����true; ʧ�ܷ���false
		*/
		bool OpenNet() override;
		/**
		 * @brief �ر�����
		*/
		void CloseNet() override;
		/**
		 * @brief ��������
		 * @param lSendIP �����ֽ���IP��ַ
		 * @param buf ���ݻ�����ָ��
		 * @param nLen ���ݴ�С
		 * @return �ɹ�����true; ʧ�ܷ���false
		*/
		bool SendData(unsigned long lSendIP, const char* buf, int nLen) override;
		/**
		 * @brief ��������
		 * @param lSendIP �����ֽ���IP��ַ
		 * @param buf ���ݻ�����ָ��
		 * @param nLen ���ݴ�С
		*/
		void DealData(unsigned long lSendIP, const char* buf, int nLen) override;
	};
}
#endif // !__TCPCLIENTMEDIATOR_H__
