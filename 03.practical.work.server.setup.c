
#include <windows.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>

#include <WinSock2.h>
#include <iostream>
#pragma comment(lib, "Ws2_32.dll")

using namespace std;
int main()
{
   cout<<"\t\t----- TCP SERVER  -------"<<endl;
   cout<<endl;
   //local variable
   WSADATA wsaData;
   int iWsaStartup;
   int iWsaCleanup;
   
   SOCKET TCPServerSocket;
   int iCloseSocket;
   struct sockaddr_in TCPServerAdd;
   struct sockaddr_in TCPClientAdd;
   int iTCPClientAdd = sizeof(TCPClientAdd);
   
   int iBind;
   int iListen;
   SOCKET sAcceptSocket;
    int iSend;
	char SenderBuffer[512] = "HEllo from server";
	int iSenderBuffer =strlen(SenderBuffer) + 1;
	
	int iRecv;
	char RecvBuffer[512];
	int iRecvBuffer = strlen(RecvBuffer) + 1;
	// wsastarup fun
	iWsaStartup = WSAStartup(MAKEWORD(2,2),&wsaData);
	if(iWsaStartup != 0){
		cout<<"WSAStartUp Failed"<<endl;
	}
	cout<<"WSAStartUp Success"<<endl;
	// fill the structure
	TCPServerAdd.sin_family = AF_INET;
	TCPServerAdd.sin_addr.s_addr =inet_addr("127.0.0.1");
	TCPServerAdd.sin_port = htons(8784);
	//socket creation
	TCPServerSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	
	if(TCPServerSocket == INVALID_SOCKET){
		cout<<"TCP Server Socket Creation failed"<<WSAGetLastError()<<endl;
		
	}
	cout<<"TCP Server Socket Creation Success"<<endl;
	// bind fun
	iBind = bind(TCPServerSocket,(SOCKADDR*)&TCPServerAdd,sizeof(TCPServerAdd));
	if(iBind == SOCKET_ERROR){
		cout<<"Binding failed & Error No->"<<WSAGetLastError()<<endl;
	}
	 cout<<"Binding Success"<<endl;
	// listen fun
	iListen = listen(TCPServerSocket,2);
	if(iListen == SOCKET_ERROR){
		cout<<"Listen Fun failed & Error No->"<<WSAGetLastError()<<endl;
	}
	cout<<"Listen Fun Success"<<endl;
	// accept
	sAcceptSocket = accept(TCPServerSocket,(SOCKADDR*)&TCPServerAdd,&iTCPClientAdd);
	if(sAcceptSocket == INVALID_SOCKET){
		cout<<"Accept Failed & Error No->"<<WSAGetLastError()<<endl;
	}
	cout<<"Success"<<endl;
	// send data to client
	iSend = send(sAcceptSocket,SenderBuffer,iSenderBuffer,0);
	if(iSend == SOCKET_ERROR){
		cout<<"Sending failed & Error No->"<<WSAGetLastError()<<endl;
	}
	cout<<"Data Sending Success"<<endl;
	// recv dta from client
	iRecv = recv(sAcceptSocket,RecvBuffer,iRecvBuffer,0);
	if(iRecv == SOCKET_ERROR){
		cout<<"Receive data failed & Error No->"<<WSAGetLastError()<<endl;
	}
	cout<<"Data Receive->"<<RecvBuffer<<endl;
	// Close Server
	iCloseSocket = closesocket(TCPServerSocket);
	if(iCloseSocket == SOCKET_ERROR){
		cout<<"Closing Failed & Error No->"<<WSAGetLastError()<<endl;
	}
	cout<<"Closing Socket Success"<<endl;
	// Clearup
	iWsaCleanup = WSACleanup();
	if(iWsaCleanup == SOCKET_ERROR){
		cout<<"Cleanup Fail & Error No->"<<WSAGetLastError()<<endl;
	}
	cout<<"Cleanup Success"<<endl;
	
	system("PAUSE");
  return 0;
}
