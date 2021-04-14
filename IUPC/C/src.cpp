#include <iostream>
#include <map>
#include <set>

using namespace std;

struct album {
	album* parent;
	map<string, album*> albums;
	set<string> pictures;
	string name;
	int size_alb;
	int size_pic;

	album(string name, album* parent)
		: parent(parent), name(name), size_alb(0), size_pic(0) {}
};

void mkalb(album* cur, const string& name) {
	auto iter = cur->albums.lower_bound(name);
	if (iter == cur->albums.end() || iter->first != name) {
		cur->albums.emplace_hint(iter, name, new album(name, cur));
		while (cur != nullptr) {
			cur->size_alb++;
			cur = cur->parent;
		}
	}
	else
		cout << "duplicated album name\n";
}

void rmalb(album* cur, const string& name) {
	if (cur->albums.empty()) {
		cout << "0 0\n";
		return;
	}

	int cnt_alb, cnt_pic;
	if (name == "-1") {
		auto iter = cur->albums.begin();
		cnt_alb = iter->second->size_alb + 1;
		cnt_pic = iter->second->size_pic;
		cur->albums.erase(iter);
	}
	else if (name == "0") {
		cnt_alb = cur->size_alb;
		cnt_pic = cur->size_pic - cur->pictures.size();
		cur->albums.clear();
	}
	else if (name == "1") {
		auto iter = --(cur->albums.end());
		cnt_alb = iter->second->size_alb + 1;
		cnt_pic = iter->second->size_pic;
		cur->albums.erase(iter);
	}
	else {
		auto iter = cur->albums.find(name);
		if (iter == cur->albums.end()) {
			cout << "0 0\n";
			return;
		}
		cnt_alb = iter->second->size_alb + 1;
		cnt_pic = iter->second->size_pic;
		cur->albums.erase(iter);
	}

	cout << cnt_alb << ' ' << cnt_pic << '\n';
	while (cur != nullptr) {
		cur->size_alb -= cnt_alb;
		cur->size_pic -= cnt_pic;
		cur = cur->parent;
	}
}

void insert(album* cur, const string& name) {
	auto iter = cur->pictures.lower_bound(name);
	if (iter == cur->pictures.end() || *iter != name) {
		cur->pictures.emplace_hint(iter, name);
		while (cur != nullptr) {
			cur->size_pic++;
			cur = cur->parent;
		}
	}
	else
		cout << "duplicated photo name\n";
}

void _delete(album* cur, const string& name) {
	if (cur->pictures.empty()) {
		cout << "0\n";
		return;
	}

	int cnt_pic;
	if (name == "-1") {
		cnt_pic = 1;
		cur->pictures.erase(cur->pictures.begin());
	}
	else if (name == "0") {
		cnt_pic = cur->pictures.size();
		cur->pictures.clear();
	}
	else if (name == "1") {
		cnt_pic = 1;
		cur->pictures.erase(--(cur->pictures.end()));
	}
	else {
		auto iter = cur->pictures.find(name);
		if (iter == cur->pictures.end()) {
			cout << "0\n";
			return;
		}
		cnt_pic = 1;
		cur->pictures.erase(iter);
	}

	cout << cnt_pic << '\n';
	while (cur != nullptr) {
		cur->size_pic -= cnt_pic;
		cur = cur->parent;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	album* root = new album("album", nullptr);
	album* cur = root;
	
	int N;
	string cmd, name;
	cin >> N;
	while (N--) {
		cin >> cmd >> name;
		if (cmd == "mkalb")
			mkalb(cur, name);
		else if (cmd == "rmalb")
			rmalb(cur, name);
		else if (cmd == "insert")
			insert(cur, name);
		else if (cmd == "delete")
			_delete(cur, name);
		else if (cmd == "ca") {
			if (name == ".." && cur != root)
				cur = cur->parent;
			else if (name == "/" && cur != root)
				cur = root;
			else {
				auto iter = cur->albums.find(name);
				if (iter != cur->albums.end())
					cur = iter->second;
			}
			cout << cur->name << '\n';
		}
	}

	return 0;
}