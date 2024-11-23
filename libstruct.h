#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libstruct.h"

// Add a book to the library
void addBook(Library *library, const char *title, const char *author, int year) {
    if (library->count >= 100) {
        printf("The library is full. Cannot add more books.\n");
        return;
    }

    // Check if the book is already in the library
    if (findBook(library, title, author, year)) {
        printf("Book with title %s, author %s, and year %d is already in the library.\n", title, author, year);
        return;
    }

    // Create a new book
    Book *newBook = (Book *)malloc(sizeof(Book));
    newBook->title = strdup(title);
    newBook->author = strdup(author);
    newBook->year = year;
    newBook->isAvailable = 1;

    // Add the book to the library
    library->library[library->count] = newBook;
    library->count++;

    printf("Book with title %s, author %s, and year %d added to the library.\n", title, author, year);
}

// Remove a book from the library
void removeBook(Library *library, const char *title, const char *author, int year) {
    for (int i = 0; i < library->count; i++) {
        Book *book = library->library[i];
        if (book && strcmp(book->title, title) == 0 && strcmp(book->author, author) == 0 && book->year == year) {
            printf("Book with title %s, author %s, and year %d has been removed from the library.\n", title, author, year);
            free(book->title);
            free(book->author);
            free(book);
            library->library[i] = NULL; // Mark the spot as empty
            library->count--;
            return;
        }
    }
    printf("Book not found\n");
}

// Print all books in the library
void printLibrary(const Library *library) {
    for (int i = 0; i < library->count; i++) {
        Book *book = library->library[i];
        if (book) {
            printf("Book with title %s, author %s, and year %d is in the library and %s checked out.\n",
                   book->title, book->author, book->year, book->isAvailable ? "isn't" : "is");
        }
    }
}

// Find a book in the library
Book *findBook(const Library *library, const char *title, const char *author, int year) {
    for (int i = 0; i < library->count; i++) {
        Book *book = library->library[i];
        if (book && strcmp(book->title, title) == 0 && strcmp(book->author, author) == 0 && book->year == year) {
            printf("Book with title %s, author %s, and year %d is found!\n", title, author, year);
            return book;
        }
    }
    return NULL;
}

// Checkout a book
void checkoutBook(Library *library, const char *title, const char *author, int year) {
    Book *book = findBook(library, title, author, year);
    if (book) {
        if (!book->isAvailable) {
            printf("Book with title %s, author %s, and year %d is already checked out.\n", title, author, year);
        } else {
            book->isAvailable = 0;
            printf("Book with title %s, author %s, and year %d is checked out.\n", title, author, year);
        }
    } else {
        printf("Book not found\n");
    }
}

// Return a book
void returnBook(Library *library, const char *title, const char *author, int year) {
    Book *book = findBook(library, title, author, year);
    if (book) {
        if (book->isAvailable) {
            printf("Book with title %s, author %s, and year %d is not checked out.\n", title, author, year);
        } else {
            book->isAvailable = 1;
            printf("Book with title %s, author %s, and year %d is returned.\n", title, author, year);
        }
    } else {
        printf("Book not found\n");
    }
}
