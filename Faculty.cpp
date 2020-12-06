#include "Faculty.hpp"

Faculty::Faculty()
{
    id = 0;
    name = "";
    level = "";
    department = "";
    numberOfAdvisee = 0;
}

Faculty::Faculty(int idNumber, string facultyName, string facultyLevel, string facultyDepartment)
{
    id = idNumber;
    name = facultyName;
    level = facultyLevel;
    department = facultyDepartment;
    numberOfAdvisee = 0;
}

Faculty::~Faculty()
{
}

void Faculty::printAdvisee()
{
    if (numberOfAdvisee == 0)
    {
        cout << "This faculty member doesn't not have any advisees." << endl;
    }
    else
    {
        for (int i = 0; i < numberOfAdvisee; ++i)
        {
            if (i > 0)
            {
                cout << ", ";
            }
            if (advisee.at(i) != 0)
            {
                cout << advisee.at(i);
            }
        }
    }
}

void Faculty::writeToFile(string fileName) {
    ofstream outFile;
    outFile.open(fileName, ios::app);

    outFile << id << "," << name << "," << level << "," << department << ",";
    for (int i = 0; i < numberOfAdvisee; ++i) {
        if (i == 0) {
            outFile << getAdvisee(i);
        } else {
            outFile << "," << getAdvisee(i);
        }
    }
    outFile << endl;

    outFile.close();
}

void Faculty::addAdvisee(int studentID)
{
    advisee.push_back(studentID);
    ++numberOfAdvisee;
}

vector<int> Faculty::getAdviseeList()
{
    return advisee;
}

int Faculty::getAdvisee(int id)
{
    return advisee.at(id);
}

string Faculty::getAdviseeWrite() {
    string result = "";
    for (int i = 0; i < advisee.size(); i++)
    {
        result += (advisee.at(i) + ",");
    }
}

void Faculty::removeAdvisee(int studentID)
{
    int adviseeIndex = -1;
    for (int i = 0; i < advisee.size(); i++)
    {
        if (advisee.at(i) == studentID)
        {
            adviseeIndex = i;
        }
    }
    if (adviseeIndex == -1)
    {
        cout << "ID not found... Can not delete something that doesn't exist" << endl;
    }
    else
    {   
        advisee.erase(advisee.begin() + adviseeIndex);
    }
    numberOfAdvisee--;
}

bool Faculty::operator<(const Faculty &f) const
{
    return (this->id < f.id);
}

bool Faculty::operator>(const Faculty &f) const
{
    return (this->id > f.id);
}

bool Faculty::operator<=(const Faculty &f) const
{
    return (this->id <= f.id);
}

bool Faculty::operator>=(const Faculty &f) const
{
    return (this->id >= f.id);
}

bool Faculty::operator!=(const Faculty &f) const
{
    return (this->id != f.id);
}

bool Faculty::operator==(const Faculty &f) const
{
    return (this->id == f.id);
}

int Faculty::operator+(const Faculty &f) const
{
    return (this->id + f.id);
}