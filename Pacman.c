#pragma warning(disable:4996)
#include <stdio.h>                            // print 함수 
#include <conio.h>                            // 콘솔 입출력(kbhit(), getch), 방향키 
#include <windows.h>                          // sleep() 함수, System("cls") 운영체제 , 색깔
#include <time.h>                             // Null, time_t (시간)
#include <process.h>                          // 스레드(헤더파일


// Monster Speed
#define Flash 60                             // 속도는(10~100)

// 팩맨 몬스터 
#define MosteR 1                             // 몬스터 = 1 
#define PizzA 0                              // 팩맨   = 0

// 방향키 
#define UP 0                                 // 위
#define DOWN 1                               // 아래
#define LEFT 2                               // 왼쪽
#define RIGHT 3                              // 오른쪽 

// 방향키 Code
#define Up 0x48                              // ▲
#define Down 0x50                            // ▼
#define Right 0x4d                           // ◀
#define Left 0x4b                            // ▶

// 변수 
int RandomBox;                               // 랜덤 박스 
int Bomb = 0;                                // 폭탄 
int pacgis = 0;                              // 팩맨 gis                  
int mongis = 0;                              // 몬스터 gis 
int* x = NULL;                               // 팩맨 x 좌표 
int* y = NULL;                               // 팩맨 y 좌표
int* mx = NULL;                              // 몬스터 x 좌표
int* my = NULL;                              // 몬스터 y 좌표
int ending = 0;                              // end 버퍼                  
int point = 0;                               // 쿠기 점수                         
int legend = 0;                              // 최고 점수
char name[20];                               // 플레이어 이름
//system("pause>null");                         any key 누르라는 문자열 delete    

