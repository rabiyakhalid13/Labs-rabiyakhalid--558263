#include <iostream>
#include <string>
using namespace std;

struct Tab {
    int id;
    string title;
    string url;
    Tab* next;
    Tab* prev;
};

class Browser {
private:
    Tab* current;   // active tab
    int nextId;     // automatic ID generator

public:
    Browser() {
        current = NULL;
        nextId = 1;
    }

    // 1. Open New Tab (current ke baad insert)
    void openNewTab(string title, string url) {
        Tab* newTab = new Tab;
        newTab->id = nextId++;
        newTab->title = title;
        newTab->url = url;

        if (current == NULL) {          // pehli tab
            newTab->next = newTab;
            newTab->prev = newTab;
            current = newTab;
        } else {
            // current ke baad insert
            newTab->next = current->next;
            newTab->prev = current;
            current->next->prev = newTab;
            current->next = newTab;
            current = newTab;           // naya tab active ban jaye
        }
        cout << "Opened Tab " << newTab->id << endl;
    }

    // 2. Close Current Tab
    void closeCurrentTab() {
        if (current == NULL) {
            cout << "No tabs open!\n";
            return;
        }

        // sirf ek tab bachi ho
        if (current->next == current) {
            delete current;
            current = NULL;
            cout << "All tabs closed.\n";
            return;
        }

        Tab* toDelete = current;
        // links update
        current->prev->next = current->next;
        current->next->prev = current->prev;
        current = current->next;   // next tab active

        cout << "Closed Tab " << toDelete->id << endl;
        delete toDelete;
    }

    // 3. Move Next
    void moveNext() {
        if (current == NULL) {
            cout << "No tabs open!\n";
            return;
        }
        current = current->next;
        cout << "Moved to next tab\n";
    }

    // 4. Move Previous
    void movePrevious() {
        if (current == NULL) {
            cout << "No tabs open!\n";
            return;
        }
        current = current->prev;
        cout << "Moved to previous tab\n";
    }

    // 5. Display Current Tab
    void displayCurrent() {
        if (current == NULL) {
            cout << "No tabs open!\n";
            return;
        }
        cout << "\n===== Current Tab =====\n";
        cout << "ID    : " << current->id << endl;
        cout << "Title : " << current->title << endl;
        cout << "URL   : " << current->url << endl;
        cout << "=======================\n";
    }

    // 6. Display All Tabs Forward (current se start, wapas current tak)
    void displayForward() {
        if (current == NULL) {
            cout << "No tabs open!\n";
            return;
        }

        cout << "\n===== All Tabs (Forward) =====\n";
        Tab* temp = current;
        do {
            cout << "ID: " << temp->id 
                 << " | " << temp->title 
                 << " | " << temp->url << endl;
            temp = temp->next;
        } while (temp != current);
        cout << "==============================\n";
    }

    // 7. Display All Tabs Backward
    void displayBackward() {
        if (current == NULL) {
            cout << "No tabs open!\n";
            return;
        }

        cout << "\n===== All Tabs (Backward) =====\n";
        Tab* temp = current;
        do {
            cout << "ID: " << temp->id 
                 << " | " << temp->title 
                 << " | " << temp->url << endl;
            temp = temp->prev;
        } while (temp != current);
        cout << "===============================\n";
    }

    // 8. Search Tab by ID
    void searchTab(int id) {
        if (current == NULL) {
            cout << "No tabs open!\n";
            return;
        }

        Tab* temp = current;
        do {
            if (temp->id == id) {
                cout << "\n===== Tab Found =====\n";
                cout << "ID    : " << temp->id << endl;
                cout << "Title : " << temp->title << endl;
                cout << "URL   : " << temp->url << endl;
                cout << "=====================\n";
                return;
            }
            temp = temp->next;
        } while (temp != current);

        cout << "Tab with ID " << id << " not found.\n";
    }
};

// ==================== MENU ====================
int main() {
    Browser browser;
    int choice;
    string title, url;
    int id;

    do {
        cout << "\n========= Browser Tab Manager =========\n";
        cout << "1. Open New Tab\n";
        cout << "2. Close Current Tab\n";
        cout << "3. Move Next\n";
        cout << "4. Move Previous\n";
        cout << "5. Display Current Tab\n";
        cout << "6. Display All Tabs Forward\n";
        cout << "7. Display All Tabs Backward\n";
        cout << "8. Search Tab by ID\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();   // buffer clear

        switch (choice) {
            case 1:
                cout << "Enter Title: ";
                getline(cin, title);
                cout << "Enter URL  : ";
                getline(cin, url);
                browser.openNewTab(title, url);
                break;
            case 2:
                browser.closeCurrentTab();
                break;
            case 3:
                browser.moveNext();
                break;
            case 4:
                browser.movePrevious();
                break;
            case 5:
                browser.displayCurrent();
                break;
            case 6:
                browser.displayForward();
                break;
            case 7:
                browser.displayBackward();
                break;
            case 8:
                cout << "Enter Tab ID to search: ";
                cin >> id;
                browser.searchTab(id);
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}