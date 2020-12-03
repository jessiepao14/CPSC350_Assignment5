#include "DatabaseManager.hpp"

void printStudentInfo(Student *student);
void printFacultyInfo(Faculty *faculty);


void DatabaseManager::runSimulation() {
    int choice = -1;
    string empty;
    menu();
    
    while(choice != 14)
    {
        cout << "Enter an option (0- for help): \n";
        cin >> choice;
        getline(cin, empty);
        choice = toupper(choice);
        if(choice == 1){
            printAllStudents();
        } else if(choice == 2) {
            printAllFaculty();   
        } else if(choice == 3) {
            findStudent();
        } else if(choice == 4) {
            findFaculty();
        } else if(choice == 5) {
            givenStudentAdvisor();
        } else if(choice == 6) {
            givenFacultyAdvisee();
        } else if(choice == 7) {
            addStudent();
        } else if(choice == 8) {
            deleteStudent();
        } else if(choice == 9) {
            addFaculty(); 
        } 
        // else if(choice == 10) {
        //     deleteFaculty();
        // } else if (choice == 11) {
        //     changeAdvisee();
        // } else if (choice == 12) {
        //     deleteAdvisee();
        // } else if (choice == 13) {
        //     rollback();
        // }
    }
}

//#1 for the assignment
void DatabaseManager::printAllStudents() {
    printStudentHeader();
    studentTree.printTree(printStudentInfo);
}

//#2 for the assignment
void DatabaseManager::printAllFaculty() {
    printFacultyHeader();
    facultyTree.printTree(printFacultyInfo);
}
//#3 for the assignment
void DatabaseManager::findStudent() {
    int studentID = 0;
    string temp;
    cout << "Please enter the ID of the student you want to search for: " << endl;
    cin >> temp;
    studentID = validateInt(temp);

    Student *targetStudent = new Student();
    Student entry;

    targetStudent->setID(studentID);
    if (studentTree.getEntry(targetStudent, entry)) {
        cout << "Student was found" << endl;
        printStudentHeader();
        printStudentInfo(&entry);
    } else {
        cout << "Sorry there is no student with that ID" << endl;
    }
}
// #6 requirment for the assignment
void DatabaseManager::findFaculty() {
    int facultyID;
    string temp;
    cout << "Please enter the ID of the faculty you want to search for: " << endl;
    cin >> temp;
    facultyID = validateInt(temp);

    Faculty *targetFaculty = new Faculty();
    Faculty entry;

    targetFaculty->setID(facultyID);
    if (facultyTree.getEntry(targetFaculty, entry)) {
        cout << "Faculty member was found" << endl;
        printFacultyHeader();
        printFacultyInfo(&entry);
    } else {
        cout << "Sorry there is no faculty with that ID" << endl;
    }
}
// #5 requirment for the assignment
void DatabaseManager::givenStudentAdvisor() {
    int studentID;
    string temp;
    cout << "Please enter the student ID to find information on their advisor: " << endl;
    cin >> temp;
    studentID = validateInt(temp);

    Student *targetStudent = new Student();
    Student studentFound;

    targetStudent->setID(studentID);
    if (studentTree.getEntry(targetStudent, studentFound)) {
        Faculty *targetFaculty = new Faculty(); 
        Faculty facultyFound;
        targetFaculty->setID(studentFound.getAdvisorID());
        if (facultyTree.getEntry(targetFaculty, facultyFound)) {
            cout << "Faculty member was found" << endl;
            printFacultyHeader();
            printFacultyInfo(&facultyFound);
        } else {
            cout << "Sorry there is no faculty with that ID" << endl;
        }
    } else {
        cout << "Sorry there is no student with that ID" << endl;
    }
}
// #4 requirment for the assignment
void DatabaseManager::givenFacultyAdvisee() {
    int facultyID;
    string temp;
    cout << "Please enter the faculty ID to find information on their advisees: " << endl;
    cin >> temp;
    facultyID = validateInt(temp);

    Faculty *targetFaculty = new Faculty();
    Faculty entry;

    targetFaculty->setID(facultyID);
    if (facultyTree.getEntry(targetFaculty, entry)) {
        printAdvisee(entry);
    } else {
        cout << "Sorry there is no faculty with that ID" << endl;
    }
}

