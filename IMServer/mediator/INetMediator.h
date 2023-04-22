#pragma once
namespace net {
	class INet;
	class INetMediator
	{
	public:
		INetMediator() {}
		virtual ~INetMediator() {}
		/**
		 * @brief ������
		 * @return �ɹ�����true; ʧ�ܷ���false
		*/
		virtual bool OpenNet() = 0;
		/**
		 * @brief �ر�����
		*/
		virtual void CloseNet() = 0;
		/**
		 * @brief ��������
		 * @param lSendIP ����ͻ��������׽���
		 * @param buf ���ݻ�����ָ��
		 * @param nLen ���ݴ�С
		 * @return �ɹ�����true; ʧ�ܷ���false
		*/
		virtual bool SendData(unsigned long lSendIP, const char* buf, int nLen) = 0;
		/**
		 * @brief ��������
		 * @param lSendIP ����ͻ��������׽���
		 * @param buf ���ݻ�����ָ��
		 * @param nLen ���ݴ�С
		*/
		virtual void DealData(unsigned long lSendIP, const char* buf, int nLen) = 0;
	protected:
		INet* m_pNet;
	};
}