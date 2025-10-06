/*
 * week4_2_struct_student.c
 * Author: [Kamal Orujov]
 * Student ID: [241ADB13]
 * Description:
 *   Demonstrates defining and using a struct in C.
 *   Students should define a 'Student' struct with fields like name, id, and grade.
 *   Then create a few instances and print them.
 */

#include <stdio.h>
#include <string.h>

// TODO: Define struct Student with fields: name (char[]), id (int), grade (float)
struct Student {
    char name[50];
    int id;
    float grade;
};
// Example:
// struct Student {
//     char name[50];
//     int id;
//     float grade;
// };

int main(void) {
    // TODO: Declare one or more Student variables
    struct Student student1, student2;

    // TODO: Assign values (either manually or via scanf)
strcpy(student1.name, "Alice");
    student1.id = 1001;
    student1.grade = 88.5;

    strcpy(student2.name, "Bob");
    student2.id = 1002;
    student2.grade = 91.0;
    // TODO: Print struct contents using printf
printf("Student 1:\n");
    printf("  Name : %s\n", student1.name);
    printf("  ID   : %d\n", student1.id);
    printf("  Grade: %.2f\n\n", student1.grade);

    printf("Student 2:\n");
    printf("  Name : %s\n", student2.name);
    printf("  ID   : %d\n", student2.id);
    printf("  Grade: %.2f\n", student2.grade);
printf("Student 1:\n");
    printf("  Name : %s\n", student1.name);
    printf("  ID   : %d\n", student1.id);
    printf("  Grade: %.2f\n\n", student1.grade);

    printf("Student 2:\n");
    printf("  Name : %s\n", student2.name);
    printf("  ID   : %d\n", student2.id);
    printf("  Grade: %.2f\n", student2.grade);
    return 0;
}
