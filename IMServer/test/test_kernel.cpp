#include <iostream>
#include "../Kernel.h"
#include "../INet/packdef.h"

using namespace std;

int main() {
	/*STRU_REGISTER_RQ rq;
	strcpy_s(rq.password,"test7");
	strcpy_s(rq.tel, "7777");
	strcpy_s(rq.username, "test7");
	char* sendbuf = (char*)&rq;*/

	if (!Kernel::getInstance().startServer()) return 0;
	while (1) {
		// cout << "Server Working ..." << endl;
		Sleep(1000);
	}
	// Kernel::getInstance().dealLoginRq(0, sendbuf, sizeof(rq)); //Kernel处理登录请求
	// Kernel::getInstance().dealRegisterRq(0, sendbuf, sizeof(rq)); //Kernel处理注册请求

	return 0;
}