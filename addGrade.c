#include "header.h" // Include the custom header file that defines structures and function prototypes

/**
 * Function to get a floating-point number from the user input.
 * This function uses fgets to get input and converts it to a float.
 *
 * @return float - The floating-point number entered by the user.
 */
float isFloat()
{
    char input[MAX_STR_LENGTH];  // Buffer to store user input
    int isNumber = 0;  // Flag to check if the input is a valid number

    // Keep prompting the user until a valid number is entered
    do 
    {
        // Get user input using fgets
        fgets(input, sizeof(input), stdin);

        // Convert input to a number using strtod
        char *endptr;
        double number = strtod(input, &endptr);

        // Check if the conversion was successful and if the entire string was consumed
        if (*endptr == '\n' || *endptr == '\0')
        {
            isNumber = 1;  // Set the flag to indicate a valid number
        } 
        else 
        {
            // Display an error message for invalid input
            printf("\t\t\t\t\t\t\tInvalid input. Please enter a valid number.\n");
            printf("\t\t\t\t\t\t\tEnter the student's grade again: ");
        }
        
    } while (!isNumber);  // Continue the loop until a valid number is entered
    
    // Convert the input string to a float and return
    float num = atof(input);
    return num;
}

// Function to calculate and record grades for a student
/**
 * @brief Calculates and records grades for a student.
 *
 * This function prompts the user to enter grades for each subject, validates the input,
 * calculates the total grade, and records the information in the "studentGrades.txt" file.
 *
 * @param studentID The ID of the student.
 */
void calculateGrade(int studentID)
{
    int numOfSubjects = countSubjects(), tempIndex;

    FILE *fptr;
    fptr = fopen("studentGrades.txt", "a");
    struct studentInfo newStudent;

    if (fptr != NULL)
    {
        for (tempIndex = 0; tempIndex < numOfSubjects; tempIndex++)
        {
            // Prompt the user to enter the student's grade for each subject
            printf("\t\t\t\t\t\t\tEnter the student's grade for %s(from 0 to 20): ", sp[tempIndex].subjectName);
        
            sp[tempIndex].grade = isFloat();

            // Validate the entered grade
            while (sp[tempIndex].grade < 0 || sp[tempIndex].grade > 20)
            {
                // Display an error message and prompt the user for input again
                printf("\t\t\t\t\t\t\tError in grade!\n");
                printf("\t\t\t\t\t\t\tPlease, enter the student's grade for %s again: ", sp[tempIndex].subjectName);
                sp[tempIndex].grade = isFloat();
            }

            // Calculate the total grade for the student
            newStudent.totalGrade += (sp[tempIndex].subjectCredit * sp[tempIndex].grade);
        }

        char str[100], strID[100];
        sprintf(str, "%f", newStudent.totalGrade);
        sprintf(strID, "%d", studentID);

        // Write the student ID and total grade to the file
        fprintf(fptr, "%d %f\n", studentID, newStudent.totalGrade);
        printf("\t\t\t\t\t\t\tThe information was recorded successfully.\n\n");
    }
    else
    {
        // Display an error message if the file cannot be opened and exit the program
        printf("\t\t\t\t\t\t\tCannot open the file.\n\n");
        exit(EXIT_FAILURE);
    }

    fclose(fptr);
}

// Function to check if a student has already been graded
/**
 * @brief Checks if a student has already been graded.
 *
 * This function checks if a given student ID exists in the "studentGrades.txt" file.
 * If the ID is found, the user is prompted to enter a new ID; otherwise, the function proceeds to calculate grades.
 *
 * @param studentID The ID of the student.
 * @param numOfStudents The total number of students.
 */
void findExistingID(int numOfStudents)
{
    int ind[100], tempIndex = 0, studentID;
    int *num = readStudentIDs();
    char arr[100];
    bool True = true;

    FILE *fptr;
    fptr = fopen("studentGrades.txt", "r");

    if (fptr != NULL)
    {
        // Read existing student IDs from the "studentGrades.txt" file
        while (fscanf(fptr, "%s %*s", arr) == 1)
        {
            ind[tempIndex] = atoi(arr);
            tempIndex++;
        }

        // Check if all students are already graded
        if (numOfStudents == tempIndex)
        {
            printf("\t\t\t\t\t\t\tAll students are already graded.\n\n");
            return;
        }

        printf("\t\t\t\t\t\t\tEnter the student's ID: ");
        studentID = isDigit();

        while (True)
        {
            tempIndex = 0;
            True = false;

            // Check if the entered student ID is already graded
            while (ind[tempIndex])
            {
                if (ind[tempIndex] == studentID)
                {
                    // Display an error message and prompt the user for input again
                    printf("\t\t\t\t\t\t\tStudent is already graded.\n");
                    printf("\t\t\t\t\t\t\tEnter the student's ID again: ");
                    studentID = isDigit();
                    True = true;
                    break;
                }
                else
                    tempIndex++;
            }
        }
    }
    else
    {
        // Display an error message if the file cannot be opened and exit the program
        printf("\t\t\t\t\t\t\tCannot open the file.\n\n");
        exit(EXIT_FAILURE);
    }

    fclose(fptr);

    FILE *fpt;
    fpt = fopen("studentInformation.txt", "r");

    if (fpt != NULL)
    {
        while (True == false)
        {
            tempIndex = 0;

            // Check if the entered student ID exists in the "studentInformation.txt" file
            while (*(num + tempIndex))
            {
                if (*(num + tempIndex) == studentID)
                {
                    fclose(fpt);
                    calculateGrade(studentID);
                    True = true;
                    break;
                }
                else
                    tempIndex++;
            }

            // Prompt the user for a new student ID if the entered ID is not found
            if (!(*(num + tempIndex)))
            {
                printf("\t\t\t\t\t\t\tNon-existent ID! Enter a valid ID.\n");
                printf("\t\t\t\t\t\t\tEnter the student's ID again: ");
                studentID = isDigit();
            }
        }
    }
    else
    {
        // Display an error message if the file cannot be opened and exit the program
        printf("\t\t\t\t\t\t\tCannot open the file.\n\n");
        exit(EXIT_FAILURE);
    }
}