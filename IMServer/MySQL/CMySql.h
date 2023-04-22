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
		 * @brief 连接数据库
		 * @param host ip
		 * @param user 用户名
		 * @param pass 密码
		 * @param db 数据库
		 * @param nport 端口号
		 * @return 成功返回true; 失败返回false
		*/
		bool ConnectMySql(const char* host, const char* user, const char* pass, const char* db, short nport = 3306);
		/**
		 * @brief 断开连接
		*/
		void  DisConnect();
		/**
		 * @brief 查询数据库
		 * @param[in] szSql 查询语句缓冲区
		 * @param[in] nColumn 数据库的列数
		 * @param[out] lstStr 输出参数:查询结果
		 * @return
		*/
		bool  SelectMySql(const char* szSql, int nColumn, std::list<std::string>& lstStr);
		/**
		 * @brief 获得数据库中的表
		 * @param szSql 查询语句缓冲区
		 * @param lstStr 输出参数:查询结果
		 * @return
		*/
		bool GetTables(const char* szSql, std::list<std::string>& lstStr);
		/**
		 * @brief 更新：删除、插入、修改
		 * @param szSql 查询语句缓冲区
		 * @return
		*/
		bool  UpdateMySql(const char* szSql);
	private:
		MYSQL* sock;
		MYSQL_RES* results;
		MYSQL_ROW record;
	};
}


