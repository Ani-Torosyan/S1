#include "deleteStudentInfo.c"

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
    int sortedRecords = 0, numberOfStudents = 0;
    char choice = 1; 

    char buf[MAX_QUANTITY_OF_STUDENTS];

    FILE* fpt;
    fpt = fopen("studentInformation.txt", "r");

    if(fpt != NULL)
    {
        while(fscanf(fpt, "%s %*s %*s %*s", buf) == 1)
        {
            numberOfStudents++;
        }
    }
    else 
    {
        printf("\t\t\t\t\t\t\tCannot open the student info file.\n\n"); 
        fclose(fpt);
        exit(EXIT_FAILURE);
    }

    fclose(fpt);

    while (choice != 0)
    {
        menu();
        scanf("%d", &choice);
        printf("\n"); 

        while(choice > 5 || choice < 0)
        {
            printf("\t\t\t\t\t\t\tWrong operator! Enter once more.\n\n");
            menu();
            scanf("%d", &choice);
            printf("\n"); 
        }
        
        switch(choice)
        {
            case 1:
            {
                numberOfStudents = addStudent(numberOfStudents);
                break;
            }
            case 2:
            {
                if(numberOfStudents == 0)
                {
                    printf("\t\t\t\t\t\t\tNo student information available.\n\t\t\t\t\t\t\tPlease add student information first.\n\n");
                    break;
                }
                printf("\t\t\t\t\t\t\tEnter the student's ID: ");
                newStudent.ID = validID();
                findExistingID(newStudent.ID, numberOfStudents);
                break;
            }
            case 3:
            {
                if(numberOfStudents == 0)
                {
                    printf("\t\t\t\t\t\t\tNo student information available.\n\t\t\t\t\t\t\tPlease add student information first.\n\n");
                    break;
                }
                sortedRecords = 1;
                printf("\t\t\t\t\t\t\tThe ranks of the students:\n");
                sortRecords(sortedRecords, numberOfStudents);
                break;
            }
            case 4:
            {
                if(numberOfStudents == 0)
                {
                    printf("\t\t\t\t\t\t\tNo student information available.\n\t\t\t\t\t\t\tPlease add student information first.\n\n");
                    break;
                }
                sortedRecords = 0;
                printf("\t\t\t\t\t\t\tThe scholarships are:\n");
                sortRecords(sortedRecords, numberOfStudents);
                break;

            }
            case 5:
            {
                if(numberOfStudents == 0)
                {
                    printf("\t\t\t\t\t\t\tNo student information available.\n\t\t\t\t\t\t\tPlease add student information first.\n\n");
                    break;
                }
                printf("\t\t\t\t\t\t\tEneter the students ID: ");
                newStudent.ID = validID();
                numberOfStudents = deleteStudent(newStudent.ID, numberOfStudents);
                break;
            }
        }   
    }

    printf("\t\t\t\t\t\t\tYou have successfully quited!\n\n");
    
    return 0;

}