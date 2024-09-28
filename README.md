# Library Management System  

## Description  
The Library Management System is a console-based application designed to automate essential library functions. The system allows library staff to efficiently manage books, patrons, and the processes of borrowing and returning books. It features a dynamic data structure implemented using linked lists, providing an optimal environment for managing the library's resources.  

## Features  

### 1. Book Management  
- **Add New Books**: Register new books with unique book IDs, titles, authors, genres, publication years, and available copies.  
- **Search for Books**: Search functionality based on title, author, genre, book ID, and availability status.  
- **Update Book Information**: Edit details of existing books, such as title, author, and available copies.  
- **Delete Books**: Remove books from the collection, ensuring no active borrow records exist for the specified book.  

### 2. Patron Management  
- **Register New Patrons**: Add new patrons with unique patron IDs, names, contact details, addresses, and library card statuses.  
- **Search for Patrons**: Search patrons by patron ID, name, and email.  
- **Update Patron Information**: Edit patron details, including address and contact information.  
- **Delete Patron Records**: Remove patrons from the system only if they have returned all borrowed books.  

### 3. Borrowing and Returning  
- **Borrow Books**: Allow patrons to borrow up to a specified limit (e.g., 3 books) only if the book is available. Track borrowing records with patron ID, book ID, borrowing date, and due date.  
- **Return Books**: Facilitate book returns, updating availability and removing borrow records.  
- **Track Overdue Books**: Identify and report overdue books, enabling staff to view a list of overdue items and their borrowers.  

### 4. Reporting  
- **Generate Reports**: Create console-readable reports for:  
  - Books currently borrowed  
  - Books available in the library  
  - A list of overdue books and their borrowers  
  - Borrowing history of individual patrons  

## Getting Started  

### Prerequisites  
- C++ Development Kit (gcc).  
- IDE (Visual Studio, Visual Studio Code, Dev etc.) or terminal for running the application  

### Installation  
1. Clone this repository using the command:  
   ```bash  
   git clone https://github.com/AbdulAHAD968/library-management-system.git
