#ifndef _FACULTY_HPP_
#define _FACULTY_HPP_

#include <iostream>
#include <vector>
#include "University.hpp"

using namespace std;

class Faculty : public University {
private:
    string department;
    unsigned int numberOfAdvisee;
    vector<int> advisee;

public:
    Faculty();
    Faculty(int facultyID, string facultyName, string facultyLevel, string facultyDepartment);
    ~Faculty();

    //Getters
    string getDepartment() {return department;}
    int getNumberOfAdvisee() {return numberOfAdvisee;}
    int getAdvisee(int position);

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