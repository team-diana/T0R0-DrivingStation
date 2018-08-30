#ifndef TCPSERVER
#define TCPSERVER

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <signal.h>
#include <thread>
#include <vector>
#include <iostream>

class TcpServer
{
    public:
        TcpServer(int port);
        ~TcpServer();

        void start8();
        void start16();

        uint8_t read8();
        uint16_t read16();
        uint8_t readLast8();
        uint16_t readLast16();
        void flush();

        bool newDataAvailable();

    private:
        int port;
        int server_fd;
        struct sockaddr_in address;
        int addrlen;

        std::vector<int> sockets;
        std::vector<std::thread> readers;
        std::thread wc;

        int bytes_waited;
        uint8_t last8;
        uint16_t last16;
        std::vector<uint8_t> vec8;
        std::vector<uint16_t> vec16;

        bool new_data_available;
        bool running = true;

        void waitForConnection();
        void pop8(int sockid);
        void pop16(int sockid);
};

#endif
