#include <iostream>
#include <list>
#include <string>

#include "../MySQL/CMySql.h"

using namespace std;

struct User
{
	string username;
};

int main3() {
	mysql::CMySql sql;
	if (!sql.ConnectMySql("127.0.0.1", "root", "becauseofyou0926", "im_database")) {
		cout << "数据库打开失败" << endl;
		// system("pause");
		return 0;
	}
	cout << "数据库打开成功" << endl;
	list<string> lstRes;
	char sqlbuf[1024] = "";
	sprintf_s(sqlbuf, "select * from user;");
	if (!sql.SelectMySql(sqlbuf, 2, lstRes)) {
		cout << "数据库查询出错" << sqlbuf << endl;
	}
	User user = {};
	while (lstRes.size() > 0) 
	{
		user.username = lstRes.front();
		lstRes.pop_front();
		cout << "username:" << user.username.c_str() << endl;
	}
	return 0;
}