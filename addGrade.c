#include "addStudent.c"

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
    int numOfSubjects = countSubjects();
    addSubjects(numOfSubjects);

    FILE *fptr;
    fptr = fopen("studentGrades.txt", "a");
    struct studentInfo newStudent;

    if (fptr != NULL)
    {
        int j;

        for (j = 0; j < numOfSubjects; j++)
        {
            printf("\t\t\t\t\t\t\tEnter the student's grade for %s: ", sp[j].subjectName);
            scanf("%f", &sp[j].grade);

            while (sp[j].grade < 0 || sp[j].grade > 20)
            {
                printf("\t\t\t\t\t\t\tError in grade!\n");
                printf("\t\t\t\t\t\t\tPlease, enter the student's grade for %s again: ", sp[j].subjectName);
                scanf("%f", &sp[j].grade);
            }
            newStudent.totalGrade += (sp[j].subjectCredit * sp[j].grade);
        }

        char str[100], strID[100];
        sprintf(str, "%f", newStudent.totalGrade);
        sprintf(strID, "%d", studentID);

        fprintf(fptr, "%d %f\n", studentID, newStudent.totalGrade);
        printf("\t\t\t\t\t\t\tThe information was recorded successfully.\n\n");
    }
    else
    {
        printf("\t\t\t\t\t\t\tCannot open the file.\n\n");
        fclose(fptr);
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
void findExistingID(int studentID, int numOfStudents)
{
    int ind[100], tempIndex = 0, True = 1;
    int *num = readStudentIDs();
    char arr[100];

    FILE *fptr;
    fptr = fopen("studentGrades.txt", "r");

    if (fptr != NULL)
    {
        while (fscanf(fptr, "%s %*s", arr) == 1)
        {
            ind[tempIndex] = atoi(arr);
            tempIndex++;
        }

        while (True == 1)
        {
            tempIndex = 0;
            True = 0;

            while (ind[tempIndex])
            {
                if (ind[tempIndex] == studentID)
                {
                    printf("\t\t\t\t\t\t\tStudent is already graded.\n");
                    printf("\t\t\t\t\t\t\tEnter the student's ID again: ");
                    studentID = validID();
                    True = 1;
                    break;
                }
                else
                    tempIndex++;
            }
        }

        fclose(fptr);
    }
    else
    {
        printf("\t\t\t\t\t\t\tCannot open the file.\n\n");
        fclose(fptr);
        exit(EXIT_FAILURE);
    }

    FILE *fpt;
    fpt = fopen("studentInformation.txt", "r");

    if (fpt != NULL)
    {
        while (True == 0)
        {
            tempIndex = 0;

            while (*(num + tempIndex))
            {
                if (*(num + tempIndex) == studentID)
                {
                    fclose(fpt);
                    calculateGrade(studentID);
                    True = 1;
                    break;
                }
                else
                    tempIndex++;
            }

            if (!(*(num + tempIndex)))
            {
                printf("\t\t\t\t\t\t\tNon-existent ID! Enter a valid ID.\n");
                printf("\t\t\t\t\t\t\tEnter the student's ID again: ");
                studentID = validID();
            }
        }
    }
    else
    {
        printf("\t\t\t\t\t\t\tCannot open the file.\n\n");
        fclose(fpt);
        exit(EXIT_FAILURE);
    }

    fclose(fpt);
}
