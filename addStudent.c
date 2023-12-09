#include "subjects.c"

struct studentInfo newStudent; // Declare a global variable to store information about a new student

// Function to read student IDs from a file and store them in the 'ind' array
/**
 * @brief Reads student IDs from a file and stores them in the 'ind' array.
 *
 * This function opens the file "studentInformation.txt" in read mode, reads student IDs from the file,
 * converts them to integers, and stores them in the 'ind' array.
 *
 * @return Pointer to the array of student IDs
 */
int *readStudentIDs()
{
    int tempIndex = 0;            // Temporary index variable
    char tempBuf[MAX_STR_LENGTH]; // Temporary buffer for reading strings

    FILE *fpt;                                  // File pointer
    fpt = fopen("studentInformation.txt", "r"); // Open the file in read mode

    if (fpt != NULL)
    {
        // Read student IDs from the file and convert them to integers
        while (fscanf(fpt, "%s %*s %*s %*s", tempBuf) == 1)
        {
            ind[tempIndex] = atoi(tempBuf);
            tempIndex++;
        }
    }

    fclose(fpt); // Close the file
    return ind;  // Return the array of student IDs
}

// Function to validate and retrieve a valid student ID from user input
/**
 * @brief Validates and retrieves a valid student ID from user input.
 *
 * This function reads a string input from the user, validates it to ensure it is a positive number or zero,
 * and converts it into an integer. It prompts the user for a valid input until a valid ID is entered.
 *
 * @return Valid student ID.
 */
int validID()
{
    char charID[MAX_STR_LENGTH];
    int valid = 0;

    while (valid == 0)
    {
        fgets(charID, sizeof(charID), stdin);

        int len = strlen(charID);

        while (len > 0 && isspace(charID[len - 1]))
        {
            len--;
            if (len > 0)
            {
                valid = 1;
                for (int i = 0; i < len; ++i)
                {
                    if (!isdigit(charID[i]))
                    {
                        valid = 0;
                        printf("\t\t\t\t\t\t\tID must be a positive number or zero. Enter the student's ID again: ");
                        break;
                    }
                }
            }
        }
    }

    int ID = atoi(charID);
    return ID;
}

// Function to check if a student ID is unique and not repeated
/**
 * @brief Checks if a student ID is unique and not repeated.
 *
 * This function takes a student ID and an array of existing student IDs.
 * It compares the input ID with existing IDs and prompts the user to enter a new ID if a match is found.
 *
 * @param studentID The student ID to be checked.
 * @param ind Array of existing student IDs.
 * @return Unique student ID.
 */
int checkID(int studentID, int * ind)
{
    int tempIndex = 0;

    while (*(ind + tempIndex))
    {
        if (*(ind + tempIndex) == studentID)
        {
            printf("\t\t\t\t\t\t\tRepeated ID! Enter another ID.\n");
            printf("\t\t\t\t\t\t\tEnter the student's ID again: ");
            studentID = validID();
            studentID = checkID(studentID, ind);
        }
        else
            tempIndex++;
    }
    return studentID;
}

// Function to validate and ensure a name contains only letters
/**
 * @brief Validates and ensures a name contains only letters.
 *
 * This function takes a character array representing a name and checks if it contains only letters.
 * If not, it prompts the user to enter the name again until a valid input is provided.
 *
 * @param name The character array representing the name.
 */
void validName(char name[])
{
    int tempIndex = 0;

    while (name[tempIndex])
    {
        if (!(isalpha(name[tempIndex])))
        {
            printf("\t\t\t\t\t\t\tName must be composed of letters and cannot contain white spaces.\n\t\t\t\t\t\t\tEnter the student's information again: ");

            getchar();

            scanf("%99[^\n]s", name); // TODO: need to use MAX_NAME_LENGTH
            tempIndex = 0;
        }
        else
            tempIndex++;
    }
}

// Function to add a new student to the student information file
/**
 * @brief Adds a new student to the student information file.
 *
 * This function prompts the user to enter the student's ID, first name, last name, and patronymic.
 * It validates the inputs and writes the information to the "studentInformation.txt" file.
 *
 * @param totalNumberOfStudents The total number of students before adding the new student.
 * @return Updated total number of students.
 */
int addStudent(int totalNumberOfStudents)
{
    totalNumberOfStudents++;

    if (totalNumberOfStudents > MAX_QUANTITY_OF_STUDENTS)
    {
        printf("\n\t\t\t\t\t\t\tToo many students. New student cannot be added!\n\n");
        return totalNumberOfStudents--;
    }

    printf("\t\t\t\t\t\t\tEnter the student's ID: ");

    newStudent.ID = validID();
    newStudent.ID = checkID(newStudent.ID, readStudentIDs());

    printf("\t\t\t\t\t\t\tEnter the student's first name: ");
    scanf("%99[^\n]s", newStudent.firstName); // TODO: need to use MAX_NAME_LENGTH

    validName(newStudent.firstName);

    getchar();

    printf("\t\t\t\t\t\t\tEnter the student's last name: ");
    scanf("%99[^\n]s", newStudent.lastName); // TODO: need to use MAX_NAME_LENGTH
    validName(newStudent.lastName);

    getchar();

    printf("\t\t\t\t\t\t\tEnter the student's patronymic: ");
    scanf("%99[^\n]s", newStudent.patronymic); // TODO: need to use MAX_NAME_LENGTH

    validName(newStudent.patronymic);

    FILE *fptr;
    fptr = fopen("studentInformation.txt", "a");

    if (fptr != NULL)
    {
        fprintf(fptr, "%d", newStudent.ID);
        fputs(" ", fptr);
        fputs(newStudent.firstName, fptr);
        fputs(" ", fptr);
        fputs(newStudent.lastName, fptr);
        fputs(" ", fptr);
        fputs(newStudent.patronymic, fptr);
        fputs("\n", fptr);

        printf("\n\t\t\t\t\t\t\tThe information was recorded successfully.\n\n");

        fclose(fptr);
    }
    else
    {
        printf("\t\t\t\t\t\t\tCannot open the file.\n\n");
        fclose(fptr);
        exit(EXIT_FAILURE);
    }

    return totalNumberOfStudents;
}