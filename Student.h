#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ===========================================================
// CLASS: Student
// Purpose: Represents a student with personal and academic data
// Demonstrates: Classes, Objects, Encapsulation, Constructors,
//               Destructors, Getter/Setter methods
// ===========================================================

class Student {
private:
  // Private data members (Encapsulation)
  int studentID;
  string name;
  string email;
  string department;
  int semester;
  float cgpa;
  vector<string> enrolledCourses; // list of course codes

public:
  // ---- Constructors ----
  Student(); // Default constructor
  Student(int id, string name, string email, string dept, int sem,
          float cgpa);       // Parameterized constructor
  Student(const Student &s); // Copy constructor

  // ---- Destructor ----
  ~Student();

  // ---- Setter Methods ----
  void setStudentID(int id);
  void setName(string name);
  void setEmail(string email);
  void setDepartment(string dept);
  void setSemester(int sem);
  void setCGPA(float cgpa);

  // ---- Getter Methods ----
  int getStudentID() const;
  string getName() const;
  string getEmail() const;
  string getDepartment() const;
  int getSemester() const;
  float getCGPA() const;
  vector<string> getEnrolledCourses() const;

  // ---- Course Management ----
  void enrollCourse(string courseCode);
  void dropCourse(string courseCode);
  bool isEnrolled(string courseCode) const;

  // ---- Display ----
  void displayStudentInfo() const;
  void displayCourses() const;

  // ---- Operator Overloading ----
  bool operator==(const Student &other) const;               // Compare by ID
  friend ostream &operator<<(ostream &os, const Student &s); // Print student
};

#endif
