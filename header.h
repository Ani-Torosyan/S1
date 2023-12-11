// This header file contains declarations and definitions for managing student records.
// It includes necessary standard C libraries and defines constants for string length and the maximum quantity of students.

// Prevent multiple inclusion of the header file
#ifndef HEADER_H_
#define HEADER_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// Maximum length for strings and the maximum number of students
#define MAX_STR_LENGTH 256
#define MAX_QUANTITY_OF_STUDENTS 180

// Array to store student indices
int ind[MAX_QUANTITY_OF_STUDENTS];

// Structure to represent student information
struct studentInfo
{
    int ID;                          // Student ID
    char firstName[MAX_STR_LENGTH];  // First name of the student
    char lastName[MAX_STR_LENGTH];   // Last name of the student
    char patronymic[MAX_STR_LENGTH]; // Patronymic name of the student
    float totalGrade;                // Total grade of the student
};

// Structure to represent subject information
struct subjectInfo
{
    int subjectCredit;                // Credits for the subject
    char subjectName[MAX_STR_LENGTH]; // Name of the subject
    float grade;                      // Grade obtained in the subject
};

// Pointer to store an array of subjectInfo structures
struct subjectInfo *sp;
// Global variable to store information about a new student
struct studentInfo newStudent;

// Function prototypes
int countSubjects(); // Counts the number of subjects
void addSubjects(int totalNumOfSubjects); // Adds subjects to the global array of subjectInfo
int *readStudentIDs(); // Reads and returns an array of student IDs
int isDigit(); // Checks if the input is int
float isFloat(); // Checks if the input is float
int checkID(int studentID, int *ind); // Checks if a student ID already exists
void validName(char name[]); // Validates the entered name
int addStudent(int totalNumberOfStudents); // Adds a new student to the records
void calculateGrade(int studentID); // Calculates the total grade for a student
void findExistingID(int numOfStudents); // Finds an existing student ID in the records
int scholarship25(int numOfStudents); // Identifies students eligible for a 25% scholarship
int scholarship50(int numOfStudents); // Identifies students eligible for a 50% scholarship
int scholarship100(int numOfStudents); // Identifies students eligible for a 100% scholarship
void swapFloat(float *xp, float *yp); // Swaps two float values
void swapInt(int *xp, int *yp); // Swaps two int values
void bubbleSort(float arr[], int arrID[], int numOfElements); // Performs bubble sort on float and int arrays
void displayStudentInfoByID(float grades[], int studentIndices[], bool sortRanks, int totalNumberOfStudents); // Displays student information by ID
void sortRecords(bool sort, int numOfStudents); // Sorts student records based on grades
int deleteStudent(int studentID, int numOfStudents); // Deletes a student record

#endif // End of the header file