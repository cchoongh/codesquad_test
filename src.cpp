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

		void setAdjacentFaces(RubikCubeFace* adj_up_face, RubikCubeFace* adj_left_face,
													RubikCubeFace* adj_right_face, RubikCubeFace* adj_down_face) {
			setAdjacentUpFace(adj_up_face);
			setAdjacentLeftFace(adj_left_face);
			setAdjacentRightFace(adj_right_face);
			setAdjacentDownFace(adj_down_face);
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
		RubikCube() = delete;
		RubikCube(int size) : size_(size) {
			up_face_ = RubikCubeFace(size_, 'B');
			left_face_ = RubikCubeFace(size_, 'W');
			front_face_ = RubikCubeFace(size_, 'O');
			right_face_ = RubikCubeFace(size_, 'G');
			back_face_ = RubikCubeFace(size_, 'Y');
			down_face_ = RubikCubeFace(size_, 'R');

			up_face_.setAdjacentFaces(&back_face_, &left_face_, &right_face_, &front_face_);
			left_face_.setAdjacentFaces(&up_face_, &back_face_, &front_face_, &down_face_);
			front_face_.setAdjacentFaces(&up_face_, &left_face_, &right_face_, &down_face_);
			right_face_.setAdjacentFaces(&up_face_, &front_face_, &back_face_, &down_face_);
			back_face_.setAdjacentFaces(&up_face_, &right_face_, &left_face_, &down_face_);
			down_face_.setAdjacentFaces(&front_face_, &left_face_, &right_face_, &back_face_);
		}

		void suffle() {
		}

		void print() {
			const int width = 2 * size_ - 1;
			string spaces = string(width, ' ');

			for (int i = 0; i < size_; i++)
				cout << spaces << spaces << spaces << up_face_.getRowToPrint(i) << '\n';
			cout << '\n';

			for (int i = 0; i < size_; i++)
				cout << left_face_.getRowToPrint(i) << spaces << front_face_.getRowToPrint(i) << spaces
					<< right_face_.getRowToPrint(i) << spaces << back_face_.getRowToPrint(i) << '\n';
			cout << '\n';

			for (int i = 0; i < size_; i++)
				cout << spaces << spaces << spaces << down_face_.getRowToPrint(i) << '\n';
			cout << '\n';
		}

		void rotateUp(bool clock) {
			string adj_up_edge = up_face_.getAdjacentUpFace()->getRow(0);
			string adj_left_edge = up_face_.getAdjacentLeftFace()->getRow(0);
			string adj_right_edge = up_face_.getAdjacentRightFace()->getRow(0);
			string adj_down_edge = up_face_.getAdjacentDownFace()->getRow(0);

			reverse(adj_up_edge.begin(), adj_up_edge.end());
			reverse(adj_right_edge.begin(), adj_right_edge.end());

			if (clock) {
				rotateClockMainFace(up_face_);
				rotateClockAdjacentEdges(adj_up_edge, adj_left_edge, adj_right_edge, adj_down_edge);
			} else {
				rotateUnclockMainFace(up_face_);
				rotateUnclockAdjacentEdges(adj_up_edge, adj_left_edge, adj_right_edge, adj_down_edge);
			}

			reverse(adj_up_edge.begin(), adj_up_edge.end());
			reverse(adj_right_edge.begin(), adj_right_edge.end());

			up_face_.getAdjacentUpFace()->setRow(0, adj_up_edge);
			up_face_.getAdjacentLeftFace()->setRow(0, adj_left_edge);
			up_face_.getAdjacentRightFace()->setRow(0, adj_right_edge);
			up_face_.getAdjacentDownFace()->setRow(0, adj_down_edge);
		}

		void rotateFront(bool clock) {
		}

		void rotateLeft(bool clock) {
		}

		void rotateRight(bool clock) {
		}

		void rotateBack(bool clock) {
		}

		void rotateDown(bool clock) {
		}

	private:
		const int size_;
		RubikCubeFace up_face_; // U
		RubikCubeFace left_face_; // L
		RubikCubeFace	front_face_; // F
		RubikCubeFace	right_face_; // R
		RubikCubeFace back_face_; // B
		RubikCubeFace down_face_; // D

		void rotateClockMainFace(RubikCubeFace& main_face) {
		}
		void rotateUnclockMainFace(RubikCubeFace& main_face) {
		}

		void rotateClockAdjacentEdges(string& up, string& left, string& right, string& down) {
			string tmp = up;
			up = left;
			left = down;
			down = right;
			right = tmp;
		}

		void rotateUnclockAdjacentEdges(string& up, string& left, string& right, string& down) {
			string tmp = up;
			up = right;
			right = down;
			down = left;
			left = tmp;
		}
};

int main() {
	RubikCube rubik_cube = RubikCube(3);
	rubik_cube.suffle();
	rubik_cube.print();

	
}
