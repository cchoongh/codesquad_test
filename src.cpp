#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <ctime>

using namespace std;

class RubikCubeFace {
	public:
		RubikCubeFace() = default;
		RubikCubeFace(int size, char ch) : size_(size) {
			face_ = vector<string>(size_, string(size_, ch));
		}
		RubikCubeFace(const RubikCubeFace& src) = default;
		RubikCubeFace& operator=(const RubikCubeFace& rhs) = default;

		string getRowString(int idx) {
			string ret;
			for (int i = 0; i < size_; i++) {
				ret += face_[idx][i];
				ret += ' ';
			}
			ret.pop_back();
			return ret;
		}

		void setRow(int idx, const string& row) {
		}
		void setColumn(int idx, const string& column) {
		}

		string getRow(int idx) const {
		}
		string getColumn(int idx) const {
		}

		void setAdjacentUpFace() {
		}
		void setAdjacentLeftFace() {
		}
		void setAdjacentRightFace() {
		}
		void setAdjacentDownFace() {
		}

		string getAdjacentUpFace() const {
		}
		string getAdjacentLeftFace() const {
		}
		string getAdjacentRightFace() const {
		}
		string getAdjacentDownFace() const {
		}

	private:
		int size_ = -1;
		vector<string> face_;
};

class RubikCube {
	public:
		RubikCube(int size) : size_(size) {
			up_face_ = RubikCubeFace(size_, 'B');
			left_face_ = RubikCubeFace(size_, 'W');
			front_face_ = RubikCubeFace(size_, 'O');
			right_face_ = RubikCubeFace(size_, 'G');
			back_face_ = RubikCubeFace(size_, 'Y');
			down_face_ = RubikCubeFace(size_, 'R');
		}

		void suffle() {
		}

		void print() {
			const int width = 2 * size_ - 1;
			string spaces = string(width, ' ');

			for (int i = 0; i < size_; i++) {
				cout << spaces << spaces << spaces << up_face_.getRowString(i) << '\n';
			}

			cout << '\n';

			for (int i = 0; i < size_; i++) {
				cout << left_face_.getRowString(i) << spaces << front_face_.getRowString(i) << spaces
					<< right_face_.getRowString(i) << spaces << back_face_.getRowString(i) << '\n';
			}

			cout << '\n';

			for (int i = 0; i < size_; i++) {
				cout << spaces << spaces << spaces << down_face_.getRowString(i) << '\n';
			}

			cout << '\n';
		}

		void rotateClockUp() {
		}
		void rotateUnclockUp() {
		}

		void rotateClockFront() {
		}
		void rotateUnclockFront() {
		}

		void rotateClockLeft() {
		}
		void rotateUnclockLeft() {
		}

		void rotateClockRight() {
		}
		void rotateUnclockRight() {
		}

		void rotateClockBack() {
		}
		void rotateUnclockBack() {
		}

		void rotateClockDown() {
		}
		void rotateUnclockDown() {
		}

	private:
		const int size_;
		RubikCubeFace up_face_; // U
		RubikCubeFace left_face_; // L
		RubikCubeFace	front_face_; // F
		RubikCubeFace	right_face_; // R
		RubikCubeFace back_face_; // B
		RubikCubeFace down_face_; // D
};

int main() {
	RubikCube rubik_cube = RubikCube(3);
	rubik_cube.suffle();
	rubik_cube.print();

	
}
