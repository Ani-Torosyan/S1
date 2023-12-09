#include "header.h" // Include the custom header file that defines structures and function prototypes

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
    int tempIndex = 0;           // Temporary index variable
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
    else
    {
        // Display an error message if the file cannot be opened
        printf("\t\t\t\t\t\t\tCannot open the file.\n\n");
        exit(EXIT_FAILURE); // Exit the program with a failure status
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
    int len = 0;
    char charID[MAX_STR_LENGTH];
    bool valid = false;

    // Continue prompting the user until a valid student ID is entered
    while (!valid)
    {
        fgets(charID, sizeof(charID), stdin); // Read user input as a string

        len = strlen(charID);

        // Remove trailing whitespaces
        while (len > 0 && isspace(charID[len - 1]))
        {
            len--;
        }

        // Check if the entered string is not empty
        if (len > 0)
        {
            valid = true;
            // Validate each character in the entered string
            for (int i = 0; i < len; ++i)
            {
                // Check if the character is a digit
                if (!isdigit(charID[i]))
                {
                    valid = false;
                    // Display an error message and prompt the user for input again
                    printf("\t\t\t\t\t\t\tID must be a positive number or zero and cannot contain white spaces.\n");
                    printf("\t\t\t\t\t\t\tEnter the student's ID again: ");
                    break;
                }
            }
        }
    }

    int ID = atoi(charID); // Convert the validated string to an integer
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
 */
int checkID(int studentID, int *ind)
{
    int tempIndex = 0;

    // Iterate through the existing array of student IDs
    while (*(ind + tempIndex))
    {
        // Check if the input ID matches any existing ID
        if (*(ind + tempIndex) == studentID)
        {
            // Display an error message and prompt the user for input again
            printf("\t\t\t\t\t\t\tRepeated ID! Enter another ID.\n");
            printf("\t\t\t\t\t\t\tEnter the student's ID again: ");
            studentID = validID(); // Get a new student ID from the user
            tempIndex = 0;         // Reset the index to recheck the entire array
        }
        else
            tempIndex++; // Move to the next element in the array
    }
    return studentID; // Return the unique and validated student ID
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

    char format[MAX_STR_LENGTH];
    sprintf(format, "%%%d[^\n]s", MAX_STR_LENGTH);

    // Continue prompting the user until a valid name is entered
    while (name[tempIndex])
    {
        // Check if the current character is not a letter
        if (!(isalpha(name[tempIndex])))
        {
            // Display an error message and prompt the user for input again
            printf("\t\t\t\t\t\t\tName must be composed of letters and cannot contain white spaces.\n");
            printf("\t\t\t\t\t\t\tEnter the student's information again: ");
            getchar(); // Consume the newline character left in the input buffer

            scanf(format, name); // Get a new name from the user
            tempIndex = 0;       // Reset the index to recheck the entire array
        }
        else
            tempIndex++; // Move to the next character in the array
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
    char format[MAX_STR_LENGTH];
    sprintf(format, "%%%d[^\n]s", MAX_STR_LENGTH);

    totalNumberOfStudents++;

    // Check if the maximum limit of students has been reached
    if (totalNumberOfStudents > MAX_QUANTITY_OF_STUDENTS)
    {
        // Display an error message and return the original total number of students
        printf("\n\t\t\t\t\t\t\tToo many students. New student cannot be added!\n\n");
        return totalNumberOfStudents--;
    }

    printf("\t\t\t\t\t\t\tEnter the student's ID: ");

    newStudent.ID = validID(); // Get a valid student ID from the user
    newStudent.ID = checkID(newStudent.ID, readStudentIDs()); // Ensure the ID is unique

    printf("\t\t\t\t\t\t\tEnter the student's first name: ");
    scanf(format, newStudent.firstName); 
    validName(newStudent.firstName); // Validate and ensure the entered name contains only letters

    getchar();

    printf("\t\t\t\t\t\t\tEnter the student's last name: ");
    scanf(format, newStudent.lastName); 
    validName(newStudent.lastName); // Validate and ensure the entered name contains only letters

    getchar();

    printf("\t\t\t\t\t\t\tEnter the student's patronymic: ");
    scanf(format, newStudent.patronymic); 
    validName(newStudent.patronymic); // Validate and ensure the entered name contains only letters

    FILE *fptr;
    fptr = fopen("studentInformation.txt", "a");

    if (fptr != NULL)
    {
        // Write the student information to the file
        fprintf(fptr, "%d", newStudent.ID);
        fputs(" ", fptr);
        fputs(newStudent.firstName, fptr);
        fputs(" ", fptr);
        fputs(newStudent.lastName, fptr);
        fputs(" ", fptr);
        fputs(newStudent.patronymic, fptr);
        fputs("\n", fptr);

        printf("\n\t\t\t\t\t\t\tThe information was recorded successfully.\n\n"); 
    }
    else
    {
        // Display an error message if the file cannot be opened and exit the program
        printf("\t\t\t\t\t\t\tCannot open the file.\n\n");
        exit(EXIT_FAILURE);
    }
    
    fclose(fptr);

    return totalNumberOfStudents; // Return the updated total number of students
}