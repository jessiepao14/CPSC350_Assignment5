#ifndef _DATABASE_MANAGER_
#define _DATABAST_MANAGER_

#include <iostream>
#include <string>
#include <fstream>

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
    // Stack<Student> undoStudentStack;
    // Stack<Student> undoStudentStack;
    // implement stack in GenStrcutures.hpp

public:
    DatabaseManager();
    ~DatabaseManager();

    void runSimulation();

    void menu();
    
    void printAllStudents();       //1
    void printAllFaculty();        //2
    void findStudent();            //3
    void findFaculty();            //4
    void givenStudentAdvisor();    //5
    void givenFacultyAdvisee();    //6
    void addStudent();             //7
    void deleteStudent();          //8
    void addFaculty();             //9

    // Do these sections
    void deleteFaculty();    // delete the faculty member and redistribute the advisees
    void changeAdvisee();   // search for student and set the advisor to the facultyID
    void deleteAdvisee();   // search for facult and delete the student from advisee list
    void rollback();        // use Stack to undo the last delete

    void printStudentHeader();
    void printFacultyHeader();
    
    int validateInt(string temp);
    bool checkInt(string temp);
    void printAdvisee(Faculty mentor);
};

#endif