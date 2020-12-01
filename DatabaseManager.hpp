#ifndef _DATABASE_MANAGER_
#define _DATABAST_MANAGER_

#include <iostream>
#include <string>

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

    void menu();
    
    void printAllStudents();
    void printAllFaculty();
    void findStudent(int studentID);
    void findFaculty(int facultyID);
    void givenStudentAdvisor(int studentID);
    void givenFacultyAdvisee(int advisorID);
    void addStudent();
    void addFaculty();

    // Do these sections
    void deleteFaculty(int facultyID);    // delete the faculty member and redistribute the advisees
    void changeAdvisee(int studentID, int facultyID);   // search for student and set the advisor to the facultyID
    void deleteAdvisee(int studentID, int facultyID);   // search for facult and delete the student from advisee list
    void rollback(); // use Stack to undo the last delete


};

#endif