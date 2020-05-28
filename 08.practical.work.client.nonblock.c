#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <cstring>
#include <fcntl.h>
using namespace std;

int main()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        return 1;
    }
	
    int Hport;
    cout<<"enter port";
    cin>>Hport;
    string ipAddress = "127.0.0.1";
	
    sockaddr_in clientAddr;
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_port = htons(Hport);
    inet_pton(AF_INET, ipAddress.c_str(), &clientAddr.sin_addr);
    int app = 1;
	int setkop = setsockopt(sock,SOL_SOCKET,SO_REUSEADDR, &app	 ,sizeof(app));
	int flg = fcntl(sock, F_GETFL, 0);
    int connectRes = connect(sock, (sockaddr*)&clientAddr, sizeof(clientAddr));

    char buf[2048];
    string userInput;
	if (connectRes < 0)
    {
		cout<<"Error disconnect"<<endl;
    }
	else{
		cout<<"Accepted!\n"<<endl;
		fcntl(sock, F_GETFL, 0);
    while(true)
    {
        cout << "Client :";
        getline(cin, userInput);
        if (strcmp(userInput.c_str(), "/quit") == 0)
	{
	    cout<<"Disconnect...\n";
	    break;
	}
        send(sock, userInput.c_str(), userInput.size() + 1, 0); 
        memset(buf, 0, 2048);
        int bytesReceived = recv(sock, buf, 256, 0);
        if (bytesReceived == -1)
        {
            cout << "There was an error getting response from server\r\n";
        }
	cout <<"Server :"<<string(buf,0, bytesReceived) << "\r\n";
    }
	}
    close(sock);
    return 0;
}
