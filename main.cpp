#include <iostream>
#include <string>
#include <iomanip>
#include "Database.h"
using namespace std;

// ============================================================
// Forward declarations for menu functions
// ============================================================
void mainMenu();
void studentMenu(Database& db);
void courseMenu(Database& db);
void enrollmentMenu(Database& db);
void statisticsMenu(Database& db);

void addStudentFlow(Database& db);
void removeStudentFlow(Database& db);
void searchStudentFlow(Database& db);
void updateStudentFlow(Database& db);

void addCourseFlow(Database& db);
void removeCourseFlow(Database& db);

void enrollFlow(Database& db);
void dropFlow(Database& db);

// ============================================================
// MAIN
// ============================================================
int main() {
    cout << "\n";
    cout << "************************************************************\n";
    cout << "*       STUDENT MANAGEMENT SYSTEM                         *\n";
    cout << "*       Object-Oriented Design & Programming (OODP)       *\n";
    cout << "************************************************************\n\n";

    Database db; // Create the database object

    // ---- Pre-load some sample data ----
    db.addCourse(Course("CS101", "Introduction to Programming", "Dr. Kumar", 4, 60));
    db.addCourse(Course("MA201", "Engineering Mathematics", "Dr. Priya", 4, 80));
    db.addCourse(Course("EC301", "Digital Electronics", "Prof. Rajan", 3, 50));
    db.addCourse(Course("ME401", "Thermodynamics", "Dr. Sharma", 3, 45));

    db.addStudent(Student(1001, "Arjun Mehta", "arjun@college.edu", "CSE", 3, 8.9f));
    db.addStudent(Student(1002, "Priya Nair", "priya@college.edu", "ECE", 2, 9.2f));
    db.addStudent(Student(1003, "Rohan Das", "rohan@college.edu", "MECH", 4, 7.5f));
    db.addStudent(Student(1004, "Sneha Reddy", "sneha@college.edu", "CSE", 3, 8.1f));
    db.addStudent(Student(1005, "Karthik Raja", "karthik@college.edu", "ECE", 1, 6.8f));

    db.enrollStudentInCourse(1001, "CS101");
    db.enrollStudentInCourse(1001, "MA201");
    db.enrollStudentInCourse(1002, "EC301");
    db.enrollStudentInCourse(1003, "ME401");

    // ---- Main program loop ----
    int choice;
    do {
        cout << "\n============================================================\n";
        cout << "  MAIN MENU\n";
        cout << "============================================================\n";
        cout << "  1. Student Management\n";
        cout << "  2. Course Management\n";
        cout << "  3. Enrollment Management\n";
        cout << "  4. Statistics & Reports\n";
        cout << "  0. Exit\n";
        cout << "------------------------------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: studentMenu(db);    break;
            case 2: courseMenu(db);     break;
            case 3: enrollmentMenu(db); break;
            case 4: statisticsMenu(db); break;
            case 0: cout << "\nThank you for using SMS! Goodbye.\n\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}

// ============================================================
// STUDENT MENU
// ============================================================
void studentMenu(Database& db) {
    int ch;
    do {
        cout << "\n--- STUDENT MANAGEMENT ---\n";
        cout << "1. Add Student\n";
        cout << "2. Remove Student\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Display All Students\n";
        cout << "6. Display by Department\n";
        cout << "7. Sort Students\n";
        cout << "0. Back\n";
        cout << "Choice: ";
        cin >> ch;

        switch (ch) {
        case 1: addStudentFlow(db); break;
        case 2: removeStudentFlow(db); break;
        case 3: searchStudentFlow(db); break;
        case 4: updateStudentFlow(db); break;
        case 5: db.displayAllStudents(); break;
        case 6: {
            string dept;
            cout << "Enter department: ";
            cin >> dept;
            vector<Student> list = db.getStudentsByDepartment(dept);
            if (list.empty())
                cout << "No students in " << dept << "\n";
            else
                for (Student& s : list) s.displayStudentInfo();
            break;
        }
        case 7: {
            cout << "Sort by: 1.CGPA  2.Name  3.ID\nChoice: ";
            int s; cin >> s;
            if (s == 1) db.sortStudentsByCGPA();
            else if (s == 2) db.sortStudentsByName();
            else if (s == 3) db.sortStudentsByID();
            db.displayAllStudents();
            break;
        }
        case 0: break;
        default: cout << "Invalid.\n";
        }
    } while (ch != 0);
}

// ============================================================
// COURSE MENU
// ============================================================
void courseMenu(Database& db) {
    int ch;
    do {
        cout << "\n--- COURSE MANAGEMENT ---\n";
        cout << "1. Add Course\n";
        cout << "2. Remove Course\n";
        cout << "3. Display All Courses\n";
        cout << "4. Search Course\n";
        cout << "5. View Students in a Course\n";
        cout << "0. Back\n";
        cout << "Choice: ";
        cin >> ch;

        switch (ch) {
        case 1: addCourseFlow(db); break;
        case 2: removeCourseFlow(db); break;
        case 3: db.displayAllCourses(); break;
        case 4: {
            string code;
            cout << "Enter course code: ";
            cin >> code;
            Course* c = db.searchCourseByCode(code);
            if (c) c->displayCourseInfo();
            else cout << "Course not found.\n";
            break;
        }
        case 5: {
            string code;
            cout << "Enter course code: ";
            cin >> code;
            db.displayCourseStudents(code);
            break;
        }
        case 0: break;
        default: cout << "Invalid.\n";
        }
    } while (ch != 0);
}

// ============================================================
// ENROLLMENT MENU
// ============================================================
void enrollmentMenu(Database& db) {
    int ch;
    do {
        cout << "\n--- ENROLLMENT MANAGEMENT ---\n";
        cout << "1. Enroll Student in Course\n";
        cout << "2. Drop Student from Course\n";
        cout << "3. View Student's Courses\n";
        cout << "0. Back\n";
        cout << "Choice: ";
        cin >> ch;

        switch (ch) {
        case 1: enrollFlow(db); break;
        case 2: dropFlow(db); break;
        case 3: {
            int id;
            cout << "Enter Student ID: ";
            cin >> id;
            db.displayStudentCourses(id);
            break;
        }
        case 0: break;
        default: cout << "Invalid.\n";
        }
    } while (ch != 0);
}

// ============================================================
// STATISTICS MENU
// ============================================================
void statisticsMenu(Database& db) {
    int ch;
    do {
        cout << "\n--- STATISTICS & REPORTS ---\n";
        cout << "1. Average CGPA\n";
        cout << "2. Total Students\n";
        cout << "3. Top 3 Students\n";
        cout << "4. Total Students Ever Added (Static)\n";
        cout << "0. Back\n";
        cout << "Choice: ";
        cin >> ch;

        switch (ch) {
        case 1:
            cout << "Average CGPA: " << fixed << setprecision(2)
                 << db.getAverageCGPA() << "\n";
            break;
        case 2:
            cout << "Total students in system: " << db.getTotalStudents() << "\n";
            break;
        case 3:
            db.displayTopStudents(3);
            break;
        case 4:
            cout << "Total students ever added (all-time): "
                 << Database::getTotalStudentsEverAdded() << "\n";
            break;
        case 0: break;
        default: cout << "Invalid.\n";
        }
    } while (ch != 0);
}

// ============================================================
// HELPER FLOWS
// ============================================================
void addStudentFlow(Database& db) {
    int id, sem;
    float cgpa;
    string name, email, dept;
    cout << "\n-- Add New Student --\n";
    cout << "Student ID: ";     cin >> id;
    cin.ignore();
    cout << "Name: ";           getline(cin, name);
    cout << "Email: ";          cin >> email;
    cout << "Department: ";     cin >> dept;
    cout << "Semester (1-8): "; cin >> sem;
    cout << "CGPA (0-10): ";    cin >> cgpa;

    Student s(id, name, email, dept, sem, cgpa);
    db.addStudent(s);
}

void removeStudentFlow(Database& db) {
    int id;
    cout << "Enter Student ID to remove: ";
    cin >> id;
    db.removeStudent(id);
}

void searchStudentFlow(Database& db) {
    cout << "Search by: 1.ID  2.Name\nChoice: ";
    int ch; cin >> ch;
    if (ch == 1) {
        int id; cout << "Enter ID: "; cin >> id;
        Student* s = db.searchStudentByID(id);
        if (s) s->displayStudentInfo();
        else cout << "Not found.\n";
    } else {
        string name; cout << "Enter name: ";
        cin.ignore(); getline(cin, name);
        vector<Student> res = db.searchStudentByName(name);
        if (res.empty()) cout << "No match found.\n";
        else for (Student& s : res) cout << s << "\n";
    }
}

void updateStudentFlow(Database& db) {
    int id; cout << "Enter Student ID: "; cin >> id;
    cout << "Update: 1.CGPA  2.Semester\nChoice: ";
    int ch; cin >> ch;
    if (ch == 1) {
        float cgpa; cout << "New CGPA: "; cin >> cgpa;
        db.updateStudentCGPA(id, cgpa);
    } else {
        int sem; cout << "New Semester: "; cin >> sem;
        db.updateStudentSemester(id, sem);
    }
}

void addCourseFlow(Database& db) {
    string code, name, instr;
    int cred, seats;
    cout << "\n-- Add New Course --\n";
    cout << "Course Code: ";  cin >> code;
    cin.ignore();
    cout << "Course Name: ";  getline(cin, name);
    cout << "Instructor: ";   getline(cin, instr);
    cout << "Credits: ";      cin >> cred;
    cout << "Max Seats: ";    cin >> seats;

    Course c(code, name, instr, cred, seats);
    db.addCourse(c);
}

void removeCourseFlow(Database& db) {
    string code;
    cout << "Enter course code to remove: ";
    cin >> code;
    db.removeCourse(code);
}

void enrollFlow(Database& db) {
    int id; string code;
    cout << "Student ID: "; cin >> id;
    cout << "Course Code: "; cin >> code;
    db.enrollStudentInCourse(id, code);
}

void dropFlow(Database& db) {
    int id; string code;
    cout << "Student ID: "; cin >> id;
    cout << "Course Code: "; cin >> code;
    db.dropStudentFromCourse(id, code);
}
