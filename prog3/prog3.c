// Write a function to print the bits of an integer
// Write a function to count the number of high bits in an integer

#include <limits.h>
#include <stdio.h>

#define INT_BITS (sizeof(int) * CHAR_BIT)

void printBits(unsigned int num);
int highBits(unsigned int num);

int main(void) {
    unsigned num;

    printf("Enter a number: ");
    scanf("%u", &num);

    printBits(num);
    printf("Number of 1s in binary representation of %u is %d\n", num,
           highBits(num));
    return 0;
}

int highBits(unsigned int num) {
    int count = 0;

    for (unsigned int i = 0; i < INT_BITS; i++) {
        if (((num >> (INT_BITS - 1)) & 01) == 1) count++;
        num <<= 1;
    }
    return count;
}

void printBits(unsigned int num) {
    char buf[sizeof(int) * CHAR_BIT] = "";
    unsigned int i                   = 0;

    do {
        buf[i++] = (((num >> (INT_BITS - 1)) & 01) == 1) ? '1' : '0';
        num <<= 1;
    } while (i < INT_BITS);

    buf[i] = '\0';
    printf("%s\n", buf);
}
