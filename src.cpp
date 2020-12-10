#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

int main() {
	string word;
	int rot; // rotate
	char dir; // direction

	while (cout << "\n> " && cin >> word >> rot >> dir) {
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

		rotate(word.begin(), word.begin() + rot, word.end());
		cout << word << '\n';
	}
}
