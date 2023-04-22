#include "Kernel.h"

#include <iostream>

std::map<int, std::function<void(unsigned long, const char*, int)> > Kernel::m_deal_items;
Kernel Kernel::kernel;

Kernel::Kernel()
{
	m_pServer = new net::TcpServerMediator;
	setProtocolMap();
}

Kernel::~Kernel()
{
}

bool Kernel::startServer()
{
	if (!m_sql.ConnectMySql("127.0.0.1", "root", "becauseofyou0926", "im_database")) {
		std::cout << "数据库打开失败" << std::endl;
		return false;
	}
	if (!m_pServer->OpenNet()) return false;
	return true;
}

void Kernel::closeServer()
{
	m_sql.DisConnect();
	if (m_pServer)
		m_pServer->CloseNet();
}

void Kernel::DealData(unsigned long lSendIP, const char* buf, int nLen)
{

	int header_type = *(int*)buf;
	std::cout << "DealData() header_type:" << header_type << std::endl;
	if (header_type >= _DEF_PROTOCOL_BASE && header_type <= _DEF_PROTOCOL_BASE + _DEF_PROTOCOL_COUNT)
		m_deal_items[header_type](lSendIP, buf, nLen);

}

void Kernel::dealLoginRq(unsigned long lSendIP, const char* buf, int nLen)
{
	STRU_LOGIN_RQ* rq = (STRU_LOGIN_RQ*)buf;
	std::list<std::string> lstRes;
	char sqlbuf[1024] = "";
	sprintf_s(sqlbuf, "select uuid, password from t_user where username = '%s';", rq->username);
	if (!m_sql.SelectMySql(sqlbuf, 100, lstRes)) {
		std::cout << "select error:" << sqlbuf << std::endl;
	}
	for (auto i : lstRes) {
		std::cout << i << std::endl;
	}
	STRU_LOGIN_RS rs;
	if (lstRes.size() == 0) {
		rs.result = user_not_exist;
	}
	else {
		int uuid = atoi(lstRes.front().c_str());
		lstRes.pop_front();
		std::string password = lstRes.front().c_str();
		lstRes.pop_front();
		if (strcmp(password.c_str(), rq->password) != 0) {
			rs.result = password_error;
		}
		else {
			rs.result = login_success;
			rs.userid = uuid;
			// 登录成功
			m_pServer->SendData(lSendIP, (char*)&rs, sizeof(rs));
			// 将uuid和对应的服务套接字对应
			m_mapIdToSock[uuid] = lSendIP;

			// 获取好友列表
			getFriendList(lSendIP, (char*)&uuid, sizeof(rs.userid));
			return;
		}
	}
	m_pServer->SendData(lSendIP, (char*)&rs, sizeof(rs));
}

void Kernel::dealRegisterRq(unsigned long lSendIP, const char* buf, int nLen)
{
	STRU_REGISTER_RQ* rq = (STRU_REGISTER_RQ*)buf;
	// 先判断该username是否已经存在
	std::list<std::string> lstRes;
	char sqlbuf[1024] = "";
	sprintf_s(sqlbuf, "select username from t_user where username = '%s'", rq->username);
	if (!m_sql.SelectMySql(sqlbuf, 10, lstRes)) {
		std::cout << "SelectMySQL Error:" << sqlbuf << std::endl;
		return;
	}
	STRU_REGISTER_RS rs;
	if (lstRes.size() > 0) {
		rs.result = user_is_exist;
		std::cout << "Register Failed: user_is_exist" << std::endl;
	}
	else {
		rs.result = register_success;
		sprintf_s(sqlbuf, "INSERT INTO `t_user` (`username`, `password`, `tel`) VALUES ('%s', '%s', '%s')", rq->username, rq->password, rq->tel);
		if (!m_sql.UpdateMySql(sqlbuf)) {
			std::cout << "UpdateMySQL Error:" << sqlbuf << std::endl;
		}
	}
	if (!m_pServer->SendData(lSendIP, (char*)&rs, sizeof(rs))) {
		std::cout << "Send Failed" << std::endl;
	}
}

