#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct course *Course;
typedef struct topics *Topic;
struct topics {
    char topic[150];
    Topic next;
};

struct course {
    int hours;
    char courseCode[20];
    char courseName[30];
    char department[25];
    Topic topicsList;
    Course Left;
    Course Right;
    int Height; //Balance information
};

//Function prototypes
Course MakeEmpty(Course T);

Course Find(char *code, Course T);

int height(Course N);

int Max(int Lhs, int Rhs);

Course leftRotate(Course x);

Course rightRotate(Course y);

Course DoubleRotateWithLeft(Course K3);

Course DoubleRotateWithRight(Course K1);

Course Insert(char [5][150], Course T);

int max(int a, int b);

int getBalance(Course N);

Course minValueNode(Course node);

void PrintInOrder(Course t);

void printCourse(Course);

Course deleteNode(Course tree, char code[20]);

Course FindByLetter(Course T, char);

void printSameDep(Course, char[25]);

Topic makeEmpty(Topic topicsList);

void DeleteList(Topic topicsList);

void printTopics(Topic listOfTopics);

int isEmptyTopics(Topic listOfTopics);

void insertTopic(Topic topicsList, char topic[20]);

void splitTopics(Topic topicsList, char topics[150]);

void printTopicsAlone(Topic topicsList);

void printToFile(FILE *, Course);

void findSameDep(Course t, char dep[25], char code[20]);

Course InsertDetails(char name[25], int hours, char code[20], char dep[30], Topic list, Course T);

Course InsertByName(char name[25], int hours, char code[20], char dep[30], Topic list, Course T);

void copy(Course t);

void save();

Course tree = NULL;
Course copyTree = NULL;

