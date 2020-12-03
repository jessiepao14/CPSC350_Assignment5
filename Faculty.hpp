#ifndef _FACULTY_HPP_
#define _FACULTY_HPP_

#include <iostream>
#include <vector>

using namespace std;

class Faculty {
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
    int getID() {return id;}
    string getName() {return name;}
    string getLevel() {return level;}
    string getDepartment() {return department;}
    int getNumberOfAdvisee() {return numberOfAdvisee;}
    int getAdvisee(int position);

    //Setters
    void setID(int facultyID) {id = facultyID;}
    void setName(string facultyName) {name = facultyName;}
    void setLevel(string facultyLevel) {level = facultyLevel;} 
    void setDepartment(string facultyDepartment) {department = facultyDepartment;}

    void printAdvisee();
    void addAdvisee(int studentID);
    void removeAdvisee(int studentID);

    bool operator < (const Faculty &f);
    bool operator > (const Faculty &f);
    bool operator <= (const Faculty &f);
    bool operator >= (const Faculty &f);
    bool operator != (const Faculty &f);
    bool operator == (const Faculty &f);
};




#endif