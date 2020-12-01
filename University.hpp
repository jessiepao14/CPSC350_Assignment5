#ifndef _UNIVERSITY_HPP_
#define _UNIVERSITY_HPP_

#include <iostream>

using namespace std;

class University {
protected:
    int id;
    string name;
    string level;


public:
    University ();
    //getters
    int getId() {return id;}
    string getName() {return name;}
    string getLevel() {return level;}
    //setters
    void setID(int idNumber) {id = idNumber;}
    void setName(string n) {name = n;}
    void setLevel(string l) {level = l;}
};

University::University (){
    id = 0;
    name = "";
    level = "";
}



#endif