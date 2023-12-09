// Header guard to prevent multiple inclusion of the header file
#ifndef HEADER_H_
#define HEADER_H_

// Include necessary standard C libraries
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// Define constants for maximum string length, number of subjects, and quantity of students
#define MAX_STR_LENGTH 100
#define MAX_NUM_OF_SUBJECTS 10
#define MAX_QUANTITY_OF_STUDENTS 180

// Declare an array to store student indices
int ind[MAX_QUANTITY_OF_STUDENTS];

// Define a structure to represent student information
struct studentInfo
{
    int ID;                          // Student ID
    char firstName[MAX_STR_LENGTH];  // First name of the student
    char lastName[MAX_STR_LENGTH];   // Last name of the student
    char patronymic[MAX_STR_LENGTH]; // Patronymic name of the student
    float totalGrade;                // Total grade of the student
};

// Define a structure to represent subject information
struct subjectInfo
{
    int subjectCredit;                // Credits for the subject
    char subjectName[MAX_STR_LENGTH]; // Name of the subject
    float grade;                      // Grade obtained in the subject
};

#endif // End of the header file