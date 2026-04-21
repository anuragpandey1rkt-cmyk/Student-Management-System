# Student Management System
### Object-Oriented Design & Programming (OODP) Project

---

## 📌 Project Overview
A console-based Student Management System built in C++ that demonstrates core OOP concepts including Classes, Objects, Encapsulation, Constructors, Destructors, Operator Overloading, Static Members, and Composition.

---

## 🏗️ OOP Concepts Used

| Concept | Where Used |
|---|---|
| Classes & Objects | `Student`, `Course`, `Database` |
| Encapsulation | Private data + public getters/setters |
| Constructors (Default, Parameterized, Copy) | `Student`, `Course` |
| Destructor | `Student`, `Course`, `Database` |
| Static Members & Methods | `Database::totalStudentsAdded` |
| Operator Overloading | `==` and `<<` in Student & Course |
| Composition (has-a) | `Database` contains `Student` and `Course` |
| Vectors (STL) | Storing students and courses |
| Lambda Functions | Sorting with `std::sort` |

---

## 📁 File Structure

```
StudentManagementSystem/
├── main.cpp        → Entry point, menus, user interaction
├── Student.h/.cpp  → Student class
├── Course.h/.cpp   → Course class
├── Database.h/.cpp → Central database manager
└── README.md
```

---

## ⚙️ How to Compile & Run

```bash
g++ main.cpp Student.cpp Course.cpp Database.cpp -o sms
./sms
```

---

## 🎯 Features
- Add, remove, search, and update students
- Add and remove courses
- Enroll / drop students from courses
- View students by department
- Sort by CGPA, Name, or ID
- Statistics: average CGPA, top students
- Static counter for all-time student additions
