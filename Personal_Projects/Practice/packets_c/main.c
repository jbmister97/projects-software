#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define STX     0x01
#define ETX     0xF0

volatile bool complete = false;
int count;

void buildPacket(uint8_t *packet, uint8_t data)
{

}

int main()
{
    uint8_t bytes[] = {0x18,0x46,STX,0x04,0x08,0x0A,0x24,0x4A,ETX,0xDE,0xAF};
    uint8_t packet[256];    //packet with max 256 bytes

    int n = sizeof(bytes);
    int i = 0;

    count = 0;

    while(!complete && i < n) {

    }

    printf("Hello world!\n");
    return 0;
}
