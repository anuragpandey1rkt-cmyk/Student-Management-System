#include "Database.h"
#include <algorithm>
#include <iomanip>

// ============================================================
// Static member initialization (outside class)
// ============================================================
int Database::totalStudentsAdded = 0;

// ============================================================
// Constructor & Destructor
// ============================================================
Database::Database() {
    cout << "[Database] System initialized.\n";
}

Database::~Database() {
    cout << "[Database] System shut down. Total students ever added: "
         << totalStudentsAdded << "\n";
}

// ============================================================
// Private Helpers
// ============================================================
int Database::findStudentIndex(int id) const {
    for (int i = 0; i < (int)students.size(); i++) {
        if (students[i].getStudentID() == id)
            return i;
    }
    return -1; // Not found
}

int Database::findCourseIndex(string code) const {
    for (int i = 0; i < (int)courses.size(); i++) {
        if (courses[i].getCourseCode() == code)
            return i;
    }
    return -1;
}

// ============================================================
// STUDENT OPERATIONS
// ============================================================

bool Database::addStudent(Student s) {
    if (findStudentIndex(s.getStudentID()) != -1) {
        cout << "Error: Student with ID " << s.getStudentID() << " already exists.\n";
        return false;
    }
    students.push_back(s);
    totalStudentsAdded++; // Increment static counter
    cout << "Student " << s.getName() << " added successfully.\n";
    return true;
}

bool Database::removeStudent(int id) {
    int idx = findStudentIndex(id);
    if (idx == -1) {
        cout << "Error: Student ID " << id << " not found.\n";
        return false;
    }
    cout << "Student " << students[idx].getName() << " removed.\n";
    students.erase(students.begin() + idx);
    return true;
}

bool Database::updateStudentCGPA(int id, float newCGPA) {
    int idx = findStudentIndex(id);
    if (idx == -1) {
        cout << "Student not found.\n";
        return false;
    }
    students[idx].setCGPA(newCGPA);
    cout << "CGPA updated for " << students[idx].getName() << "\n";
    return true;
}

bool Database::updateStudentSemester(int id, int newSem) {
    int idx = findStudentIndex(id);
    if (idx == -1) {
        cout << "Student not found.\n";
        return false;
    }
    students[idx].setSemester(newSem);
    cout << "Semester updated for " << students[idx].getName() << "\n";
    return true;
}

Student* Database::searchStudentByID(int id) {
    int idx = findStudentIndex(id);
    if (idx == -1) return nullptr;
    return &students[idx];
}

vector<Student> Database::searchStudentByName(string name) const {
    vector<Student> result;
    for (const Student& s : students) {
        // Case-insensitive partial match
        string sName = s.getName();
        string qName = name;
        transform(sName.begin(), sName.end(), sName.begin(), ::tolower);
        transform(qName.begin(), qName.end(), qName.begin(), ::tolower);
        if (sName.find(qName) != string::npos)
            result.push_back(s);
    }
    return result;
}

vector<Student> Database::getStudentsByDepartment(string dept) const {
    vector<Student> result;
    for (const Student& s : students) {
        if (s.getDepartment() == dept)
            result.push_back(s);
    }
    return result;
}

void Database::displayAllStudents() const {
    if (students.empty()) {
        cout << "No students in the system.\n";
        return;
    }
    cout << "\n============================================================\n";
    cout << "  ALL STUDENTS (" << students.size() << " total)\n";
    cout << "============================================================\n";
    cout << left << setw(8) << "ID"
         << setw(20) << "Name"
         << setw(15) << "Department"
         << setw(5) << "Sem"
         << setw(8) << "CGPA" << "\n";
    cout << "------------------------------------------------------------\n";
    for (const Student& s : students) {
        cout << left << setw(8) << s.getStudentID()
             << setw(20) << s.getName()
             << setw(15) << s.getDepartment()
             << setw(5) << s.getSemester()
             << setw(8) << fixed << setprecision(2) << s.getCGPA() << "\n";
    }
    cout << "============================================================\n";
}

