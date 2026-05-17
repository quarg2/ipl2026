// Bitfields

#include <stdio.h>

typedef struct {
    unsigned int firstBit  : 1;
    unsigned int secondBit : 1;
    unsigned int thirdBit  : 1;
} Bitfield;

int main(void) {
    Bitfield a = {0, 1, 1};

    printf("Size of bitfield: %zu\n", sizeof(a));

    printf("Value of firstBit: %u\n", a.firstBit);
    printf("Value of firstBit: %u\n", a.secondBit);
    printf("Value of firstBit: %u\n", a.thirdBit);
    
    return 0;
}