int main() {

    tree = MakeEmpty(tree);
    copyTree = MakeEmpty(copyTree);
    FILE *coursesFile;

    int s;
    printf("1. Read the file courses.txt file and create the tree.\n"
           "2. Insert a new course from the user with all its associated data.\n"
           "3. Find a course and support updating of its information.\n"
           "4. List courses in lexicographic order with their associated information (credit hours, IDs, and topics).\n"
           "5. List all topics associated with a given course.\n"
           "6. List all courses in lexicographic order that belong to the same department.\n"
           "7. Delete a course.\n"
           "8. Delete all courses that start with a specific letter.\n"
           "9. Delete all courses belong to a given department.\n"
           "10. Save all words in file offered_courses.txt\n"
           "or 0 to close the program.\n\n");
    printf("Enter your selection:\n");
    scanf("%d", &s);
    while (s) {
        switch (s) {
            case 1: { // READ FILE AND STORE IN THE TREE.
                coursesFile = fopen("courses.txt", "r");
                char dataLine[200];
                char tempCourseData[5][150];
                if (coursesFile) {
                    while (fgets(dataLine, sizeof(dataLine), coursesFile)) {
                        int index = 0;
                        char *token = strtok(dataLine, "[:#/]");
                        while (token != NULL) {
                            strcpy(tempCourseData[index], token);
                            token = strtok(NULL, "[:#/]");
                            index++;
                        }
                        tree = Insert(tempCourseData, tree);
                    }
                }
                printf("\n");
                PrintInOrder(tree);

                break;
            }//Ahmad:4#DAC#GG/ele
            case 2: {//insert new node to the tree.
                printf("Please enter a complete data for a new course, on this form :\n"
                       "Course:CreditHours#CourseCode#Department/topic1, topic2, . . ., topicN\n");
                char newDAta[200], out;
                scanf("%c", &out);
                //read the data of new course
                fgets(newDAta, 200, stdin);
                int count = 0;
                char newCourseData[5][150];
                char *token = strtok(newDAta, "[:#/]");
                // split line by comma.
                while (token != NULL) {
                    strcpy(newCourseData[count], token);
                    token = strtok(NULL, "[:#/]");
                    count++;
                }
                // insert the new course.
                tree = Insert(newCourseData, tree);
                break;
            }
            case 3: {//show data for a specific course
                printf("Enter the code of the course you searching for:\n");
                char out, sCode[20];
                scanf("%c", &out);
                scanf("%s", sCode);
                //printf("%s\n", sCode);
                Course result = NULL;
                // search for the node by the code
                result = Find(sCode, tree);
                if (result)
                    printCourse(result);
                else
                    printf("Course Not Found!\n");
                if (result) {
                    // update the data of the course.
                    printf("1- Update Name\n"
                           "2- Update Credit Hours\n"
                           "3- Update Course Code\n"
                           "4- Update Department\n"
                           "5- Update/Add Topics\n"
                           "6- Nothing\n");
                    printf("Select an Option:\n");
                    int option;
                    scanf("%d", &option);
                    switch (option) {

                        case 1: {
                            char garbage, name[30];
                            scanf("%c", &garbage);
                            printf("Enter the new name:\n");
                            scanf("%[^\n]", name);
                            strcpy(result->courseName, name);
                            break;
                        }
                        case 2: {
                            int hours;
                            printf("Enter the new credit hours:\n");
                            scanf("%d", &hours);
                            result->hours = hours;
                            break;
                        }
                        case 3: {
                            char garbage, code[20], name[25], dep[30];
                            int hours;
                            Topic list;
                            list = makeEmpty(list);
                            scanf("%c", &garbage);
                            printf("Enter the new code:\n");
                            scanf("%[^\n]", code);
                            // check if the code is unique or not.
                            if (Find(code, tree) == NULL) {
                                //if code is unique, delete the node and insert it again.
                                strcpy(name, result->courseName);
                                hours = result->hours;
                                strcpy(dep, result->department);
                                list = result->topicsList;
                                tree = deleteNode(tree, code);
                                InsertDetails(name, hours, code, dep, list, tree);
                            } else
                                printf("There's already a course which has the same code, the code should be unique\n");

                            break;
                        }
                        case 4: {
                            char garbage, dep[25];
                            scanf("%c", &garbage);
                            printf("Enter the new department:\n");
                            scanf("%[^\n]", dep);
                            strcpy(result->department, dep);
                            break;
                        }
                        case 5: {
                            char garbage, topic[20];
                            scanf("%c", &garbage);
                            printf("Enter new topic:\n");
                            scanf("%[^\n]", topic);
                            insertTopic(result->topicsList, topic);
                            break;
                        }
                        case 6: {
                            break;
                        }
                        default: {
                            printf("There's no case with number %d, select again:\n", option);
                        }
                    }
                    printf("Update course information done correctly!\n");
                }
                break;
            }

            case 4: {//print all courses.
//                copy(tree);
//                printf("-----------------------\n");
                PrintInOrder(tree);
                break;
            }
            case 5: {
                printf("Enter the code of the course you want to see the topics for:\n");
                char out, sCode[20];
                scanf("%c", &out);
                scanf("%s", sCode);
                Course result = NULL;
                // search for the specific course
                result = Find(sCode, tree);
                if (result)//print topic of the course.
                    printTopicsAlone(result->topicsList);
                else
                    printf("Course Not Found!\n");
                break;
            }

            case 6: {// print all courses for a specific department.
                printf("Enter the name of department :\n");
                char out, dep[25];
                scanf("%c", &out);
                scanf("%[^\n]", dep);
                printSameDep(tree, dep);
                printf("----------------------------\n");
                break;
            }

            case 7: {//delete a course by it's code.
                printf("Enter the code of the course you want to delete:\n");
                char out, dCode[20];
                scanf("%c", &out);
                scanf("%s", dCode);
                tree = deleteNode(tree, dCode);
                break;
            }
            case 8: {//delete all courses which there code begin with a specific letter.
                printf("Enter the letter : \n");
                char out, letter;
                scanf("%c", &out);
                scanf("%c", &letter);
                Course result;
                result = FindByLetter(tree, letter);
                while (result) {// while there is another course accept the condition, get&delete it
                    tree = deleteNode(tree, result->courseCode);
                    result = FindByLetter(tree, letter);
                }
                //Done.
                break;
            }
            case 9: {//delete all courses in the same department.
                // done
                printf("Enter the name of the department :\n");
                char out, dep[25], code[20];
                scanf("%c", &out);
                scanf("%[^\n]", dep);
                Course result;
                findSameDep(tree, dep, code);
                result = Find(code, tree);
                while (result) {//while there is another course accept the condition, get&delete it
                    tree = deleteNode(tree, code);
                    findSameDep(tree, dep, code);
                    result = Find(code, tree);
                }
                break;
            }
            case 10: {
                save();
                printf("Data Saved Correctly\n");
                break;
            }
            default:
                printf("No case with the number %d, please enter number between 1-10 !\n", s);
        }
        printf("\n1. Read the file courses.txt file and create the tree.\n"
               "2. Insert a new course from the user with all its associated data.\n"
               "3. Find a course and support updating of its information.\n"
               "4. List courses in lexicographic order with their associated information (credit hours, IDs, and topics).\n"
               "5. List all topics associated with a given course.\n"
               "6. List all courses in lexicographic order that belong to the same department.\n"
               "7. Delete a course.\n"
               "8. Delete all courses that start with a specific letter.\n"
               "9. Delete all courses belong to a given department.\n"
               "10. Save all words in file offered_courses.txt\n"
               "or 0 to close the program.\n");
        printf("Enter your selection:\n\n");
        scanf("%d", &s);

    }
    fclose(coursesFile);
    return 0;
}

