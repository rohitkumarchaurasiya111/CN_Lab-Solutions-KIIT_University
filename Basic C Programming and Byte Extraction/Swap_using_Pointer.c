// 1. Write a C program to swap the content of 2 variables using pointer.

#include <stdio.h>
void swap(int *a, int *b);
int main()
{
    int num1;
    int num2;
    printf("Enter two numbers to swap:\n");
    scanf("%d", &num1);
    scanf("%d", &num2);
    int *p = &num1;
    int *q = &num2;
    printf("Before Swap: %d and %d\n", num1, num2);
    swap(p, q);
    printf("After Swap: %d and %d", num1, num2);
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}