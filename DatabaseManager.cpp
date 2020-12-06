#include "DatabaseManager.hpp"

void printStudentInfo(Student *student);
void printStudentName(Student *student);
void writeStudentFile(Student *student, ofstream outFile);
void printFacultyInfo(Faculty *faculty);
void printFacultyName(Faculty *faculty);
void writeFacultyFile(Faculty *faculty, ofstream outFile);


void DatabaseManager::runSimulation()
{
    int choice = -1;
    string temp;
    string empty;
    menu();

    while (choice != 18)
    {
        cout << "Enter an option (0- for help): \n";
        cin >> temp;
        getline(cin, empty);
        choice = validateInt(temp);
        if (choice == 0) 
        {
            menu();
        } 
        else if (choice == 1)
        {
            printAllStudents();
        }
        else if (choice == 2)
        {
            printAllFaculty();
        }
        else if (choice == 3)
        {
            findStudent();
        }
        else if (choice == 4)
        {
            findFaculty();
        }
        else if (choice == 5)
        {
            givenStudentAdvisor();
        }
        else if (choice == 6)
        {
            givenFacultyAdvisee();
        }
        else if (choice == 7)
        {
            addStudent();
        }
        else if (choice == 8)
        {
            deleteStudent();
        }
        else if (choice == 9)
        {
            addFaculty();
        }
        else if(choice == 10) 
        {
            deleteFaculty();
        } 
        else if (choice == 11) 
        {
            changeAdvisee();
        } 
        else if (choice == 12) 
        {
            deleteAdvisee();
        } 
        else if (choice == 13) 
        {
            rollback();
        }
        else if (choice == 14) {
            printStudentTree();
        } 
        else if (choice == 15) {
            printFacultyTree();
        } 
        else if (choice == 16) {
            clearStudentTree();
        } 
        else if (choice == 17) {
            clearFacultyTree();
        } 
        else if (choice != 18 && choice < 18) {
            cout << "Invalid input..." << endl;
        }
    } 
    clearFiles("StudentTable.txt", "FacultyTable.txt");
    writeToFile("StudentTable.txt", "FacultyTable.txt");
}

bool DatabaseManager::setUpStudentTree(string studentFile) {
    ifstream inFile;
    inFile.open(studentFile);
    if (!inFile) {
        cout << "Student File not found" << endl;
        return false;
    }
    string temp = "";
    int count = 0;
    int studentID = 0;
    string studentName = "";
    string studentLevel = "";
    string studentMajor = "";
    double studentGPA = 0.0;
    int advisorID = 0;

    while (getline(inFile, temp)) {
        if (count == 0) {
            studentID = validateInt(temp);
            count++;
        } else if (count == 1) {
            studentName = temp;
            count++;
        } else if (count == 2) {
            studentLevel = temp;
            count++;
        } else if (count == 3) {
            studentMajor = temp;
            count++;
        } else if (count == 4) {
            studentGPA = stoi(temp);
            count++;
        } else if (count == 5) {
            advisorID = validateInt(temp);
            Student *newStudent = new Student(studentID, studentName, studentLevel, studentMajor, studentGPA, advisorID);
            studentTree.insert(newStudent);
            count = 0;
        }
    }
    inFile.close();
    return true;
}

bool DatabaseManager::setUpFacultyTree(string facultyFile) {
    ifstream inFile;
    inFile.open(facultyFile);
    if (!inFile) {
        cout << "Faculty File not found" << endl;
        return false;
    }
    string temp = "";
    int count = 0;
    int facultyID = 0;
    string facultyName = "";
    string facultyLevel = "";
    string facultyDepartment = "";
    int advisorID = 0;

    while (getline(inFile, temp)) {
        if (count == 0) {
            facultyID = validateInt(temp);
            count++;
        } else if (count == 1) {
            facultyName = temp;
            count++;
        } else if (count == 2) {
            facultyLevel = temp;
            count++;
        } else if (count == 3) {
            facultyDepartment = temp;
            count++;
        } else if (count == 4) {
            Faculty *newFaculty = new Faculty(facultyID, facultyName, facultyLevel, facultyDepartment);
            string idString = "";
            int idNumber = 0;
            for (int i = 0; i < temp.length(); ++i) {
                if (temp[i] != ',') {
                    idString += temp[i];
                } else {
                    idNumber = stoi(idString);
                }
                newFaculty->addAdvisee(idNumber);
            }
            facultyTree.insert(newFaculty);
            count = 0;
        } 
    }
    inFile.close();
    return true;
}

