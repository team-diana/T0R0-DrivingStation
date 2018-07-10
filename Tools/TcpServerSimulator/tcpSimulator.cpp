#include "TcpServer.h"

#include <stdio.h>
#include <unistd.h>

int main()
{
    TcpServer *serverLeft = new TcpServer(50100);
    serverLeft->start16();

    TcpServer *serverRight = new TcpServer(50101);
    serverRight->start16();

    uint16_t dataL = 0, dataR = 0;
    int valL = 0, valR = 0;
    printf("Server is listening...\n");

    while(true)
    {
        if(serverLeft->newDataAvailable())
        {
            dataL = serverLeft->readLast16();
            //valL = (int) dataL;
            printf("LEFT %hu\n", dataL);
        }

        if(serverRight->newDataAvailable())
        {
            dataR = serverRight->readLast16();
            //valR = (int) dataR;
            printf("RIGHT %hu\n", dataR);
        }
    }

    return 0;
}
