#include <iostream>
#include <algorithm>
#include <vector>

class Album {
public:
    Album* child;
    Album* parent;
    vector<string> pictures;
    string name;

    Album(string name){
        this->name = name;
        this->parent = NULL;
        this->child = NULL;
    }

    void Insert(string name) {
        if (Search(name) == EOF) this->pictures.push_back(name);
        else cout << "duplicated photo name\n";     
    }

    void Delete(string name) {
        int n = 0;
        if (this->pictures.size() < 1) return;
        else if (name == "-1") {
            sort(this->pictures.begin(), this->pictures.end());
            this->pictures.erase(this->pictures.begin());
            n++;
        }
        else if (name == "0") {
            n = this->pictures.size();
            this->pictures.clear();
        }
        else if (name == "1") {
            sort(this->pictures.begin(), this->pictures.end());
            this->pictures.pop_back();
            n++;
        }
        else {
            int idx = Search(name);
            if (idx != EOF) this->pictures.erase(this->pictures.begin() + idx);    
            n++;
        }
        cout << n << "\n";
    }

    int Search(string name) {
        int idx = lower_bound(this->pictures.begin(), this->pictures.end(), name) - this->pictures.begin();
        return (this->pictures[idx] == name && idx < this->pictures.size() ? idx : EOF);
    }
};

class Computer {
public:
    Album top;

    Computer() {
        this->top.name = "album";
    }


};
using namespace std;

int main() {

    return 0;
}
