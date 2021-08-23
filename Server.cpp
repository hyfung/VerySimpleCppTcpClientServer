#include <iostream>
#include <stdio.h>
#include <string.h>    //strlen
#include <sys/socket.h> // Socket
#include <arpa/inet.h> //inet_addr
#include <unistd.h>    //write

using namespace std;

int main(int argc, char** argv)
{
    int port = -1;
    char addr[16] = {0};
    char opt;

    while((opt = getopt(argc, argv, "p:")) != -1)
    {
        switch(opt)
        {
            case 'p':
                port = atoi(optarg);
                cout << "Port: " << port << endl;
            break;
        }
    }

    // If there is no port we assign one
    if(port == -1)
    {
        port = 8080;
    }

    // First create a socket
    int client_sock, c, read_size;
    struct sockaddr_in server , client;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    
    // Check for error
    if (sock == -1)
    {
        cout << "Socket creation failed" << endl;
        exit(-1);
    }

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET; // Using TCP
    server.sin_addr.s_addr = INADDR_ANY; // 0.0.0.0
    server.sin_port = htons(port); // Using designated port
     
    // Bind the socket to a port
    if(bind(sock,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        cout << "Socket bind failed" << endl;
        exit(-1);
    }

    // Listen to the socket
    listen(sock , 3);
    cout << "Listening to port: " << port << endl;

    while(1)
    {
        char client_message[2048] = {0};
        // Accepting clients
        client_sock = accept(sock, (struct sockaddr *)&client, (socklen_t*)&c);
        if (client_sock < 0)
        {
            cout << "Failed to accept client" << endl;
            exit(-1);
        }

        // Read the clients message and send back something
        while((read_size = recv(client_sock , client_message , 2048 , 0)) > 0 )
        {
            //Send the message back to client
            cout << "Received from Client: " << client_message << endl;
            write(client_sock , client_message , strlen(client_message));
        }
    }

    return 0;
}