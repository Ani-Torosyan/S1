#include "header.h" // Include the custom header file that defines structures and function prototypes

// Function to swap two float values
/**
 * @brief Swaps two float values.
 *
 * This function takes two float pointers and swaps the values they point to.
 *
 * @param xp Pointer to the first float value.
 * @param yp Pointer to the second float value.
 */
void swapFloat(float *xp, float *yp)
{
    float temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// Function to swap two int values
/**
 * @brief Swaps two int values.
 *
 * This function takes two int pointers and swaps the values they point to.
 *
 * @param xp Pointer to the first int value.
 * @param yp Pointer to the second int value.
 */
void swapInt(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// Function to perform bubble sort on an array of floats and corresponding array of ints
/**
 * @brief Performs bubble sort on an array of floats and corresponding array of ints.
 *
 * This function sorts the array of floats in descending order using the bubble sort algorithm.
 * It also swaps the corresponding elements in the array of ints accordingly.
 *
 * @param arr Array of floats to be sorted.
 * @param arrID Array of ints corresponding to the sorted floats.
 * @param numOfElements Number of elements in the arrays.
 */
void bubbleSort(float arr[], int arrID[], int numOfElements)
{
    int tempIndI, tempIndJ;
    bool swapped;
    for (tempIndI = 0; tempIndI < numOfElements - 1; ++tempIndI)
    {
        swapped = false;
        for (tempIndJ = 0; tempIndJ < numOfElements - tempIndI - 1; ++tempIndJ)
        {
            if (arr[tempIndJ] < arr[tempIndJ + 1])
            {
                swapFloat(&arr[tempIndJ], &arr[tempIndJ + 1]);
                swapInt(&arrID[tempIndJ], &arrID[tempIndJ + 1]);
                swapped = true;
            }
        }

        if (swapped == false)
            break;
    }
}

// Function to display student information by ID with scholarship information
/**
 * @brief Displays student information by ID with scholarship information.
 *
 * This function displays student information (ID, name, and grade) sorted by ID.
 * If sortRanks is true, it displays the sorted array of student indices and grades;
 * otherwise, it calculates and displays scholarship information based on predefined thresholds.
 *
 * @param grades Array of student grades.
 * @param studentIndices Array of student indices.
 * @param sortRanks Flag indicating whether to show sorted array of students or scholarship information.
 * @param totalNumberOfStudents Total number of students.
 */
void displayStudentInfoByID(float grades[], int studentIndices[], bool sortRanks, int totalNumberOfStudents)
{
    int currentStudentIndex[MAX_QUANTITY_OF_STUDENTS], fileReadIndex = 0, loopIndex = 0;
    char studentFirstName[MAX_STR_LENGTH], studentLastName[MAX_STR_LENGTH], studentPatronymic[MAX_STR_LENGTH];

    int *indexes = readStudentIDs();

    FILE *filePointer;
    filePointer = fopen("studentInformation.txt", "r");

    if (filePointer == NULL)
    {
        printf("\t\t\t\t\t\t\tCannot open the file.\n\n");
        exit(EXIT_FAILURE);
    }

    if (sortRanks)
    {
        // Display information for sorted records
        for (loopIndex = 0; loopIndex < totalNumberOfStudents; loopIndex++)
        {
            fileReadIndex = 0;

            while (fileReadIndex < studentIndices[loopIndex])
            {
                fileReadIndex++;
                fscanf(filePointer, "%*s %s %s %s", studentFirstName, studentLastName, studentPatronymic);
            }

            // Print student information
            printf("\t\t\t\t\t\t\t%.2f\t", grades[loopIndex]);
            printf("%d ", studentIndices[loopIndex]);
            printf("%s ", studentFirstName);
            printf("%s ", studentLastName);
            printf("%s\n", studentPatronymic);

            rewind(filePointer); // Move file pointer back to the beginning
        }
    }
    else
    {
        // Calculate and display scholarship information
        int maxScholarship100 = scholarship100(totalNumberOfStudents);
        int maxScholarship50 = scholarship50(totalNumberOfStudents);
        int maxScholarship25 = scholarship25(totalNumberOfStudents);

        bool isScholarshipGranted = false;

        for (loopIndex = 0; loopIndex < totalNumberOfStudents; loopIndex++)
        {
            isScholarshipGranted = false;

            // Determine scholarship level and print information if a scholarship is granted
            if (loopIndex < maxScholarship100)
            {
                printf("\t\t\t\t\t\t\t%s\t", "100%");
                isScholarshipGranted = true;
            }
            else if (loopIndex < maxScholarship50)
            {
                printf("\t\t\t\t\t\t\t%s\t", "50%");
                isScholarshipGranted = true;
            }
            else if (loopIndex < maxScholarship25)
            {
                printf("\t\t\t\t\t\t\t%s\t", "25%");
                isScholarshipGranted = true;
            }

            if (isScholarshipGranted)
            {
                fileReadIndex = 0;

                while (fileReadIndex < studentIndices[loopIndex])
                {
                    fileReadIndex++;
                    fscanf(filePointer, "%*s %s %s %s", studentFirstName, studentLastName, studentPatronymic);
                }

                // Print student information
                printf("%d ", studentIndices[loopIndex]);
                printf("%s ", studentFirstName);
                printf("%s ", studentLastName);
                printf("%s\n", studentPatronymic);

                rewind(filePointer); // Move file pointer back to the beginning
            }
        }
    }

    fclose(filePointer); // Close the file

    printf("\n");
}

// Function to sort and display student records based on scholarship criteria
/**
 * @brief Sorts and displays student records based on scholarship criteria.
 *
 * This function reads student grades from "studentGrades.txt", sorts them in descending order,
 * and displays student information along with scholarship information.
 *
 * @param sort Scholarship level (0, 25, 50, 100).
 * @param numOfStudents Total number of students.
 */
void sortRecords(bool sort, int numOfStudents)
{
    char tempBuf[100];
    float grades[100];
    int tempIndex = 0, ind[100];

    FILE *fptr;
    fptr = fopen("studentGrades.txt", "r");

    // Check if the file is successfully opened
    if (fptr != NULL)
    {
        // Read student grades from the file
        while (fscanf(fptr, "%*s %s", tempBuf) == 1)
        {
            grades[tempIndex] = atof(tempBuf);
            tempIndex++;
        }

        // Check if the number of grades matches the total number of students
        if (tempIndex != numOfStudents)
        {
            printf("\n\t\t\t\t\t\t\tNot all students are graded!\n\t\t\t\t\t\t\tPlease, enter all the grades first.\n\n");
            return;
        }
        printf("\n");

        tempIndex = 0;
        rewind(fptr);

        // Read student IDs from the file
        while (fscanf(fptr, "%s %*s", tempBuf) == 1)
        {
            ind[tempIndex] = atoi(tempBuf);
            tempIndex++;
        }
    }
    else
    {
        // Display an error message if the file cannot be opened
        printf("\t\t\t\t\t\t\tCannot open the file.\n\n");
        exit(EXIT_FAILURE);
    }

    fclose(fptr); // Close the file

    // Use the bubble sort algorithm to sort grades and corresponding indices in descending order
    bubbleSort(grades, ind, tempIndex);

    // Display student information based on scholarship criteria using displayStudentInfoByID function
    displayStudentInfoByID(grades, ind, sort, numOfStudents);
}