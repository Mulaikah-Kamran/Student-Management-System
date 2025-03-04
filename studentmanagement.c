#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define structure for student
struct Student {
    int id;
    char name[50];
    float marks;
};

// Function prototypes
void addStudent();
void viewStudents();
void searchStudent();
void sortStudents();
void deleteStudent();
int studentCount();

// File to store students
#define FILE_NAME "students.txt"

int main() {
    int choice;
    do {
        printf("\n===== Student Management System =====\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Search Student\n");
        printf("4. Sort Students by Name\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // Consume newline

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: searchStudent(); break;
            case 4: sortStudents(); break;
            case 5: deleteStudent(); break;
            case 6: printf("Exiting program...\n"); break;
            default: printf("Invalid choice! Try again.\n");
        }
    } while (choice != 6);

    return 0;
}

// Function to add student record
void addStudent() {
    struct Student s;
    FILE *file = fopen(FILE_NAME, "a");

    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Student ID: ");
    scanf("%d", &s.id);
    getchar();  // Consume newline
    printf("Enter Name: ");
    fgets(s.name, 50, stdin);
    s.name[strcspn(s.name, "\n")] = 0;  // Remove newline
    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fprintf(file, "%d,%s,%.2f\n", s.id, s.name, s.marks);
    fclose(file);

    printf("Student added successfully!\n");
}

// Function to view all students
void viewStudents() {
    struct Student s;
    FILE *file = fopen(FILE_NAME, "r");

    if (!file) {
        printf("No student records found!\n");
        return;
    }

    printf("\nID\tName\t\tMarks\n");
    printf("----------------------------\n");
    while (fscanf(file, "%d,%49[^,],%f\n", &s.id, s.name, &s.marks) != EOF) {
        printf("%d\t%-15s %.2f\n", s.id, s.name, s.marks);
    }

    fclose(file);
}

// Function to search a student by ID
void searchStudent() {
    struct Student s;
    int searchID, found = 0;
    FILE *file = fopen(FILE_NAME, "r");

    if (!file) {
        printf("No student records found!\n");
        return;
    }

    printf("Enter Student ID to search: ");
    scanf("%d", &searchID);

    while (fscanf(file, "%d,%49[^,],%f\n", &s.id, s.name, &s.marks) != EOF) {
        if (s.id == searchID) {
            printf("Student Found: ID: %d, Name: %s, Marks: %.2f\n", s.id, s.name, s.marks);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student not found!\n");
    }

    fclose(file);
}

// Function to sort students by name
void sortStudents() {
    struct Student students[100];
    int count = 0, i, j;
    FILE *file = fopen(FILE_NAME, "r");

    if (!file) {
        printf("No student records found!\n");
        return;
    }

    while (fscanf(file, "%d,%49[^,],%f\n", &students[count].id, students[count].name, &students[count].marks) != EOF) {
        count++;
    }
    fclose(file);

    // Sorting using Bubble Sort
    struct Student temp;
    for (i = 0; i < count - 1; i++) {
        for (j = i + 1; j < count; j++) {
            if (strcmp(students[i].name, students[j].name) > 0) {
                temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }

    // Write sorted students back to file
    file = fopen(FILE_NAME, "w");
    for (i = 0; i < count; i++) {
        fprintf(file, "%d,%s,%.2f\n", students[i].id, students[i].name, students[i].marks);
    }
    fclose(file);

    printf("Students sorted by name successfully!\n");
}

// Function to delete a student by ID
void deleteStudent() {
    struct Student students[100];
    int count = 0, i, deleteID, found = 0;
    FILE *file = fopen(FILE_NAME, "r");

    if (!file) {
        printf("No student records found!\n");
        return;
    }

    while (fscanf(file, "%d,%49[^,],%f\n", &students[count].id, students[count].name, &students[count].marks) != EOF) {
        count++;
    }
    fclose(file);

    printf("Enter Student ID to delete: ");
    scanf("%d", &deleteID);

    file = fopen(FILE_NAME, "w");
    for (i = 0; i < count; i++) {
        if (students[i].id == deleteID) {
            found = 1;
            continue;
        }
        fprintf(file, "%d,%s,%.2f\n", students[i].id, students[i].name, students[i].marks);
    }
    fclose(file);

    if (found) {
        printf("Student deleted successfully!\n");
    } else {
        printf("Student not found!\n");
    }
}

