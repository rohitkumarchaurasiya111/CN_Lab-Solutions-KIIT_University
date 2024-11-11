// Write a C program to assign values to each members of the following structure. Pass the populated structure to a function Using call-by address and print the value of each member of the structure with in that function.
//  struct info{
//  int roll_no;
//  char name[50];
//  float CGPA;
//  }

#include <stdio.h>
struct info
{
    int roll_no;
    char name[50];
    float CGPA;
};
void print_value(struct info *Student);

int main()
{
    struct info Student;
    printf("Enter Roll NO of student: ");
    scanf("%d", &Student.roll_no);
    printf("Enter Name of Student: ");
    scanf(" %[^\n]s", &Student.name);
    printf("Enter CGPA of Student: ");
    scanf("%f", &Student.CGPA);

    print_value(&Student);
}

void print_value(struct info *Student)
{
    printf("\nName: %s\n", Student->name);
    printf("Roll No: %d\n", Student->roll_no);
    printf("CGPA: %f\n", Student->CGPA);
}