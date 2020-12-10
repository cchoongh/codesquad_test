## 동작 과정

(`step-1` 수준의 설명은 생략하였습니다.)

* 정육면체를 표현하는 클래스 `Matrix` 구현
 - `print()` 멤버함수
 - 요구사항에 맞도록 구현된 `rotateLeft*()`와 `rotateRight*()` 멤버함수
  + 내부적으로는 `std::rotate`함수를 이용하여 구현하였음.
    
    행(row)인 경우는 간단하게 `std::rotate`를 사용함.
    
    ```
    void rotateLeftTopRow() {
			string& top_row = matrix_[0];
			rotate(top_row.begin(), top_row.begin() + 1, top_row.end());
		};
    ```
    
    열(column)인 경우, 가로로 변환하여 `get`한 후, `std::rotate`하고 다시 세로로 변환하여 `set`
    
    ```
    void rotateUpLeftColumn() {
			string left_column;
			getColumn(0, left_column);
			rotate(left_column.begin(), left_column.begin() + size_ - 1, left_column.end());
			setColumn(0, left_column);
		};
    ```

* `Matrix`의 객체 `matrix` 생성 후, 초기상태 출력

  ```
  Matrix matrix = Matrix(3);
	matrix.print();
  ```

* 명령어 문자열을 `input`에 받고, 루프를 돌면서 각 문자에 맞는 동작 실행
  - 따옴표(`quotes`)인 경우도 고려한 로직 구현
  
   
    ```
    bool quotes = false;
    
    if (i < input.size() - 1 && input[i + 1] == '\'') {
        quotes = true;
 	   i++;
    }
    ```

## 구동 캡처 화면

![Alt text](/step-2.jpg)
