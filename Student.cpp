#include "Student.h"
#include <algorithm>
#include <iomanip>

// ============================================================
// Default Constructor
// ============================================================
Student::Student() {
    studentID = 0;
    name = "Unknown";
    email = "";
    department = "";
    semester = 1;
    cgpa = 0.0f;
    cout << "[Student] Default object created.\n";
}

// ============================================================
// Parameterized Constructor
// ============================================================
Student::Student(int id, string name, string email,
                 string dept, int sem, float cgpa) {
    this->studentID = id;
    this->name = name;
    this->email = email;
    this->department = dept;
    this->semester = sem;
    this->cgpa = cgpa;
    cout << "[Student] Object created for: " << name << "\n";
}

// ============================================================
// Copy Constructor
// ============================================================
Student::Student(const Student& s) {
    this->studentID = s.studentID;
    this->name = s.name;
    this->email = s.email;
    this->department = s.department;
    this->semester = s.semester;
    this->cgpa = s.cgpa;
    this->enrolledCourses = s.enrolledCourses;
    cout << "[Student] Copy constructor called for: " << name << "\n";
}

// ============================================================
// Destructor
// ============================================================
Student::~Student() {
    cout << "[Student] Object destroyed for ID: " << studentID << "\n";
}

// ============================================================
// Setter Methods
// ============================================================
void Student::setStudentID(int id)       { studentID = id; }
void Student::setName(string n)          { name = n; }
void Student::setEmail(string e)         { email = e; }
void Student::setDepartment(string dept) { department = dept; }
void Student::setSemester(int sem)       { semester = sem; }
void Student::setCGPA(float c) {
    if (c >= 0.0f && c <= 10.0f)
        cgpa = c;
    else
        cout << "Invalid CGPA! Must be between 0 and 10.\n";
}

// ============================================================
// Getter Methods
// ============================================================
int Student::getStudentID() const       { return studentID; }
string Student::getName() const         { return name; }
string Student::getEmail() const        { return email; }
string Student::getDepartment() const   { return department; }
int Student::getSemester() const        { return semester; }
float Student::getCGPA() const          { return cgpa; }
vector<string> Student::getEnrolledCourses() const { return enrolledCourses; }

// ============================================================
// Course Management
// ============================================================
void Student::enrollCourse(string courseCode) {
    if (!isEnrolled(courseCode)) {
        enrolledCourses.push_back(courseCode);
        cout << "Student " << name << " enrolled in course: " << courseCode << "\n";
    } else {
        cout << "Already enrolled in " << courseCode << "\n";
    }
}

void Student::dropCourse(string courseCode) {
    auto it = find(enrolledCourses.begin(), enrolledCourses.end(), courseCode);
    if (it != enrolledCourses.end()) {
        enrolledCourses.erase(it);
        cout << "Course " << courseCode << " dropped for " << name << "\n";
    } else {
        cout << "Course not found in enrollment list.\n";
    }
}

bool Student::isEnrolled(string courseCode) const {
    return find(enrolledCourses.begin(), enrolledCourses.end(), courseCode)
           != enrolledCourses.end();
}

// ============================================================
// Display Methods
// ============================================================
void Student::displayStudentInfo() const {
    cout << "\n========================================\n";
    cout << "  STUDENT INFORMATION\n";
    cout << "========================================\n";
    cout << left << setw(15) << "ID:"         << studentID << "\n";
    cout << left << setw(15) << "Name:"       << name << "\n";
    cout << left << setw(15) << "Email:"      << email << "\n";
    cout << left << setw(15) << "Department:" << department << "\n";
    cout << left << setw(15) << "Semester:"   << semester << "\n";
    cout << left << setw(15) << "CGPA:"       << fixed << setprecision(2) << cgpa << "\n";
    cout << "========================================\n";
}

void Student::displayCourses() const {
    cout << "\nCourses enrolled by " << name << ":\n";
    if (enrolledCourses.empty()) {
        cout << "  No courses enrolled.\n";
    } else {
        for (int i = 0; i < (int)enrolledCourses.size(); i++) {
            cout << "  " << (i + 1) << ". " << enrolledCourses[i] << "\n";
        }
    }
}

// ============================================================
// Operator Overloading
// ============================================================
bool Student::operator==(const Student& other) const {
    return this->studentID == other.studentID;
}

ostream& operator<<(ostream& os, const Student& s) {
    os << "[" << s.studentID << "] " << s.name
       << " | " << s.department
       << " | Sem " << s.semester
       << " | CGPA: " << fixed << setprecision(2) << s.cgpa;
    return os;
}
