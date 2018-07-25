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



    TcpServer *serverA1 = new TcpServer(50150);
    serverA1->start16();
    TcpServer *serverA2 = new TcpServer(50151);
    serverA2->start16();
    TcpServer *serverA3 = new TcpServer(50152);
    serverA3->start16();
    TcpServer *serverA4 = new TcpServer(50153);
    serverA4->start16();
    TcpServer *serverA5 = new TcpServer(50154);
    serverA5->start16();
    TcpServer *serverA6 = new TcpServer(50155);
    serverA6->start16();
    TcpServer *serverA7 = new TcpServer(50156);
    serverA7->start16();


    uint16_t dataFL = 0, dataFR = 0, dataRL = 0, dataRR = 0;
    uint16_t arm1=0, arm2=0, arm3=0, arm4=0, arm5=0, arm6=0, arm7=0;
    printf("Server is listening...\n\n");
    printf(" ----------------------------------------\n");


    while(true)
    {
        if(serverFrontLeft->newDataAvailable())
        {
            dataFL = serverFrontLeft->readLast16();
        }

        if(serverFrontRight->newDataAvailable())
        {
            dataFR = serverFrontRight->readLast16();
        }

        if(serverRearLeft->newDataAvailable())
        {
            dataRL = serverRearLeft->readLast16();
        }

        if(serverRearRight->newDataAvailable())
        {
            dataRR = serverRearRight->readLast16();
        }


        if (serverA1->newDataAvailable())
        {
            arm1 = serverA1->readLast16();
        }
        if (serverA2->newDataAvailable())
        {
            arm2 = serverA2->readLast16();
        }
        if (serverA3->newDataAvailable())
        {
            arm3 = serverA3->readLast16();
        }
        if (serverA4->newDataAvailable())
        {
            arm4 = serverA4->readLast16();
        }
        if (serverA5->newDataAvailable())
        {
            arm5 = serverA5->readLast16();
        }
        if (serverA6->newDataAvailable())
        {
            arm6 = serverA6->readLast16();
        }
        if (serverA7->newDataAvailable())
        {
            arm7 = serverA7->readLast16();
        }

        printf(" |FL %5hu | RL %5hu | FR %5hu | RR %5hu || A1 %5hu | A2 %5hu | A3 %5hu | A4 %5hu | A5 %5hu | A6 %5hu | A7 %5hu | \r", dataFL, dataRL, dataFR, dataRR, arm1, arm2, arm3, arm4, arm5, arm6, arm7);
        fflush(stdout);
    }
    printf(" \n----------------------------------------\n");
    return 0;
}