void Kernel::getFriendList(unsigned long lSendIP, const char* buf, int nLen)
{
	int* uuid = (int*)buf;
	STRU_FRIEND_INFO info;
	getFriendInfoFromSql(*uuid, &info); // 获取自己的信息
	/*std::cout << "getFriendList() *uuid :" << info.uuid << std::endl;
	std::cout << "getFriendList() info.type: " << info.type << std::endl;
	std::cout << "getFriendList() info.username: " << info.username << std::endl;
	std::cout << "getFriendList() info.feeling: " << info.feeling << std::endl;*/
	m_pServer->SendData(lSendIP, (char*)&info, sizeof(info));

	// 获取好友信息列表
	std::list<std::string> lstRes;
	char sqlbuf[1024] = "";
	sprintf_s(sqlbuf, "select friend_id from t_friendship where uuid = '%d';", *uuid);
	if (!m_sql.SelectMySql(sqlbuf, 1, lstRes)) {
		std::cout << "getFriendList() SELECT Error:" << sqlbuf << std::endl;
	}
	while (lstRes.size() > 0) {
		int friend_id = atoi(lstRes.front().c_str());
		lstRes.pop_front();
		STRU_FRIEND_INFO friendinfo;
		getFriendInfoFromSql(friend_id, &friendinfo);
		// std::cout << "getFriendList() friend_id: " << friendinfo.uuid << std::endl;
		m_pServer->SendData(lSendIP, (char*)&friendinfo, sizeof(friendinfo));
		// 如果好友在线, 将自己上线的信息发送给好友
		if (m_mapIdToSock.find(friendinfo.uuid) != m_mapIdToSock.end()) {
			SOCKET sockFriend = m_mapIdToSock[friendinfo.uuid];
			m_pServer->SendData(sockFriend, (char*)&info, sizeof(info));
		}
	}
}

void Kernel::dealChatRq(unsigned long lSendIP, const char* buf, int nLen)
{
	std::cout << __func__ << std::endl;
	STRU_CHAT_RQ* rq = (STRU_CHAT_RQ*)buf;
	if (m_mapIdToSock.find(rq->friendid) == m_mapIdToSock.end()) { // 好友离线
		STRU_CHAT_RS rs;
		rs.userid = rq->userid;
		rs.friendid = rq->friendid;
		rs.result = user_offline;
		std::cout << "dealChatRq() rs.userid" << rs.userid << " rs.friendid: " << rs.friendid << std::endl;
		m_pServer->SendData(lSendIP, (char*)&rs, sizeof(rs));
		return;
	}
	// 好友在线
	SOCKET sockFirend = m_mapIdToSock[rq->friendid];
	m_pServer->SendData(sockFirend, buf, nLen);
}

void Kernel::dealAddFriendRq(unsigned long lSendIP, const char* buf, int nLen)
{
	STRU_ADD_FRIEND_RQ* rq = (STRU_ADD_FRIEND_RQ*)buf;
	// 查询数据库看friendName是否存在
	std::list<std::string> lstRes;
	char sqlbuf[1024] = "";
	sprintf_s(sqlbuf, "select uuid from t_user where username = '%s';", rq->friendName);
	if (!m_sql.SelectMySql(sqlbuf, 1, lstRes)) {
		std::cout << "dealAddFriendRq() SELECT ERROR:" << sqlbuf << std::endl;
	}
	if (lstRes.size() > 0) {
		int friendId = atoi(lstRes.front().c_str());
		lstRes.pop_front();
		// 查看该好友是否在线
		if (m_mapIdToSock.find(friendId) != m_mapIdToSock.end()) {
			// 在线
			// 向friend发送好友申请添加请求
			SOCKET sockFriend = m_mapIdToSock[friendId];
			m_pServer->SendData(sockFriend, buf, nLen); // 直接转发
		}
		else {
			// 该用户不在线
			STRU_ADD_FRIEND_RS rs;
			rs.result = user_offline;
			rs.friendid = friendId;
			strcpy_s(rs.friendName, rq->friendName);
			rs.userid = rq->userid;
			m_pServer->SendData(lSendIP, (char*)&rs, sizeof(rs));
		}
	}
	else {
		// 不存在这个人
		STRU_ADD_FRIEND_RS rs;
		rs.result = no_this_user;
		rs.friendid = 0;
		strcpy_s(rs.friendName, rq->friendName);
		rs.userid = rq->userid;
		m_pServer->SendData(lSendIP, (char*)&rs, sizeof(rs));
	}
}

void Kernel::dealAddFriendRs(unsigned long lSendIP, const char* buf, int nLen)
{
	STRU_ADD_FRIEND_RS* rs = (STRU_ADD_FRIEND_RS*)buf;
	STRU_ADD_FRIEND_RS rq;
	if (rs->result == add_success) { // 在好友关系表中加入该关系
		char sqlbuf[1024] = "";
		sprintf_s(sqlbuf, "insert into t_friendship values(%d, %d);", rs->friendid, rs->userid);
		if (!m_sql.UpdateMySql(sqlbuf)) {
			std::cout << "dealAddFriendRs() INSERT ERROR: " << sqlbuf << std::endl;
		}
		sprintf_s(sqlbuf, "insert into t_friendship values(%d, %d);", rs->userid, rs->friendid);
		if (!m_sql.UpdateMySql(sqlbuf)) {
			std::cout << "dealAddFriendRs() INSERT ERROR: " << sqlbuf << std::endl;
		}

		getFriendList(lSendIP, (char*)&rs->friendid, nLen);
	}
	if (m_mapIdToSock.count(rs->userid) > 0) {
		SOCKET sock = m_mapIdToSock[rs->userid];
		m_pServer->SendData(sock, buf, nLen);
	}
}