void Database::displayTopStudents(int n) const {
    vector<Student> sorted = students;
    sort(sorted.begin(), sorted.end(), [](const Student& a, const Student& b) {
        return a.getCGPA() > b.getCGPA();
    });

    cout << "\n  TOP " << n << " STUDENTS BY CGPA:\n";
    cout << "-----------------------------\n";
    for (int i = 0; i < n && i < (int)sorted.size(); i++) {
        cout << (i + 1) << ". " << sorted[i].getName()
             << " - " << fixed << setprecision(2) << sorted[i].getCGPA() << "\n";
    }
}

// ============================================================
// COURSE OPERATIONS
// ============================================================

bool Database::addCourse(Course c) {
    if (findCourseIndex(c.getCourseCode()) != -1) {
        cout << "Course " << c.getCourseCode() << " already exists.\n";
        return false;
    }
    courses.push_back(c);
    cout << "Course " << c.getCourseCode() << " added.\n";
    return true;
}

bool Database::removeCourse(string code) {
    int idx = findCourseIndex(code);
    if (idx == -1) {
        cout << "Course not found.\n";
        return false;
    }
    courses.erase(courses.begin() + idx);
    cout << "Course " << code << " removed.\n";
    return true;
}

Course* Database::searchCourseByCode(string code) {
    int idx = findCourseIndex(code);
    if (idx == -1) return nullptr;
    return &courses[idx];
}

void Database::displayAllCourses() const {
    if (courses.empty()) {
        cout << "No courses available.\n";
        return;
    }
    cout << "\n============================================================\n";
    cout << "  ALL COURSES\n";
    cout << "============================================================\n";
    for (const Course& c : courses)
        cout << c << "\n";
    cout << "============================================================\n";
}

// ============================================================
// ENROLLMENT OPERATIONS
// ============================================================

bool Database::enrollStudentInCourse(int studentID, string courseCode) {
    int si = findStudentIndex(studentID);
    int ci = findCourseIndex(courseCode);

    if (si == -1) { cout << "Student not found.\n"; return false; }
    if (ci == -1) { cout << "Course not found.\n"; return false; }

    if (courses[ci].addStudent(studentID)) {
        students[si].enrollCourse(courseCode);
        cout << "Enrollment successful!\n";
        return true;
    }
    return false;
}

bool Database::dropStudentFromCourse(int studentID, string courseCode) {
    int si = findStudentIndex(studentID);
    int ci = findCourseIndex(courseCode);

    if (si == -1) { cout << "Student not found.\n"; return false; }
    if (ci == -1) { cout << "Course not found.\n"; return false; }

    courses[ci].removeStudent(studentID);
    students[si].dropCourse(courseCode);
    cout << "Course dropped successfully.\n";
    return true;
}

void Database::displayStudentCourses(int studentID) const {
    int idx = findStudentIndex(studentID);
    if (idx == -1) { cout << "Student not found.\n"; return; }
    students[idx].displayCourses();
}

void Database::displayCourseStudents(string courseCode) const {
    int idx = findCourseIndex(courseCode);
    if (idx == -1) { cout << "Course not found.\n"; return; }

    cout << "\nStudents in " << courseCode << ":\n";
    vector<int> ids = courses[idx].getEnrolledStudentIDs();
    if (ids.empty()) { cout << "  No students enrolled.\n"; return; }
    for (int id : ids) {
        int si = findStudentIndex(id);
        if (si != -1)
            cout << "  " << students[si] << "\n";
    }
}

// ============================================================
// STATISTICS
// ============================================================

float Database::getAverageCGPA() const {
    if (students.empty()) return 0.0f;
    float sum = 0;
    for (const Student& s : students)
        sum += s.getCGPA();
    return sum / students.size();
}

int Database::getTotalStudents() const {
    return students.size();
}

int Database::getTotalStudentsEverAdded() {
    return totalStudentsAdded;
}

// ============================================================
// SORTING
// ============================================================

void Database::sortStudentsByCGPA() {
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.getCGPA() > b.getCGPA(); // Descending
    });
    cout << "Students sorted by CGPA (highest first).\n";
}

void Database::sortStudentsByName() {
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.getName() < b.getName();
    });
    cout << "Students sorted alphabetically by name.\n";
}

void Database::sortStudentsByID() {
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.getStudentID() < b.getStudentID();
    });
    cout << "Students sorted by ID.\n";
}
