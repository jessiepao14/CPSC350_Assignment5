#ifndef _STUDENT_HPP_
#define _STUDENT_HPP_

#include <iostream>
#include "University.hpp"

using namespace std;

class Student : public University
{
private:
    string major;
    double gpa;
    int advisorId;

public:
    Student();
    Student(int idNumber, string studentName, string studentLevel, string studentMajor, double studentGPA, int studentAdvisorID);
    ~Student();
    //getter
    string getMajor() {return major;}
    double getGPA() {return gpa;}
    int getAdvisorID() {return advisorId;}
    //setter 
    void setMajor(string studentMajor) {major = studentMajor;}
    void setGPA(double studentGPA) {gpa = studentGPA;}
    void setAdvisorID(int studentAdvisorID) {advisorId = studentAdvisorID;}

    void printStudentInformation();

    bool operator < (const Student &s);
    bool operator > (const Student &s);
    bool operator <= (const Student &s);
    bool operator >= (const Student &s);
    bool operator != (const Student &s);
    bool operator == (const Student &s);
};

Student::Student()
{
}

Student::~Student()
{
}


#endif