#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iomanip>

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

		bool isFitted() {
			const char element = face_[0][0];

			for (int r = 0; r < size_; r++) {
				for (int c = 0; c < size_; c++) {
					if (face_[r][c] != element)
						return false;
				}
			}

			return true;
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

		void setOutLine(const string& out_line) {
			face_[0] = out_line.substr(0, size_);
			int r = 1; // row
			int c = size_ - 1; // column
			int idx = size_; // index of 'out_line'

			while (r + 1 < size_) { face_[r][c] = out_line[idx++]; r++; }
			while (c > 0) { face_[r][c] = out_line[idx++]; c--; }
			while (r > 0) { face_[r][c] = out_line[idx++]; r--; }
		}
		string getOutLine() {
			string out_line = getRow(0);
			int r = 1; // row
			int c = size_ - 1; // column

			while (r + 1 < size_) { out_line += face_[r][c]; r++; }
			while (c > 0) { out_line += face_[r][c]; c--; }
			while (r > 0) { out_line += face_[r][c]; r--; }
		
			return out_line;
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
			srand(time(NULL));
			int num_rotate = 500;

			while (num_rotate-- > 0) {
				int rand_rotate = rand() % 12;

				switch (rand_rotate) {
					case 0:
						rotateFront(true); break;
					case 1:
						rotateFront(false); break;
					case 2:
						rotateLeft(true); break;
					case 3:
						rotateLeft(false); break;
					case 4:
						rotateRight(true); break;
					case 5:
						rotateRight(false); break;
					case 6:
						rotateUp(true); break;
					case 7:
						rotateUp(false); break;
					case 8:
						rotateDown(true); break;
					case 9:
						rotateDown(false); break;
					case 10:
						rotateBack(true); break;
					case 11:
						rotateBack(false); break;
				}
			}
		}

		bool isFitted() {
			bool is_fitted = front_face_.isFitted();
			is_fitted = is_fitted && left_face_.isFitted();
			is_fitted = is_fitted && right_face_.isFitted();
			is_fitted = is_fitted && up_face_.isFitted();
			is_fitted = is_fitted && down_face_.isFitted();
			is_fitted = is_fitted && back_face_.isFitted();
			return is_fitted;
		}

		void print() {
			const int width = 2 * size_ - 1;
			string spaces = string(width, ' ');

			for (int i = 0; i < size_; i++)
				cout << spaces << spaces << up_face_.getRowToPrint(i) << '\n';
			cout << '\n';

			for (int i = 0; i < size_; i++)
				cout << left_face_.getRowToPrint(i) << spaces << front_face_.getRowToPrint(i) << spaces
					<< right_face_.getRowToPrint(i) << spaces << back_face_.getRowToPrint(i) << '\n';
			cout << '\n';

			for (int i = 0; i < size_; i++)
				cout << spaces << spaces << down_face_.getRowToPrint(i) << '\n';
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
			std::string adj_up_edge = front_face_.getAdjacentUpFace()->getRow(size_ - 1);
			std::string adj_left_edge = front_face_.getAdjacentLeftFace()->getColumn(size_ - 1);
			std::string adj_right_edge = front_face_.getAdjacentRightFace()->getColumn(0);
			std::string adj_down_edge = front_face_.getAdjacentDownFace()->getRow(0);

			if (clock) {
				rotateClockMainFace(front_face_);
				rotateClockAdjacentEdges(adj_up_edge, adj_left_edge, adj_right_edge, adj_down_edge);
			} else {
				rotateUnclockMainFace(front_face_);
				rotateUnclockAdjacentEdges(adj_up_edge, adj_left_edge, adj_right_edge, adj_down_edge);
			}

			front_face_.getAdjacentUpFace()->setRow(size_ - 1, adj_up_edge);
			front_face_.getAdjacentLeftFace()->setColumn(size_ - 1, adj_left_edge);
			front_face_.getAdjacentRightFace()->setColumn(0, adj_right_edge);
			front_face_.getAdjacentDownFace()->setRow(0, adj_down_edge);
		}

		void rotateLeft(bool clock) {
			std::string adj_up_edge = left_face_.getAdjacentUpFace()->getColumn(0);
			std::string adj_left_edge = left_face_.getAdjacentLeftFace()->getColumn(size_ - 1);
			std::string adj_right_edge = left_face_.getAdjacentRightFace()->getColumn(0);
			std::string adj_down_edge = left_face_.getAdjacentDownFace()->getColumn(0);

			reverse(adj_down_edge.begin(), adj_down_edge.end());

			if (clock) {
				rotateClockMainFace(left_face_);
				rotateClockAdjacentEdges(adj_up_edge, adj_left_edge, adj_right_edge, adj_down_edge);
			} else {
				rotateUnclockMainFace(left_face_);
				rotateUnclockAdjacentEdges(adj_up_edge, adj_left_edge, adj_right_edge, adj_down_edge);
			}

			reverse(adj_down_edge.begin(), adj_down_edge.end());

			left_face_.getAdjacentUpFace()->setColumn(0, adj_up_edge);
			left_face_.getAdjacentLeftFace()->setColumn(size_ - 1, adj_left_edge);
			left_face_.getAdjacentRightFace()->setColumn(0, adj_right_edge);
			left_face_.getAdjacentDownFace()->setColumn(0, adj_down_edge);
		}

		void rotateRight(bool clock) {
			std::string adj_up_edge = right_face_.getAdjacentUpFace()->getColumn(size_ - 1);
			std::string adj_left_edge = right_face_.getAdjacentLeftFace()->getColumn(size_ - 1);
			std::string adj_right_edge = right_face_.getAdjacentRightFace()->getColumn(0);
			std::string adj_down_edge = right_face_.getAdjacentDownFace()->getColumn(size_ - 1);

			reverse(adj_up_edge.begin(), adj_up_edge.end());

			if (clock) {
				rotateClockMainFace(right_face_);
				rotateClockAdjacentEdges(adj_up_edge, adj_left_edge, adj_right_edge, adj_down_edge);
			} else {
				rotateUnclockMainFace(right_face_);
				rotateUnclockAdjacentEdges(adj_up_edge, adj_left_edge, adj_right_edge, adj_down_edge);
			}

			reverse(adj_up_edge.begin(), adj_up_edge.end());

			right_face_.getAdjacentUpFace()->setColumn(size_ - 1, adj_up_edge);
			right_face_.getAdjacentLeftFace()->setColumn(size_ - 1, adj_left_edge);
			right_face_.getAdjacentRightFace()->setColumn(0, adj_right_edge);
			right_face_.getAdjacentDownFace()->setColumn(size_ - 1, adj_down_edge);
		}

		void rotateBack(bool clock) {
			std::string adj_up_edge = back_face_.getAdjacentUpFace()->getRow(0);
			std::string adj_left_edge = back_face_.getAdjacentLeftFace()->getColumn(size_ - 1);
			std::string adj_right_edge = back_face_.getAdjacentRightFace()->getColumn(0);
			std::string adj_down_edge = back_face_.getAdjacentDownFace()->getRow(size_ - 1);

			reverse(adj_up_edge.begin(), adj_up_edge.end());
			reverse(adj_down_edge.begin(), adj_down_edge.end());

			if (clock) {
				rotateClockMainFace(back_face_);
				rotateClockAdjacentEdges(adj_up_edge, adj_left_edge, adj_right_edge, adj_down_edge);
			} else {
				rotateUnclockMainFace(back_face_);
				rotateUnclockAdjacentEdges(adj_up_edge, adj_left_edge, adj_right_edge, adj_down_edge);
			}

			reverse(adj_up_edge.begin(), adj_up_edge.end());
			reverse(adj_down_edge.begin(), adj_down_edge.end());

			back_face_.getAdjacentUpFace()->setRow(0, adj_up_edge);
			back_face_.getAdjacentLeftFace()->setColumn(size_ - 1, adj_left_edge);
			back_face_.getAdjacentRightFace()->setColumn(0, adj_right_edge);
			back_face_.getAdjacentDownFace()->setRow(size_ - 1, adj_down_edge);
		}

		void rotateDown(bool clock) {
			std::string adj_up_edge = down_face_.getAdjacentUpFace()->getRow(size_ - 1);
			std::string adj_left_edge = down_face_.getAdjacentLeftFace()->getRow(size_ - 1);
			std::string adj_right_edge = down_face_.getAdjacentRightFace()->getRow(size_ - 1);
			std::string adj_down_edge = down_face_.getAdjacentDownFace()->getRow(size_ - 1);

			reverse(adj_left_edge.begin(), adj_left_edge.end());
			reverse(adj_down_edge.begin(), adj_down_edge.end());

			if (clock) {
				rotateClockMainFace(down_face_);
				rotateClockAdjacentEdges(adj_up_edge, adj_left_edge, adj_right_edge, adj_down_edge);
			} else {
				rotateUnclockMainFace(down_face_);
				rotateUnclockAdjacentEdges(adj_up_edge, adj_left_edge, adj_right_edge, adj_down_edge);
			}

			reverse(adj_left_edge.begin(), adj_left_edge.end());
			reverse(adj_down_edge.begin(), adj_down_edge.end());

			down_face_.getAdjacentUpFace()->setRow(size_ - 1, adj_up_edge);
			down_face_.getAdjacentLeftFace()->setRow(size_ - 1, adj_left_edge);
			down_face_.getAdjacentRightFace()->setRow(size_ - 1, adj_right_edge);
			down_face_.getAdjacentDownFace()->setRow(size_ - 1, adj_down_edge);
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
			string out_line = main_face.getOutLine();
			rotate(out_line.begin(), out_line.begin() + 3 * (size_ - 1), out_line.end());
			main_face.setOutLine(out_line);
		}
		void rotateUnclockMainFace(RubikCubeFace& main_face) {
			string out_line = main_face.getOutLine();
			rotate(out_line.begin(), out_line.begin() + size_ - 1, out_line.end());
			main_face.setOutLine(out_line);
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
	
	cout << "[Before suffling]" << '\n';
	rubik_cube.print();

	rubik_cube.suffle();

	cout << "\n[After suffling]" << '\n';
	rubik_cube.print();

	int operate_cnt = 0;
	time_t start_time = time(NULL);
	bool is_fitted = false;
	
	std::string input;
	while (!is_fitted && cout << "\nCUBE> " && cin >> input && input != "Q") {
		for (int i = 0; i < input.size(); i++) {
			char inst = input[i]; // instruction
			bool clock = true;
			bool degree180 = false;
			bool success = true;

			if (i < input.size() - 1 && input[i + 1] == '\'') {
				clock = false;
				i++;
			}

			if (i < input.size() - 1 && input[i + 1] == '2') {
				degree180 = true;
				i++;
			}

			cout << '\n' << inst << (clock ? "" : "'") << (degree180 ? "2" : "") << '\n';
			
			switch (inst) {
				case 'F':
					rubik_cube.rotateFront(clock);
					if (degree180) rubik_cube.rotateFront(clock);
					break;
				case 'R':
					rubik_cube.rotateRight(clock);
					if (degree180) rubik_cube.rotateRight(clock);
					break;
				case 'U':
					rubik_cube.rotateUp(clock);
					if (degree180) rubik_cube.rotateUp(clock);
					break;
				case 'B':
					rubik_cube.rotateBack(clock);
					if (degree180) rubik_cube.rotateBack(clock);
					break;
				case 'L':
					rubik_cube.rotateLeft(clock);
					if (degree180) rubik_cube.rotateLeft(clock);
					break;
				case 'D':
					rubik_cube.rotateDown(clock);
					if (degree180) rubik_cube.rotateDown(clock);
					break;
				default:
					cerr << "(ignore bad instruction: " << inst << ")\n";
					success = false;
					break;
			}

			if (success) {
				rubik_cube.print();
				operate_cnt++;
			}

			if (rubik_cube.isFitted()) {
				cout << "Congratulations! The cube is fitted!" << '\n';
				is_fitted = true;
				break;
			}
		}

		input.clear();
	}

	time_t end_time = time(NULL) - start_time;
	struct tm* tm = localtime(&end_time);
	cout << "Elapsed time: " << (tm->tm_min < 10 ? "0" : "") << tm->tm_min << ":"
		<< (tm->tm_sec < 10 ? "0" : "") << tm->tm_sec << '\n';
	cout << "Operation count: " << operate_cnt << '\n';
	cout << "Thank you for using my Rubik's cube!" << '\n';
}
