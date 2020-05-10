#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

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
    cin>>port;
    string ipAddress = "127.0.0.1";

    sockaddr_in clientAddr;
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_port = htons(Hport);
    inet_pton(AF_INET, ipAddress.c_str(), &clientAddr.sin_addr);

    
    int connectRes = connect(sock, (sockaddr*)&clientAddr, sizeof(clientAddr));
    if (connectRes == -1)
    {
        return 1;
    }

    
    char buf[2048];
    string userInput;


    do {
        
        cout << ">> ";
        getline(cin, userInput);

       
        int sendRes = send(sock, userInput.c_str(), userInput.size() + 1, 0);
        if (sendRes == -1)
        {
            cout << "Could not send to server! Whoops!\r\n";
            continue;
        }

        
        memset(buf, 0, 2048);
        int bytesReceived = recv(sock, buf, 2048, 0);
        if (bytesReceived == -1)
        {
            cout << "There was an error getting response from server\r\n";
        }
        else
        {
            
            cout << "SERVER> " << string(buf, bytesReceived) << "\r\n";
        }
    } while(true);

    
    close(sock);

    return 0;
}
