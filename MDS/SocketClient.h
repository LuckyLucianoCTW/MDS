class NetWork
{
	int iResult;
	SOCKET ConnectSocket;
	WSADATA wsaData;
	char recvbuf[512]; 
	int recvbuflen = 512;
	struct addrinfo* result = NULL,* ptr = NULL,hints;
	std::string server;
public:
	NetWork(std::string url);
	void connecting();
	void disconnectt();
	void receivee();
	void sendd(std::string msg);

};