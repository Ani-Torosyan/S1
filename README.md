# S1
# Student Scholarship Control System for UFAR

The Student Scholarship Control System is a simple console-based application written in C. It allows users to manage student information, record grades, view student ranks, and determine scholarship eligibility.

## Features

1. **Add a Student:** Add new students to the system, recording their ID, first name, last name, and patronymic.

2. **Add Student's Grade:** Assign grades to students for various subjects, calculating their total grades.

3. **View Student Ranks:** View the ranks of students based on their total grades.

4. **View Available Scholarships:** Display available scholarship options based on the number of students.

5. **Delete Student's Information:** Remove a student's information from the system.

6. **Quit:** Exit the program.

## File Structure

- `header.h`: Contains common definitions, structures, and function prototypes used across multiple source files.

- `addStudent.c`: Implements functions related to adding a new student.

- `addGrade.c`: Implements functions for adding grades to students.

- `scholarship.c`: Contains thresholds to determine scholarship eligibility.

- `calculateScholarship.c`: Contains functions to determine scholarship eligibility.

- `deleteStudentInfo.c`: Implements functions to delete a student's information.

- `sortRecords.c`: Implements functions for sorting and displaying student records.

- `scholarshipSystem.c`: The main program file containing the `main` function and user interface.

## Requirements 

To run this program, you need: 
A. C compiler (e.g., GCC) 
B. Basic understanding of the C programming language

## How to Use

1. **Clone the repository:**
   
   git clone https://github.com/Ani-Torosyan/S1.git

2. **Compile the program:**

   gcc -o my_program scholarshipSystem.c subjects.c addStudent.c addGrade.c scholarships.c sortRecords.c deleteStudentInfo.c

3. **Run the executable:**

   ./myprogram

4. **Follow the On-Screen Instructions:**

    - Use the menu options to perform various tasks.
    - Enter data as prompted.

5. **Quit the Program:**

    - Choose option `0` to exit the program.

## Notes

- Student information is stored in the file `studentInformation.txt`.
- Student grades are stored in the file `studentGrades.txt`.
- Subject information is stored in the file `subjectInfo.txt`.
- The program uses a modular structure with multiple source files for better organization.

## Contributing

Feel free to contribute or report issues!
