#include <iostream>
#include <string>
using namespace std;

struct Photo {
    int id;
    string name;
    string date;
    string location;
    Photo* next;
    Photo* prev;
};

class PhotoAlbum {
private:
    Photo* current;     // currently selected photo
    int totalPhotos;

public:
    PhotoAlbum() {
        current = NULL;
        totalPhotos = 0;
    }

    // 1. Add Photo at the end
    void addPhoto(int id, string name, string date, string location) {
        Photo* newPhoto = new Photo{id, name, date, location, NULL, NULL};

        if (current == NULL) {                  // empty album
            newPhoto->next = newPhoto;
            newPhoto->prev = newPhoto;
            current = newPhoto;
        } else {
            Photo* last = current->prev;        // last node
            last->next = newPhoto;
            newPhoto->prev = last;
            newPhoto->next = current;
            current->prev = newPhoto;
        }
        totalPhotos++;
        cout << "Photo " << id << " added successfully.\n";
    }

    // 2. Insert Photo After Current
    void insertAfterCurrent(int id, string name, string date, string location) {
        if (current == NULL) {
            addPhoto(id, name, date, location);
            return;
        }

        Photo* newPhoto = new Photo{id, name, date, location, NULL, NULL};

        newPhoto->next = current->next;
        newPhoto->prev = current;
        current->next->prev = newPhoto;
        current->next = newPhoto;

        totalPhotos++;
        cout << "Photo " << id << " inserted after current.\n";
    }

    // 3. Remove Photo by ID
    void removePhoto(int id) {
        if (current == NULL) {
            cout << "Album is empty!\n";
            return;
        }

        Photo* temp = current;
        do {
            if (temp->id == id) {
                // only one photo
                if (temp->next == temp) {
                    delete temp;
                    current = NULL;
                    totalPhotos = 0;
                    cout << "Photo " << id << " removed. Album is now empty.\n";
                    return;
                }

                // more than one photo
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;

                if (temp == current)
                    current = temp->next;

                delete temp;
                totalPhotos--;
                cout << "Photo " << id << " removed.\n";
                return;
            }
            temp = temp->next;
        } while (temp != current);

        cout << "Photo with ID " << id << " not found.\n";
    }

    // 4. Remove Current Photo
    void removeCurrent() {
        if (current == NULL) {
            cout << "Album is empty!\n";
            return;
        }

        int id = current->id;

        if (current->next == current) {     // only one photo
            delete current;
            current = NULL;
            totalPhotos = 0;
        } else {
            Photo* toDelete = current;
            current->prev->next = current->next;
            current->next->prev = current->prev;
            current = current->next;
            delete toDelete;
            totalPhotos--;
        }
        cout << "Current photo (ID " << id << ") removed.\n";
    }

    // 5. Move Next
    void moveNext() {
        if (current == NULL) {
            cout << "Album is empty!\n";
            return;
        }
        current = current->next;
        cout << "Moved to next photo.\n";
    }

    // 6. Move Previous
    void movePrevious() {
        if (current == NULL) {
            cout << "Album is empty!\n";
            return;
        }
        current = current->prev;
        cout << "Moved to previous photo.\n";
    }

    // 7. Display Album Forward
    void displayForward() {
        if (current == NULL) {
            cout << "Album is empty!\n";
            return;
        }

        cout << "\n===== Album (Forward) =====\n";
        Photo* temp = current;
        do {
            cout << "ID: " << temp->id 
                 << " | Name: " << temp->name
                 << " | Date: " << temp->date
                 << " | Location: " << temp->location << endl;
            temp = temp->next;
        } while (temp != current);
        cout << "===========================\n";
    }

    // 8. Display Album Backward
    void displayBackward() {
        if (current == NULL) {
            cout << "Album is empty!\n";
            return;
        }

        cout << "\n===== Album (Backward) =====\n";
        Photo* temp = current;
        do {
            cout << "ID: " << temp->id 
                 << " | Name: " << temp->name
                 << " | Date: " << temp->date
                 << " | Location: " << temp->location << endl;
            temp = temp->prev;
        } while (temp != current);
        cout << "============================\n";
    }

    // 9. Search Photo
    void searchPhoto(int id) {
        if (current == NULL) {
            cout << "Album is empty!\n";
            return;
        }

        Photo* temp = current;
        do {
            if (temp->id == id) {
                cout << "\n===== Photo Found =====\n";
                cout << "ID       : " << temp->id << endl;
                cout << "Name     : " << temp->name << endl;
                cout << "Date     : " << temp->date << endl;
                cout << "Location : " << temp->location << endl;
                cout << "=======================\n";
                return;
            }
            temp = temp->next;
        } while (temp != current);

        cout << "Photo with ID " << id << " not found.\n";
    }

    // 10. Count Photos
    void countPhotos() {
        cout << "Total photos in album: " << totalPhotos << endl;
    }
};

// ==================== MENU ====================
int main() {
    PhotoAlbum album;
    int choice, id, n;
    string name, date, location;

    cout << "Enter number of initial photos: ";
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; i++) {
        cout << "\nPhoto " << i + 1 << " details:\n";
        cout << "ID: ";
        cin >> id;
        cin.ignore();
        cout << "Name: ";
        getline(cin, name);
        cout << "Date Taken: ";
        getline(cin, date);
        cout << "Location: ";
        getline(cin, location);
        album.addPhoto(id, name, date, location);
    }

    do {
        cout << "\n========= Photo Album Menu =========\n";
        cout << "1.  Add Photo (at end)\n";
        cout << "2.  Insert Photo After Current\n";
        cout << "3.  Remove Photo by ID\n";
        cout << "4.  Remove Current Photo\n";
        cout << "5.  Move Next\n";
        cout << "6.  Move Previous\n";
        cout << "7.  Display Album Forward\n";
        cout << "8.  Display Album Backward\n";
        cout << "9.  Search Photo\n";
        cout << "10. Count Photos\n";
        cout << "0.  Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "ID: "; cin >> id; cin.ignore();
                cout << "Name: "; getline(cin, name);
                cout << "Date: "; getline(cin, date);
                cout << "Location: "; getline(cin, location);
                album.addPhoto(id, name, date, location);
                break;
            case 2:
                cout << "ID: "; cin >> id; cin.ignore();
                cout << "Name: "; getline(cin, name);
                cout << "Date: "; getline(cin, date);
                cout << "Location: "; getline(cin, location);
                album.insertAfterCurrent(id, name, date, location);
                break;
            case 3:
                cout << "Enter ID to remove: ";
                cin >> id;
                album.removePhoto(id);
                break;
            case 4:
                album.removeCurrent();
                break;
            case 5:
                album.moveNext();
                break;
            case 6:
                album.movePrevious();
                break;
            case 7:
                album.displayForward();
                break;
            case 8:
                album.displayBackward();
                break;
            case 9:
                cout << "Enter ID to search: ";
                cin >> id;
                album.searchPhoto(id);
                break;
            case 10:
                album.countPhotos();
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