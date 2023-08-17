
// ABCUniversity.cpp 

// Author: Matt Knutson 

// CS300 - Analysis & Design 

// Instructor Ling 

// Date: 08/10/2023 



//******************************************************************//
//******************************************************************//

                 // # Included Libraries //

//******************************************************************//
//******************************************************************//



#include <iostream>
#include <vector>
#include <algorithm>

#include "time.h"

#include "CSVparser.hpp"

using namespace std;



//******************************************************************//
//******************************************************************//

    // Global Definitions (Visible to ALL Methods & Classes) //

//******************************************************************//
//******************************************************************//



//* Define a structure for the course data *//

struct CourseData {

    string courseId;  // Course identification number and unique identifier for the algorithm //

    string courseName;  // Course name //

    string prereq1;   // Course prerequisite 1 //
    
    string prereq2;   // Course prerequisite 2 //            

   

    //* Initialize Coursedata *//

    CourseData() {

    }

};



//* Define an internal structure for a TREE node *//

struct Node {

    CourseData course;  // Create a course of type CourseData //

    Node* left;   // Create a pointer for the LEFT node //

    Node* right;  // Create a pointer for the RIGHT node //



    //* Default tree node constructor *//

    Node() {

        left = nullptr;  // Set the LEFT node to NULL //

        right = nullptr;  // Set the RIGHT node to NULL //
    }



    //* Initialize the TREE node with a course *//

    Node(CourseData aCourse) :

        Node() {

        course = aCourse;
    }
};



//******************************************************************//
//******************************************************************//

         // The Binary Search Tree Class Definition //

//******************************************************************//
//******************************************************************//



//* Define the Binary Search Tree Class *//

class BinarySearchTree {

 //* Private variables used in the Binary Search Tree *//

private:

    Node* root;  

    void addNode(Node* node, CourseData course);   
    void inOrder(Node* node);
    void preOrder(Node* node);
    void postOrder(Node* node);
    Node* removeNode(Node* node, string courseId);

//* Public variables used in the Binary Search Tree *//

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void PostOrder();
    void PreOrder();
    void Insert(CourseData course);
    void Remove(string courseId);
    CourseData Search(string courseId);
};



//* Default Binary Tree Constructor *//

BinarySearchTree::BinarySearchTree() {

    // INITIALIZE the ROOT node as NULL //

    root = nullptr;
}



//* Binary Search Tree Destructor *//

BinarySearchTree::~BinarySearchTree() {   // Recurse from the ROOT deleting every node //
    
}



//* Traverse the Binary Tree IN order *//

void BinarySearchTree::InOrder() {

    // Start at the ROOT by passing it through the function //

    inOrder(root);

}



//* PRINT the courses IN order *//

void BinarySearchTree::inOrder(Node* node) {

    // IF there is data in the node //

    if (node != nullptr) {

        // CALL the function to traverse down the LEFT side of the tree //

        inOrder(node->left);

        // PRINT the course information from the node //

        std::cout << node->course.courseId << ", " << node->course.courseName << endl; 

        // CALL the function to traverse the RIGHT side of the tree //

        inOrder(node->right);
    }

}



//* Traverse the Binary Tree POST order *//

void BinarySearchTree::PostOrder() {

    // Start at the ROOT by passing it through the function //

    postOrder(root);

}



//* PRINT the courses POST order *//

void BinarySearchTree::postOrder(Node* node) {

    // IF there is data in the node //

    if (node != nullptr) {

        // CALL the function to traverse down the LEFT side of the tree //

        postOrder(node->left);

        // CALL the function to traverse the RIGHT side of the tree //

        postOrder(node->right);

        // PRINT the course information from the node //

        std::cout << node->course.courseId << ", " << node->course.courseName << endl;    

    }

}



//* Traverse the Binary Tree PRE order *//

void BinarySearchTree::PreOrder() {

    // Start at the ROOT by passing it through the function //

    preOrder(root);

}



