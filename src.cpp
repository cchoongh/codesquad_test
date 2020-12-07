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

		string getRowToPrint(int idx) {
			string row;
			for (int i = 0; i < size_; i++) {
				row += face_[idx][i];
				row += ' ';
			}
			row.pop_back();
			return row;
		}

		void setRow(int idx, const string& row) {
			face_[idx] = row;
		}
		void setColumn(int idx, const string& column) {
			for (int i = 0; i < size_; i++) {
				face_[i][idx] = column[i];
			}
		}

		string getRow(int idx) const {
			return face_[idx];
		}
		string getColumn(int idx) const {
			string column;
			for (int i = 0; i < size_; i++) {
				column += face_[i][idx];
			}
			return column;
		}

		void setAdjacentUpFace(RubikCubeFace* adj_up_face) { adj_up_face_ = adj_up_face; }
		void setAdjacentLeftFace(RubikCubeFace* adj_left_face) { adj_left_face_ = adj_left_face; }
		void setAdjacentRightFace(RubikCubeFace* adj_right_face) { adj_right_face_ = adj_right_face; }
		void setAdjacentDownFace(RubikCubeFace* adj_down_face) { adj_down_face_ = adj_down_face; }

		RubikCubeFace* getAdjacentUpFace() const { return adj_up_face_; }
		RubikCubeFace* getAdjacentLeftFace() const { return adj_left_face_; }
		RubikCubeFace* getAdjacentRightFace() const { return adj_right_face_; }
		RubikCubeFace* getAdjacentDownFace() const { return adj_down_face_; }

	private:
		int size_ = -1;
		vector<string> face_;
		RubikCubeFace* adj_up_face_ = nullptr;
		RubikCubeFace* adj_left_face_ = nullptr;
		RubikCubeFace* adj_right_face_ = nullptr;
		RubikCubeFace* adj_down_face_ = nullptr;
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
				cout << spaces << spaces << spaces << up_face_.getRowToPrint(i) << '\n';
			}

			cout << '\n';

			for (int i = 0; i < size_; i++) {
				cout << left_face_.getRowToPrint(i) << spaces << front_face_.getRowToPrint(i) << spaces
					<< right_face_.getRowToPrint(i) << spaces << back_face_.getRowToPrint(i) << '\n';
			}

			cout << '\n';

			for (int i = 0; i < size_; i++) {
				cout << spaces << spaces << spaces << down_face_.getRowToPrint(i) << '\n';
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
