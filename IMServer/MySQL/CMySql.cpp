//#include "stdafx.h"
#include "CMySql.h"

namespace mysql {
	CMySql::CMySql(void)
	{
		/*�����������������߳�ʼ��һ��MYSQL������������mysql����ˡ�
		����㴫��Ĳ�����NULLָ�룬�����Զ�Ϊ�����һ��MYSQL����
		������MYSQL���������Զ�����ģ���ô�ڵ���mysql_close��ʱ�򣬻��ͷ��������*/
		sock = new MYSQL;
		mysql_init(sock);
		// mysql_ssl_set(sock, NULL, NULL, NULL, NULL, 0);
		mysql_set_character_set(sock, "gb2312"); //gb2312 �л����񹲺͹������ֱ�׼
	}


	CMySql::~CMySql(void)
	{
		if (sock)
		{
			delete sock;
			sock = NULL;
		}
	}

	void CMySql::DisConnect()
	{
		mysql_close(sock);
	}

	bool CMySql::ConnectMySql(const char* host, const char* user, const char* pass, const char* db, short nport)
	{

		if (!mysql_real_connect(sock, host, user, pass, db, nport, NULL, CLIENT_MULTI_STATEMENTS))
		{
			//���Ӵ���
			fprintf_s(stderr, "Failed to connect to database:Error: %s\n", mysql_error(sock));
			return false;
		}

		return true;
	}
	bool CMySql::GetTables(const char* szSql, std::list<std::string>& lstStr)
	{
		if (mysql_query(sock, szSql))return false;

		results = mysql_store_result(sock);
		if (NULL == results)return false;
		while (record = mysql_fetch_row(results))
		{
			lstStr.push_back(record[0]);
		}

		return true;

	}
	bool CMySql::SelectMySql(const char* szSql, int nColumn, std::list<std::string>& lstStr)
	{
		//mysql_query() ���������� MySQL ���Ͳ�ִ�� SQL ���
		if (mysql_query(sock, szSql))return false;
		/**
		 * @brief mysql_store_result ���ڳɹ����������ݵ�ÿ����ѯ(SELECT��SHOW��DESCRIBE��EXPLAIN��CHECK TABLE��)
		 * @return
			. CR_COMMANDS_OUT_OF_SYNC �����Բ�ǡ����˳��ִ�������
	����		�� CR_OUT_OF_MEMORY ����		  �ڴ������
	����		�� CR_SERVER_GONE_ERROR ����   MySQL�����������á�
	����		�� CR_SERVER_LOST ����         �ڲ�ѯ�����У�������������Ӷ�ʧ��
	����		�� CR_UNKNOWN_ERROR ����		  ����δ֪����
		*/
		results = mysql_store_result(sock);
		if (NULL == results)return false;
		nColumn = mysql_num_fields(results);
		//�������е���һ�У�ȡ�����ݷ���record �����
		while (record = mysql_fetch_row(results))
		{

			for (int i = 0; i < nColumn; i++)
			{
				if (!record[i])
					lstStr.push_back("");
				else
					lstStr.push_back(record[i]);
			}
		}
		return true;
	}

	bool CMySql::UpdateMySql(const char* szSql)
	{
		if (!szSql)return false;

		if (mysql_query(sock, szSql))return false;

		return true;
	}
}