void save() {// define the output file and call the print function
    FILE *outFile = fopen("offered_courses.txt", "w");
    if (!outFile) {//check if the file founded
        printf("File Not Found!\n");
    }
    printToFile(outFile, tree);
    fclose(outFile);
}

void printToFile(FILE *pointerFile, Course t) { // print all courses on the output file.
    //print the data into the file inorder
    if (t != NULL) {
        printToFile(pointerFile, t->Left);
        fprintf(pointerFile, "%s  %d  %s  %s  ", t->courseName, t->hours, t->courseCode,
                t->department);
        //print the linked list of topics
        Topic ptr = t->topicsList;
        int counter = 0;
        if (isEmptyTopics(t->topicsList))//check if the linked list of the topics is empty
            fprintf(pointerFile, "Empty List!\n");
        else {//print the linked list of the topics in the file
            ptr = ptr->next;
            while (ptr != NULL) {
                fprintf(pointerFile, "\"%s\"", ptr->topic);
                if (ptr->next == NULL)
                    fprintf(pointerFile, ".");
                else
                    fprintf(pointerFile, ", ");
                if (counter % 4 == 0)
                    fprintf(pointerFile, "\n");
                counter++;
                ptr = ptr->next;
            }
        }
        fprintf(pointerFile, "\n\n");
        printToFile(pointerFile, t->Right);
    }
}

//function to find topics in the same department.
void findSameDep(Course t, char dep[25], char code[20]) {
    if (t != NULL) {
        findSameDep(t->Left, dep, code);
        if (strcmp(t->department, dep) == 0)
            strcpy(code, t->courseCode);
        findSameDep(t->Right, dep, code);
    }
}

//function to print topics in the same deepatment
void printSameDep(Course t, char dep[25]) {
    if (t != NULL) {
        printSameDep(t->Left, dep);
        if (strcmp(t->department, dep) == 0)
            printCourse(t);
        printSameDep(t->Right, dep);
    }
}

//insert the linked list of the topics to the tree
void insertTopic(Topic topicsList, char topic[20]) {
    Topic temp = (Topic) malloc(sizeof(struct topics));
    strcpy(temp->topic, topic);
    temp->next = topicsList->next;
    topicsList->next = temp;
}

void splitTopics(Topic topicsList, char topics[150]) {
    char *token = strtok(topics, ",");
//keep splitting the topics
    while (token != NULL) {
        for (int i = 0; i < strlen(token); ++i) {
            if (token[i] == '\n')
                token[i] = '\000';
        }
        insertTopic(topicsList, token);
        token = strtok(NULL, ",");
    }
}

