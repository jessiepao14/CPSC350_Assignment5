#include "Faculty.hpp"

Faculty::Faculty() {
    id = 0;
    name = "";
    level = "";
    department = "";
    numberOfAdvisee = 0;
}

Faculty::Faculty(int idNumber, string facultyName, string facultyLevel, string facultyDepartment){
    id = idNumber;
    name = facultyName;
    level = facultyLevel;
    department = facultyDepartment;
    numberOfAdvisee = 0;
}

Faculty::~Faculty(){
    
}

void Faculty::printAdvisee() {
    if (numberOfAdvisee == 0) {
        cout << "This faculty member doesn't not have any advisees." << endl;
    } else {
        for (int i = 0; i < numberOfAdvisee; ++i) {
            if (i > 0) {
                cout << ", ";
            }
            if (advisee[i] != 0) {
                cout << advisee[i];
            }
        }
    }
    cout << endl;
}

void Faculty::addAdvisee(int studentID){
    advisee.push_back(studentID);
    ++numberOfAdvisee;
}

int Faculty::getAdvisee(int position) {
    return advisee.at(position);
}

void Faculty::removeAdvisee(int studentID) {
    int adviseeIndex = -1;
    for (int i = 0; i < advisee.size(); i++) {
        if (advisee.at(i) == studentID) {
            adviseeIndex = i;
        }
    }
    if (adviseeIndex = -1) {
        cout<< "ID not found... Can not delete something that doesn't exist"<< endl;
    } else {
        advisee.erase(advisee.begin() + adviseeIndex);
    }
}

bool Faculty::operator < (const Faculty &f){
    return (id < f.id);
}

bool Faculty::operator > (const Faculty &f){
    return (id > f.id);
}

bool Faculty::operator <= (const Faculty &f){
    return (id <= f.id);
}

bool Faculty::operator >= (const Faculty &f){
    return (id >= f.id);
}

bool Faculty::operator != (const Faculty &f){
    return (id != f.id);
}

bool Faculty::operator == (const Faculty &f){
    return (id == f.id);
}