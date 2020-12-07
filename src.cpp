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

	
}
