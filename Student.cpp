#include "Student.hpp"

Student::Student() {
    id = 0;
    name = "";
    level = "";
    major = "";
    gpa = 0.0;
    advisorId = 0;
}

Student::Student(int idNumber, string studentName, string studentLevel, string studentMajor, double studentGPA, int studentAdvisorID) {
    id = idNumber;
    name = studentName;
    level = studentLevel;
    major = studentMajor;
    gpa = studentGPA;
    advisorId = studentAdvisorID;
}

// void Student::printStudentInformation(){
    
// }

bool Student::operator < (const Student &s){
    return (id < s.id);
}

bool Student::operator > (const Student &s){
    return (id > s.id);
}

bool Student::operator <= (const Student &s){
    return (id <= s.id);
}

bool Student::operator >= (const Student &s){
    return (id >= s.id);
}

bool Student::operator != (const Student &s){
    return (id != s.id);
}

bool Student::operator == (const Student &s){
    return (id == s.id);
}