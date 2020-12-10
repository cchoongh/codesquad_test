#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

class Matrix {
	public:
		Matrix(int size) : size_(size) {
			matrix_ = {"RRW", "GCW", "GBB"};
		};

		void print() {
			for (string row : matrix_) {
				string buf;

				for (char ch : row) {
					buf += ch; 
					buf += ' ';
				}

				buf.pop_back();
				cout << buf << '\n';;
			}
			
			cout << '\n';
		}

		void rotateLeftTopRow() {
			string& top_row = matrix_[0];
			rotate(top_row.begin(), top_row.begin() + 1, top_row.end());
		};
		void rotateRightTopRow() {
			string& top_row = matrix_[0];
			rotate(top_row.begin(), top_row.begin() + size_ - 1, top_row.end());
		};

		void rotateLeftBottomRow() {
			string& bottom_row = matrix_[size_ - 1];
			rotate(bottom_row.begin(), bottom_row.begin() + 1, bottom_row.end());
		};
		void rotateRightBottomRow() {
			string& bottom_row = matrix_[size_ - 1];
			rotate(bottom_row.begin(), bottom_row.begin() + size_ - 1, bottom_row.end());
		};

		void rotateUpLeftColumn() {
			string left_column;
			getColumn(0, left_column);
			rotate(left_column.begin(), left_column.begin() + size_ - 1, left_column.end());
			setColumn(0, left_column);
		};
		void rotateDownLeftColumn() {
			string left_column;
			getColumn(0, left_column);
			rotate(left_column.begin(), left_column.begin() + 1, left_column.end());
			setColumn(0, left_column);
		};

		void rotateUpRightColumn() {
			string right_column;
			getColumn(size_ - 1, right_column);
			rotate(right_column.begin(), right_column.begin() + size_ - 1, right_column.end());
			setColumn(size_ - 1, right_column);
		};
		void rotateDownRightColumn() {
			string right_column;
			getColumn(size_ - 1, right_column);
			rotate(right_column.begin(), right_column.begin() + 1, right_column.end());
			setColumn(size_ - 1, right_column);
		};

	private:
		const int size_;
		vector<string> matrix_;

		void setColumn(int col, const string& input) {
			for (int i = 0; i < size_; i++) {
				matrix_[i][col] = input[i];
			}
		}
		void getColumn(int col, string& output) {
			for (int i = 0; i < size_; i++) {
				output.push_back(matrix_[i][col]);
			}
		}
};

int main() {
	Matrix matrix = Matrix(3);
	matrix.print();

	string input;
	bool is_end = false; // in case that 'Q' is in instruction string

	while (!is_end && cout << "CUBE> " && cin >> input && input != "Q") {
		for (int i = 0; i < input.size(); i++) {
			if (is_end) {
				cerr << "Some instructions exist after 'Q', these are ignored." << '\n';
				break;
			}

			char inst = input[i]; // instruction
			bool quotes = false;

			if (i < input.size() - 1 && input[i + 1] == '\'') {
				quotes = true;
				i++;
			}

			cout << '\n' << inst << (quotes ? "'" : "") << '\n';

			switch(inst) {
				case 'U':
					if (quotes)
						matrix.rotateRightTopRow();
					else
						matrix.rotateLeftTopRow();
					break;

				case 'B':
					if (quotes)
						matrix.rotateLeftBottomRow();
					else
						matrix.rotateRightBottomRow();
					break;

				case 'R':
					if (quotes)
						matrix.rotateUpRightColumn();
					else
						matrix.rotateDownRightColumn();
					break;

				case 'L':
					if (quotes)
						matrix.rotateDownLeftColumn();
					else
						matrix.rotateUpLeftColumn();
					break;

				case 'Q': // in case that 'Q' is in instruction string
					is_end = true;
					break;

				default:
					cerr << "Ignore bad instruction: " << inst << '\n';
					break;
			}

			matrix.print();
		}

		input.clear();
	}

	cout << "Bye~" << '\n';
	return 0;
}
