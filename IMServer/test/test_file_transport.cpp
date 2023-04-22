//#include <iostream>
//#include <Windows.h>
//#include <stdio.h>
//#include "Kernel.h"
//#include "mediator/TcpClientMediator.h"
//#include "INet/packdef.h"
//
//using namespace std;
//
//string GetFileName(char* path) {
//	if (!path) {
//		return string();
//	}
//	int nlen = strlen(path);
//	if (nlen < 1) {
//		return string();
//	}
//	for (int i = nlen - 1; i >= 0; i--) {
//		if (path[i] == '\\' || path[i] == '/') {
//			return &path[i + 1];
//		}
//	}
//	return string();
//}
//
//void SendInfo(unsigned long sockClient) {
//	net::TcpClientMediator client;
//	if (!client.OpenNet()) {
//		cout << "������ʧ��" << endl;
//		system("pause");
//	}
//	// 1. ��ȡ�ļ���Ϣ
//	char file_path[_MAX_FILE_PATH_SIZE] = "";
//	OPENFILENAMEA file{}; //  = new OPENFILENAMEA;
//	file.lStructSize = sizeof(file);
//	// file.hwndOwner = 0;
//	file.lpstrFilter = "�ı�(*.txt)\0*.txt\0�����ļ�(*.*)\0*.*\0";
//	file.lpstrFile = file_path;
//	file.nMaxFile = sizeof(file_path) / sizeof(*file_path);
//	file.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
//	BOOL flag = GetOpenFileNameA(&file);
//	if (flag == FALSE) {
//		return;
//	}
//	// std::cout << file.lpstrFile << std::endl;
//	// 2. ���ļ���Ϣ����
//	STRU_FILE_INFO_RQ rq;
//	string strfilename = GetFileName(file.lpstrFile);
//	strcpy_s(rq.szFileName, _MAX_FILE_PATH_SIZE, strfilename.c_str());
//	std::cout << "rq.szFileName: " << rq.szFileName << std::endl;
//	SYSTEMTIME time{};
//	GetLocalTime(&time);
//	sprintf_s(rq.szFileId, "%s_%02d_%02d_%02d_%d", rq.szFileName, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
//	std::cout << "rq.szFileId: " << rq.szFileId << std::endl;
//	FILE* pFile = nullptr;
//	if (fopen_s(&pFile, file.lpstrFile, "rb") != 0) {
//		cout << "���ļ�ʧ��" << endl;
//		system("pause");
//	}
//	strerror
//	fseek(pFile, 0, SEEK_END); //�����ļ�β
//	rq.nFileSize = _ftelli64(pFile);
//	fseek(pFile, 0, SEEK_SET); // �����ļ�ͷ
//	std::cout << "rq.nFileSize: " << rq.nFileSize << std::endl;
//	client.SendData(0, (char*)&rq, sizeof(rq));
//	// 3. Ĭ�϶Է�Ĭ�Ͻ���, ֱ�ӷ����ļ���(8KB)
//	STRU_FILE_BLOCK_RQ blockRq;
//	// char buffer[1024] = "";
//	uint64_t nPos = 0;
//	int nReadLen = 0;
//	while (true) {
//		// Sleep(100);
//		while ((nReadLen = fread(blockRq.szFileContent, sizeof(char), _DEF_FILE_CONTENT_SIZE, pFile)) > 0) {
//			std::cout << "fread() nReadLen: " << nReadLen << std::endl;
//			// std::cout << "fread() buffer: " << blockRq.szFileContent << std::endl;
//			blockRq.nBlockSize = nReadLen;
//			strcpy_s(blockRq.szFileId, rq.szFileId);
//			client.SendData(0, (char*)&blockRq, sizeof(blockRq));
//			nPos += nReadLen;
//			if (nPos >= rq.nFileSize || nReadLen < _DEF_FILE_CONTENT_SIZE) {
//				fclose(pFile);
//				break;
//			}
//			Sleep(1);
//		}
//	}
//}
//
////void test() {
////	char filePath[_MAX_FILE_PATH_SIZE]{};
////	OPENFILENAME file{};
////	file.lStructSize = sizeof(file);
////	file.lpstrFilter = "�����ļ�(*.*)\0*.*\0";
////	file.lpstrFile = filePath;
////	file.nMaxFile = sizeof(filePath) / sizeof(*filePath);
////	file.Flags = OFN_EXPLORER;
////	// strcpy_s(file.lpstrFile, 1024, rq->szFileName);
////	BOOL flag = GetSaveFileNameA(&file); // Ĭ�Ͻ���
////	if (flag != FALSE) {
////		// strcpy_s(file.lpstrFile, 1024, rq->szFileName);
////		cout << "GetSaveFileNameA() file.lpstrFile: " << file.lpstrFile << endl;
////	}
////}
//
//int main() {
//	Kernel kernel;
//	if (!Kernel::getInstance().startServer()) {
//		cout << "������������ʧ��" << endl;
//		system("pause");
//	}
//	/*do {
//		SendInfo(0);
//	} while (0);
//	cout << "inter while(1) " << endl;*/
//	cout << "Server Working ..." << endl;
//	while (1) {
//		Sleep(100);
//	}
//	system("pause");
//	return 0;
//}
//
////#include <stdio.h>
////#include <iostream>
////int main()
////{
////	FILE* from = nullptr;
////	fopen_s(&from, "C:\\Users\\28568\\test.txt", "rb");
////	FILE* to = nullptr;
////	fopen_s(&to, "C:\\Users\\28568\\copy.txt", "wb");
////	unsigned char buffer[1024];
////	int len;
////	if (from && to)
////	{
////		while ((len = fread(buffer, sizeof(char), 1024, from)) > 0)
////		{
////			std::cout << "len:" << len << std::endl;
////			fwrite(buffer, sizeof(buffer), len, to);
////		}
////
////		fclose(from);
////		fclose(to);
////	}
////	return 0;
////}