void DatabaseManager::writeToFile(string studentFile, string facultyFile) {
    studentTree.writeTree(studentFile);
    facultyTree.writeTree(facultyFile);
}

void DatabaseManager::clearFiles(string studentFile, string facultyFile) {
    ofstream outFile;
    outFile.open(studentFile);
    outFile.close();
    outFile.open(facultyFile);
    outFile.close();
}

void DatabaseManager::printAllStudents()
{
    printStudentHeader();
    studentTree.printTree(printStudentInfo);
}

void DatabaseManager::printAllFaculty()
{
    printFacultyHeader();
    facultyTree.printTree(printFacultyInfo);
}

void DatabaseManager::findStudent()
{
    int studentID = 0;
    string temp;
    cout << "Please enter the ID of the student you want to search for: " << endl;
    cin >> temp;
    studentID = validateInt(temp);

    Student *targetStudent = new Student();

    targetStudent->setID(studentID);
    if (studentTree.search(targetStudent))
    {
        cout << "Student was found" << endl;
        targetStudent = studentTree.find(targetStudent);
        printStudentHeader();
        printStudentInfo(targetStudent);
    }
    else
    {
        cout << "Sorry there is no student with that ID" << endl;
    }
}

void DatabaseManager::findFaculty()
{
    int facultyID;
    string temp;
    cout << "Please enter the ID of the faculty you want to search for: " << endl;
    cin >> temp;
    facultyID = validateInt(temp);

    Faculty *targetFaculty = new Faculty();

    targetFaculty->setID(facultyID);

    if (facultyTree.search(targetFaculty))
    {
        cout << "Faculty member was found" << endl;
        targetFaculty = facultyTree.find(targetFaculty);
        printFacultyHeader();
        printFacultyInfo(targetFaculty);
    }
    else
    {
        cout << "Sorry there is no faculty with that ID" << endl;
    }
}

void DatabaseManager::givenStudentAdvisor()
{
    int studentID;
    string temp;
    cout << "Please enter the student ID to find information on their advisor: " << endl;
    cin >> temp;
    studentID = validateInt(temp);

    Student *targetStudent = new Student();

    targetStudent->setID(studentID);
    if (studentTree.search(targetStudent))
    {
        targetStudent = studentTree.find(targetStudent);
        Faculty *targetFaculty = new Faculty();
        targetFaculty->setID(targetStudent->getAdvisorID());
        if (facultyTree.search(targetFaculty))
        {
            targetFaculty = facultyTree.find(targetFaculty);
            cout << "Faculty member was found" << endl;
            printFacultyHeader();
            printFacultyInfo(targetFaculty);
        }
        else
        {
            cout << "Sorry there is no faculty with that ID" << endl;
        }
    }
    else
    {
        cout << "Sorry there is no student with that ID" << endl;
    }
}

void DatabaseManager::givenFacultyAdvisee()
{
    int facultyID;
    string temp;
    cout << "Please enter the faculyt ID to find information on their advisees: " << endl;
    cin >> temp;
    facultyID = validateInt(temp);

    Faculty *targetFaculty = new Faculty();

    targetFaculty->setID(facultyID);
    if (facultyTree.search(targetFaculty))
    {
        targetFaculty = facultyTree.find(targetFaculty);
        if (targetFaculty->getNumberOfAdvisee() == 0) {
            cout << "This faculty member does not have any advisee" << endl;
        } else {
            printAdvisee(*targetFaculty);
        }
        
    }
    else
    {
        cout << "Sorry there is no faculty with that ID" << endl;
    }
}

void DatabaseManager::printAdvisee(Faculty mentor)
{
    printStudentHeader();
    for (int i = 0; i < mentor.getNumberOfAdvisee(); ++i)
    {
        Student *targetStudent = new Student();

        targetStudent->setID(mentor.getAdvisee(i));
        if (studentTree.search(targetStudent))
        {
            cout << "Student was found" << endl;
            targetStudent = studentTree.find(targetStudent);
            printStudentInfo(targetStudent);
        }
        else
        {
            cout << "Sorry there is no student with ID: " << mentor.getAdvisee(i) << endl;
        }
    }
}

