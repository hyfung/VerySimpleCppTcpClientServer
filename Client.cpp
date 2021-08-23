#include <unistd.h>
#include <iostream>
#include <cstring>

// Headers required by socket
#include <sys/socket.h> //socket
#include <arpa/inet.h> //inet_addr

using namespace std;

int main(int argc, char** argv)
{
    // First we get the parameter for the client connection
    int port = -1;
    char addr[16] = {0};
    char opt;

    while((opt = getopt(argc, argv, "h:p:")) != -1)
    {
        switch(opt)
        {
            case 'h':
                strncpy(addr, optarg, 15); //Max len of IP address is XXX.XXX.XXX.XXX, 15 bytes without \0
                cout << "Host: " << addr << endl;
            break;
            case 'p':
                port = atoi(optarg);
                cout << "Port: " << port << endl;
            break;
        }
    }

    // Check if connection parameter is supplied
    if (port == -1)
    {
        cout << "No port was provided! Defaulting to 8080" << endl;
        port = 8080;
    }

    if(strlen(addr) == 0)
    {
        cout << "No address was provided! Defaulting to 127.0.0.1" << endl;
        sprintf(addr, "127.0.0.1");
    }

    // Boilerplate code for TCP connection
    int sock = socket(AF_INET , SOCK_STREAM , 0);
    struct sockaddr_in server;

    server.sin_addr.s_addr = inet_addr(addr);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    // Connect to remote server
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        cout << "Error connecting to server!" << endl;
        exit(-1);
    }

    cout << "Successfully connected to server" << endl;

    int counter = 0;
    while(1)
    {

        char message[256];
        sprintf(message, "%d", counter);
        char server_reply[2048] = {0};

        if(send(sock, message, strlen(message), 0) < 0)
        {
            cout << "Failure to send message!" << endl;
            exit(-1);
        }

        if(recv(sock, server_reply, 2048, 0) < 0)
        {
            cout << "Failure to receive message!" << endl;
            exit(-1);
        }
        else
        {
            cout << "[From Server] " << server_reply << endl;
        }

        sleep(1);
        cout << "[*] Sleeping for 1 second" << endl;
        counter++;
    }
    
    return 0;
}
