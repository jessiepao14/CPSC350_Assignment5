#ifndef _FACULTY_HPP_
#define _FACULTY_HPP_

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Faculty
{
private:
    int id;
    string name;
    string level;
    string department;
    unsigned int numberOfAdvisee;
    vector<int> advisee;

public:
    Faculty();
    Faculty(int facultyID, string facultyName, string facultyLevel, string facultyDepartment);
    ~Faculty();

    //Getters
    int getID() { return id; }
    string getName() { return name; }
    string getLevel() { return level; }
    string getDepartment() { return department; }
    int getNumberOfAdvisee() { return numberOfAdvisee; }
    vector<int> getAdviseeList();
    int getAdvisee(int id);
    string getAdviseeWrite();

    //Setters
    void setID(int facultyID) { id = facultyID; }
    void setName(string facultyName) { name = facultyName; }
    void setLevel(string facultyLevel) { level = facultyLevel; }
    void setDepartment(string facultyDepartment) { department = facultyDepartment; }

    void printAdvisee();
    void writeToFile(string fileName);
    void addAdvisee(int studentID);
    void removeAdvisee(int studentID);

    bool operator<(const Faculty &f1) const;
    bool operator>(const Faculty &f1) const;
    bool operator<=(const Faculty &f1) const;
    bool operator>=(const Faculty &f1) const;
    bool operator!=(const Faculty &f1) const;
    bool operator==(const Faculty &f1) const;

    int operator+(const Faculty &f1) const;

    friend ostream &operator<<(ostream &os, Faculty &f1)
    {
        os << "Faculty ID: " << f1.id;
        return os;
    }
};

#endif