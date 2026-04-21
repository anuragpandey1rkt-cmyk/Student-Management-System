#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ============================================================
// CLASS: Course
// Purpose: Represents an academic course
// Demonstrates: Another class, Encapsulation, Constructors
// ============================================================

class Course {
private:
    string courseCode;
    string courseName;
    string instructor;
    int credits;
    int maxSeats;
    int enrolledCount;
    vector<int> enrolledStudentIDs;

public:
    // Constructors
    Course();
    Course(string code, string name, string instructor, int credits, int maxSeats);
    ~Course();

    // Setters
    void setCourseCode(string code);
    void setCourseName(string name);
    void setInstructor(string instructor);
    void setCredits(int credits);
    void setMaxSeats(int seats);

    // Getters
    string getCourseCode() const;
    string getCourseName() const;
    string getInstructor() const;
    int getCredits() const;
    int getMaxSeats() const;
    int getEnrolledCount() const;
    vector<int> getEnrolledStudentIDs() const;

    // Functionality
    bool addStudent(int studentID);
    bool removeStudent(int studentID);
    bool isFull() const;
    bool hasStudent(int studentID) const;

    // Display
    void displayCourseInfo() const;

    // Operator overloading
    bool operator==(const Course& other) const;
    friend ostream& operator<<(ostream& os, const Course& c);
};

#endif
