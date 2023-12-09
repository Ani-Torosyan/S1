#include "header.h" // Include the custom header file that defines structures and function prototypes

// Function to delete a student's information
/**
 * @brief Deletes a student's information based on the given student ID.
 *
 * This function deletes a student's information from both "studentInformation.txt" and "studentGrades.txt"
 * files based on the provided student ID. It updates the files and prints a success message.
 *
 * @param studentID The ID of the student to be deleted.
 * @param numOfStudents The current total number of students.
 * @return The updated number of students after deletion.
 */
int deleteStudent(int studentID, int numOfStudents)
{
    int tempIndex = 0, True = 0;
    FILE *fpt, *fptr, *filePointer;
    char str[MAX_STR_LENGTH], newStr[MAX_STR_LENGTH], temp[] = "temp.txt";

    // Read existing student IDs from the file
    int *num = readStudentIDs();

    // Open "studentInformation.txt" to read student IDs and validate the provided student ID
    fpt = fopen("studentInformation.txt", "r");

    // Check if the file is successfully opened
    if (!fpt)
    {
        printf("\t\t\t\t\t\t\tCannot open the file.\n\n");
        fclose(fpt);
        exit(EXIT_FAILURE);
    }

    // Validate if the student ID exists
    while (True == 0)
    {
        // Loop through existing student IDs
        while (tempIndex < numOfStudents)
        {
            // Check if the current student ID is not equal to the provided student ID
            if (studentID != *(num + tempIndex))
            {
                tempIndex++;
            }
            // If the student ID is found, set True to 1 and break out of the loop
            else
            {
                True = 1;
                break;
            }
        }

        // If the provided student ID is not found, prompt the user to enter a valid ID
        if (True == 0)
        {
            printf("\t\t\t\t\t\t\tNon-existent ID! Enter a valid ID.\n");
            printf("\t\t\t\t\t\t\tEnter the student's ID again: ");
            studentID = validID();
        }
    }

    tempIndex = 0;

    // Create a temporary file for "studentInformation.txt"
    fptr = fopen(temp, "w");

    // Check if the temporary file is successfully created
    if (!fptr)
    {
        printf("Unable to open a temporary file to write!!\n");
        fclose(fptr);
        exit(EXIT_FAILURE);
    }

    // Copy all contents to the temporary file except the specific line corresponding to the student ID
    while (!feof(fpt))
    {
        strcpy(str, "\0");
        fgets(str, MAX_STR_LENGTH, fpt);
        if (!feof(fpt))
        {
            tempIndex++;
            // Skip the line at the given line number (studentID)
            if (tempIndex != studentID)
            {
                fprintf(fptr, "%s", str);
            }
        }
    }

    // Close the original file and the temporary file
    fclose(fpt);
    fclose(fptr);

    // Remove the original "studentInformation.txt" file
    remove("studentInformation.txt");

    // Rename the temporary file to "studentInformation.txt"
    rename(temp, "studentInformation.txt");

    tempIndex = 0;

    // Open "studentGrades.txt" to process grades information
    filePointer = fopen("studentGrades.txt", "r");

    // Check if the file is successfully opened
    if (!filePointer)
    {
        printf("\t\t\t\t\t\t\tCannot open the file.\n\n");
        fclose(fpt);
        exit(EXIT_FAILURE);
    }

    // Create a temporary file for "studentGrades.txt"
    fptr = fopen(temp, "w");

    // Check if the temporary file is successfully created
    if (!fptr)
    {
        printf("Unable to open a temporary file to write!!\n");
        fclose(fptr);
        exit(EXIT_FAILURE);
    }

    // Copy all contents to the temporary file except the specific line corresponding to the student ID
    while (!feof(filePointer))
    {
        strcpy(newStr, "\0");
        fgets(newStr, MAX_STR_LENGTH, filePointer);
        if (!feof(filePointer))
        {
            tempIndex++;
            // Skip the line at the given line number (studentID)
            if (tempIndex != studentID)
            {
                fprintf(fptr, "%s", newStr);
            }
        }
    }

    // Close the original file and the temporary file
    fclose(filePointer);
    fclose(fptr);

    // Remove the original "studentGrades.txt" file
    remove("studentGrades.txt");

    // Rename the temporary file to "studentGrades.txt"
    rename(temp, "studentGrades.txt");

    // Print a success message
    printf("\t\t\t\t\t\t\tThe information was deleted successfully!\n\n");

    // Reset elements of the global array "ind" to 0
    for (int tempIndex = 0; tempIndex < numOfStudents; ++tempIndex)
    {
        ind[tempIndex] = 0;
    }

    // Return the updated number of students after deletion
    return --numOfStudents;
}