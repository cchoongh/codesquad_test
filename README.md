(최대한 영어를 쓰려고 노력하는데, 영어를 잘 못해서 각 step의 README는 한글로 작성했습니다.)

## 동작 과정

* `word`, `rot(회전수)`, `dir(방향)`변수에 순서대로 입력을 받음.

* 방향이 소문자로 입력됐을 경우를 고려해서 `dir`을 `toupper`함수로 대문자로 만듦.

* 회전방향을 단순화하기위해(즉, 왼쪽방향만 고려) 방향이 오른쪽일 경우 -1을 곱해줌.

  ```rot *= -1;```

* 회전수가 음수이거나, `word`의 길이보다 긴 경우를 고려한 로직 구현

  ```
  while (rot < 0) rot += word.size();
  while (rot > word.size()) rot -= word.size();
  ```

* 마지막으로, C++ 표준함수인 `rotate`를 이용하여 단어를 순환회전 시킴.

  ```
  rotate(word.begin(), word.begin() + rot, word.end());
  ```

## 구동 캡처 화면

![Alt text](/step-1.jpg)
