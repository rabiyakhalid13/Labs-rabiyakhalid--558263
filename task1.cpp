#include <iostream>
#include <string>
using namespace std;


struct Song {
    int id;
    string name;
    int minutes, seconds;
    Song* next;
    Song* prev;
    Song(int i, string n, int m, int s) {
        id = i; name = n; minutes = m; seconds = s;
        next = nullptr; prev = nullptr;
    }
};

class Playlist {
private:
    Song* head;     // first song
    Song* tail;     // last song
    Song* current;  // song currently playing

    void printSong(Song* s) {
        cout << "ID: " << s->id << " | " << s->name << " | "
             << s->minutes << ":" << (s->seconds < 10 ? "0" : "") << s->seconds << endl;
    }

    Song* findById(int id) {
        for (Song* t = head; t != nullptr; t = t->next)
            if (t->id == id) return t;
        return nullptr;
    }

public:
    Playlist() { head = tail = current = nullptr; }

    ~Playlist() {                       // memory free 
        while (head != nullptr) {
            Song* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // 1. Add song at end
    void addSong(int id, string name, int m, int s) {
        if (findById(id) != nullptr) { cout << "ID already exists!\n"; return; }
        Song* n = new Song(id, name, m, s);
        if (head == nullptr) head = tail = n;      // empty list 
        else {
            tail->next = n;                        
            n->prev = tail;
            tail = n;                              
        }
        cout << "Song added.\n";
    }

    // 2. Delete by ID
    void deleteSong(int id) {
        Song* t = findById(id);
        if (t == nullptr) { cout << "Song not found!\n"; return; }

        if (current == t)                          
            current = (t->next != nullptr) ? t->next : t->prev;

        if (t->prev != nullptr) t->prev->next = t->next;
        else head = t->next;                       

        if (t->next != nullptr) t->next->prev = t->prev;
        else tail = t->prev;                      

        delete t;
        cout << "Song deleted.\n";
    }

    // 3. Forward
    void displayForward() {
        if (head == nullptr) { cout << "Playlist empty.\n"; return; }
        for (Song* t = head; t != nullptr; t = t->next) printSong(t);
    }

    // 4. Backward
    void displayBackward() {
        if (tail == nullptr) { cout << "Playlist empty.\n"; return; }
        for (Song* t = tail; t != nullptr; t = t->prev) printSong(t);
    }

    // 5. Search
    void searchSong(int id) {
        Song* s = findById(id);
        if (s == nullptr) cout << "Song not found!\n";
        else printSong(s);
    }

    // 6. Play next / previous
    void playNext() {
        if (head == nullptr) { cout << "Playlist empty.\n"; return; }
        if (current == nullptr) current = head;
        else if (current->next != nullptr) current = current->next;
        else cout << "Last song, no next song.\n";
        cout << "Now playing: "; printSong(current);
    }

    void playPrevious() {
        if (head == nullptr) { cout << "Playlist empty.\n"; return; }
        if (current == nullptr) current = head;
        else if (current->prev != nullptr) current = current->prev;
        else cout << "First song, no previous song.\n";
        cout << "Now playing: "; printSong(current);
    }

    // 7. Reverse in place:
    void reversePlaylist() {
        Song* temp = nullptr;
        Song* cur = head;
        while (cur != nullptr) {
            temp = cur->prev;
            cur->prev = cur->next;
            cur->next = temp;
            cur = cur->prev;                    
        }
        temp = head; head = tail; tail = temp;    
        cout << "Playlist reversed.\n";
    }
};

int main() {
    Playlist p;
    int choice;
    do {
        cout << "\n1.Add 2.Delete 3.Forward 4.Backward 5.Search 6.Next 7.Previous 8.Reverse 0.Exit\nChoice: ";
        cin >> choice;
        if (choice == 1) {
            int id, m, s; string name;
            cout << "ID: "; cin >> id;
            cout << "Name: "; cin.ignore(); getline(cin, name);
            cout << "Duration (min sec): "; cin >> m >> s;
            p.addSong(id, name, m, s);
        }
        else if (choice == 2) { int id; cout << "ID: "; cin >> id; p.deleteSong(id); }
        else if (choice == 3) p.displayForward();
        else if (choice == 4) p.displayBackward();
        else if (choice == 5) { int id; cout << "ID: "; cin >> id; p.searchSong(id); }
        else if (choice == 6) p.playNext();
        else if (choice == 7) p.playPrevious();
        else if (choice == 8) p.reversePlaylist();
    } while (choice != 0);
    return 0;
}