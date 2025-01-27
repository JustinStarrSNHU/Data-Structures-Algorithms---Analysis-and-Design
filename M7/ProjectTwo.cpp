//= ========================================================================== =
// Name        : ProjectTwo.cpp
// Author      : Justin Starr
// Version     : 1.0
// Description : 7-1 Project Two
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>
#include <list>

#include <string>

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
vector<string>  getNextLineAndSplitIntoTokens(istream& str);

// define a structure to hold course information
struct Course {
    string courseId; // unique identifier
    string courseTitle;
    string coursePrereq1;
    string coursePrereq2;
};

// Internal structure for tree node
struct Node {
    Course course;
    Node* left;
    Node* right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a course
    Node(Course aCourse) :
        Node() {
        course = aCourse;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Course course);
    void printCoursesInOrder(Node* node);

    // Added for recursive delete
    void DeleteRecursive(Node*& node);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void PrintCoursesInOrder();
    void Insert(Course course);
    Course Search(string courseId);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    // root is equal to nullptr
    root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
    DeleteRecursive(root);
}

void BinarySearchTree::DeleteRecursive(Node*& node) {
    // return if the node is nullptr
    if (node == nullptr) {
        return;
    }
    // otherwise recursive delete all nodes in the bst
    else {
        DeleteRecursive(node->left);
        DeleteRecursive(node->right);
        delete node;
        node = nullptr;
    }
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::PrintCoursesInOrder() { 
    // if the root is nullptr there is nothing in the bst
    if (root == nullptr) {
        cout << "There is no course data to display" << endl << endl;
    }
    else {
        cout << "Here is a sample schedule:" << endl << endl;
        // call inOrder fuction and pass root 
        this->printCoursesInOrder(root);
    }
}

/**
 * Insert a course
 */
void BinarySearchTree::Insert(Course course) {
    // if root equarl to null ptr
    if (root == nullptr) {
        // root is equal to new node course
        root = new Node(course);
    }
    // else
    else {
        // add Node root and course
        this->addNode(root, course);
    }
}

/**
 * Search for a course
 */
Course BinarySearchTree::Search(string courseId) {

    // set current node equal to root
    Node* current = root;

    // keep looping downwards until bottom reached or matching courseId found
    while (current != nullptr) {
        // if match found, return current course
        if (current->course.courseId.compare(courseId) == 0) {
            return current->course;
        }

        // if course is smaller than current node then traverse left
        if (courseId.compare(current->course.courseId) < 0) {
            current = current->left;
        }

        // else larger so traverse right
        else {
            current = current->right;
        }
    }

    // if the course is not found create an empty course and return it 
    Course course;
    return course;
}

/**
 * Add a course to some node (recursive)
 *
 * @param node Current node in tree
 * @param course Course to be added
 */
void BinarySearchTree::addNode(Node* node, Course course) {

    // if node is larger then add to left
    if (node->course.courseId.compare(course.courseId) > 0) {
        // if no left node
        if (node->left == nullptr) {
            // this node becomes left
            node->left = new Node(course);
        }

        // else recurse down the left node
        else {
            this->addNode(node->left, course);
        }
    }
    // else add to right subtree
    else {
        // if no right node
        if (node->right == nullptr) {
            // this node becomes right
            node->right = new Node(course);
        }

        //else
        else {
            // recurse down the right node
            this->addNode(node->right, course);
        }
    }
}

void BinarySearchTree::printCoursesInOrder(Node* node) {
    //if node is not equal to null ptr
    if (node != nullptr) {
        //InOrder not left
        printCoursesInOrder(node->left);

        //output courseID, courseTitle
        std::cout << node->course.courseId << ", " << node->course.courseTitle <<  endl;

        //InOder right
        printCoursesInOrder(node->right);
    }
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the course information to the console (std::out)
 *
 * @param course struct containing the course info
 */
void displayCourse(Course course) {
    // display courseId and courseTitle
    cout << course.courseId << ", " << course.courseTitle << endl;

    // If there is one prerequisite
    if (course.coursePrereq1 != "" && course.coursePrereq2 == "") {
        cout << "Prerequisites: " << course.coursePrereq1 << endl << endl;
    }

    // If there are two prerequisites
    else if (course.coursePrereq1 != "" && course.coursePrereq2 != "") {
        cout << "Prerequisites: " << course.coursePrereq1 << ", " << course.coursePrereq2 << endl << endl;
    }

    // If there are no prerequisites
    else {
        cout << "Prerequisites: None" << endl << endl;
    }
    
    return;
}

/**
 * Load a CSV file containing courses into a container
 *
 * @param csvPath the path to the CSV file to load
 */
void loadCourses(string csvPath, BinarySearchTree* bst) {
    cout << endl << "Loading CSV file " << csvPath << endl;

    // open the csv file
    ifstream inputFile(csvPath);

    // if the file does not open display an error message
    if (!inputFile.is_open()) {
        cout << "Error opening csv file" << endl;
        return;
    }

    vector<string> row;
    list<string> courseList;

    // first read the file to create a list of courses that exist in the csv file
    while (!inputFile.eof()) {
        row = getNextLineAndSplitIntoTokens(inputFile);
        courseList.push_back(row.at(0));
    }

    inputFile.close();

    // Now that courseList has been created we re-open the csv file and add courses to the bst
    ifstream inputFileAgain(csvPath);

    // if the file does not open display an error message
    if (!inputFileAgain.is_open()) {
        cout << "Error opening csv file" << endl;
        return;
    }
    
    while (!inputFileAgain.eof()) {
        // call the method to split the current line of the csvFile into seperate tokens which can be stored into a vector of rows
        row = getNextLineAndSplitIntoTokens(inputFileAgain);

        // create a new course object
        Course course;

        // for prerequisites
        bool courseFound = false;
        bool courseFound2 = false;

        // break if the end of the csv file has been reached
        if (inputFileAgain.eof()) {
            break;
        }

        // if there are no course prerequisites
        if (row.at(2) == "" && row.at(3) == "") {
            // assign course attributes
            course.courseId = row.at(0);
            course.courseTitle = row.at(1);

            // insert the course in the bst
            bst->Insert(course);
        }

        // if there is one course prerequisite
        else if (row.at(2) != "" && row.at(3) == "") {
            // check that the course prerequisite exists somewhere in the csvFile
            for (string searchCourse : courseList) {
                if (searchCourse == row.at(2)) {
                    courseFound = true;
                }
            }
            // if the prerequisite exists somewhere in the csvFile
            if (courseFound) {
                // assign course attributes
                course.courseId = row.at(0);
                course.courseTitle = row.at(1);
                course.coursePrereq1 = row.at(2);

                // insert the course in the bst
                bst->Insert(course);
            }
        }

        // if there are two course prerequisites    
        else if (row.at(2) != "" && row.at(3) != "") {

            // check that the course prerequisites exists somewhere in the csvFile
            for (string searchCourse : courseList) {
                if (searchCourse == row.at(2)) {
                    courseFound = true;
                }
                if (searchCourse == row.at(3)) {
                    courseFound2 = true;
                }
            }
            // if the prerequisites exists somewhere in the csvFile
            if (courseFound && courseFound2) {
                // assign course attributes
                course.courseId = row.at(0);
                course.courseTitle = row.at(1);
                course.coursePrereq1 = row.at(2);
                course.coursePrereq2 = row.at(3);

                // insert the course in the bst
                bst->Insert(course);
            }
        }
        
        // otherwise the line in the csv file has less than 2 parameters
        else {
            cout << "The course can not be added because there is not enough course data" << endl;
        }
    }

    inputFileAgain.close();
}

// method for spliting the rows in the csvFile into tokens
vector<string>  getNextLineAndSplitIntoTokens(istream& str) {
    // vector for storing the tokens of each line in the csvFile
    vector<string> result;
    
    // a string for reading the line in the csvFile
    string line;

    // read the line in the csvFile
    getline(str, line);

    //  for extracting items from the line
    stringstream lineStream(line);

    //define the token
    string cell;

    // each time a comma is seen push the token to the back of the result vector
    while (getline(lineStream, cell, ',')) {
        result.push_back(cell);
    }

    // if the token is empty push back an empty string to the result vector
    if (!lineStream && cell.empty()) {
        result.push_back("");
    }

    // return the result vector
    return result;
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, searchValue;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        searchValue = "";
        break;
    case 3:
        csvPath = argv[1];
        searchValue = argv[2];
        break;
    default:
        csvPath = "";
        searchValue = "";
    }

    // Define a binary search tree to hold all courses
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Course course;

    int choice = 0;
    while (choice != 9) {

        // display the menu
        cout << "Menu:" << endl;
        cout << "  1. Load Data Structure." << endl;
        cout << "  2. Print Course List." << endl;
        cout << "  3. Print Course." << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        
        cin >> choice;

        switch (choice) {

            case 1:

                // get the csv file path from input
                while (csvPath == "") {
                    cout << endl << "What is the name of the file you would like to load: ";
                    cin.ignore();
                    getline(cin, csvPath);
                }
 
                // call the function to load the data structure
                loadCourses(csvPath, bst);

                cout << endl;

                csvPath = "";
                break;

            case 2:

                // call InOrder() to sort and print course information alphanumerically from lowest to highest
                bst->PrintCoursesInOrder();

                cout << endl;
                break;

            case 3:

                // get the course id from input
                while (searchValue == "") {
                    cout << "What course do you want to know about? ";
                    cin.ignore();
                    getline(cin, searchValue);
                }
            
                // convert the string to upper case
                for (auto& x : searchValue) {
                    x = toupper(x);
                }

                // call the function to search for the course and have it return the course if found otherwise an empty course is returned
                course = bst->Search(searchValue);

                // if the returned course is not an empty course call the function to display the course information
                if (!course.courseId.empty()) {
                    displayCourse(course);
                }
                // otherwise display error message
                else {
                    cout << "Course Id " << searchValue << " not found." << endl;
                }
                // needed to clear the input buffer
                cout << endl << "Press any key to return to the main menu..." << endl << endl;
                cin.ignore();

                searchValue = "";

                break;

            default:
                // we only display this message if the user is not exiting and they make an invalid choice
                if (choice != 9) {
                    cout << choice << " is not a valid option." << endl << endl;
                }

                break;
        }
    }

    cout << "Good bye." << endl;

    // clean up memory
    delete(bst);

    return 0;
}
