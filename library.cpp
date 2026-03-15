#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

// Structure to hold Book details
struct Book {
    string title;
    string author;
};

// Helper function to convert a string to lowercase for case-insensitive matching
string toLowerCase(string str) {
    transform(str.begin(), str.end(), str.begin(), [](unsigned char c){ return tolower(c); });
    return str;
}

// Efficient Binary Search implementation for Title lookups (O(log N))
int binarySearchTitle(Book arr[], int size, string target) {
    int left = 0;
    int right = size - 1;
    target = toLowerCase(target);

    while (left <= right) {
        int mid = left + (right - left) / 2;
        string midTitle = toLowerCase(arr[mid].title);

        if (midTitle == target) {
            return mid; // Book found at index 'mid'
        }
        if (midTitle < target) {
            left = mid + 1; // Search the right half
        } else {
            right = mid - 1; // Search the left half
        }
    }
    return -1; // Book not found
}

int main() {
    // Predefined dataset using array-based data handling
    const int numBooks = 5;
    Book library[numBooks] = {
        {"The Great Gatsby", "F. Scott Fitzgerald"},
        {"1984", "George Orwell"},
        {"To Kill a Mockingbird", "Harper Lee"},
        {"Pride and Prejudice", "Jane Austen"},
        {"The Catcher in the Rye", "J.D. Salinger"}
    };

    // OPTIMIZATION: Sort the array by title alphabetically to enable Binary Search
    sort(library, library + numBooks, [](const Book& a, const Book& b) {
        return toLowerCase(a.title) < toLowerCase(b.title);
    });

    int choice;
    string searchInput;

    do {
        // Display search options
        cout << "\n--- Library Search System ---" << endl;
        cout << "1. Search by Title (Fast Binary Search)" << endl;
        cout << "2. Search by Author" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice (1-3): ";
        cin >> choice;
        
        cin.ignore(); // Clear the input buffer

        bool found = false;

        switch (choice) {
            case 1: {
                cout << "Enter Book Title to search: ";
                getline(cin, searchInput);
                
                // Improved Efficiency: Using Binary Search
                int index = binarySearchTitle(library, numBooks, searchInput);
                
                if (index != -1) {
                    cout << "\nBook Found Successfully!" << endl;
                    cout << "Title: " << library[index].title << " | Author: " << library[index].author << endl;
                } else {
                    cout << "\nBook not found in the library." << endl;
                }
                break;
            }
            case 2: {
                cout << "Enter Author Name to search: ";
                getline(cin, searchInput);
                
                // Linear search for authors (since one author can have multiple books)
                for (int i = 0; i < numBooks; i++) {
                    if (toLowerCase(library[i].author) == toLowerCase(searchInput)) {
                        if (!found) cout << "\nBook Found Successfully!" << endl;
                        cout << "Title: " << library[i].title << " | Author: " << library[i].author << endl;
                        found = true;
                    }
                }
                if (!found) cout << "\nNo books found by that author." << endl;
                break;
            }
            case 3:
                cout << "Exiting the program. Goodbye!" << endl;
                break;

            default:
                cout << "Invalid choice. Please enter 1, 2, or 3." << endl;
        }

    } while (choice != 3);

    return 0;
}