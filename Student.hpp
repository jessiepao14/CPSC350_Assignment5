#ifndef _STUDENT_HPP_
#define _STUDENT_HPP_

#include <iostream>
#include <fstream>

using namespace std;

class Student
{
private:
    int id;
    string name;
    string level;
    string major;
    double gpa;
    int advisorId;

public:
    Student();
    Student(int idNumber, string studentName, string studentLevel, string studentMajor, double studentGPA, int studentAdvisorID);

    //getter
    int getID() { return id; }
    string getName() { return name; }
    string getLevel() { return level; }
    string getMajor() { return major; }
    double getGPA() { return gpa; }
    int getAdvisorID() { return advisorId; }
    //setter
    void setID(int studentID) { id = studentID; }
    void setName(string studentName) { name = studentName; }
    void setLevel(string studentLevel) { level = studentLevel; }
    void setMajor(string studentMajor) { major = studentMajor; }
    void setGPA(double studentGPA) { gpa = studentGPA; }
    void setAdvisorID(int studentAdvisorID) { advisorId = studentAdvisorID; }

    void writeToFile(string fileName);

    //void printStudentInformation();

    bool operator<(const Student &s);
    bool operator>(const Student &s);
    bool operator<=(const Student &s);
    bool operator>=(const Student &s);
    bool operator!=(const Student &s);
    bool operator==(const Student &s);
    int operator+(const Student &s1) const;
};

#endif