Course Insert(char data[5][150], Course T) {
    if (T == NULL) {
        /* Create and return a one-node tree */
        T = (Course) malloc(sizeof(struct course));
        if (T == NULL)
            printf("Out of space!!!");
        else {
            if (Find(data[2], tree) == NULL) {
                //creat a linked list of topics
                T->topicsList = NULL;
                T->topicsList = makeEmpty(T->topicsList);
                //insertTopic(T->topicsList, data[4]);
                splitTopics(T->topicsList, data[4]);
                //insert course data
                strcpy(T->courseName, data[0]);
                T->hours = strtol(data[1], NULL, 10);
                strcpy(T->courseCode, data[2]);
                strcpy(T->department, data[3]);
                T->Height = 0;
                T->Left = T->Right = NULL;
            } else
                printf("There's already a course which has the same code, the code should be unique\n");
        }
    }
        //if data less than tree data go left
    else if (strcmp(data[2], T->courseCode) < 0) {
        T->Left = Insert(data, T->Left);
        if (height(T->Left) - height(T->Right) == 2) {//check balance
            if (strcmp(data[2], T->Left->courseCode) < 0)    //if data less than tree data single rotate
                T = leftRotate(T);
                //else double rotate
            else
                T = DoubleRotateWithLeft(T);
        }
    } else if (strcmp(data[2], T->courseCode) > 0) {//if data larger than tree data go right
        T->Right = Insert(data, T->Right);
        if (height(T->Right) - height(T->Left) == 2) {//check balance
            if (strcmp(data[2], T->Right->courseCode) > 0)//if data larger than tree data single rotate
                T = rightRotate(T);
            else
                T = DoubleRotateWithRight(T);
        }
    }
    /* Else X is in the tree already; we'll do nothing */
    if (T)
        T->Height = Max(height(T->Left), height(T->Right)) + 1;

    return T;
}

Course InsertDetails(char name[25], int hours, char code[20], char dep[30], Topic list, Course T) {
    if (T == NULL) {
        /* Create and return a one-node tree */
        T = (Course) malloc(sizeof(struct course));
        if (T == NULL)
            printf("Out of space!!!");
        else {
            //creat a linked list of topics
            T->topicsList = NULL;
            T->topicsList = makeEmpty(T->topicsList);
            //insert course data
            T->topicsList = list;
            strcpy(T->courseName, name);
            T->hours = hours;
            strcpy(T->courseCode, code);
            strcpy(T->department, dep);
            T->Height = 0;
            T->Left = T->Right = NULL;
        }
    } else if (strcmp(code, T->courseCode) < 0) {    //if data less than tree data go left
        T->Left = InsertDetails(name, hours, code, dep, list, T->Left);
        if (height(T->Left) - height(T->Right) == 2) {//check balance
            if (strcmp(code, T->Left->courseCode) < 0) //if data less than tree data single rotate
                T = leftRotate(T);
            else
                T = DoubleRotateWithLeft(T);//else double rotate
        }
    } else if (strcmp(code, T->courseCode) > 0) {//if data larger than tree data go right
        T->Right = InsertDetails(name, hours, code, dep, list, T->Right);
        if (height(T->Right) - height(T->Left) == 2) {
            if (strcmp(code, T->Right->courseCode) > 0)//if data larger than tree data single rotate
                T = rightRotate(T);
            else//else double rotate
                T = DoubleRotateWithRight(T);
        }
    }
    /* Else X is in the tree already; we'll do nothing */
    if (T)
        T->Height = Max(height(T->Left), height(T->Right)) + 1;

    return T;
}

Course InsertByName(char name[25], int hours, char code[20], char dep[30], Topic list, Course T) {
    if (T == NULL) {
        /* Create and return a one-node tree */
        T = (Course) malloc(sizeof(struct course));
        if (T == NULL)
            printf("Out of space!!!");
        else {
            //creat a linked list of topics
            T->topicsList = NULL;
            T->topicsList = makeEmpty(T->topicsList);
            //insert course data
            T->topicsList = list;
            strcpy(T->courseName, name);
            T->hours = hours;
            strcpy(T->courseCode, code);
            strcpy(T->department, dep);
            T->Height = 0;
            T->Left = T->Right = NULL;
        }
    } else if (strcmp(name, T->courseName) < 0) {//if data less than tree data go left
        T->Left = InsertByName(name, hours, code, dep, list, T->Left);
        if (height(T->Left) - height(T->Right) == 2) {//check balance
            if (strcmp(name, T->Left->courseName) < 0)//if data less than tree data single rotate
                T = leftRotate(T);
            else//else double rotate
                T = DoubleRotateWithLeft(T);
        }
    } else if (strcmp(name, T->courseName) > 0) {//if data larger than tree data go right
        T->Right = InsertByName(name, hours, code, dep, list, T->Right);
        if (height(T->Right) - height(T->Left) == 2) {//check height
            if (strcmp(name, T->Right->courseName) > 0)//if data larger than tree data single rotate
                T = rightRotate(T);
            else//else double rotate
                T = DoubleRotateWithRight(T);
        }
    }
    /* Else X is in the tree already; we'll do nothing */
    if (T)
        T->Height = Max(height(T->Left), height(T->Right)) + 1;

    return T;
}

