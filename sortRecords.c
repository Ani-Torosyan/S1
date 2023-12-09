#include "scholarships.c"

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
 * @param n Number of elements in the arrays.
 */
void bubbleSort(float arr[], int arrID[], int n)
{
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++)
    {
        swapped = false;
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] < arr[j + 1])
            {
                swapFloat(&arr[j], &arr[j + 1]);
                swapInt(&arrID[j], &arrID[j + 1]);
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
 * If sortedRecords is 1, it uses the sorted array of student indices and grades;
 * otherwise, it calculates and displays scholarship information based on predefined thresholds.
 *
 * @param grades Array of student grades.
 * @param studentIndices Array of student indices.
 * @param sortedRecords Flag indicating whether records are sorted.
 * @param totalNumberOfStudents Total number of students.
 */
void displayStudentInfoByID(float grades[], int studentIndices[], int sortedRecords, int totalNumberOfStudents)
{
    int currentStudentIndex[100], fileReadIndex = 0, loopIndex = 0;
    char studentFirstName[100], studentLastName[100], studentPatronymic[100];

    int *indexes = readStudentIDs();

    if (sortedRecords == 1)
    {
        for (loopIndex = 0; loopIndex < totalNumberOfStudents; loopIndex++)
        {
            fileReadIndex = 0;

            FILE *filePointer;
            filePointer = fopen("studentInformation.txt", "r");

            if (filePointer != NULL)
            {
                while (fileReadIndex < studentIndices[loopIndex])
                {
                    fileReadIndex++;
                    fscanf(filePointer, "%*s %s %s %s", studentFirstName, studentLastName, studentPatronymic);
                }

                printf("\t\t\t\t\t\t\t%d ", studentIndices[loopIndex]);
                printf("%s ", studentFirstName);
                printf("%s ", studentLastName);
                printf("%s   ", studentPatronymic);
                printf("%.2f\n", grades[loopIndex]);

                fclose(filePointer);
            }
            else
            {
                printf("\t\t\t\t\t\t\tCannot open the file.\n\n");
                fclose(filePointer);
                exit(EXIT_FAILURE);
            }
        }
    }
    else
    {
        int maxScholarship100 = scholarship100(totalNumberOfStudents);
        int maxScholarship50 = scholarship50(totalNumberOfStudents);
        int maxScholarship25 = scholarship25(totalNumberOfStudents);

        int True = 0;
        int scholarship25Count = 0, scholarship50Count = 0, scholarship100Count = 0, tempIndex = 0, tempLoopIndex = 0, temp = 0;

        FILE *filePointer;
        filePointer = fopen("studentInformation.txt", "r");
        if (filePointer != NULL)
        {
            for (loopIndex = 0; loopIndex < totalNumberOfStudents; loopIndex++)
            {
                if (tempLoopIndex < maxScholarship100)
                {
                    temp = 0;
                    True = 0;

                    while (temp < studentIndices[loopIndex])
                    {
                        True = 1;
                        temp++;
                        fscanf(filePointer, "%*s %s %s %s", studentFirstName, studentLastName, studentPatronymic);
                    }

                    while (True == 1)
                    {
                        printf("\t\t\t\t\t\t\t%d ", studentIndices[loopIndex]);
                        printf("%s ", studentFirstName);
                        printf("%s ", studentLastName);
                        printf("%s   ", studentPatronymic);
                        printf("\t%s\n", "100%");
                        True = 0;
                    }

                    tempLoopIndex++;
                    rewind(filePointer);
                }
                else if (tempLoopIndex < maxScholarship50)
                {
                    temp = 0;
                    True = 0;

                    while (temp < studentIndices[loopIndex])
                    {
                        True = 1;
                        temp++;
                        fscanf(filePointer, "%*s %s %s %s", studentFirstName, studentLastName, studentPatronymic);
                    }

                    while (True == 1)
                    {
                        printf("\t\t\t\t\t\t\t%d ", studentIndices[loopIndex]);
                        printf("%s ", studentFirstName);
                        printf("%s ", studentLastName);
                        printf("%s   ", studentPatronymic);
                        printf("\t%s\n", "50%");
                        True = 0;
                    }

                    tempLoopIndex++;
                    rewind(filePointer);
                }
                else if (tempIndex < maxScholarship25)
                {
                    temp = 0;
                    True = 0;

                    while (temp < studentIndices[loopIndex])
                    {
                        True = 1;
                        temp++;
                        fscanf(filePointer, "%*s %s %s %s", studentFirstName, studentLastName, studentPatronymic);
                    }

                    if (True == 1)
                    {
                        printf("\t\t\t\t\t\t\t%d ", studentIndices[loopIndex]);
                        printf("%s ", studentFirstName);
                        printf("%s ", studentLastName);
                        printf("%s   ", studentPatronymic);
                        printf("\t%s\n", "25%");
                        True = 0;
                    }

                    tempIndex++;
                    rewind(filePointer);
                }
            }
        }
        else
        {
            printf("\t\t\t\t\t\t\tCannot open the file.\n\n");
            fclose(filePointer);
            exit(EXIT_FAILURE);
        }

        fclose(filePointer);
    }

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
void sortRecords(int sort, int numOfStudents)
{
    char tempBuf[100];
    float grades[100];
    int tempIndex = 0, ind[100];

    FILE *fptr;
    fptr = fopen("studentGrades.txt", "r");

    if (fptr != NULL)
    {
        while (fscanf(fptr, "%*s %s", tempBuf) == 1)
        {
            grades[tempIndex] = atof(tempBuf);
            tempIndex++;
        }

        if (tempIndex != numOfStudents)
        {
            printf("\n\t\t\t\t\t\t\tNot all students are graded!\n\t\t\t\t\t\t\tPlease, enter all the grades first.\n\n");
            return;
        }
        printf("\n");

        tempIndex = 0;
        rewind(fptr);

        while (fscanf(fptr, "%s %*s", tempBuf) == 1)
        {
            ind[tempIndex] = atoi(tempBuf);
            tempIndex++;
        }
    }
    else
    {
        printf("\t\t\t\t\t\t\tCannot open the file.\n\n");
        fclose(fptr);
        exit(EXIT_FAILURE);
    }

    fclose(fptr);

    bubbleSort(grades, ind, tempIndex);
    displayStudentInfoByID(grades, ind, sort, numOfStudents);
}