#include "header.h" // Include the custom header file that defines structures 

int countSubjects();
void addSubjects(int totalNumOfSubjects);

// Declare a pointer to store an array of subjectInfo structures
struct subjectInfo *sp;

/**
 * @brief Counts the number of subjects listed in the "subjectInfo.txt" file.
 *
 * This function opens the "subjectInfo.txt" file in read mode and counts the number
 * of subjects based on the format of the file. It returns the count of subjects.
 *
 * @return int The count of subjects.
 */
int countSubjects()
{
    int numOfSubjects = 0;        // Variable to store the count of subjects
    char tempBuf[MAX_STR_LENGTH]; // Temporary buffer for reading strings

    FILE *fpt;                           // File pointer
    fpt = fopen("subjectInfo.txt", "r"); // Open the file in read mode

    if (fpt != NULL)
    {
        // Count the number of subjects in the file
        while (fscanf(fpt, "%*s %s", tempBuf) == 1)
        {
            numOfSubjects++;
        }
    }
    else
    {
        // Display an error message if the file cannot be opened
        printf("\t\t\t\t\t\t\tCannot open the file.\n\n");
        fclose(fpt);
        exit(EXIT_FAILURE); // Exit the program with a failure status
    }

    fclose(fpt);          // Close the file
    return numOfSubjects; // Return the count of subjects
}

/**
 * @brief Reads subjects from the "subjectInfo.txt" file and stores them in the 'sp' array.
 *
 * This function allocates memory for the 'sp' array, reads subject information from the
 * "subjectInfo.txt" file, and copies the information to the 'sp' array.
 *
 * @param totalNumOfSubjects The total number of subjects to read from the file.
 */
void addSubjects(int totalNumOfSubjects)
{
    sp = (struct subjectInfo *)malloc(totalNumOfSubjects * sizeof(struct subjectInfo)); // Allocate memory for 'sp' array
    if (sp == NULL)
    {
        perror("\t\t\t\t\t\t\tMemory allocation error.\n\n"); // Display an error message for memory allocation failure
        exit(EXIT_FAILURE);                                   // Exit the program with a failure status
    }

    int credits[MAX_QUANTITY_OF_STUDENTS], tempIndex = 0;                   // Arrays to store subject credits and a temporary index variable
    char tempBuf[MAX_STR_LENGTH], arr[MAX_NUM_OF_SUBJECTS][MAX_STR_LENGTH]; // Temporary buffers

    FILE *fpt;
    fpt = fopen("subjectInfo.txt", "r"); // Open the file in read mode

    if (fpt != NULL)
    {
        // Read subject information from the file
        while (tempIndex < totalNumOfSubjects)
        {
            fscanf(fpt, "%s %s", arr[tempIndex], tempBuf);
            credits[tempIndex] = atoi(tempBuf);
            tempIndex++;
        }
    }
    else
    {
        // Display an error message if the file cannot be opened
        printf("\t\t\t\t\t\t\tCannot open the file.\n\n");
        fclose(fpt);
        exit(EXIT_FAILURE); // Exit the program with a failure status
    }

    fclose(fpt); // Close the file

    // Copy subject information to the 'sp' array
    for (tempIndex = 0; tempIndex < totalNumOfSubjects; tempIndex++)
    {
        strcpy(sp[tempIndex].subjectName, arr[tempIndex]);
        sp[tempIndex].subjectCredit = credits[tempIndex];
    }

    free(sp); // Free the allocated memory for 'sp' array
}