//check if theres no topics
int isEmptyTopics(Topic listOfTopics) {
    return listOfTopics->next == NULL;
}

void printTopicsAlone(Topic topicsList) {
    Topic ptr = topicsList;
    int counter = 1;
    if (isEmptyTopics(topicsList))
        printf("Empty List!\n");
    else {
        ptr = ptr->next;
        while (ptr != NULL) {
            printf("\"%s\"", ptr->topic);//keep printing all topics
            counter++;
            if (ptr->next == NULL)//print . at the end of the topics
                printf(".");
            else
                printf(",  ");
            if (counter % 6 == 0)
                printf("\n");
            ptr = ptr->next;
        }
    }
    printf("\n");
}

void printTopics(Topic listOfTopics) {
    Topic ptr = listOfTopics;
    int counter = 0;
    if (isEmptyTopics(listOfTopics))
        printf("Empty List!\n");
    else {
        ptr = ptr->next;
        while (ptr != NULL) {
            printf("\"%s\"", ptr->topic);//keep printing all topics
            if (ptr->next == NULL)//print . at the end of the topics
                printf(".");
            else
                printf(",   ");
            if (counter % 4 == 0)
                printf("\n");
            counter++;

            ptr = ptr->next;
        }
    }
    printf("\n");
}

void DeleteList(Topic topicsList) {
    Topic ptr, temp;
    ptr = topicsList->next;
    topicsList->next = NULL;
    while (ptr != NULL) {//free topics data until the end of the linked list
        temp = ptr->next;
        free(ptr);
        ptr = temp;
    }
}

//empty all topics data recursively
Topic makeEmpty(Topic topicsList) {
    if (topicsList != NULL)
        DeleteList(topicsList);
    topicsList = (Topic) malloc(sizeof(struct topics));
    if (topicsList == NULL)
        printf("Out Of Memory!");
    topicsList->next = NULL;
    return topicsList;
}

//keep searching until find given letter
Course FindByLetter(Course t, char letter) {
    if (t == NULL)
        return NULL;
    if (letter < t->courseCode[0])
        return FindByLetter(t->Left, letter);
    else if (letter > t->courseCode[0])
        return FindByLetter(t->Right, letter);
    else
        return t;
}

/* START: fig4_37.txt */
//print all courses data
void printCourse(Course c) {
    if (c != NULL) {
        printf("Course Name: %s, Credit Hours: %d, Course Code: %s,"
               " Department:%s\nTopics: ", c->courseName, c->hours, c->courseCode, c->department);
        printTopicsAlone(c->topicsList);
    }
}

Course MakeEmpty(Course T) {
    if (T != NULL) {//Empty all tree data
        MakeEmpty(T->Left);
        MakeEmpty(T->Right);
        free(T);
    }
    return NULL;
}


void PrintInOrder(Course t) {//print tree data inorder
    if (t != NULL) {
        PrintInOrder(t->Left);
        printf("%s  %d  %s  %s  ", t->courseName, t->hours, t->courseCode, t->department);
        printTopics(t->topicsList);
        printf("\n");
        PrintInOrder(t->Right);
    }
}

//search in the tree depending on the given code
Course Find(char code[20], Course T) {
    if (T == NULL)
        return NULL;
    if (strcmp(code, T->courseCode) < 0)
        return Find(code, T->Left);
    else if (strcmp(code, T->courseCode) > 0)
        return Find(code, T->Right);
    else
        return T;
}

Course minValueNode(Course node) {
    Course current = node;

    /* loop down to find the leftmost leaf */
    while (current->Left != NULL)
        current = current->Left;

    return current;
}

//get the height of the tree
int height(Course N) {
    if (N == NULL)
        return 0;
    return N->Height;
}

// A utility function to get maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

//get balance depending on the difference between left and right nodes
int getBalance(Course N) {
    if (N == NULL)
        return 0;
    return height(N->Left) - height(N->Right);
}


int Max(int Lhs, int Rhs) {
    return Lhs > Rhs ? Lhs : Rhs;
}

