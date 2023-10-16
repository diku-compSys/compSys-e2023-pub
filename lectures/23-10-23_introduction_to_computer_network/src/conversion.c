#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <string.h>

#ifdef __APPLE__
#include "./endian.h"
#else
#include <endian.h>
#endif

typedef struct NetworkMessage {
    uint32_t i;
    uint32_t j;
} NetworkMessage_t;

int main() 
{
    uint8_t one_start = 4;
    uint16_t two_start = 12840;
    uint32_t four_start = 5463300;
    uint64_t eight_start = 7980987145;

    printf("Starting values are:        %d, %d, %d, %ld\n\n", 
        one_start, two_start, four_start, eight_start);

    // Task 1. Update these four assignments so that they are dynamically
    // converted from host-byte-order to network-byte-order (e.g. little-endian
    // to big-endian)
    uint8_t one_network = 0;
    uint16_t two_network = 0;
    uint32_t four_network = 0; 
    uint64_t eight_network = 0;

    printf("Network values should be:   %d, %d, %d, %ld\n", 
        4, 10290, 73224960, 663072422861209600);
    printf("Network values are:         %d, %d, %d, %ld\n\n", 
        one_network, two_network, four_network, eight_network);

    // Task 2. Update these four assignments so that they are dynamically
    // converted from network-byte-order to host-byte-order (e.g. big-endian to
    // little-endian)
    uint8_t one_host = 0;
    uint16_t two_host = 0;
    uint32_t four_host = 0; 
    uint64_t eight_host = 0;

    printf("Host values should be:      %d, %d, %d, %ld\n", 
        4, 12840, 5463300, 7980987145);
    printf("Host values are:            %d, %d, %d, %ld\n\n", 
        one_host, two_host, four_host, eight_host);

    // Task 3. Hopefully by now you've noticed that the uint8_t value does not
    // get converted. Describe why this is.

    char buffer[8] = {4, 24, 102, 7, 0, 89, 24, -92};

    // Task 4. In the above char array, which simulates a message read from the
    // network, the first 4 bytes should be read as one number, and the final 4
    // bytes as another. Extract these. Note that first has been *partially* 
    // implemented but you should be aware that as this is supposedly a 
    // networked message it will be network-byte-order

    uint32_t first = *(uint32_t*)&buffer[0]; // This is not complete
    uint32_t second = 0;

    printf("Extacted values should be:      %d, %d, \n", 68707847, 5839012);
    printf("Extacted values are:            %d, %d, \n\n", first, second);
}
