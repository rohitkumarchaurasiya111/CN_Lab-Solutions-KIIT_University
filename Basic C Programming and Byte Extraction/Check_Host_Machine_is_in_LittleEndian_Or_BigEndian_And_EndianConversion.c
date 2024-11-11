/* Write a C program to check whether the Host machine is in Little Endian or Big Endian. Enter a
number, print the content of each byte location and Convert the Endianness of the same i.e. Little to Big
Endian and vice-versa. */
#include <stdio.h>

void check_endianness() {
    unsigned int x = 1;
    char *c = (char*)&x;  // Correctly cast to a char pointer
    if (*c) {
        printf("Host Machine is Little Endian\n");
    } else {
        printf("Host Machine is Big Endian\n");
    }
}

unsigned int reverse_endianness(unsigned int num) {
    unsigned int b0, b1, b2, b3;
    b0 = (num & 0x000000ff) << 24u;
    b1 = (num & 0x0000ff00) << 8u;
    b2 = (num & 0x00ff0000) >> 8u;
    b3 = (num & 0xff000000) >> 24u;
    return (b0 | b1 | b2 | b3);
}

int main() {
    unsigned int num;
    printf("Enter a number: ");
    scanf("%u", &num);
    check_endianness();

    printf("Original Number: %u\n", num);
    printf("Bytes of the number: ");
    for (int i = 0; i < 4; ++i) {
        printf("%02x ", ((unsigned char*)&num)[i]);
    }
    printf("\n");

    unsigned int reversed = reverse_endianness(num);
    printf("Number after endianness conversion: %u\n", reversed);
    printf("Bytes after conversion: ");
    for (int i = 0; i < 4; ++i) {
        printf("%02x ", ((unsigned char*)&reversed)[i]);
    }
    printf("\n");
    return 0;
}

