#include "Course.h"
#include <algorithm>
#include <iomanip>

// Default Constructor
Course::Course() {
    courseCode = "N/A";
    courseName = "Unknown";
    instructor = "TBA";
    credits = 0;
    maxSeats = 30;
    enrolledCount = 0;
}

// Parameterized Constructor
Course::Course(string code, string name, string instr, int cred, int seats) {
    this->courseCode = code;
    this->courseName = name;
    this->instructor = instr;
    this->credits = cred;
    this->maxSeats = seats;
    this->enrolledCount = 0;
    cout << "[Course] Created: " << code << " - " << name << "\n";
}

// Destructor
Course::~Course() {
    cout << "[Course] Destroyed: " << courseCode << "\n";
}

// Setters
void Course::setCourseCode(string code)     { courseCode = code; }
void Course::setCourseName(string name)     { courseName = name; }
void Course::setInstructor(string instr)    { instructor = instr; }
void Course::setCredits(int cred)           { credits = cred; }
void Course::setMaxSeats(int seats)         { maxSeats = seats; }

// Getters
string Course::getCourseCode() const        { return courseCode; }
string Course::getCourseName() const        { return courseName; }
string Course::getInstructor() const        { return instructor; }
int Course::getCredits() const              { return credits; }
int Course::getMaxSeats() const             { return maxSeats; }
int Course::getEnrolledCount() const        { return enrolledCount; }
vector<int> Course::getEnrolledStudentIDs() const { return enrolledStudentIDs; }

// Add Student
bool Course::addStudent(int studentID) {
    if (isFull()) {
        cout << "Course " << courseCode << " is full!\n";
        return false;
    }
    if (hasStudent(studentID)) {
        cout << "Student already in course.\n";
        return false;
    }
    enrolledStudentIDs.push_back(studentID);
    enrolledCount++;
    return true;
}

// Remove Student
bool Course::removeStudent(int studentID) {
    auto it = find(enrolledStudentIDs.begin(), enrolledStudentIDs.end(), studentID);
    if (it != enrolledStudentIDs.end()) {
        enrolledStudentIDs.erase(it);
        enrolledCount--;
        return true;
    }
    cout << "Student ID " << studentID << " not found in course.\n";
    return false;
}

bool Course::isFull() const {
    return enrolledCount >= maxSeats;
}

bool Course::hasStudent(int studentID) const {
    return find(enrolledStudentIDs.begin(), enrolledStudentIDs.end(), studentID)
           != enrolledStudentIDs.end();
}

void Course::displayCourseInfo() const {
    cout << "\n========================================\n";
    cout << "  COURSE INFORMATION\n";
    cout << "========================================\n";
    cout << left << setw(15) << "Code:"       << courseCode << "\n";
    cout << left << setw(15) << "Name:"       << courseName << "\n";
    cout << left << setw(15) << "Instructor:" << instructor << "\n";
    cout << left << setw(15) << "Credits:"    << credits << "\n";
    cout << left << setw(15) << "Seats:"      << enrolledCount << "/" << maxSeats << "\n";
    cout << "========================================\n";
}

bool Course::operator==(const Course& other) const {
    return this->courseCode == other.courseCode;
}

ostream& operator<<(ostream& os, const Course& c) {
    os << "[" << c.courseCode << "] " << c.courseName
       << " | " << c.instructor
       << " | Credits: " << c.credits
       << " | Seats: " << c.enrolledCount << "/" << c.maxSeats;
    return os;
}
