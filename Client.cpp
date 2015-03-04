#include <iostream>
#include <winsock2.h>
#include <fstream>
#include <time.h>

// adds wsock32.lib to the linker
#pragma comment(lib, "wsock32.lib")
using namespace std;

void main() {
	char servaddr[100] = "127.0.0.1";
	int port = 55556;
	char filepath[1024] = "C:\\Users\\Farooq Arshad\\Documents\\sample1.txt";
	long size;
	char *hostname = servaddr;
	WSADATA win_data; // this variable will contain the details of the winsock connection
	
	if (WSAStartup(MAKEWORD(2, 0), &win_data) != 0) {
		cout << "Error: Initializing winsock version 2.0." << endl;
		WSACleanup(); // terminates the use of the winsock 2 DLL
		return;
	}

	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET) {
		cout << "Error: Creating socket." << endl;
		WSACleanup(); 
		return;
	}
	
	// resolves the hostname to an IP address, stored in the hostent structure
	struct hostent *server = gethostbyname(hostname);
	if (server == NULL) {
		cout << "Error: Resolving hostname to an IP address." << endl;
		WSACleanup(); 
		return;
	}

	SOCKADDR_IN server_info;
	server_info.sin_port = htons(port);
	server_info.sin_family = AF_INET;
	server_info.sin_addr.s_addr = *((unsigned long *)server->h_addr);

	if (connect(sock, (SOCKADDR*)(&server_info), sizeof(server_info)) != 0) {
		cout << "Error: Connecting to server." << endl;
		WSACleanup(); 
		return;
	}

	char* read_buffer;			//will save file content here
	ifstream file;
	file.open(filepath, ios::in | ios::binary | ios::ate);		//open file

	if (file.is_open()){
		file.seekg(0, ios::end);
		size = file.tellg();	//file size! 

		file.seekg(0, ios::beg);		//sets location back to beginning of file

		read_buffer = new char[size];
		file.read(read_buffer, size);		//write file to buffer

		int j = send(sock, read_buffer, size, NULL);	//send file to server

		if (j == -1){
			cout << "Error: Unable to upload file." << endl;
		}

		file.close();
	}

	char* write_buffer;
	write_buffer = new char[size];		//will write message to this buffer

	int k = recv(sock, write_buffer, size, NULL);	//receiving message from server
	if (k == -1){
		cout << "Error: Unable to download file." << endl;
	}
	cout << "Receiving file." << endl;

	shutdown(sock, SD_SEND);
	closesocket(sock);
	WSACleanup();
}


