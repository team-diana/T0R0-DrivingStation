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
  running = false;

  wc.join();

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

    while(running)
    {
        if ((sock = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0)
        {
        }
        else
        {
            sockets.push_back(sock);

            if(bytes_waited == 1)
                readers.push_back(std::thread(&TcpServer::pop8, this, sockets.size() - 1));
            else if(bytes_waited == 2)
                readers.push_back(std::thread(&TcpServer::pop16, this, sockets.size() - 1));
        }
    }

    for(int i = 0; i < readers.size(); i++)
    {
      readers[i].join();
    }
}

void TcpServer::pop8(int sockid)
{
    int n_bytes;
    uint8_t data;

    while(running)
    {
        n_bytes = read(sockets[sockid], &data, 1);

        if(n_bytes == -1)
            exit(0);
        else if(n_bytes == 1)
        {
            last8 = data;
            vec8.push_back(last8);
            new_data_available = true;
        }
    }
}

void TcpServer::pop16(int sockid)
{
    int n_bytes;
    uint8_t data[2];

    while(running)
    {
        n_bytes = read(sockets[sockid], data, 2);

        if(n_bytes == -1)
         exit(0);
        else if(n_bytes == 2)
        {
            last16 = (data[0] * 256) + data[1];
            vec16.push_back(last16);
            new_data_available = true;
        }
    }
}

uint8_t TcpServer::readLast8()
{
    new_data_available = false;
    vec8.clear();
    return last8;
}

uint16_t TcpServer::readLast16()
{
    new_data_available = false;
    vec16.clear();
    return last16;
}

uint8_t TcpServer::read8()
{
  uint8_t data;

  if(vec8.size() > 0)
  {
    data = vec8[0];
    vec8.erase(vec8.begin());

    if(vec8.size() == 0)
      new_data_available = false;

    return data;
  }
  else
    return 0;
}

uint16_t TcpServer::read16()
{
  uint16_t data;

  if(vec16.size() > 0)
  {
    data = vec16[0];
    vec16.erase(vec16.begin());

    if(vec16.size() == 0)
      new_data_available = false;

    return data;
  }
  else
    return 0;
}

void TcpServer::flush()
{
  vec8.clear();
  vec16.clear();
  new_data_available = false;
}

bool TcpServer::newDataAvailable()
{
    return new_data_available;
}
