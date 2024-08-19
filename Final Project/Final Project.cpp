// Mitchell Fontaine
// CS-300 Final Project
// 08/14/2024

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Define a struct to represent a Course
struct Course {
    string courseNumber; // Variable for the course number
    string courseTitle; // Title of the course
    vector<string> prerequisites; // List of prerequisites for the course
};

// Define a struct to represent a Node in the Binary Search Tree
struct Node {
    Course course; // Course information stored in the node
    Node* left; // Pointer to the left child node
    Node* right; // Pointer to the right child node

    // Constructor to initialize a new node with a course
    Node(Course course) : course(course), left(nullptr), right(nullptr) {}
};

// Define a class to represent a Binary Search Tree
class BinarySearchTree {
private:
    Node* root; // Pointer to the root node of the tree

    // Helper function to add a new node to the tree
    void addNode(Node* node, Node* newNode) {
        // If the new node's course number is less than the current node's,
        // add it to the left subtree
        if (newNode->course.courseNumber < node->course.courseNumber) {
            if (node->left == nullptr) {
                node->left = newNode;
            }
            else {
                addNode(node->left, newNode);
            }
        }
        // Otherwise, add it to the right subtree
        else {
            if (node->right == nullptr) {
                node->right = newNode;
            }
            else {
                addNode(node->right, newNode);
            }
        }
    }
    // Helper function to perform an in-order traversal of the tree
    void inOrder(Node* node) {
        if (node == nullptr) return;
        inOrder(node->left);
        cout << node->course.courseNumber << ", " << node->course.courseTitle << endl;
        inOrder(node->right);
    }
    // Helper function to search for a course by its number
    Node* search(Node* node, string courseNumber) {
        if (node == nullptr || node->course.courseNumber == courseNumber) {
            return node;
        }

        if (courseNumber < node->course.courseNumber) {
            return search(node->left, courseNumber);
        }

        return search(node->right, courseNumber);
    }

public:
    // Constructor to initialize an empty tree
    BinarySearchTree() : root(nullptr) {}

    // Function to insert a new course into the tree
    void insert(Course course) {
        Node* newNode = new Node(course);
        if (root == nullptr) {
            root = newNode;
        }
        else {
            addNode(root, newNode);
        }
    }
    // Function to print all courses in the tree
    void printCourses() {
        inOrder(root);
    }
    // Function to print information about a specific course
    void printCourseInfo(string courseNumber) {
        Node* node = search(root, courseNumber);
        if (node == nullptr) {
            cout << "Course not found." << endl;
            return;
        }

        cout << node->course.courseNumber << ", " << node->course.courseTitle << endl;
        if (!node->course.prerequisites.empty()) {
            cout << "Prerequisites: ";
            for (size_t i = 0; i < node->course.prerequisites.size(); ++i) {
                if (i > 0) cout << ", ";
                cout << node->course.prerequisites[i];
            }
            cout << endl;
        }
        else {
            cout << "No prerequisites" << endl;
        }
    }
};
// Function to load courses from a CSV file into the Binary Search Tree
void loadCourses(BinarySearchTree& bst) {
    ifstream file("CS 300 ABCU_Advising_Program_Input.csv"); // Use the .csv file in the source directory
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string courseNumber, courseTitle;
        getline(ss, courseNumber, ',');
        getline(ss, courseTitle, ',');

        Course course;
        course.courseNumber = courseNumber;
        course.courseTitle = courseTitle;

        string prerequisite;
        while (getline(ss, prerequisite, ',')) {
            course.prerequisites.push_back(prerequisite);
        }

        bst.insert(course);
    }
    file.close();
    cout << "Data loaded successfully." << endl;
}
// Main function
int main() {
    BinarySearchTree bst;
    int choice;
    do {
        cout << "Welcome to the course planner." << endl;
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit." << endl;
        cout << "What would you like to do? ";
        cin >> choice;

        switch (choice) {
        case 1:
            // Load courses from the CSV file into the Binary Search Tree
            loadCourses(bst);
            break;
        case 2:
            // Print all courses in the tree
            bst.printCourses();
            break;
        case 3:
        {
            string courseNumber;
            cout << "What course do you want to know about? ";
            cin >> courseNumber;
            // Print information about a specific course
            bst.printCourseInfo(courseNumber);
            break;
        }
        case 9:
            // Exit the program
            cout << "Thank you for using the course planner!" << endl;
            break;
        default:
            // Handle invalid input
            cout << choice << " is not a valid option." << endl;
            break;
        }
    } while (choice != 9);

    return 0;
}
