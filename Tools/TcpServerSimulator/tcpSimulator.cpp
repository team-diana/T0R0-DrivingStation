#include "TcpServer.h"

#include <stdio.h>
#include <unistd.h>

int main()
{
    TcpServer *serverFrontRight = new TcpServer(50100);
    serverFrontRight->start16();

    TcpServer *serverFrontLeft = new TcpServer(50101);
    serverFrontLeft->start16();

    TcpServer *serverRearLeft = new TcpServer(50102);
    serverRearLeft->start16();

    TcpServer *serverRearRight = new TcpServer(50103);
    serverRearRight->start16();

    uint16_t dataFL = 0, dataFR = 0, dataRL = 0, dataRR = 0;
    printf("Server is listening...\n\n\n\n\n\n\n\n\n\n\n");


    while(true)
    {
        if(serverFrontLeft->newDataAvailable())
        {
            dataFL = serverFrontLeft->readLast16();
            //printf("%12s%hu\n", "FRONT LEFT", dataFL);
        }

        if(serverFrontRight->newDataAvailable())
        {
            dataFR = serverFrontRight->readLast16();
            //printf("%12s%hu\n", "FRONT RIGHT", dataFR);
        }

        if(serverRearLeft->newDataAvailable())
        {
            dataRL = serverRearLeft->readLast16();
            //printf("%12s%hu\n", "REAR LEFT", dataRL);
        }

        if(serverRearRight->newDataAvailable())
        {
            dataRR = serverRearRight->readLast16();
            //printf("%12s%hu\n", "REAR RIGHT", dataRR);
        }
        printf("|LF %5hu | LR %5hu | RL %5hu | RR %5hu | \r", dataFL, dataFR, dataRL, dataRR);
    }

    return 0;
}