// 함수 
void Map();                                  // 맵 
void pizza(int x, int y);                    // 팩맨 무빙 Sc
void moster(int x, int y);                   // 몬스터 무빙 Sc
void pizzap(int* x, int* y);                 // 팩맨 무빙 void
void mob(int* x, int* y);                    // 몬스터 무빙 void
void shadowpizza(int x, int y);				 // 팩맨 그림자
void shadowmob(int x, int y);                // 몬스터 그림자 
void M(int* x, int* y, int me, int Ruler);   // M void
void start();                                // 시작
void end();                                  // 엔딩 
void color(int design) {                      // 색깔
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), design);
}
// 좌표 
void gotoxy(int Coordinatex, int Coordinatey) {
	COORD Pos = { Coordinatex - 1, Coordinatey - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
// Wall(1)   Cookie(0)   SuperCookie(3)  Bomb(4)  RandomBox(5)(꺠진다...)
int PacManMap[24][22] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1},
	{1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1},
	{1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1},
	{1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1},
	{1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
	{1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1},
	{1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, };

void Map(void) {
	// i, j (24x22) 행렬 
	int i, j;
	// int RandomBox;
	system("cls");

	for (i = 0; i < 24; i++) {
		for (j = 0; j < 22; j++)
		{   // Wall(1) 
			if (PacManMap[i][j] == 1) {
				color(9);
				printf("■");
			}
			// Pacman 
			else if (i == 1 && j == 1) {
				color(6);
				printf("ⓒ");
				legend += 10;
			}
			// Cookie(0)
			else if (PacManMap[i][j] == 0) {
				color(15);
				printf("＊");
				legend += 10;
			}
			/*
			// SuperCookie(3)
			else if (PacManMap[i][j] == 3) {
				color(6);
				printf("★");
				legend += 20;
			}
			// Bomb(4)
			else if (PacManMap[i][j] == 4) {
				color(8);
				printf("★");
				Bomb -= 100;
			}
			// RandomBox(5)
			else if (PacManMap[i][j] == 5) {
				color(15);
				printf("?");
				RandomBox = rand() % 10 + 1;
				if (RandomBox % 2 == 0)
					RandomBox += 1000;
				else if (RandomBox % 2 == 1) {
					RandomBox -= 1000;
				}
			}*/
		}
		printf("\n");
	} // Wall exit X 
	gotoxy(1, 1);
}

// 팩맨 무빙 Sc
void pizza(int x, int y) {
	gotoxy(x, y);
	if (pacgis == UP) {
		color(6);
		printf("ⓒ");
	}
	else if (pacgis == DOWN) {
		color(6);
		printf("ⓒ");
	}
	else if (pacgis == LEFT) {
		color(6);
		printf("ⓒ");
	}
	else if (pacgis == RIGHT) {
		color(6);
		printf("ⓒ");
	}
	gotoxy(x, y);
}

// 몬스터 무빙 Sc 
void moster(int x, int y) {

	gotoxy(x, y);
	if (mongis == UP) {
		color(4);
		printf("▣");
	}
	else if (mongis == DOWN) {
		color(4);
		printf("▣");
	}
	else if (mongis == LEFT) {
		color(4);
		printf("▣");
	}
	else if (mongis == RIGHT) {
		color(4);
		printf("▣");
	}
	gotoxy(x, y);
}

// 팩맨 무빙 void 
void pizzap(int* x, int* y) {

	while (1) {
		while (!_kbhit())
		{
			Sleep(50);
		}
		int me = _getch();

		M(x, y, me, PizzA);
		if (*x == *mx && *y == *my)
			break;
		if (point >= legend)
			break;

	}ending = 1;
	return;
}
// 몬스터 무빙 void
void mob(void* mob) {

	while (!ending) {
		// 난수 생성 함수
		srand((unsigned)time(NULL));
		int  me;
		while (1) {
			// 난수 
			int box = rand() % 4;
			if (box == UP) {
				if (PacManMap[*my - 2][*mx / 2] == 1)
					continue;
				else {
					me = Up;
					break;
				}
			}
			else if (box == DOWN) {
				if (PacManMap[*my][*mx / 2] == 1)
					continue;
				else {
					me = Down;
					break;
				}
			}
			else if (box == LEFT) {
				if (PacManMap[*my - 1][*mx / 2 - 1] == 1)
					continue;
				else {
					me = Left;
					break;
				}
			}
			else if (box == RIGHT) {
				if (PacManMap[*my - 1][*mx / 2 + 1] == 1)
					continue;
				else {
					me = Right;
					break;
				}
			}
		}
		M(mx, my, me, MosteR);
		if (*mx == *x && *my == *y)
			ending = 1;
		Sleep(Flash);
	}
}

// 몬스터 그림자 
void shadowmob(int x, int y) {
	gotoxy(x, y);
	color(15);
	//
	if (PacManMap[y - 1][x / 2] == 0)
		printf("  ");


	color(15);
	gotoxy(x, y);
}

//팩맨 그림자
void shadowpizza(int x, int y) {
	gotoxy(x, y);
	if (PacManMap[y - 1][x / 2] == 0)
		printf(" ");

	else PacManMap[y - 1][x / 2] = 2;
	point += 10;
	printf(" \n");
	gotoxy(x, y);
}

// M void 
void M(int* x, int* y, int me, int Ruler) {
	// 그림자 없애기 
	if (Ruler == PizzA)
		shadowpizza(*x, *y);
	else
		shadowmob(*x, *y);

	// 방향키 동작 함수 
	switch (me) {

	case Up:
		if (Ruler == PizzA) pacgis = UP;
		else mongis = UP;
		if (PacManMap[*y - 2][*x / 2] != 1) *y = *y - 1;
		break;

	case Down:
		if (Ruler == PizzA) pacgis = DOWN;
		else mongis = DOWN;
		if (PacManMap[*y][*x / 2] != 1) *y = *y + 1;
		break;

	case Right:
		if (Ruler == PizzA) pacgis = LEFT;
		else mongis = LEFT;
		if (PacManMap[*y - 1][*x / 2 + 1] != 1) *x = *x + 2;
		break;

	case Left:
		if (Ruler == PizzA) pacgis = RIGHT;
		else mongis = RIGHT;
		if (PacManMap[*y - 1][*x / 2 - 1] != 1) *x = *x - 2;
		break;
	default: break;
	}

	if (Ruler == PizzA)
		pizza(*x, *y);
	else
		moster(*x, *y);
}

// 시작 
void start(void) {
	char name[20];
	color(15);
	gotoxy(10, 6); printf("________________________________________\n");
	gotoxy(10, 7); printf("I");
	color(10);
	gotoxy(28, 7); printf("ㅅ");
	color(6);
	gotoxy(30, 7); printf("ㅇ");
	color(9);
	gotoxy(32, 7); printf("ㄱ");
	color(15);
	gotoxy(49, 7); printf("I\n");

	color(15);
	gotoxy(10, 8); printf("I");
	color(11);
	gotoxy(21, 8); printf("C 프로그래밍 프로젝트");
	color(15);
	gotoxy(49, 8); printf("I\n");

	color(15);
	gotoxy(10, 9); printf("I");
	color(14);
	gotoxy(21, 9); printf("Pac Man \n");
	color(14);
	gotoxy(30, 9); printf("Game Project \n");
	color(15);
	gotoxy(49, 9); printf("I\n");

	gotoxy(10, 10); printf("----------------------------------------\n");
	color(9);
	gotoxy(10, 12); printf("            PLAYER NAME INPUT           \n");
	gotoxy(28, 13); scanf("%s", &name);
	gotoxy(10, 14); printf("----------------------------------------\n");
	gotoxy(10, 15); printf("I           Player Name: %s        I", name);
	gotoxy(10, 16); printf("________________________________________\n");

	color(2);
	gotoxy(10, 18); printf("________________________________________\n");
	gotoxy(10, 19); printf("I         게임시작        조작키       I\n");
	gotoxy(10, 20); printf("I         (Any key)         ▲         I\n");
	gotoxy(10, 21); printf("I           Input        ◀ ▼ ▶      I\n");
	gotoxy(10, 22); printf("----------------------------------------\n");
	system("pause>null");
}

// 엔딩 
void end(void) {
	system("cls"); // 끝 화면 
	color(1);
	if (point >= legend) {
		color(15);
		gotoxy(10, 3); printf("________________________________________\n");
		gotoxy(10, 4); printf("I                                      I\n");
		color(11);
		gotoxy(10, 5); printf("I          Y       O       U           I\n");
		gotoxy(10, 6); printf("I      W   I    N     N    E    R      I\n");
		color(15);
		gotoxy(10, 7); printf("I                                      I\n");
		color(11);
		gotoxy(10, 8); printf("I         ^-^     ^-^     ^-^          I\n");
		color(15);
		gotoxy(10, 9); printf("I                                      I\n");
		color(5);
		gotoxy(10, 10); printf("I                                      I\n");
		gotoxy(10, 11); printf("I         Point           %d$        I\n", point);
		color(15);
		gotoxy(10, 12); printf("----------------------------------------\n");
		system("pause>null");
	}
	else
	{
		color(8);
		gotoxy(10, 3); printf("________________________________________\n");
		gotoxy(10, 4); printf("I                                      I\n");
		color(12);
		gotoxy(10, 5); printf("I      G       A       M       E       I\n");
		gotoxy(10, 6); printf("I      0       V       E       R       I\n");
		color(8);
		gotoxy(10, 7); printf("I                                      I\n");
		color(12);
		gotoxy(10, 8); printf("I         TmT     TmT     TmT          I\n");
		color(8);
		gotoxy(10, 9); printf("I                                      I\n");
		color(5);
		gotoxy(10, 10); printf("I                                      I\n");
		gotoxy(10, 11); printf("I         Point           %d$         I\n", point);
		color(8);
		gotoxy(10, 12); printf("----------------------------------------\n");
		system("pause>null");
	}
}

int main() {

	// 위치
	int Coordinatex = 3;
	int Coordinatey = 2;
	int Mosterx = 15;
	int Mostery = 13;

	// 좌표 값 초기화 
	x = &Coordinatex;
	y = &Coordinatey;
	mx = &Mosterx;
	my = &Mostery;


	start();                       // 콘솔창 시작 
	Map();                         // 맵
	_beginthread(mob, 0, 0);       // 몬스터 무빙
	pizzap(x, y);                  // 팩맨 무빙 
	end();                         // 콘솔창 엔딩 
	system("pause");               // ㅂ_ㅂ

	return 0;
}