void DatabaseManager::addStudent()
{
    int studentID;
    string studentName;
    string studentLevel;
    string studentMajor;
    double studentGPA;
    int studentAdvisorID;
    string temp;

    Faculty *targetFaculty = new Faculty();

    cout << "Please input the student's ID: " << endl;
    cin >> temp;
    studentID = validateInt(temp);
    getline(cin, temp);
    cout << "Please input the student's name: " << endl;
    getline(cin, studentName);
    cout << "Please input the student's level: " << endl;
    cin >> studentLevel;
    getline(cin, temp);
    cout << "Please input the student's major: " << endl;
    getline(cin, studentMajor);
    cout << "Please input the student's GPA: " << endl;
    cin >> studentGPA;
    cout << "Please input the student's advisor ID: " << endl;
    cin >> temp;
    studentAdvisorID = validateInt(temp);
    targetFaculty->setID(studentAdvisorID);
    while (!facultyTree.search(targetFaculty))
    {
        cout << "Faculty ID not found. Please enter a valid faculty ID :" << endl;
        cin >> temp;
        studentAdvisorID = validateInt(temp);
        targetFaculty->setID(studentAdvisorID);
    }
    targetFaculty = facultyTree.find(targetFaculty);
    targetFaculty->addAdvisee(studentID);
    Student *newStudent = new Student(studentID, studentName, studentLevel, studentMajor, studentGPA, studentAdvisorID);
    studentTree.insert(newStudent);
    undoActionStack.push(0);
    undoStudentStack.push(*newStudent);
}

void DatabaseManager::addFaculty()
{
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
    getline(cin, temp);
    cout << "Please input the faculty's department: " << endl;
    getline(cin, department);

    Faculty *newFaculty = new Faculty(facultyID, facultyName, facultyLevel, department);
    facultyTree.insert(newFaculty);
    undoActionStack.push(1);
    undoFacultyStack.push(*newFaculty);
}

void DatabaseManager::deleteStudent()
{
    int facultyID = 0;
    int studentID = 0;
    string temp;
    cout << "Please enter the ID of the student you want to delete: " << endl;
    cin >> temp;
    studentID = validateInt(temp);

    Student *targetStudent = new Student();
    targetStudent->setID(studentID);

    if (studentTree.search(targetStudent))
    {
        targetStudent = studentTree.find(targetStudent);
        facultyID = targetStudent->getAdvisorID();
        Faculty *targetFaculty = new Faculty();
        targetFaculty->setID(facultyID);
        targetFaculty = facultyTree.find(targetFaculty);
        targetFaculty->removeAdvisee(studentID);
    }
    else
    {
        cout << "Sorry there is no student with that ID" << endl;
    }
    if (studentTree.remove(targetStudent))
    {
        cout << "Student was sucessfully deleted" << endl;
    }
    else
    {
        cout << "ERROR! Student was not deleted." << endl;
    }
    undoActionStack.push(2);
    undoStudentStack.push(*targetStudent);
}

void DatabaseManager::deleteFaculty()
{
    vector<int> advisee;
    int facultyID = 0;
    string temp;
    cout << "Please enter the ID of the faculty you want to delete: " << endl;
    cin >> temp;
    facultyID = validateInt(temp);

    Faculty *targetFaculty = new Faculty();
    targetFaculty->setID(facultyID);

    if (facultyTree.search(targetFaculty))
    {
        targetFaculty = facultyTree.find(targetFaculty);
        advisee = targetFaculty->getAdviseeList();
        Student *targetStudent = new Student();
        for (int i = 0; i < advisee.size(); i++) {
            targetStudent->setID(advisee.at(i));
            targetStudent = studentTree.find(targetStudent);
            targetStudent->setAdvisorID(facultyTree.getRandomNode().getID());
        }
    }
    else
    {
        cout << "Sorry there is no facluty with that ID" << endl;
    }
    if (facultyTree.remove(targetFaculty))
    {
        cout << "Faculty was sucessfully deleted" << endl;
    }
    else
    {
        cout << "ERROR! Faculty was not deleted." << endl;
    }
    undoActionStack.push(3);
    undoFacultyStack.push(*targetFaculty);
}

