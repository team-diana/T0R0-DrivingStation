#ifndef TCPCLIENT
#define TCPCLIENT

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>

class TcpClient
{
    public:
        TcpClient(const char* address, int port);
        ~TcpClient();

        void send8(uint8_t data);
        void send16(uint16_t data);

        bool isConnected();

    private:
        int sock;
        int port;
        char address[16];

        bool connected;
};

#endif