void Kernel::getFriendInfoFromSql(int uuid, STRU_FRIEND_INFO* info)
{

	info->uuid = uuid;
	std::list<std::string> lstRes;
	char sqlbuf[1024] = "";
	sprintf_s(sqlbuf, "select username, feeling from t_user where uuid = '%d';", uuid);
	if (!m_sql.SelectMySql(sqlbuf, 2, lstRes)) {
		std::cout << "getFriendInfoFromSql() Select Error:" << sqlbuf << std::endl;
	}
	if (lstRes.size() == 2) {
		strcpy_s(info->username, lstRes.front().c_str());
		lstRes.pop_front();
		strcpy_s(info->feeling, lstRes.front().c_str());
		lstRes.pop_front();
	}
	if (m_mapIdToSock.find(uuid) != m_mapIdToSock.end()) {
		info->state = 1;
	}
	else {
		info->state = 0;
	}
	std::cout << "getFriendInfoFromSql() info->uuid: " << info->uuid << " info->username: " << info->username << std::endl;
}

void Kernel::DealFileInfoRq(unsigned long lSendIP, const char* buf, int nLen)
{
	std::cout << __func__ << std::endl;
	STRU_FILE_INFO_RQ* rq = (STRU_FILE_INFO_RQ*)buf;
	if (m_mapIdToSock.find(rq->friendid) == m_mapIdToSock.end()) {
		// 好友不在线
		STRU_FILE_INFO_RS rs;
		rs.friendid = rq->uuid;
		rs.uuid = rq->friendid;
		rs.nResult = _file_refuse;
		strcpy_s(rs.szFileId, rq->szFileId);
		m_pServer->SendData(lSendIP, (char*)&rs, sizeof(rs));
		return;
	}
	else {
		// 好友在线
		std::cout << rq->friendid << "好友 在线, 转发包" << std::endl;
		SOCKET sockFriend = m_mapIdToSock[rq->friendid];
		m_pServer->SendData(sockFriend, buf, nLen);
	}

	//std::cout << __func__ << std::endl;
	//STRU_FILE_INFO_RQ* rq = (STRU_FILE_INFO_RQ*)buf;
	//char filePath[_MAX_FILE_PATH_SIZE]{};
	//OPENFILENAME file{};
	//file.lStructSize = sizeof(file);
	//file.lpstrFilter = "所有文件(*.*)\0*.*\0";
	//file.lpstrFile = filePath;
	//file.nMaxFile = sizeof(filePath) / sizeof(*filePath);
	//file.Flags = OFN_EXPLORER;
	//// strcpy_s(file.lpstrFile, 1024, rq->szFileName);
	//BOOL flag = GetSaveFileNameA(&file); // 默认接受
	//if (flag == FALSE) {
	//	strcpy_s(file.lpstrFile, 1024, rq->szFileName);
	//}
	//std::cout << "GetSaveFileNameA() file.lpstrFile: " << file.lpstrFile << std::endl;
	//FileInfo* info = new FileInfo;
	//info->nFileSize = rq->nFileSize;
	//info->nPos = 0;
	//strcpy_s(info->szFileId, rq->szFileId);
	//strcpy_s(info->szFileName, rq->szFileName);
	//strcpy_s(info->szFilePath, file.lpstrFile);
	//std::cout << "info->szFileId: " << info->szFileId << "info->szFileName: " << info->szFileName << "\n" << "info->szFilePath: " << info->szFilePath << "info->nFileSize: " << info->nFileSize << std::endl;
	//std::string strFileId = info->szFileId;
	//fopen_s(&info->pFile, info->szFilePath, "wb");
	//if (m_mapFileIdToFileInfo.find(strFileId) == m_mapFileIdToFileInfo.end()) {
	//	m_mapFileIdToFileInfo[strFileId] = info;
	//}
}

void Kernel::DealFileInfoRs(unsigned long lSendIP, const char* buf, int nLen)
{
	std::cout << __func__ << std::endl;
	STRU_FILE_INFO_RS* rs = (STRU_FILE_INFO_RS*)buf;
	if (m_mapIdToSock.find(rs->friendid) == m_mapIdToSock.end()) {
		// 好友不在线
		return;
	}
	else {
		// 好友在线
		std::cout << "好友在线, 直接转发文件信息回复包" << std::endl;
		SOCKET sockFriend = m_mapIdToSock[rs->friendid];
		m_pServer->SendData(sockFriend, buf, nLen);
	}
}