void DatabaseManager::changeAdvisee() {
    int facultyID = 0;
    int oldAdvisor = 0;
    int studentID = 0;
    string temp;
    cout << "Please enter the ID of the student you want to change advisor for: " << endl;
    cin >> temp;
    studentID = validateInt(temp);
    Student *targetStudent = new Student();
    targetStudent->setID(studentID);
    while (!studentTree.search(targetStudent))
    {
        cout << "Student ID not found. Please enter a valid student ID :" << endl;
        cin >> temp;
        studentID = validateInt(temp);
        targetStudent->setID(studentID);
    }

    cout << "Please enter the ID of the faculty you want for student: " << endl;
    cin >> temp;
    facultyID = validateInt(temp);
    Faculty *targetFaculty = new Faculty();
    targetFaculty->setID(facultyID);
    
    while (!facultyTree.search(targetFaculty))
    {
        cout << "Faculty ID not found. Please enter a valid faculty ID :" << endl;
        cin >> temp;
        facultyID = validateInt(temp);
        targetFaculty->setID(facultyID);
    }
    targetStudent = studentTree.find(targetStudent);
    oldAdvisor = targetStudent->getAdvisorID();
    targetStudent->setAdvisorID(facultyID);

    targetFaculty->setID(oldAdvisor);
    targetFaculty->removeAdvisee(studentID);
}

void DatabaseManager::deleteAdvisee() {
    int facultyID = 0;
    int studentID = 0;
    string temp;
    string userResponse;
    cout << "Please enter the ID of the faculty that includes the advisee needed to remove: " << endl;
    cin >> temp;
    facultyID = validateInt(temp);
    Faculty *targetFaculty = new Faculty();
    targetFaculty->setID(facultyID);
    while (!facultyTree.search(targetFaculty))
    {
        cout << "Faculty ID not found. Please enter a valid faculty ID :" << endl;
        cin >> temp;
        facultyID = validateInt(temp);
        targetFaculty->setID(facultyID);
    } 

    cout << "Please enter the ID of the student you want delete from advisee list: " << endl;
    
    cin >> temp;
    studentID = validateInt(temp);
    Student *targetStudent = new Student();
    Faculty facultyEntry;
    targetStudent->setID(studentID);
    while (!studentTree.search(targetStudent))
    {
        cout << "Student ID not found. Please enter a valid student ID :" << endl;
        cin >> temp;
        studentID = validateInt(temp);
        targetStudent->setID(studentID);
    }
    targetFaculty = facultyTree.find(targetFaculty);
    targetFaculty->removeAdvisee(studentID);
    
    cout << "Do you want to assign random advisor to student or enter advisor (R - Rand or E - Enter): " << endl;
    cin >> userResponse;
    while (userResponse != "R" && userResponse != "E" && userResponse != "r" && userResponse != "e" ) {
        cout << "Invalid Response Try Again..." << endl;
        cin >> userResponse;
    }

    if (userResponse == "E" || userResponse == "e") {
        cout << "Please enter the ID of the advisor: " << endl;
        cin >> temp;
        facultyID = validateInt(temp);
        Faculty *targetFaculty = new Faculty();
        targetFaculty->setID(facultyID);
        while (!facultyTree.search(targetFaculty))
        {
            cout << "Faculty ID not found. Please enter a valid faculty ID :" << endl;
            cin >> temp;
            facultyID = validateInt(temp);
            targetFaculty->setID(facultyID);
        } 
        targetFaculty = facultyTree.find(targetFaculty);
        targetStudent = studentTree.find(targetStudent);
        targetStudent->setAdvisorID(facultyID);
        targetFaculty->addAdvisee(studentID);
    } else {
        facultyEntry = facultyTree.getRandomNode();
        Faculty *newFaculty = new Faculty();
        newFaculty->setID(facultyEntry.getID());
        targetFaculty = facultyTree.find(newFaculty);
        targetStudent = studentTree.find(targetStudent);
        targetStudent->setAdvisorID(facultyEntry.getID());
        targetFaculty->addAdvisee(studentID);
    }
}

