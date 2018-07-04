#include "TcpServer.h"

#include <stdio.h>
#include <unistd.h>

int main()
{
    TcpServer *serverLeft = new TcpServer(50100);
    serverLeft->start16();

    TcpServer *serverRight = new TcpServer(50101);
    serverRight->start16();

    while(true)
    {
        if(serverLeft->newDataAvailable())
        {
            uint16_t data = serverLeft->readLast16();
            printf("LEFT %u\n", data);
        }

        if(serverRight->newDataAvailable())
        {
            uint16_t data = serverRight->readLast16();
            printf("RIGHT %u\n", data);
        }
    }

    return 0;
}
