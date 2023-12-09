#include "header.h" // Include the custom header file that defines structures and function prototypes

// Function to determine the 25% scholarship level based on the number of students
/**
 * @brief Determines the 25% scholarship level based on the number of students.
 *
 * This function takes the total number of students and determines the scholarship level based on predefined thresholds.
 * It returns an integer representing the scholarship level.
 *
 * @param numOfStudents The total number of students.
 * @return Integer representing the scholarship level.
 */
int scholarship25(int numOfStudents)
{
    if (numOfStudents < 18 || (numOfStudents > 19 && numOfStudents < 23))
    {
        return 0; // Return the determined scholarship level
    }
    else if (numOfStudents < 20 || numOfStudents == 23)
    {
        return 1; // Return the determined scholarship level
    }

    // Define scholarship level thresholds and determine the appropriate level
    const int thresholds[] = {18, 23, 29, 40, 52, 63, 74, 86, 97, 108, 120, 131, 143, 154, 165, 177};
    const int numThresholds = sizeof(thresholds) / sizeof(thresholds[0]);

    for (int tempIndex = 2; tempIndex < numThresholds; tempIndex++)
    {
        if (numOfStudents < thresholds[tempIndex])
        {
            return tempIndex; // Return the determined scholarship level
        }
    }

    return numThresholds; // Default value when numOfStudents is greater than or equal to the last threshold
}

// Function to determine the 50% scholarship level based on the number of students
/**
 * @brief Determines the 50% scholarship level based on the number of students.
 *
 * This function takes the total number of students and determines the scholarship level based on predefined thresholds.
 * It returns an integer representing the scholarship level.
 *
 * @param numOfStudents The total number of students.
 * @return Integer representing the scholarship level.
 */
int scholarship50(int numOfStudents)
{
    // Define scholarship level thresholds and determine the appropriate level
    const int thresholds[] = {20, 34, 57, 79, 102, 124, 147, 169};
    const int numThresholds = sizeof(thresholds) / sizeof(thresholds[0]);

    for (int tempIndex = 0; tempIndex < numThresholds; tempIndex++)
    {
        if (numOfStudents < thresholds[tempIndex])
        {
            return tempIndex; // Return the determined scholarship level
        }
    }

    return numThresholds; // Default value when numOfStudents is greater than or equal to the last threshold
}

// Function to determine the 100% scholarship level based on the number of students
/**
 * @brief Determines the 100% scholarship level based on the number of students.
 *
 * This function takes the total number of students and determines the scholarship level based on predefined thresholds.
 * It returns an integer representing the scholarship level.
 *
 * @param numOfStudents The total number of students.
 * @return Integer representing the scholarship level.
 */
int scholarship100(int numOfStudents)
{
    // Define scholarship level thresholds and determine the appropriate level
    const int thresholds[] = {5, 68, 113, 158};
    const int numThresholds = sizeof(thresholds) / sizeof(thresholds[0]);

    for (int tempIndex = 0; tempIndex < numThresholds; tempIndex++)
    {
        if (numOfStudents < thresholds[tempIndex])
        {
            return tempIndex; // Return the determined scholarship level
        }
    }

    return numThresholds; // Default value when numOfStudents is greater than or equal to the last threshold
}