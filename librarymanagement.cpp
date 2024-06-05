#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Book class
class Book {
public:
    std::string title;
    std::string author;
    std::string isbn;

    Book(std::string t, std::string a, std::string i) : title(t), author(a), isbn(i) {}

    // comparing books by  their ISBN
    bool operator==(const Book& other) const {
        return this->isbn == other.isbn;
    }
};

// User class
class User {
public:
    std::string name;
    std::vector<Book> borrowedBooks;

    //initializing the user
    User(std::string n) : name(n) {}

    // Method to borrow a book
    void borrowBook(Book &book) {
        borrowedBooks.push_back(book);
    }

    // Method to return a borrowed book
    void returnBook(Book &book) {
        borrowedBooks.erase(std::remove(borrowedBooks.begin(), borrowedBooks.end(), book), borrowedBooks.end());
    }
};

// Library class
class Library {
private:
    std::vector<Book> books;
    std::vector<User> users;

public:
    // Adding a book
    void addBook(const Book& book) {
        books.push_back(book);
    }


    //adding a user to the library
    void addUser(const User& user) {
        users.push_back(user);
    }

    //finding a user by name
    User* findUser(const std::string& name) {
        for (auto &user : users) {
            if (user.name == name) {
                return &user;
            }
        }
        return nullptr;
    }

    //searching for a book by title
    Book* searchBookByTitle(const std::string& title) {
        for (auto &book : books) {
            if (book.title == title) {
                return &book;
            }
        }
        return nullptr;
    }

    //searching for a book by author
    Book* searchBookByAuthor(const std::string& author) {
        for (auto &book : books) {
            if (book.author == author) {
                return &book;
            }
        }
        return nullptr;
    }

    //searching for a book by ISBN
    Book* searchBookByISBN(const std::string& isbn) {
        for (auto &book : books) {
            if (book.isbn == isbn) {
                return &book;
            }
        }
        return nullptr;
    }

      // Removing a book by ISBN
    void removeBook(const std::string& isbn) {
        books.erase(std::remove_if(books.begin(), books.end(),
                                   [isbn](const Book &book) { return book.isbn == isbn; }),
                    books.end());
    }
};

// Testing the code
int main() {
    Library lib;

    // Adding books to the library
    lib.addBook(Book("Thinking, Fast and Slow", "Daniel Kahneman", "12345"));
    lib.addBook(Book("Influence: The Psychology of Persuasion", "Robert B. Cialdini", "67890"));
    lib.addBook(Book("Man's Search for Meaning", "Viktor E. Frankl", "11111"));

    // Adding users to the library
    lib.addUser(User("Ian"));
    lib.addUser(User("Kiburio"));

    // Searching for a book by title
    Book* book = lib.searchBookByTitle("Thinking, Fast and Slow");
    if (book) {
        std::cout << "Book found by title: " << book->title << " by " << book->author << std::endl;
    } else {
        std::cout << "Book not found by title." << std::endl;
    }

    // Searching for a book by author
    book = lib.searchBookByAuthor("Robert B. Cialdini");
    if (book) {
        std::cout << "Book found by author: " << book->title << " by " << book->author << std::endl;
    } else {
        std::cout << "Book not found by author." << std::endl;
    }

    // Searching for a book by ISBN
    book = lib.searchBookByISBN("11111");
    if (book) {
        std::cout << "Book found by ISBN: " << book->title << " by " << book->author << std::endl;
    } else {
        std::cout << "Book not found by ISBN." << std::endl;
    }

    // Finding a user by name
    User* user = lib.findUser("Ian");
    if (user) {
        std::cout << "User found: " << user->name << std::endl;
    } else {
        std::cout << "User not found." << std::endl;
    }

    // User borrows a book
    if (user && book) {
        user->borrowBook(*book);
        std::cout << user->name << " borrowed " << book->title << std::endl;
    } else {
        std::cout << "User or book not available for borrowing." << std::endl;
    }

    // Removing a book from the library
    lib.removeBook("12345");
    book = lib.searchBookByTitle("Thinking, Fast and Slow");
    if (!book) {
        std::cout << "Book removed from library." << std::endl;
    } else {
        std::cout << "Book still in library." << std::endl;
    }

    // User returns a book
    Book* bookToReturn = lib.searchBookByISBN("11111");
    if (user && bookToReturn) {
        user->returnBook(*bookToReturn);
        std::cout << user->name << " returned " << bookToReturn->title << std::endl;
    } else {
        std::cout << "User could not return the book." << std::endl;
    }

    return 0;

    // Attempting to borrow a non-existent book
    Book* nonExistentBook = lib.searchBookByTitle("Non-Existent Book");
    if (user && nonExistentBook) {
        user->borrowBook(*nonExistentBook);
    } else {
        std::cout << "Cannot borrow non-existent book." << std::endl;
    }
}