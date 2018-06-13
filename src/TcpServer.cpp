#include "TcpServer.h"

TcpServer::TcpServer(int port)
{
    int opt = 1;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    addrlen = sizeof(address);
      
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        return;
    }
     
    // Forcefully attaching socket to the port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        return;
    }
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        return;
    }
    if (listen(server_fd, 2) < 0)
    {
        perror("listen");
        return;
    }

    last8 = 0;
    last16 = 0;

    new_data_available = false;
}

TcpServer::~TcpServer()
{
    close(server_fd);

    for(int i = 0; i < sockets.size(); i++)
    {
        close(sockets[i]);
    }

    sockets.clear();
}

void TcpServer::start8()
{
    bytes_waited = 1;
    wc = std::thread(&TcpServer::waitForConnection, this);
}

void TcpServer::start16()
{
    bytes_waited = 2;
    wc = std::thread(&TcpServer::waitForConnection, this);
}

void TcpServer::waitForConnection()
{
    int sock;

    while(true)
    {
        if ((sock = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0)
        {
        }
        else
        {
            sockets.push_back(sock);

            if(bytes_waited == 1)
                readers.push_back(std::thread(&TcpServer::read8, this, sockets.size() - 1));
            else if(bytes_waited == 2)
                readers.push_back(std::thread(&TcpServer::read16, this, sockets.size() - 1));
        }
    }
}

void TcpServer::read8(int sockid)
{
    int n_bytes;
    uint8_t data;

    while(true)
    {
        n_bytes = read(sockets[sockid], &data, 1);

        if(n_bytes == -1)
            exit(0);
        else if(n_bytes == 1)
        {
            last8 = data;
            new_data_available = true;
        }
    }
}

void TcpServer::read16(int sockid)
{
    int n_bytes;
    uint16_t data;

    while(true)
    {
        n_bytes = read(sockets[sockid], &data, 2);

        if(n_bytes == -1)
         exit(0);
        else if(n_bytes == 2)
        {
            last16 = data;
            new_data_available = true;
        }
    }
}

uint8_t TcpServer::readLast8()
{
    new_data_available = false;
    return last8;
}

uint16_t TcpServer::readLast16()
{
    new_data_available = false;
    return last16;
}

bool TcpServer::newDataAvailable()
{
    return new_data_available;
}