void DatabaseManager::rollback() {
    int action = undoActionStack.pop();
    if (action == 0) {  //Undo add Student
        Student undoStudent = undoStudentStack.pop();
        Student *studentToDelete = new Student();
        studentToDelete->setID(undoStudent.getID());
        studentToDelete = studentTree.find(studentToDelete);  
        studentTree.remove(studentToDelete);
        cout << "Undo add student complete" << endl;
    } else if (action == 1) {   //Undo add Faculty
        Faculty undoFaculty = undoFacultyStack.pop();
        Faculty *facultyToDelete = new Faculty();
        facultyToDelete->setID(undoFaculty.getID());
        facultyToDelete = facultyTree.find(facultyToDelete);  
        facultyTree.remove(facultyToDelete);
        cout << "Undo add faculty complete" << endl;
    } else if (action == 2) {   //Undo delete Student
        Student undoStudent = undoStudentStack.pop();
        Student *studentToDelete = new Student();
        studentToDelete->setID(undoStudent.getID());
        studentToDelete->setName(undoStudent.getName());
        studentToDelete->setLevel(undoStudent.getLevel());
        studentToDelete->setMajor(undoStudent.getMajor());
        studentToDelete->setGPA(undoStudent.getGPA());
        studentToDelete->setAdvisorID(undoStudent.getAdvisorID());
        studentTree.insert(studentToDelete);
        cout << "Undo delete student complete" << endl;
    } else if (action == 3) {   //Undo delete Faculty
        Faculty undoFaculty = undoFacultyStack.pop();
        Faculty *facultyToDelete = new Faculty();
        facultyToDelete->setID(undoFaculty.getID());
        facultyToDelete->setName(undoFaculty.getName());
        facultyToDelete->setDepartment(undoFaculty.getDepartment());
        facultyToDelete->setLevel(undoFaculty.getLevel());
        Student *advisee = new Student();
        for (int i = 0; i < undoFaculty.getNumberOfAdvisee(); ++i) {
            advisee->setID(undoFaculty.getAdvisee(i));
            advisee = studentTree.find(advisee);
            advisee->setAdvisorID(undoFaculty.getID());
        }
        
        facultyTree.insert(facultyToDelete);
        cout << "Undo delete faculty complete" << endl;
    }
}

void DatabaseManager::printStudentTree() {
    if (studentTree.getsize() == 0) {
        cout << "Cannot print empty Tree" << endl;
    } else {
        studentTree.printAsTree(printStudentName);
    }
    
}

void DatabaseManager::printFacultyTree() {
    if (facultyTree.getsize() == 0) {
        cout << "Cannot print empty Tree" << endl;
    } else {
        facultyTree.printAsTree(printFacultyName);
    }
}

void DatabaseManager::clearStudentTree() {
    studentTree.clear();
    cout << "Student tree has been cleared" << endl;
}

void DatabaseManager::clearFacultyTree() {
    facultyTree.clear();
    cout << "Faculty tree has been cleared" << endl;
}
int DatabaseManager::validateInt(string temp)
{
    while (checkInt(temp))
    {
        cout << "Invalid Input! Please enter again: " << endl;
        cin >> temp;
    }
    return stoi(temp);
}

bool DatabaseManager::checkInt(string temp)
{
    bool check = false;
    for (int i = 0; i < temp.length() && !check; ++i)
    {
        if (!isdigit(temp[i]))
        {
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

void DatabaseManager::printFacultyHeader()
{
    cout << "========== ========================= =========== ========================= ==================" << endl;
    cout << " ID        Name                      Level       Department                Advisee IDs" << endl;
    cout << "========== ========================= =========== ========================= ==================" << endl;
}

void printStudentInfo(Student *student)
{
    cout << left << setw(10) << student->getID() << " "
         << setw(25) << student->getName() << " "
         << setw(11) << student->getLevel() << " "
         << setw(25) << student->getMajor() << " "
         << setw(5) << student->getGPA() << " "
         << setw(12) << student->getAdvisorID() << endl;
}

void printStudentName(Student *student) {
    cout << student->getID() << ": " << student->getName() << endl;
}

void writeStudentFile(Student *student, ofstream outFile) {
    outFile << student->getID() << "," 
            << student->getName() << ","
            << student->getLevel() << ","
            << student->getMajor() << ","
            << student->getGPA() << ","
            << student->getAdvisorID() << endl;
}

void printFacultyInfo(Faculty *faculty)
{
    cout << left << setw(10) << faculty->getID() << " "
         << setw(25) << faculty->getName() << " "
         << setw(11) << faculty->getLevel() << " "
         << setw(25) << faculty->getDepartment() << " "
         << setw(18);
    faculty->printAdvisee();
    cout << endl;
}

void printFacultyName(Faculty *faculty) {
    cout << faculty->getID() << ": " << faculty->getName() << endl;
}

void writeFacultyFile(Faculty *faculty, ofstream outFile) {
    outFile << faculty->getID() << ","
            << faculty->getName() << ","
            << faculty->getDepartment() << ","
            << faculty->getAdviseeWrite() << endl;
}

void DatabaseManager::menu()
{
    cout << "\n===== Main Menu ======" << endl;
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
    cout << "14 - Print Student information as a tree" << endl;
    cout << "15 - Print Faculty information as a tree" << endl;
    cout << "16 – Delete entire Student Table" << endl;
    cout << "17 – Delete entire Faculty Table" << endl;
    cout << "18 – Exit" << endl;
}