void DatabaseManager::printAdvisee(Faculty mentor){
    printStudentHeader();
    for (int i = 0; i < mentor.getNumberOfAdvisee(); ++i) {
        Student *targetStudent = new Student();
        Student entry;

        targetStudent->setID(mentor.getAdvisee(i));
        if (studentTree.getEntry(targetStudent, entry)) {
            cout << "Student was found" << endl;
            printStudentInfo(&entry);
        } else {
            cout << "Sorry there is no student with ID: " << mentor.getAdvisee(i) << endl;
        }
    }
}
// #7 requirment for the assignment
void DatabaseManager::addStudent() {
    int studentID;
    string studentName;
    string studentLevel;
    string studentMajor;
    double studentGPA;
    int studentAdvisorID;

    string temp;

    Faculty *targetFaculty = new Faculty();
    Faculty entry;
    

    cout << "Please input the student's ID: " << endl;
    cin >> temp;
    studentID = validateInt(temp);
    cout << "Please input the student's name: " << endl;
    cin >> studentName;
    cout << "Please input the student's level: " << endl;
    cin >> studentLevel;
    cout << "Please input the student's major: " << endl;
    cin >> studentMajor;
    cout << "Please input the student's GPA: " << endl;
    cin >> studentGPA;
    cout << "Please input the student's advisor ID: " << endl;
    cin >> studentAdvisorID;
    targetFaculty->setID(studentAdvisorID);
    facultyTree.getEntry(targetFaculty, entry);
    entry.addAdvisee(studentID);
    Student *newStudent = new Student(studentID, studentName, studentLevel, studentMajor, studentGPA, studentAdvisorID);
    studentTree.insert(newStudent);
}
// #9 requirment for the assignment
void DatabaseManager::addFaculty() {
    int facultyID;
    string facultyName;
    string facultyLevel;
    string department;

    string temp;

    cout << "Please input the faculty's ID: " << endl;
    cin >> temp;
    facultyID = validateInt(temp);
    cout << "Please input the faculty's name: " << endl;
    cin >> facultyName;
    cout << "Please input the faculty's level: " << endl;
    cin >> facultyLevel;
    cout << "Please input the faculty's department: " << endl;
    cin >> department;
    
    Faculty *newFaculty = new Faculty(facultyID, facultyName, facultyLevel, department);
    facultyTree.insert(newFaculty);
}
// #8 requirment for the assignment
void DatabaseManager::deleteStudent() {
    int facultyID = 0;
    int studentID = 0;
    string temp;
    cout << "Please enter the ID of the student you want to delete: " << endl;
    cin >> temp;
    studentID = validateInt(temp);
    
    Student *targetStudent = new Student();
    Student entry;
    targetStudent->setID(studentID);
    
    if(studentTree.getEntry(targetStudent, entry)) {
        facultyID = entry.getAdvisorID();
        Faculty *targetFaculty = new Faculty();
        Faculty facultyFound;
        targetFaculty->setID(facultyID);
        facultyTree.getEntry(targetFaculty, facultyFound);
        facultyFound.removeAdvisee(studentID);
    } else {
        cout << "Sorry there is no student with that ID" << endl;
    }
    if (studentTree.remove(targetStudent)){
        cout << "Student was sucessfully deleted" << endl;
    } else {
        cout << "ERROR! Student was not deleted." << endl;
    }
}


int DatabaseManager::validateInt(string temp) {
    while (checkInt(temp)) {
        cout << "Invalid Input! Please enter again: " << endl;
        cin >> temp;
    }
    return stoi(temp);
}

bool DatabaseManager::checkInt(string temp) {
    bool check = false;
    for (int i = 0; i < temp.length() && !check; ++i) {
        if (!isdigit(temp[i])) {
            check = true;
        } 
    }
    return check;
}

void DatabaseManager::printStudentHeader()
{
    cout << "========== ========================= =========== ========================= ===== ============" << endl;
    cout << " ID        Name                      Level       Major                     GPA   Advisor ID" << endl;
    cout << "========== ========================= =========== ========================= ===== ============" << endl;
}

void DatabaseManager::printFacultyHeader() {
    cout << "========== ========================= =========== ========================= ==================" << endl;
    cout << " ID        Name                      Level       Department                Advisee IDs" << endl;
    cout << "========== ========================= =========== ========================= ==================" << endl;
}

void printStudentInfo(Student *student) {
    cout << left << setw(10) << student->getID() << " "
                 << setw(25) << student->getName() << " "
                 << setw(11) << student->getLevel() << " "
                 << setw(25) << student->getMajor() << " "
                 << setw(5) << student->getGPA() << " "
                 << setw(12) << student->getAdvisorID() << endl;
}

void printFacultyInfo(Faculty *faculty) {
    cout << left << setw(10) << faculty->getID() << " "
                 << setw(25) << faculty->getName() << " "
                 << setw(11) << faculty->getLevel() << " "
                 << setw(25) << faculty->getDepartment() << " "
                 << setw(18); 
    faculty->printAdvisee();
}

void DatabaseManager::menu() {
    cout << "\n===== Main Menu ======\n" << endl;
    cout << "1 – Print all students and their information" << endl;
    cout << "2 – Print all faculty and their information" << endl;
    cout << "3 – Find and display student information given the students id" << endl;
    cout << "4 - Find and display faculty information given the faculty id" << endl;
    cout << "5 - Given a student’s id, print the name and info of their faculty advisor" << endl;
    cout << "6 - Given a faculty id, print ALL the names and info of his/her advisees." << endl;
    cout << "7 - Add a new student" << endl;
    cout << "8 – Delete a student given the id" << endl;
    cout << "9 – Add a new faculty member" << endl;
    cout << "10 – Delete a faculty member given the id." << endl;
    cout << "11 – Change a student’s advisor given the student id and the new faculty id." << endl;
    cout << "12 – Remove an advisee from a faculty member given the ids" << endl;
    cout << "13 – Rollback" << endl;
    cout << "14 – Exit" << endl;
}