//* PRINT the courses PRE order *//

void BinarySearchTree::preOrder(Node* node) {

    // IF there is data in the node //

    if (node != nullptr) {

        // PRINT the course information from the node //

        std::cout << node->course.courseId << ", " << node->course.courseName << endl;    

        // CALL the function to traverse down the LEFT side of the tree //

        preOrder(node->left);

        // CALL the function to traverse the RIGHT side of the tree //

        preOrder(node->right);
    }

}



//* Insert a course *//

void BinarySearchTree::Insert(CourseData course) {

    // IF the ROOT node IS EMPTY // 

    if (root == nullptr) {

        // ASSIGN the ROOT node with the course data //

        root = new Node(course);
    }

    // ELSE the root has data inside //

    else {

        // CALL the addNode function to add the node //

        this->addNode(root, course);
    }
}



//* ADD a course to a node recursively using the CURRENT node and a CourseData course *//

void BinarySearchTree::addNode(Node* node, CourseData course) {

    // IF the CURRENT node IS NOT EMPTY and the CURRENT node's courseId is LARGER than the NEW courseId //

    if (node != nullptr && node->course.courseId.compare(course.courseId) > 0) {

        // Proceed down the LEFT side of the tree //

        // IF the node to LEFT is EMPTY //

        if (node->left == nullptr) {

            // ASSIGN the empty node with the course data //

            node->left = new Node(course);

            return;

        }

        // ELSE the node is NOT EMPTY //

        else {

            // CALL the addNode function to continue down the LEFT side of the tree //

            this->addNode(node->left, course);

        }

    }

    // IF the CURRENT node IS NOT EMPTY and the CURRENT node's courseId is SMALLER than the NEW courseId //

    else if (node != nullptr && node->course.courseId.compare(course.courseId) < 0) {

        // Proceed down the RIGHT side of the tree //

        // IF the node to RIGHT is EMPTY //

        if (node->right == nullptr) {

            // ASSIGN the EMPTY node with the course data //

            node->right = new Node(course);

            return;

        }

        // ELSE the node is NOT EMPTY //

        else {

            // CALL the addNode function to continue down the RIGHT side of the tree //

            this->addNode(node->right, course);

        }
    }

}



//* REMOVE a course *//

void BinarySearchTree::Remove(string courseId) {

    // CALL the removeNode function starting at the ROOT using the courseId //

    this->removeNode(root, courseId);

}



//* REMOVE a node of CourseData using a CURRENT node and a courseId *//

Node* BinarySearchTree::removeNode(Node* node, string courseId) {

    // IF the CURRENT node IS EMPTY //

    if (node == nullptr) {

        // RETURN //

        return node;
    }

    // IF the CURRENT node's courseId IS LARGER than the courseId being searched for // 

    else if (courseId.compare(node->course.courseId) < 0) {

        // Traverse down the LEFT side of the tree using the removeNode function //

        node->left = removeNode(node->left, courseId);

    }

    // IF the CURRENT node's courseId IS SMALLER than the courseId being searched for // 

    else if (courseId.compare(node->course.courseId) > 0) {

        // Traverse down the RIGHT side of the tree using the removeNode function //

        node->right = removeNode(node->right, courseId);

    }

    // ELSE a MATCH is found //

    else {

        // IF this is a LEAF node and BOTH RIGHT and LEFT nodes are EMPTY //

        if (node->left == nullptr && node->right == nullptr) {

            // DELETE the node and SET the node to NULL //

            delete node;
            node = nullptr;

        }

        // IF the LEFT child has data and the RIGHT child is EMPTY //

        else if (node->left != nullptr && node->right == nullptr) {

            // CREATE a TEMPORARY node to hold the CURRENT node's data //

            Node* temp = node;

            // ASSIGN the CURRENT node with the LEFT child's data //

            node = node->left;

            // DELETE the TEMPORARY node and SET it to NULL //

            delete temp;
            temp = nullptr;

        }

        // IF the RIGHT child has data and the LEFT child is EMPTY //

        else if (node->right != nullptr && node->left == nullptr) {

            // CREATE a TEMPORARY node to hold the CURRENT node's data //

            Node* temp = node;

            // ASSIGN the CURRENT node with the RIGHT child's data //

            node = node->right;

            // DELETE the TEMPORARY node and SET it to NULL //

            delete temp;
            temp = nullptr;

        }

        // ELSE the node has TWO children //

        else {

            // ASSIGN a TEMPORARY node with the RIGHT node's data //

            Node* temp = node->right;

            // WHILE the TEMPORARY LEFT node IS NOT EMPTY //

            while (temp->left != nullptr) {

                // ASSIGN the TEMPORARY node with the TEMPORARY LEFT node's data //

                temp = temp->left;
            }

            // ASSIGN the CURRENT node's data with TEMPORARY node's data //

            node->course = temp->course;

            // MOVE down the tree to the RIGHT by CALLING the removeNode function on the RIGHT NODE using the TEMPORARY courseId //

            node->right = removeNode(node->right, temp->course.courseId);
        }

    }

    return node;

}



