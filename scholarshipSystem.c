#include "header.h" // Include the custom header file that defines structures and function prototypes

// Function to display the menu options
/**
 * @brief Displays the main menu of the Student Scholarship Control System.
 *
 * This function prints the menu options for the user to interact with the system.
 */
void menu()
{
    printf("\t\t\t\t\t\t\t=========Student Scholarship Control System=========");
    printf("\n\n\t\t\t\t\t\t\t1. Add a student.\n");
    printf("\t\t\t\t\t\t\t2. Add student's grade.\n");
    printf("\t\t\t\t\t\t\t3. View the students' ranks.\n");
    printf("\t\t\t\t\t\t\t4. View the available scholarships.\n");
    printf("\t\t\t\t\t\t\t5. Delete student's information.\n");
    printf("\t\t\t\t\t\t\t0. Quit.\n");
    printf("\t\t\t\t\t\t\t----------------------------------------------------\n");
    printf("\t\t\t\t\t\t\t"); 
}

// Main function
/**
 * @brief The main function of the Student Scholarship Control System.
 *
 * This function initializes necessary variables, reads existing student information from the file,
 * and enters a loop to interact with the user based on their menu choices.
 * The main loop calls different functions based on the user's choice.
 *
 * @return 0 to indicate successful program execution.
 */
int main()
{
    struct studentInfo newStudent;
    int numberOfStudents = 0;
    char choice = 1; 
    bool sortRanks;

    char buf[MAX_QUANTITY_OF_STUDENTS];

    // Initialize subjects
    addSubjects(countSubjects());

    FILE* fpt;
    fpt = fopen("studentInformation.txt", "r");

    // Check if the file is successfully opened
    if(fpt != NULL)
    {
        // Count the number of students in the file
        while(fscanf(fpt, "%s %*s %*s %*s", buf) == 1)
        {
            numberOfStudents++;
        }
    }
    else 
    {
        // Print an error message if the file cannot be opened
        printf("\t\t\t\t\t\t\tCannot open the student info file.\n\n"); 
        exit(EXIT_FAILURE);
    }

    fclose(fpt);

    // Main loop for user interaction
    while (choice != 0)
    {
        // Display the main menu
        menu();
        // Get user input for menu choice and check if it is a number
        choice = isDigit();

        // Validate user input
        while(choice > 5 || choice < 0)
        {
            // Prompt the user for a valid choice if the input is incorrect
            printf("\t\t\t\t\t\t\tWrong operator! Enter once more: ");
            choice = isDigit();
            printf("\n"); 
        }
        
        // Switch based on user choice
        switch(choice)
        {
            case 1:
            {
                // Add a new student and update the number of students
                numberOfStudents = addStudent(numberOfStudents);
                break;
            }
            case 2:
            {
                if(numberOfStudents == 0)
                {
                    // Display an error message if there are no students
                    printf("\t\t\t\t\t\t\tNo student information available.\n\t\t\t\t\t\t\tPlease add student information first.\n\n");
                    break;
                }
                
                // Find an existing ID and add student grade
                findExistingID(numberOfStudents);
                break;
            }
            case 3:
            {
                if(numberOfStudents == 0)
                {
                    // Display an error message if there are no students
                    printf("\t\t\t\t\t\t\tNo student information available.\n\t\t\t\t\t\t\tPlease add student information first.\n\n");
                    break;
                }
                
                // Display students' ranks
                sortRanks = true;
                printf("\t\t\t\t\t\t\tThe ranks of the students:\n");
                sortRecords(sortRanks, numberOfStudents);
                break;
            }
            case 4:
            {
                // Option to display student records with scholarship information
                if (numberOfStudents == 0)
                {
                    // Check if there is no student information available
                    printf("\t\t\t\t\t\t\tNo student information available.\n\t\t\t\t\t\t\tPlease add student information first.\n\n");
                    break;
                }
                sortRanks = false;
                printf("\t\t\t\t\t\t\tThe scholarships are:\n");
                // Sort and display student records with scholarship information
                sortRecords(sortRanks, numberOfStudents);
                break;
            }

            case 5:
            {
                // Option to delete a student's information
                if (numberOfStudents == 0)
                {
                    // Check if there is no student information available
                    printf("\t\t\t\t\t\t\tNo student information available.\n\t\t\t\t\t\t\tPlease add student information first.\n\n");
                    break;
                }
                printf("\t\t\t\t\t\t\tEnter the student's ID: ");
                newStudent.ID = isDigit();
                // Delete the student's information and update the number of students
                numberOfStudents = deleteStudent(newStudent.ID, numberOfStudents);
                break;
            }
        } 
    }

    // Exit the loop and terminate the program
    printf("\t\t\t\t\t\t\tYou have successfully quited!\n\n");

    // Free the allocated memory for the 'sp' array
    free(sp);

    // Return 0 to indicate successful execution
    return 0;
}