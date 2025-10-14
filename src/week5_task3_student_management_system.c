// week5_task3_student_management_system.c
// Task 3: Mini-project – Student management system with file persistence
// Week 5 – Files & Modular Programming
// TODO: Implement functions to load, save, add, and list students.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LEN 50
#define DATA_FILE "students.txt"

typedef struct {
    char name[NAME_LEN];
    int id;
    float gpa;
} Student;

// Function prototypes
int load_students(Student arr[]);
void save_students(Student arr[], int count);
void add_student(Student arr[], int *count);
void list_students(Student arr[], int count);

int main(void) {
    Student students[MAX_STUDENTS];
    int count = 0;
    int choice;

    // TODO: Load existing data from file using load_students()

    do {
        printf("\n=== Student Management System ===\n");
        printf("1. List students\n");
        printf("2. Add student\n");
        printf("3. Save and Exit\n");
        printf("Select an option: ");
        scanf("%d", &choice);
        getchar(); // clear newline

        switch (choice) {
            case 1:
                // TODO: Call list_students()
                list_students(students,count);
                break;
            case 2:
                // TODO: Call add_student()
                add_student(students,&count);
                break;
            case 3:
                // TODO: Call save_students() and exit loop
                save_students(students,count);
                printf("Data saved.Existing...\n");
                break;
            default:
                printf("Invalid option. Try again.\n");
        }
    } while (choice != 3);

    return 0;
}

// TODO: Implement load_students()
// Open DATA_FILE, read records until EOF, return number of records loaded
int load_students(Student arr[]) {
FILE *fp = fopen(DATA_FILE, "r");
    if (fp == NULL) {
        // No file yet, return 0 students
        return 0;
    
}
int count = 0;
    while (count < MAX_STUDENTS &&
           fscanf(fp, "%49s %d %f", arr[count].name, &arr[count].id, &arr[count].gpa) == 3) {
        count++;
    }
    fclose(fp);
    return count;
}

// TODO: Implement save_students()
// Write all students to DATA_FILE
void save_students(Student arr[], int count) {
 FILE *fp = fopen(DATA_FILE, "w");
    if (fp == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
     for (int i = 0; i < count; i++) {
        fprintf(fp, "%s %d %.2f\n", arr[i].name, arr[i].id, arr[i].gpa);
    }
fclose(fp);
}

// TODO: Implement add_student()
// Read input from user and append to array
void add_student(Student arr[], int *count) {
    if (*count >= MAX_STUDENTS) {
        printf("Cannot add more students. Maximum reached.\n");
        return;
}
Student s;
    printf("Enter name: ");
    scanf("%49s", s.name);
    printf("Enter ID: ");
    scanf("%d", &s.id);
    printf("Enter GPA: ");
    scanf("%f", &s.gpa);

    arr[*count] = s;
    (*count)++;

    printf("Student added successfully!\n");
}

// TODO: Implement list_students()
// Print all students in readable format
void list_students(Student arr[], int count) {
    if (count == 0) {
        printf("No students found.\n");
        return;
}
printf("\n--- Student List ---\n");
    for (int i = 0; i < count; i++) {
        printf("%d) Name: %s | ID: %d | GPA: %.2f\n",
               i + 1, arr[i].name, arr[i].id, arr[i].gpa);
        }
    }
