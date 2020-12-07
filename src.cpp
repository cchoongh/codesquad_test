#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

int main() {
	string word;
	int rot; // rotate
	char dir; // direction

	while (true) {
		cin >> word >> rot >> dir;

		if (!cin.good()) {
			cerr << "Bad input, check and retry!" << '\n';
			cin.clear();
			continue;
		}

		dir = toupper(dir);

		if (toupper(dir) == 'R') {
			rot *= -1;
		} else if (toupper(dir) != 'L') {
			cerr << "Bad third input: " << dir << ", this must become 'L' or 'R'('l' or 'r')!" << '\n';
			cin.clear();
			continue;
		}

		while (rot < 0) rot += word.size();
		while (rot > word.size()) rot -= word.size();

		cout << "rot: " << rot << '\n';

		rotate(word.begin(), word.begin() + rot, word.end());
		cout << word << '\n';
	}
}
