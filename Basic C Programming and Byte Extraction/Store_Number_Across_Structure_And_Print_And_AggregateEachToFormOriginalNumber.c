/* Write a C Program to enter a number and store the number across the following structure and print the
content of each member of the structure. Then aggregate each member of the structure to form the
original number and print the same.
struct pkt{
char ch1;
char ch2[2];
char ch3;
}; */
#include <stdio.h>

struct pkt {
    char ch1;
    char ch2[2];
    char ch3;
};

int main() {
    struct pkt data;
    int num;

    printf("Enter a number: ");
    scanf("%d", &num);

    data.ch1 =  num & 0xFF;
    data.ch2[0] = (num >> 8) & 0xFF;
    data.ch2[1] = (num >> 16) & 0xFF;
    data.ch3 = (num >> 24) & 0xFF;

    printf("ch1: %d\n", data.ch1);
    printf("ch2[0]: %d\n", data.ch2[0]);
    printf("ch2[1]: %d\n", data.ch2[1]);
    printf("ch3: %d\n", data.ch3);

    int reconstructed_num = (data.ch1 ) | (data.ch2[0] << 8) | (data.ch2[1] << 16) | data.ch3<<24;
    printf("Reconstructed Number: %d\n", reconstructed_num);

    return 0;
}
