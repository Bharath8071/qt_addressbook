# Qt Address Book Application

## Table of Contents

* [Overview](#overview)
* [Application Features](#application-features)
* [Technologies Used](#technologies-used)
* [Project Structure](#project-structure)
* [Implementation Details](#implementation-details)
* [Button Functionalities](#button-functionalities)
* [Input Validation](#input-validation)
* [Error Handling](#error-handling)
* [Build Instructions](#build-instructions)
* [Conclusion](#conclusion)


## Overview

The **Qt Address Book Application** is a desktop application developed using **Qt Widgets and C++**.
The application allows users to manage contacts through a graphical user interface.

Each contact contains the following fields:

* Name
* Mobile Number
* Email Address
* Birthday

The application supports **CRUD operations** (Create, Read, Update, Delete) and stores the data using an **SQLite database**.

This project demonstrates the use of:

* Qt Widgets for GUI development
* SQLite database integration
* C++ object-oriented programming
* Input validation
* Modular software design

---

# Application Features

The application provides the following functionalities:

### 1. View Contacts

When the application starts, all contacts stored in the database are loaded and displayed in a table.

### 2. Add Contact

Users can add a new contact using the **Add button**.

### 3. Edit Contact

Users can modify existing contact details using the **Edit button**.

### 4. Delete Contact

Users can remove a selected contact using the **Delete button**.

### 5. Data Validation

The application validates user inputs before storing them in the database.

---

# Technologies Used

| Technology | Purpose                   |
| ---------- | ------------------------- |
| C++        | Core programming language |
| Qt Widgets | Graphical User Interface  |
| SQLite     | Local database storage    |
| qmake      | Build system              |
| Git        | Version control           |

---

# Project Structure

```
qt-addressbook
│
├── main.cpp
├── mainwindow.cpp
├── mainwindow.h
├── mainwindow.ui
│
├── addcontactdialog.cpp
├── addcontactdialog.h
├── addcontactdialog.ui
│
├── database.cpp
├── database.h
│
├── contacts.db
├── qt-addressbook.pro
└── README.md
```

---

# Implementation Details

## Database Implementation

The application uses **SQLite** as the database engine.

When the application starts, it initializes the database and creates the contacts table if it does not exist.

Database schema:

```
CREATE TABLE contacts (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT,
    mobile TEXT,
    email TEXT,
    birthday TEXT
);
```

The `id` field is used as the **primary key** to uniquely identify each contact.

---

# UI Implementation

The graphical interface is built using **Qt Designer**.

Main components used:

| Widget       | Purpose                        |
| ------------ | ------------------------------ |
| QTableWidget | Displays contacts              |
| QPushButton  | Add, Edit, Delete operations   |
| QLineEdit    | User text input                |
| QDateEdit    | Date selection for birthday    |
| QMessageBox  | Error and confirmation dialogs |

The table automatically resizes columns and disables direct cell editing to ensure controlled data modification.

---

# Button Functionalities

## Add Button

Function:

* Opens the **Add Contact Dialog**
* User enters contact details
* Data is validated
* Contact is inserted into the SQLite database
* Table refreshes automatically

Database Query:

```
INSERT INTO contacts (name, mobile, email, birthday)
VALUES (?, ?, ?, ?);
```

---

## Edit Button

Function:

* Retrieves the selected contact
* Opens dialog with existing contact data
* User modifies the fields
* Updated data is saved to the database

Database Query:

```
UPDATE contacts
SET name=?, mobile=?, email=?, birthday=?
WHERE id=?;
```

---

## Delete Button

Function:

* Retrieves selected contact ID
* Displays confirmation dialog
* Deletes the contact from the database

Database Query:

```
DELETE FROM contacts
WHERE id=?;
```

Using the **primary key ID** ensures that only the selected record is removed.

---

# Input Validation

The application validates user inputs before saving the data.

## Name Validation

Rule:

```
Name cannot be empty
```

If empty:

```
Error: Name cannot be empty
```

---

## Mobile Validation

Rule:

```
Mobile number must contain digits only
```

Validation uses a **regular expression**.

---

## Email Validation

Rule:

```
Email must follow valid format
```

Example valid email:

```
user@example.com
```

Invalid emails trigger an error message.

---

# Error Handling

The application checks and handles several errors:

| Error Case                      | Handling         |
| ------------------------------- | ---------------- |
| Empty name                      | Warning message  |
| Invalid mobile number           | Validation error |
| Invalid email format            | Validation error |
| No row selected for edit/delete | Warning dialog   |
| Database query failure          | Debug message    |

All critical operations are verified before execution.

---

# Test Cases

## Test Case 1 – Add Contact

Input:

```
Name: Bharath
Mobile: 9876543210
Email: bharath@email.com
Birthday: 2002-05-10
```

Expected Result:

Contact appears in the table and database.

---

## Test Case 2 – Invalid Email

Input:

```
Email: bharath@email
```

Expected Result:

```
Error message: Invalid email address
```

---

## Test Case 3 – Empty Name

Input:

```
Name: (empty)
```

Expected Result:

```
Error message: Name cannot be empty
```

---

## Test Case 4 – Delete Contact

Action:

* Select contact
* Click Delete
* Confirm deletion

Expected Result:

Contact removed from database and table refreshes.

---

## Build Instructions

This project uses the **qmake build system** and can be compiled directly from the command line on **Debian GNU/Linux**.

### 1. Install Required Dependencies

Install the Qt development libraries and compiler tools:

```bash
sudo apt update
sudo apt install qtbase5-dev build-essential
```

These packages provide:

* **Qt libraries** required to build Qt applications
* **qmake**, the Qt build system generator
* **g++ compiler** and standard build tools

---

### 2. Clone the Repository

Download the project from GitHub:

```bash
git clone https://github.com/<your-username>/qt-addressbook.git
```

Move into the project directory:

```bash
cd qt-addressbook
```

---

### 3. Generate the Makefile

Run `qmake` to generate a Makefile from the project configuration file (`.pro`):

```bash
qmake
```

This command reads the file:

```
qt-addressbook.pro
```

and prepares the build configuration.

---

### 4. Compile the Project

Compile the project using:

```bash
make
```

During this step:

* All `.cpp` files are compiled
* Qt libraries are linked
* An executable program is created

After successful compilation, the executable file will appear in the project directory.

---

### 5. Run the Application

Run the program using:

```bash
./qt-addressbook
```

This launches the **Qt Address Book Application**.

When the application starts:

* The SQLite database is initialized
* The `contacts` table is created if it does not already exist
* Stored contacts are loaded and displayed in the table

---

### 6. Clean the Build (Optional)

To remove compiled files and rebuild the project:

```bash
make clean
qmake
make
```

This ensures a fresh build of the application.


# Conclusion

The Qt Address Book application demonstrates a simple yet complete **desktop contact management system**.
It integrates **GUI development, database management, and input validation** using C++ and Qt.

The project follows modular design principles and demonstrates practical implementation of CRUD operations in a desktop environment.
