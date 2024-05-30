#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>

// 파라미터
#define LEN_MIN 15	// 기차 길이
#define LEN_MAX 50
#define STM_MIN 0	// 마동석 체력
#define STM_MAX 5
#define PROB_MIN 10	// 확률
#define PROB_MAX 90
#define AGGRO_MIN 0	// 어그로 범위
#define AGGRO_MAX 5

// 마동석 이동 방향
#define MOVE_LEFT 1
#define MOVE_STAY 0

// 좀비의 공격 대상
#define ATK_NONE 0
#define ATK_CITIZEN 1
#define ATK_DONGSEOK 2

// 마동석 행동
#define ACTION_REST 0
#define ACTION_PROVOKE 1
#define ACTION_PULL 2

void intro(void) {	// 인트로
	printf("~ ");
	Sleep(300);
	printf("부 ");
	Sleep(300);
	printf("산 ");
	Sleep(300);
	printf("헹 ");
	Sleep(300);
	printf("~\n\n");
	Sleep(300);
	printf("좀비로부터..\n");
	Sleep(300);
	printf("시민을 지켜라!\n\n");
}

int main(void) {
	srand((unsigned int)time(NULL));

	intro();

	//열차의 길이와 확률p(%)를 입력 받는다.
	//잘못된 입력을 받으면 프로그램 종료
	int len, p;
	printf("train length(%d~%d)>> ", LEN_MIN, LEN_MAX);
	scanf_s("%d", &len);
	if (len < LEN_MIN || len > LEN_MAX) {
		return 1;
	}
	printf("percentile probability 'p'(%d~%d)>> ", PROB_MIN, PROB_MAX);
	scanf_s("%d", &p);
	if (p < PROB_MIN || p > PROB_MAX) {
		return 1;
	}

	//열차의 초기 상태를 출력한다. (0~lne-1)
	//오른쪽부터 마동석(M)len-2, 좀비(Z)len-3, 빈 칸('')2개, 시민(C)len-6
	//배열 사용x
	int M, Z, C;
	M = len - 2;
	Z = len - 3;
	C = len - 6;
	for (int i = 0; i <= len - 1; i++) {
		printf("#");
	}
	printf("\n");
	for (int i = 0; i <= len - 1; i++) {
		if (i == 0 || i == len - 1) {
			printf("#");
		}
		else if (i == M) {
			printf("M");
		}
		else if (i == Z) {
			printf("Z");
		}
		else if (i == C) {
			printf("C");
		}
		else {
			printf(" ");
		}
	}
	printf("\n");
	for (int i = 0; i <= len - 1; i++) {
		printf("#");
	}
	printf("\n\n");

	int turn = 1;
	while (1) {

		//프로그램 구성
		//4초마다 시민 이동, 좀비 이동, 열차 출력, 시민, 좀비 상태 출력
		//Windows.h:Sleep(millis);
		//<Windows.h>

		//1-4. 시민 이동
		//(100-p)% 확률로 왼쪽으로 1칸 이동하거나, p% 확률로 제자리에 대기
		//p가 낮을수록 성공 가능성 증가, p가 높을수록 실패 가능성 증가(뒷장 참고)
		int cr = rand() % 100 + 1;
		if (cr <= 100 - p) {
			C--;
		}

		//1-5. 좀비 이동
		//좀비는 2턴 주기로 움직임
		//1턴은 p% 확률로 왼쪽으로 1칸 이동하거나 (100-p)% 확률로 제자리에 대기
		//2턴은 아무것도 하지 않음
		//3턴은 p% 확률로 왼쪽으로 1칸 이동하거나 (100-p)% 확률로 제자리에 대기
		//4턴은 아무것도 하지 않음 ...
		int zr;
		if (turn % 2 == 0) {
			zr = 100 - p;
		}
		else {
			zr = rand() % 100 + 1;
			if (zr <= p) {
				Z--;
			}
		}


		//1-2, 1-3. 출력
		//매 턴마다 
		//1-2. 열차 상태 출력
		for (int i = 0; i <= len - 1; i++) {
			printf("#");
		}
		printf("\n");
		for (int i = 0; i <= len - 1; i++) {
			if (i == 0 || i == len - 1) {
				printf("#");
			}
			else if (i == M) {
				printf("M");
			}
			else if (i == Z) {
				printf("Z");
			}
			else if (i == C) {
				printf("C");
			}
			else {
				printf(" ");
			}
		}
		printf("\n");
		for (int i = 0; i <= len - 1; i++) {
			printf("#");
		}
		printf("\n\n");

		//1-3. 시민, 좀비 상태 출력
		//시민 상태 출력
		if (cr <= 100 - p) {
			printf("citizen : %d -> %d\n", C + 1, C);
		}
		else {
			printf("citizen : stay %d\n", C);
		}

		//좀비 짝수턴 상태 출력
		if (turn % 2 == 0) {
			printf("zombie : stay %d (cannot move)\n\n\n", Z);
		}
		else {
			//좀비 홀수턴 상태 출력
			if (zr <= p) {
				printf("zombie : %d -> %d\n\n\n", Z + 1, Z);
			}
			else {
				printf("zombie : stay %d\n\n\n", Z);
			}
		}
		turn++;

		//시민이 왼쪽 끝(1번 열)에 도달하면 구출 성공
		if (C == 1) {
			printf("SUCCESS!");
			break;
		}
		//좀비가 이동한 후, 시민 바로 옆 칸에 도착했으면 시민은 사망하고 구출 실패
		if (Z == C + 1) {
			printf("GAME OVER!");
			break;
		}
		//millis 밀리초 동안 대기
		Sleep(4000);
	}
	//아웃트로

	return 0;
}
