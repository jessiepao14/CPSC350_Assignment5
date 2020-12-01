#include "Faculty.hpp"


Faculty::Faculty(){
    id = 0;
    name = "";
    level = "";
    department ="";
    numberOfAdvisee = 0;
    maxAdvisee = 10;
    advisee = new int[maxAdvisee];
    for (int i = 0; i < maxAdvisee; ++i) {
        advisee[i] = 0;
    }
}

Faculty::~Faculty(){
    delete []advisee;
}

void Faculty::addAdvisee(int studentID){

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