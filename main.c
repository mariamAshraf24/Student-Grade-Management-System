#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    int id;
    char name[50];
    int* scores;
    int numSubjects;
    float average;
    char grade;
} Student;

Student* students = NULL;
int studentCount = 0;

int isUniqueID(int id) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            return 0;
        }
    }
    return 1;
}

char assignGrade(float average) {
    if (average >= 90) return 'A';
    if (average >= 80) return 'B';
    if (average >= 70) return 'C';
    if (average >= 60) return 'D';
    return 'F';
}

void addStudent() {
    students = realloc(students, (studentCount + 1) * sizeof(Student));
    if (!students) {
        printf("Memory allocation failed. Exiting program.\n");
        exit(1);
    }

    Student *newStudent = &students[studentCount];

    printf("Enter student ID: ");
    scanf("%d", &newStudent->id);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == newStudent->id) {
            printf("Error: Student ID must be unique.\n");
            return;
        }
    }

    printf("Enter student name: ");
    scanf("%s", newStudent->name);

    printf("Enter number of subjects: ");
    scanf("%d", &newStudent->numSubjects);

    newStudent->scores = malloc(newStudent->numSubjects * sizeof(int));
    if (!newStudent->scores) {
        printf("Memory allocation failed. Exiting program.\n");
        exit(1);
    }

    for (int i = 0; i < newStudent->numSubjects; i++) {
        printf("Enter score for subject %d: ", i + 1);
        scanf("%d", &newStudent->scores[i]);
    }

    studentCount++;
    printf("Student added successfully!\n");
}

void updateStudent() {
    int id, found = 0;
    printf("Enter Student ID to update: ");
    scanf("%d", &id);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            found = 1;
            printf("Updating scores for %s (ID: %d)\n", students[i].name, students[i].id);

            for (int j = 0; j < students[i].numSubjects; j++) {
                printf("Enter new score for subject %d: ", j + 1);
                scanf("%d", &students[i].scores[j]);
            }

            printf("Scores updated successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("Student with ID %d not found.\n", id);
    }
}


void calculateGrades() {
    for (int i = 0; i < studentCount; i++) {
        int total = 0;
        if (students[i].numSubjects > 0) {
            for (int j = 0; j < students[i].numSubjects; j++) {
                total += students[i].scores[j];
            }
            students[i].average = (float)total / students[i].numSubjects;
        } else {
            students[i].average = 0;
        }
        students[i].grade = assignGrade(students[i].average);
    }
    printf("Grades calculated successfully!\n");
}

void displayResults() {
    if (studentCount == 0) {
        printf("No students available to display.\n");
        return;
    }

    printf("--- Student Results ---\n");
    for (int i = 0; i < studentCount; i++) {
        printf("ID: %d, Name: %s, Average: %.2f, Grade: %c\n",
               students[i].id, students[i].name, students[i].average, students[i].grade);
    }

    int highestIndex = 0;
    for (int i = 1; i < studentCount; i++) {
        if (students[i].average > students[highestIndex].average) {
            highestIndex = i;
        }
    }
    printf("\nStudent with highest average: %s (ID: %d) with %.2f\n",
           students[highestIndex].name, students[highestIndex].id, students[highestIndex].average);

    float overallAverage = 0;
    for (int i = 0; i < studentCount; i++) {
        overallAverage += students[i].average;
    }
    overallAverage /= studentCount;
    printf("Overall average score: %.2f\n\n", overallAverage);

    printf("Students who passed:\n");
    for (int i = 0; i < studentCount; i++) {
        if (students[i].grade != 'F') {
            printf("%s (ID: %d)\n", students[i].name, students[i].id);
        }
    }

    printf("\nStudents who failed:\n");
    for (int i = 0; i < studentCount; i++) {
        if (students[i].grade == 'F') {
            printf("%s (ID: %d)\n", students[i].name, students[i].id);
        }
    }
}

int main() {
    int choice;
    while (1) {
        printf("\n");
        printf("1. Add Student\n");
        printf("2. Update Student\n");
        printf("3. Calculate Grades\n");
        printf("4. Display Results\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                updateStudent();
                break;
            case 3:
                calculateGrades();
                break;
            case 4:
                displayResults();
                break;
            case 5:
                for (int i = 0; i < studentCount; i++) {
                    free(students[i].scores);
                }
                free(students);
                printf("Exiting the program. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

