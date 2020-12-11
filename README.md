## 동작 과정

(`step-2` 수준의 설명은 생략하였습니다.)

* 하나의 루빅스 큐브를 나타내는 `RubikCube`클래스와 큐브의 한 면을 나타내는 `RubikCubeFace`클래스 구현
  - `RubikCubeFace`
    + 상대적으로 상, 하, 좌, 우에 인접해 있는 `RubikCubeFace'객체 포인터를 멤버변수로 가지고 있음.
  
  - `RubikCube`
    + 6개의 'RubikCubeFace'객체를 가지고 있음.
    + 회전시에는 회전하는 면(`MainFace`)과 측면에 있는 모서리(`Edge`)들을 고려하여 회전 함.
      + 예시 및 설명
	
		```
		void rotateFront(bool clock) {
	   		// [A]
			std::string adj_up_edge = front_face_.getAdjacentUpFace()->getRow(size_ - 1);
			std::string adj_left_edge = front_face_.getAdjacentLeftFace()->getColumn(size_ - 1);
			std::string adj_right_edge = front_face_.getAdjacentRightFace()->getColumn(0);	
			std::string adj_down_edge = front_face_.getAdjacentDownFace()->getRow(0);

			// [B]
			if (clock) {
				rotateClockMainFace(front_face_);
				rotateClockAdjacentEdges(adj_up_edge, adj_left_edge, adj_right_edge, adj_down_edge);
			} else {
				rotateUnclockMainFace(front_face_);
				rotateUnclockAdjacentEdges(adj_up_edge, adj_left_edge, adj_right_edge, adj_down_edge);
			}
			
			// [C]
			front_face_.getAdjacentUpFace()->setRow(size_ - 1, adj_up_edge);
			front_face_.getAdjacentLeftFace()->setColumn(size_ - 1, adj_left_edge);
			front_face_.getAdjacentRightFace()->setColumn(0, adj_right_edge);
			front_face_.getAdjacentDownFace()->setRow(0, adj_down_edge);
		}
		```
	
		[A]: `MainFace`의 인접한 모서리들을 불러옴.
	
		[B]: 시계방향 플래그에 맞게 `MainFace`와 인접한 `Edge`들을 회전시킴.
	
		[C]: 회전된 `Edge`들을 `set`


## 구동 캡처 화면

( ※※※※※

![Alt text](/step-3_2.jpg)

위 사진과 같이, 올려주신 참고링크에 있는 큐브시뮬레이션 동작을 참고해서 구현하였고,

위의 시뮬레이션과 같이 전개도로 표현하여 루빅스 큐브의 상태를 출력하였습니다.)

![Alt text](/step-3.jpg)
