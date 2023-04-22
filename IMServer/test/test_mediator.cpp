#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "../mediator/TcpClientMediator.h"
#include "../mediator/TcpServerMediator.h"
#include "../INet/INet.h"

using namespace std;
int main2() {
	net::TcpServerMediator server;
	if (!server.OpenNet()) {
		cout << "server InitNet failed." << endl;
		system("pause");
	}

	while (1) {
		cout << "Server Working ..." << endl;
		Sleep(1000);
	}
	/*net::TcpClient client;
	net::TcpServer server;
	if (!server.InitNet()) {
		cout << "server InitNet failed." << endl;
		system("pause");
	}
	if (!client.InitNet()) {
		cout << "client InitNet failed." << endl;
		system("pause");
	}
	char sendbuf[1024] = "Hello, World!";
	client.SendData(0UL, sendbuf, (int)strlen(sendbuf));
	while (1) {
		Sleep(100);
	}*/
	return 0;
}