//* Search for a course *//

CourseData BinarySearchTree::Search(string courseId) {

    // ASSIGN a pointer to hold the CURRENT node value starting at the ROOT //

    Node* cur = root;

    // WHILE the CURRENT node is NOT EMPTY //

    while (cur != nullptr) {

        // IF the CURRENT node holds the courseId being searched for //

        if (cur->course.courseId.compare(courseId) == 0) {

            // Return the CURRENT nodes data //

            return cur->course;
        }

        // IF the CURRENT node's courseId is GREATER than the coursId being used for the search //

        else if (cur->course.courseId.compare(courseId) > 0) {

            // Proceed down the LEFT side of the tree //

            cur = cur->left;
        }

        // ELSE the CURRENT node's courseId is LESS than the coursId being used for the search //

        else {

            // Proceed down the RIGHT side of the tree //

            cur = cur->right;

        }

    }

    CourseData course;
    return course;
}



//******************************************************************//
//******************************************************************//

             // Static Methods Used For TESTING //

//******************************************************************//
//******************************************************************//



//* DISPLAY the course information to the console using a CourseData structure *//

void displayCourse(CourseData course) {

    // PRINT the course information //                                                            
    
    std::cout << endl;
    std::cout << course.courseId << ", " << course.courseName << endl;               
    std::cout << endl;

    // PRINT the course prerequisites //

    std::cout << "Course Prerequisites: " << course.prereq1 << ", " << course.prereq2 << endl;
    std::cout << endl;


    return;
}



//* LOAD a CSV file containing CourseData into a container of courses using the csvPath variable *//

void loadCourses(string csvPath, BinarySearchTree* bst) {

    // PRINT a message to the console //

    std::cout << endl;
    std::cout << "Loading CSV file " << csvPath << endl;
    std::cout << endl;

    // INITIALIZE the CSV Parser using the given path //

    csv::Parser file = csv::Parser(csvPath);
    
    // LOOP to read the rows of a CSV file and check for parseing ERRORS //

    try {
        
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // CREATE a course data structure and ADD to the collection of courses //

            CourseData course;
            course.courseId = file[i][0];
            course.courseName = file[i][1];
            course.prereq1 = file[i][2];                    
            course.prereq2 = file[i][3];
            

            // PUSH this course to the end of the container //

            bst->Insert(course);
        }
    }

    // IF an ERROR occurs //
    catch (csv::Error& e) {

        // PRINT the ERROR //

        std::cerr << e.what() << std::endl;
    }
}



//******************************************************************//
//******************************************************************//

         // The MAIN Method Where the Program is RUN!!! //

//******************************************************************//
//******************************************************************//


