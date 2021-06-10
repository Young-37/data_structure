# data_structure
multimedia data structure assignment

## 환경
Linux 서버(학과 서버), vi Editor   

<hr/>

## Assignment #1
### 두 행렬의 곱(MXN) 구하기
- M(axb)과 N(bxc)은 단순연결리스트 구조
- 각 행렬의 성분들은 1 ~ 10,000 사이의 난수 값
- 수행 결과는 L에 저장   

## Assignment #2
### 다항식의 곱 multPoly() 구현 
- 우선순위 {}, () 고려하기
- 띄어쓰기 고려 X
- 다항식과 다항식 사이에는 * 연산자만 고려
- ax^b 에서 a, b는 모두 자연수
- 다항식은 차수에 상관없이 입력됨
- 입력 ex: (3x^7+4x^2-1)*{{(5x^4-3x^2+7)*(3x^3-4x^2)}*(2x^7-3x^1+9)}
- 다항식 구조
![2_linkedlist](https://user-images.githubusercontent.com/67675422/120058213-53dadb00-c084-11eb-9cc0-e19b59981b8e.jpg)
   
## Assignment #3
### 원형 이중연결리스트 이용, 가위바위보 프로그램 작성
- 사용자가 이기면 win +1 & 오른쪽 노드 이동, 지면 lose +1 & 왼쪽 노드로 이동
- win >= 2이면 win 0으로 변경 후 현재 노드 양쪽에 새로운 노드 삽입
- lose >= 2이면 현재 노드 삭제
- 노드 0개 되면 종료
- 노드 구조
![3_circular](https://user-images.githubusercontent.com/67675422/120058522-61916000-c086-11eb-83f1-0fe00bb980ab.jpg)
   
## Assignment #4
### 연결리스트 기반 multi-queue 구현
- 각각의 sub Queue는 다른 sub Queue 침범 불가능
- s(전체 큐의 최대 크기) * 3 크기만큼 루프 실행
- 루프: 랜덤으로 사용할 큐 선택, 1(=enQueue) 또는 2(=deQueue) 랜덤으로 실행
- multi-queue 구조
![4_multiqueue](https://user-images.githubusercontent.com/67675422/120058582-e9776a00-c086-11eb-8334-6b9e77c0422c.jpg)
   
## Assignment #5
- 이진탐색트리에서 "탐색", "삽입", "삭제" 기능 구현
- 삽입: INSERT abcd
- 탐색: SEARCH abcd
- 삭제: DELETE abcd
- 종료: QUIT
- 종료 전까지 계속 실행
- (삭제 수행 시 버그 존재)