/* START: fig4_39.txt */
/* This function can be called only if K2 has a left child */
/* Perform a rotate between a node (K2) and its left child */
/* Update heights, then return new root */

Course rightRotate(Course y) {
    Course x = y->Left;
    Course T2 = x->Right;

    // Perform rotation
    x->Right = y;
    y->Left = T2;

    // Update heights
    y->Height = max(height(y->Left), height(y->Right)) + 1;
    x->Height = max(height(x->Left), height(x->Right)) + 1;

    // Return new root
    return x;
}

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
Course leftRotate(Course x) {
    Course y = x->Right;
    Course T2 = y->Left;

    // Perform rotation
    y->Left = x;
    x->Right = T2;

    //  Update heights
    x->Height = max(height(x->Left), height(x->Right)) + 1;
    y->Height = max(height(y->Left), height(y->Right)) + 1;

    // Return new root
    return y;
}

/* START: fig4_41.txt */
/* This function can be called only if K3 has a left */
/* child and K3's left child has a right child */
/* Do the left-right double rotation */
/* Update heights, then return new root */

Course DoubleRotateWithLeft(Course K3) {
    /* Rotate between K1 and K2 */
    K3->Left = rightRotate(K3->Left);

    /* Rotate between K3 and K2 */
    return rightRotate(K3);
}
/* END */

/* This function can be called only if K1 has a right */
/* child and K1's right child has a left child */
/* Do the right-left double rotation */
/* Update heights, then return new root */

Course DoubleRotateWithRight(Course K1) {
    /* Rotate between K3 and K2 */
    K1->Right = leftRotate(K1->Right);

    /* Rotate between K1 and K2 */
    return leftRotate(K1);
}


//in-order print to see the elements

Course deleteNode(Course tree, char code[20]) {
    // STEP 1: PERFORM STANDARD BST DELETE

    if (tree == NULL)
        return tree;

    // If the key to be deleted is smaller than the
    // tree's key, then it lies in left subtree
    if (strcmp(code, tree->courseCode) < 0)
        tree->Left = deleteNode(tree->Left, code);

        // If the key to be deleted is greater than the
        // tree's key, then it lies in right subtree
    else if (strcmp(code, tree->courseCode) > 0)
        tree->Right = deleteNode(tree->Right, code);

        // if key is same as tree's key, then This is
        // the node to be deleted
    else {
        // node with only one child or no child
        if ((tree->Left == NULL) || (tree->Right == NULL)) {
            Course temp = tree->Left ? tree->Left :
                          tree->Right;

            // No child case
            if (temp == NULL) {
                temp = tree;
                tree = NULL;
            } else { // One child case Copy the contents of the non-empty child
                strcpy(tree->courseName, temp->courseName);
                tree->hours = temp->hours;
                strcpy(tree->courseCode, temp->courseCode);
                strcpy(tree->department, temp->department);
                tree->topicsList = temp->topicsList;
                free(temp);
            }
        } else {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            Course temp = minValueNode(tree->Right);

            // Copy the inorder successor's data to this node
            strcpy(tree->courseName, temp->courseName);
            tree->hours = temp->hours;
            strcpy(tree->courseCode, temp->courseCode);
            strcpy(tree->department, temp->department);
            tree->topicsList = temp->topicsList;
            // Delete the inorder successor
            tree->Right = deleteNode(tree->Right, temp->courseCode);
        }
    }

    // If the tree had only one node then return
    if (tree == NULL)
        return tree;

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    tree->Height = 1 + max(height(tree->Left),
                           height(tree->Right));

    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
    // check whether this node became unbalanced)
    int balance = getBalance(tree);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalance(tree->Left) >= 0)
        return rightRotate(tree);

    // Left Right Case
    if (balance > 1 && getBalance(tree->Left) < 0) {
        tree->Left = leftRotate(tree->Left);
        return rightRotate(tree);
    }

    // Right Right Case
    if (balance < -1 && getBalance(tree->Right) <= 0)
        return leftRotate(tree);

    // Right Left Case
    if (balance < -1 && getBalance(tree->Right) > 0) {
        tree->Right = rightRotate(tree->Right);
        return leftRotate(tree);
    }

    return tree;
}

// PROJECT 2 d d d d d doneeeeeeeee