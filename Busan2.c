#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>

// �Ķ����
#define LEN_MIN 15	// ���� ����
#define LEN_MAX 50
#define STM_MIN 0	// ������ ü��
#define STM_MAX 5
#define PROB_MIN 10	// Ȯ��
#define PROB_MAX 90
#define AGGRO_MIN 0	// ��׷� ����
#define AGGRO_MAX 5

// ������ �̵� ����
#define MOVE_LEFT 1
#define MOVE_STAY 0

// ������ ���� ���
#define ATK_NONE 0
#define ATK_CITIZEN 1
#define ATK_DONGSEOK 2

// ������ �ൿ
#define ACTION_REST 0
#define ACTION_PROVOKE 1
#define ACTION_PULL 2

void intro(void) {	// ��Ʈ��
	printf("~ ");
	Sleep(300);
	printf("�� ");
	Sleep(300);
	printf("�� ");
	Sleep(300);
	printf("�� ");
	Sleep(300);
	printf("~\n\n");
	Sleep(300);
	printf("����κ���..\n");
	Sleep(300);
	printf("�ù��� ���Ѷ�!\n\n");
}

int main(void) {
	srand((unsigned int)time(NULL));

	intro();

	//������ ���̿� Ȯ��p(%)�� �Է� �޴´�.
	//�߸��� �Է��� ������ ���α׷� ����
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

	//������ �ʱ� ���¸� ����Ѵ�. (0~lne-1)
	//�����ʺ��� ������(M)len-2, ����(Z)len-3, �� ĭ('')2��, �ù�(C)len-6
	//�迭 ���x
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

		//���α׷� ����
		//4�ʸ��� �ù� �̵�, ���� �̵�, ���� ���, �ù�, ���� ���� ���
		//Windows.h:Sleep(millis);
		//<Windows.h>

		//1-4. �ù� �̵�
		//(100-p)% Ȯ���� �������� 1ĭ �̵��ϰų�, p% Ȯ���� ���ڸ��� ���
		//p�� �������� ���� ���ɼ� ����, p�� �������� ���� ���ɼ� ����(���� ����)
		int cr = rand() % 100 + 1;
		if (cr <= 100 - p) {
			C--;
		}

		//1-5. ���� �̵�
		//����� 2�� �ֱ�� ������
		//1���� p% Ȯ���� �������� 1ĭ �̵��ϰų� (100-p)% Ȯ���� ���ڸ��� ���
		//2���� �ƹ��͵� ���� ����
		//3���� p% Ȯ���� �������� 1ĭ �̵��ϰų� (100-p)% Ȯ���� ���ڸ��� ���
		//4���� �ƹ��͵� ���� ���� ...
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


		//1-2, 1-3. ���
		//�� �ϸ��� 
		//1-2. ���� ���� ���
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

		//1-3. �ù�, ���� ���� ���
		//�ù� ���� ���
		if (cr <= 100 - p) {
			printf("citizen : %d -> %d\n", C + 1, C);
		}
		else {
			printf("citizen : stay %d\n", C);
		}

		//���� ¦���� ���� ���
		if (turn % 2 == 0) {
			printf("zombie : stay %d (cannot move)\n\n\n", Z);
		}
		else {
			//���� Ȧ���� ���� ���
			if (zr <= p) {
				printf("zombie : %d -> %d\n\n\n", Z + 1, Z);
			}
			else {
				printf("zombie : stay %d\n\n\n", Z);
			}
		}
		turn++;

		//�ù��� ���� ��(1�� ��)�� �����ϸ� ���� ����
		if (C == 1) {
			printf("SUCCESS!");
			break;
		}
		//���� �̵��� ��, �ù� �ٷ� �� ĭ�� ���������� �ù��� ����ϰ� ���� ����
		if (Z == C + 1) {
			printf("GAME OVER!");
			break;
		}
		//millis �и��� ���� ���
		Sleep(4000);
	}
	//�ƿ�Ʈ��

	return 0;
}