int main(int argc, char* argv[]) {

    //* PROCESS Command Line Arguments *//

    string csvPath, courseKey;

    switch (argc) {

    case 2:

        csvPath = argv[1];
        courseKey = "98109";

        break;

    case 3:

        csvPath = argv[1];
        courseKey = argv[2];

        break;

    default:

        csvPath = "CourseList.csv";
        courseKey = "98109";
    }

    // CREATE a timer variable //

    clock_t ticks;


    // CREATE a Binary Search Tree to hold all of the courses //

    BinarySearchTree* bst;

    bst = new BinarySearchTree();
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
    CourseData course;


    // PRINT a message to the user //

    std::cout << endl;
    std::cout << "Welcome to the ABCUniversity Course Planner" << endl;
    std::cout << endl;

    // CREATE a variable to hold the user's input and SET it equal to 0 //

    int choice = 0;

    // LOOP to the menu until the user enters the choice 9 //

    while (choice != 9) {
        std::cout << "Menu:" << endl;
        std::cout << "  1. Load Courses" << endl;
        std::cout << "  2. Display the Computer Science Courses List" << endl;
        std::cout << "  3. Search for Course Information" << endl;
        std::cout << "  9. Exit" << endl;
        std::cout << endl;
        std::cout << "Enter choice: ";
               
        // GRAB user's input //

        cin >> choice;                  
                                 
        // CREATE a switch using the user's input //

        switch (choice) {


        case 1:

            // INITIALIZE a timer variable BEFORE loading the courses //

            ticks = clock();

            // CALL the loadCourses function to LOAD the courses from the csvPath //

            loadCourses(csvPath, bst);
                                  
            // DISPLAY a message to the user //

            std::cout << "Your courses have been loaded!!" << endl;
            std::cout << endl;

            // CALCULATE the elapsed time and DISPLAY result //

            ticks = clock() - ticks;   // CURRENT clock ticks minus STARTING clock ticks

            std::cout << "time: " << ticks << " clock ticks" << endl;   // DISPLAY Clock Ticks to the user //

            std::cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;   // DISPLAY Seconds to the user //

            std::cout << endl;

            // RETURN to the menu //

            break;


        case 2:

            // DISPLAY a message to the user //

            std::cout << endl;
            std::cout << "Here is the list of our Computer Science classes:" << endl;
            std::cout << endl;

            // CALL the InOrder function on the Binary Tree of courses //

            bst->InOrder();

            std::cout << endl;

            // RETURN to the menu //

            break;


        case 3:                                    

            // DISPLAY a message to the user //

            std::cout << endl;
            std::cout << "Please enter the course ID of the course you are interested in." << endl;
            std::cout << endl;
            
            std::cout << "Course ID: ";

            // GRAB the user's input and place it in the courseKey variable //

            cin >> courseKey;

            // SEARCH for the course ID using the search function //

            course = bst->Search(courseKey);
            
            // IF the course ID IS found //

            if (!course.courseId.empty()) {

                // DISPLAY the course data to the user using the displayCourse function //

                displayCourse(course);
            }

            // ELSE the course ID IS NOT found //

            else {

                // DISPLAY a message to the user //

                std::cout << endl;
                std::cout << "Course ID " << courseKey << " NOT found." << endl;
                std::cout << endl;
            }
                       
            // RETURN to the menu //

            break;  


        case 9:

            //* SAY Good Bye and EXIT the program *//

            std::cout << endl;
            std::cout << "Thank you for using the ABCUniversity Course Planner!!" << endl;
            std::cout << endl;
            std::cout << "Good bye." << endl;
            std::cout << endl;

            return 0;
        

        // IF the user DOES NOT choose option 1, 2, 3, OR 9 on the menu //

        default:

            // PROMPT user to pick a valid entry //

            std::cout << endl;
            std::cout << "Please enter a valid menu option." << endl;
            std::cout << endl;

            // RETURN to the menu //

            break;
        }
    }   

    //* EXIT THE PROGRAM *//

    return 0;
}


