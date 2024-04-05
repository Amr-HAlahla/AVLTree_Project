# Course Management System

## Description
The Course Management System is a program designed to manage course data including course names, credit hours, course codes, departments, and topics. It provides functionalities such as reading data from a file, inserting new courses, updating course information, listing courses, listing topics associated with a course, deleting courses, and saving course data to a file.

## Features
- Read course data from a file (`courses.txt`) and construct a binary search tree.
- Insert a new course with all its associated data including course name, credit hours, course code, department, and topics.
- Update information of a specific course including name, credit hours, code, department, and topics.
- List all courses in lexicographic order with their associated information.
- List all topics associated with a given course.
- List all courses in lexicographic order that belong to the same department.
- Delete a course by its code.
- Delete all courses whose codes start with a specific letter.
- Delete all courses that belong to a given department.
- Save all course data to a file (`offered_courses.txt`).

## Usage
1. Run the program.
2. Choose an option from the menu:
    - **1:** Read the course data from `courses.txt`.
    - **2:** Insert a new course.
    - **3:** Find and update course information.
    - **4:** List all courses.
    - **5:** List topics associated with a course.
    - **6:** List courses belonging to a department.
    - **7:** Delete a course.
    - **8:** Delete courses by starting letter.
    - **9:** Delete courses by department.
    - **10:** Save course data to `offered_courses.txt`.
    - **0:** Exit the program.
3. Follow the prompts to perform the desired action.

## Installation
1. Clone the repository:
    ```
    git clone https://github.com/Amr-HAlahla/AVLTree_Project.git
    ```
2. Compile the program:
    ```
    gcc main.c -o course_management_system
    ```
3. Run the executable:
    ```
    ./course_management_system
    ```

## File Structure
- `main.c`: Source code of the program.
- `courses.txt`: Input file containing course data.
- `offered_courses.txt`: Output file where course data is saved.

