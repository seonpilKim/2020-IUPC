#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Album {
public:
    vector<Album*> albums;
    Album* parent;
    vector<string> pictures;
    string name;
    int size_pic;
    int size_alb;

    Album(string name){
        this->name = name;
        this->parent = NULL;
        this->size_alb = 0;
        this->size_pic = 0;
    }

    void Insert(string name) {
        if (this->pictures.size() == 0) {
            this->pictures.push_back(name);
            this->size_pic++;
        }
        else if (Search(name) == EOF) {
            this->pictures.push_back(name);
            this->size_pic++;
            sort(this->pictures.begin(), this->pictures.end());
        }
        else if (Search(name) > EOF) cout << "duplicated photo name\n";     
    }

    void Delete(string name) {
        if (this->pictures.size() < 1) cout << 0 << "\n";
        else if (name == "-1") {
            this->pictures.erase(this->pictures.begin());
            this->size_pic--;
            cout << 1 << "\n";
        }
        else if (name == "0") {
            cout << this->pictures.size() << "\n";
            this->pictures.clear();
            this->size_pic = 0;
        }
        else if (name == "1") {
            this->pictures.pop_back();
            this->size_pic--;
            cout << 1 << "\n";
        }
        else {
            int idx = Search(name);
            if (idx != EOF) this->pictures.erase(this->pictures.begin() + idx);
            this->size_pic--;
            cout << 1 << "\n";
        }
    }

    int Search(string name) {
        int idx = lower_bound(this->pictures.begin(), this->pictures.end(), name) - this->pictures.begin();
        return ((idx < this->pictures.size() && this->pictures[idx] == name) ? idx : EOF);
    }
};

class Computer {
public:
    Album* top;
    Album* cur;
    Album* ser;
    int cnt_a;
    int cnt_p;

    Computer() {
        Album* newAlbum = new Album("album");
        this->top = newAlbum;
        this->cur = this->top;
        this->ser = NULL;
    }

    static bool compare(Album* a, Album* b) {
        return a->name < b->name;
    }

    void Make(string name) {
        for (int i = 0; i < this->cur->albums.size(); i++) {
            if (this->cur->albums[i]->name == name) {
                cout << "duplicated album name\n";
                return;
            }
        }
        Album* newAlbum = new Album(name);
        newAlbum->parent = this->cur;
        this->cur->albums.push_back(newAlbum);
        sort(this->cur->albums.begin(), this->cur->albums.end(), compare);
        this->cur->size_alb++;
    }

    void Remove(string name) {
        if (this->cur->albums.size() == 0) cout << "0 0\n";
        else if (name == "-1") {
            this->cnt_a = this->cur->albums[0]->size_alb + 1;
            this->cnt_p = this->cur->albums[0]->size_pic;
            Counting(this->cur->albums[0]);
            this->cur->size_alb--;
            this->cur->albums.erase(this->cur->albums.begin());
            cout << this->cnt_a << " " << this->cnt_p << "\n";
            return;
        }
        else if (name == "0") {
            this->cnt_a = this->cur->size_alb;
            this->cnt_p = 0;
            for (int i = 0; i < this->cur->albums.size(); i++) {
                Counting(this->cur->albums[i]);
                this->cnt_a += this->cur->albums[i]->size_alb;
                this->cnt_p += this->cur->albums[i]->size_pic;
            }
            this->cur->albums.clear();
            cout << this->cnt_a << " " << this->cnt_p << "\n";
            this->cur->size_alb = 0;
            return;
        }
        else if (name == "1") {
            this->cnt_a = this->cur->albums[this->cur->albums.size() - 1]->size_alb + 1;
            this->cnt_p = this->cur->albums[this->cur->albums.size() - 1]->size_pic;
            Counting(this->cur->albums[this->cur->albums.size() - 1]);
            this->cur->size_alb--;
            this->cur->albums.pop_back();
            cout << this->cnt_a << " " << this->cnt_p << "\n";
            return;
        }
        else {
            for (int i = 0; i < this->cur->albums.size(); i++) {
                if (this->cur->albums[i]->name == name) {
                    this->cnt_a = this->cur->albums[i]->size_alb + 1;
                    this->cnt_p = this->cur->albums[i]->size_pic;
                    Counting(this->cur->albums[i]);
                    this->cur->size_alb--;
                    this->cur->albums.erase(this->cur->albums.begin() + i);
                    cout << this->cnt_a << " " << this->cnt_p << "\n";
                    return;
                }
            }
        }
    }

    void Counting(Album* ptr) {
        for (int i = 0; i < ptr->albums.size(); i++) {
            if (ptr->albums[i] != NULL) {
                Counting(ptr->albums[i]);
                this->cnt_a += ptr->albums[i]->size_alb;
                this->cnt_p += ptr->albums[i]->size_pic;
            }
        }
    }

    void Change(string name) {
        if (name == "..") {
            if (this->cur->name == "album") {
                cout << this->cur->name << "\n";
                return;
            }
            this->cur = this->cur->parent;
        }
        else if (name == "/") this->cur = this->top;
        else {
            Search(this->cur, name);
            if (this->ser != NULL) this->cur = this->ser;
            this->ser = NULL;
        }
        cout << this->cur->name << "\n";
    }

    void Search(Album* ptr, string name) {
        for (int i = 0; i < ptr->albums.size(); i++) {
            if (ptr->albums[i] != NULL) {
                if (ptr->albums[i]->name == name) {
                    this->ser = ptr->albums[i];
                    return;
                }
                Search(ptr->albums[i], name);
            }
        }
    }
};

int main() {
    int N;
    string S, str;
    Computer pc;

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;

    for (int i = 0; i < N; i++) {
        cin >> S;
        if (S == "mkalb") {
            cin >> str;
            pc.Make(str);
        }
        else if (S == "rmalb") {
            cin >> str;
            pc.Remove(str);
        }
        else if (S == "insert") {
            cin >> str;
            pc.cur->Insert(str);
        }
        else if (S == "delete") {
            cin >> str;
            pc.cur->Delete(str);
        }
        else if (S == "ca") {
            cin >> str;
            pc.Change(str);
        }
    }

    return 0;
}
