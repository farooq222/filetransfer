#include <iostream>
#include <winsock2.h>
#include <fstream>
#include <time.h>

// adds wsock32.lib to the linker
#pragma comment(lib, "wsock32.lib")
using namespace std;

void main() {
	WSADATA win_data; // this variable will contain the details of the winsock connection

	if (WSAStartup(MAKEWORD(2, 0), &win_data) != 0) {
		cout << "Error: Initializing winsock version 2.0." << endl;
		WSACleanup(); // terminates the use of the winsock 2 DLL
		return;
	}

	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET) {
		cout << "Error: creating socket." << endl;
		WSACleanup(); 
		return;
	}

	SOCKADDR_IN server_info;
	server_info.sin_family = AF_INET;
	server_info.sin_addr.s_addr = INADDR_ANY;
	server_info.sin_port = htons(55556);

	if (bind(sock, (SOCKADDR *)(&server_info), sizeof(server_info)) == SOCKET_ERROR) {
		cout << "Error: Binding socket." << endl;
		WSACleanup(); 
		return;
	}

	listen(sock, 1);
	cout << "Waiting for connection..." << endl;
	SOCKET client_socket = accept(sock, NULL, NULL);

	char* read_buffer;
	read_buffer = new char[5000]; //will write message to this buffer
	//read_buffer = "C:\\Users\Farooq Arshad\Documents\BSCS\Semester 6\Advance Programming\Lab 3\sample.txt";

	int k = recv(client_socket, read_buffer, sizeof(read_buffer), NULL);
	cout << k;
	if (k < 0){
		cout << "Error: Unable to upload file." << endl;
	}
	else
		cout << "Transfer Successfull." << endl;

	shutdown(client_socket, SD_SEND);
	closesocket(client_socket);
	WSACleanup();
}
