#ifndef DATABASE_H
#define DATABASE_H

#include "Student.h"
#include "Course.h"
#include <vector>

// ============================================================
// CLASS: Database
// Purpose: Central manager for Students and Courses
// Demonstrates: Composition (has-a relationship), vectors,
//               searching, sorting, static members
// ============================================================

class Database {
private:
    vector<Student> students;
    vector<Course> courses;
    static int totalStudentsAdded; // Static member - shared across all objects

    // Private helper: find index
    int findStudentIndex(int id) const;
    int findCourseIndex(string code) const;

public:
    Database();
    ~Database();

    // ---- Student Operations ----
    bool addStudent(Student s);
    bool removeStudent(int id);
    bool updateStudentCGPA(int id, float newCGPA);
    bool updateStudentSemester(int id, int newSem);
    Student* searchStudentByID(int id);
    vector<Student> searchStudentByName(string name) const;
    vector<Student> getStudentsByDepartment(string dept) const;
    void displayAllStudents() const;
    void displayTopStudents(int n) const; // Top n by CGPA

    // ---- Course Operations ----
    bool addCourse(Course c);
    bool removeCourse(string code);
    Course* searchCourseByCode(string code);
    void displayAllCourses() const;

    // ---- Enrollment Operations ----
    bool enrollStudentInCourse(int studentID, string courseCode);
    bool dropStudentFromCourse(int studentID, string courseCode);
    void displayStudentCourses(int studentID) const;
    void displayCourseStudents(string courseCode) const;

    // ---- Statistics ----
    float getAverageCGPA() const;
    int getTotalStudents() const;
    static int getTotalStudentsEverAdded(); // Static method

    // ---- Sorting ----
    void sortStudentsByCGPA();        // Descending
    void sortStudentsByName();        // Alphabetical
    void sortStudentsByID();          // Ascending
};

#endif