void Kernel::DealFileBlockRq(unsigned long lSendIP, const char* buf, int nLen)
{
	std::cout << __func__ << std::endl;
	STRU_FILE_BLOCK_RQ* rq = (STRU_FILE_BLOCK_RQ*)buf;
	if (m_mapIdToSock.find(rq->friendid) == m_mapIdToSock.end()) {
		// 好友不在线
		return;
	}
	else {
		// 好友在线
		SOCKET sockFriend = m_mapIdToSock[rq->friendid];
		m_pServer->SendData(sockFriend, buf, nLen);
	}
	//std::cout << __func__ << std::endl;
	//STRU_FILE_BLOCK_RQ* rq = (STRU_FILE_BLOCK_RQ*)buf;
	//std::string strFileId = rq->szFileId;
	//if (m_mapFileIdToFileInfo.find(strFileId) == m_mapFileIdToFileInfo.end()) {
	//	return;
	//}
	//FileInfo* info = m_mapFileIdToFileInfo[strFileId];
	//int nResult = fwrite(rq->szFileContent, 1, rq->nBlockSize, info->pFile);
	//info->nPos += nResult;
	//std::cout << "info->nPos: " << info->nPos << std::endl;
	//if (info->nPos >= info->nFileSize) {
	//	// 已经传输完毕
	//	std::cout << "文件" << info->szFileName << "传输完毕" << std::endl;
	//	fclose(info->pFile);
	//	m_mapFileIdToFileInfo.erase(strFileId);
	//	delete info;
	//	info = nullptr;
	//}
}

void Kernel::DealFileBlockRs(unsigned long lSendIP, const char* buf, int nLen)
{
	std::cout << __func__ << std::endl;
	STRU_FILE_BLOCK_RS* rs = (STRU_FILE_BLOCK_RS*)buf;
	if (m_mapIdToSock.find(rs->friendid) == m_mapIdToSock.end()) {
		// 好友不在线
		return;
	}
	else {
		// 好友在线
		SOCKET sockFriend = m_mapIdToSock[rs->friendid];
		m_pServer->SendData(sockFriend, buf, nLen);
	}
}

void Kernel::DealOfflineRq(unsigned long lSendIP, const char* buf, int nLen)
{
	STRU_OFFLINE* rq = (STRU_OFFLINE*)buf;
	// 给这个请求发送者的所有好友发送下线通知
	std::list<std::string> lstRes;
	char sqlbuf[1024] = "";
	sprintf_s(sqlbuf, "select friend_id from t_friendship where uuid = '%d'", rq->uuid);
	if (!m_sql.SelectMySql(sqlbuf, 1, lstRes)) {
		std::cout << __func__ << "SELECT ERROR:" << sqlbuf << std::endl;
	}
	while (lstRes.size() > 0) {
		int friendid = atoi(lstRes.front().c_str());
		std::cout << "告诉好友" << friendid << "好友" << rq->uuid << "下线请求" << std::endl;
		lstRes.pop_front();
		if (m_mapIdToSock.find(friendid) != m_mapIdToSock.end()) {
			SOCKET sockFriend = m_mapIdToSock[friendid];
			m_pServer->SendData(sockFriend, buf, nLen);
		}
	}
	if (m_mapIdToSock.find(rq->uuid) != m_mapIdToSock.end()) {
		m_mapIdToSock.erase(rq->uuid);
	}
}

void Kernel::setProtocolMap()
{
#define XX(str, func) {\
	auto call = std::bind(&Kernel::func, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3); \
	m_deal_items.insert({ str, call });}

	XX(_DEF_PACK_LOGIN_RQ, dealLoginRq);
	XX(_DEF_PACK_REGISTER_RQ, dealRegisterRq);
	XX(_DEF_PACK_CHAT_RQ, dealChatRq);
	XX(_DEF_PACK_ADDFRIEND_RQ, dealAddFriendRq);
	XX(_DEF_PACK_ADDFRIEND_RS, dealAddFriendRs);

	XX(_DEF_PROTOCOL_FILE_INFO_RQ, DealFileInfoRq);
	XX(_DEF_PROTOCOL_FILE_INFO_RS, DealFileInfoRs);
	XX(_DEF_PROTOCOL_FILE_BLOCK_RQ, DealFileBlockRq);
	XX(_DEF_PROTOCOL_FILE_BLOCK_RS, DealFileBlockRs);
	XX(_DEF_PACK_OFFLINE_RQ, DealOfflineRq);
#undef XX
}
