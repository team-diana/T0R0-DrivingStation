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
    uint16_t vec[10] = {0, 32768, 65535, 20123, 49654};

    for (int i=0; i<5; i++) printf("%d\t%u\n", i, vec[i]);

    while(true)
    {
        if(serverLeft->newDataAvailable())
        {
            dataL = serverLeft->readLast16();

            //valL = (int) dataL;
            printf("LEFT %hhu\n", dataL);
        }

        if(serverRight->newDataAvailable())
        {
            dataR = serverRight->readLast16();
            valR = (int) dataR;
            printf("RIGHT %d\n", valR);
        }
    }

    return 0;
}
