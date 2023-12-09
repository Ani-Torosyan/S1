#include "sortRecords.c"

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

    int *num = readStudentIDs();

    fpt = fopen("studentInformation.txt", "r");

    if (!fpt)
    {
        printf("\t\t\t\t\t\t\tCannot open the file.\n\n");
        fclose(fpt);
        exit(EXIT_FAILURE);
    }

    // Validate if the student ID exists
    while (True == 0)
    {
        while (tempIndex < numOfStudents)
        {
            if (studentID != *(num + tempIndex))
            {
                tempIndex++;
            }
            else
            {
                True = 1;
                break;
            }
        }

        if (True == 0)
        {
            printf("\t\t\t\t\t\t\tNon-existent ID! Enter a valid ID.\n");
            printf("\t\t\t\t\t\t\tEnter the student's ID again: ");
            studentID = validID();
        }
    }

    tempIndex = 0;

    fptr = fopen(temp, "w");

    if (!fptr)
    {
        printf("Unable to open a temporary file to write!!\n");
        fclose(fptr);
        exit(EXIT_FAILURE);
    }

    // Copy all contents to the temporary file except the specific line
    while (!feof(fpt))
    {
        strcpy(str, "\0");
        fgets(str, MAX_STR_LENGTH, fpt);
        if (!feof(fpt))
        {
            tempIndex++;
            // Skip the line at the given line number
            if (tempIndex != studentID)
            {
                fprintf(fptr, "%s", str);
            }
        }
    }

    fclose(fpt);
    fclose(fptr);
    remove("studentInformation.txt");      // Remove the original file
    rename(temp, "studentInformation.txt"); // Rename the temporary file to the original name

    tempIndex = 0;

    filePointer = fopen("studentGrades.txt", "r");

    if (!filePointer)
    {
        printf("\t\t\t\t\t\t\tCannot open the file.\n\n");
        fclose(fpt);
        exit(EXIT_FAILURE);
    }

    fptr = fopen(temp, "w");

    if (!fptr)
    {
        printf("Unable to open a temporary file to write!!\n");
        fclose(fptr);
        exit(EXIT_FAILURE);
    }

    while (!feof(filePointer))
    {
        strcpy(newStr, "\0");
        fgets(newStr, MAX_STR_LENGTH, filePointer);
        if (!feof(filePointer))
        {
            tempIndex++;
            // Skip the line at the given line number
            if (tempIndex != studentID)
            {
                fprintf(fptr, "%s", newStr);
            }
        }
    }

    fclose(filePointer);
    fclose(fptr);
    remove("studentGrades.txt");      // Remove the original file
    rename(temp, "studentGrades.txt");

    printf("\t\t\t\t\t\t\tThe information was deleted successfully!\n\n");

    return numOfStudents--;
}