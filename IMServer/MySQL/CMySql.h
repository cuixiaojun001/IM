#pragma once

#include <mysql.h>
#include <list>
#include <string>
#pragma comment(lib,"libmysql.lib")


namespace mysql {
	class CMySql
	{
	public:
		CMySql(void);
		~CMySql(void);
	public:
		/**
		 * @brief �������ݿ�
		 * @param host ip
		 * @param user �û���
		 * @param pass ����
		 * @param db ���ݿ�
		 * @param nport �˿ں�
		 * @return �ɹ�����true; ʧ�ܷ���false
		*/
		bool ConnectMySql(const char* host, const char* user, const char* pass, const char* db, short nport = 3306);
		/**
		 * @brief �Ͽ�����
		*/
		void  DisConnect();
		/**
		 * @brief ��ѯ���ݿ�
		 * @param[in] szSql ��ѯ��仺����
		 * @param[in] nColumn ���ݿ������
		 * @param[out] lstStr �������:��ѯ���
		 * @return
		*/
		bool  SelectMySql(const char* szSql, int nColumn, std::list<std::string>& lstStr);
		/**
		 * @brief ������ݿ��еı�
		 * @param szSql ��ѯ��仺����
		 * @param lstStr �������:��ѯ���
		 * @return
		*/
		bool GetTables(const char* szSql, std::list<std::string>& lstStr);
		/**
		 * @brief ���£�ɾ�������롢�޸�
		 * @param szSql ��ѯ��仺����
		 * @return
		*/
		bool  UpdateMySql(const char* szSql);
	private:
		MYSQL* sock;
		MYSQL_RES* results;
		MYSQL_ROW record;
	};
}


