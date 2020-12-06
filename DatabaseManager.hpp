#ifndef _DATABASE_MANAGER_
#define _DATABASE_MANAGER_

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

#include "BinarySearchTree.hpp"
#include "Faculty.hpp"
#include "Student.hpp"

using namespace std;

class DatabaseManager
{
private:
    Student students;
    Faculty faculty;
    BinarySearchTree<Student> studentTree;
    BinarySearchTree<Faculty> facultyTree;
    GenStack<Student> undoStudentStack;
    GenStack<Faculty> undoFacultyStack;
    GenStack<int> undoActionStack;      // 0 - Add Student  1 - Add Faculty   2 - Delete Student    3 - Delete Faculty
    // implement stack in GenStrcutures.hpp
public:
    DatabaseManager() {};
    ~DatabaseManager() {};
    void runSimulation();
    bool setUpStudentTree(string studentFile);
    bool setUpFacultyTree(string facultyFile);
    void writeToFile(string studentFile, string facultyFile);
    void clearFiles(string studentFile, string facultyFile);

    void menu();

    void printAllStudents();    //1
    void printAllFaculty();     //2
    void findStudent();         //3
    void findFaculty();         //4
    void givenStudentAdvisor(); //5
    void givenFacultyAdvisee(); //6
    void addStudent();          //7
    void deleteStudent();       //8
    void addFaculty();          //9
    void deleteFaculty();       //10 delete the faculty member and redistribute the advisees
    void changeAdvisee();       //11 search for student and set the advisor to the facultyID
    void deleteAdvisee();       //12 search for facult and delete the student from advisee list
    void rollback();            //13 use Stack to undo the last delete
    void printStudentTree();    //14
    void printFacultyTree();    //15
    void clearStudentTree();    //16
    void clearFacultyTree();    //17


    void printStudentHeader();
    void printFacultyHeader();

    int validateInt(string temp);
    bool checkInt(string temp);
    void printAdvisee(Faculty mentor);
};

#endif