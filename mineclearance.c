#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int Menu() {
	printf("***********************\n");
	printf("       扫雷游戏       \n");
	printf(" 1.开始游戏 0.结束游戏 \n");
	printf("***********************\n");
	printf("   请输入您的选择：    \n");
	int choice = 0;
	scanf("%d", &choice);
	return choice;
}

#define MAX_ROW 9
#define MAX_COL 9
#define MINE_COUNT 10

void PrintMap(char map[MAX_ROW][MAX_COL]) {//打印地图
	for (int i = 0; i < MAX_COL; ++i) {
		printf("   %d", i);
	}
	printf("\n");
	printf("  ");
	for (int i = 0; i < MAX_COL; ++i) {
		printf("----");
	}
	printf("\n");
	for (int row = 0; row < MAX_ROW; ++row) {
		printf("%d|", row);
		for (int col = 0; col < MAX_COL; ++col) {
			printf(" %c |", map[row][col]);
		}
		printf("\n");
		if (row != MAX_ROW - 1) {
			printf("  ---|---|---|---|---|---|---|---|---|\n");
		}
		if (row == MAX_ROW - 1) {
			printf("  ------------------------------------\n");
		}
	}
}
int UpdateShowMap(int row,int col,char show_map[MAX_ROW][MAX_COL],
	char mine_map[MAX_ROW][MAX_COL]) {
	//根据当前位置判定周围八个格子有几个地雷，并将这个数字更新到show_map中
	int mine_count = 0;
	if (row - 1 >= 0 && col - 1 >= 0 && row - 1 < MAX_ROW
		&&col - 1 < MAX_COL&&mine_map[row - 1][col - 1] == '1') {
		++mine_count;
	}
	if (row - 1 >= 0 && col >= 0 && row - 1 < MAX_ROW
		&&col < MAX_COL&&mine_map[row - 1][col] == '1') {
		++mine_count;
	}
	if (row - 1 >= 0 && col + 1 >= 0 && row - 1 < MAX_ROW
		&&col + 1 < MAX_COL&&mine_map[row - 1][col + 1] == '1') {
		++mine_count;
	}
	if (row >= 0 && col - 1 >= 0 && row < MAX_ROW
		&&col - 1 < MAX_COL&&mine_map[row][col - 1] == '1') {
		++mine_count;
	}
	if (row >= 0 && col + 1 >= 0 && row < MAX_ROW
		&&col + 1 < MAX_COL&&mine_map[row][col + 1] == '1') {
		++mine_count;
	}
	if (row + 1 >= 0 && col - 1 >= 0 && row + 1 < MAX_ROW
		&&col - 1 < MAX_COL&&mine_map[row + 1][col - 1] == '1') {
		++mine_count;
	}
	if (row + 1 >= 0 && col >= 0 && row + 1 < MAX_ROW
		&&col < MAX_COL&&mine_map[row + 1][col] == '1') {
		++mine_count;
	}
	if (row + 1 >= 0 && col + 1 >= 0 && row + 1 < MAX_ROW
		&&col + 1 < MAX_COL&&mine_map[row + 1][col + 1] == '1') {
		++mine_count;
	}
	return mine_count;
}
void Extend_Board(int row, int col, char show_map[MAX_ROW][MAX_COL],
	char mine_map[MAX_ROW][MAX_COL]) {
	int n = 0;
	n = UpdateShowMap(row,col,show_map, mine_map);
	if (n == 0) {//当前位置周围雷数为0时扩展
		show_map[row][col] = ' ';//扩展的位置打印为空格
		if (row - 1 >= 0 && col - 1 >= 0 && row - 1 < MAX_ROW
			&&col - 1 < MAX_COL&&mine_map[row - 1][col - 1] == '0'
			&&show_map[row - 1][col - 1] == '*') {
			Extend_Board(row - 1, col - 1,show_map, mine_map);
		}
		if (row - 1 >= 0 && col >= 0 && row - 1 < MAX_ROW
			&&col < MAX_COL&&mine_map[row - 1][col] == '0'
			&&show_map[row - 1][col] == '*') {
			Extend_Board(row - 1, col,show_map, mine_map);
		}
		if (row - 1 >= 0 && col + 1 >= 0 && row - 1 < MAX_ROW
			&&col + 1 < MAX_COL&&mine_map[row - 1][col + 1] == '0'
			&&show_map[row - 1][col + 1] == '*') {
			Extend_Board(row - 1, col + 1,show_map, mine_map);
		}
		if (row >= 0 && col - 1 >= 0 && row  < MAX_ROW
			&&col - 1 < MAX_COL&&mine_map[row][col - 1] == '0'
			&&show_map[row][col - 1] == '*') {
			Extend_Board(row, col - 1,show_map, mine_map);
		}
		if (row  >= 0 && col + 1 >= 0 && row  < MAX_ROW
			&&col + 1 < MAX_COL&&mine_map[row][col + 1] == '0'
			&&show_map[row][col + 1] == '*') {
			Extend_Board(row, col + 1,show_map, mine_map);
		}
		if (row + 1 >= 0 && col - 1 >= 0 && row + 1 < MAX_ROW
			&&col - 1 < MAX_COL&&mine_map[row + 1][col - 1] == '0'
			&&show_map[row + 1][col - 1] == '*') {
			Extend_Board(row + 1, col - 1,show_map, mine_map);
		}
		if (row + 1 >= 0 && col  >= 0 && row + 1 < MAX_ROW
			&&col < MAX_COL&&mine_map[row + 1][col] == '0'
			&&show_map[row + 1][col] == '*') {
			Extend_Board(row + 1, col,show_map, mine_map );
		}
		if (row + 1 >= 0 && col + 1 >= 0 && row + 1 < MAX_ROW
			&&col + 1 < MAX_COL&&mine_map[row + 1][col + 1] == '0'
			&&show_map[row + 1][col + 1] == '*') {
			Extend_Board(row + 1, col + 1,show_map, mine_map);
		}
	}
	else show_map[row][col] = '0' + n;
}
int Not_Showed(char show_map[MAX_ROW][MAX_COL],char mine_map[MAX_ROW][MAX_COL]) {
	int not_showed_count = 0;
	for (int row = 0; row < MAX_ROW; ++row) {
		for (int col = 0; col < MAX_COL; ++col) {
			if (show_map[row][col] == '*'){
				++not_showed_count;
			}
		}
	}
	return not_showed_count;
}

void Init(char show_map[MAX_ROW][MAX_COL],
	char mine_map[MAX_ROW][MAX_COL]) {
	//对于show_map需要都设为*
	for (int row = 0; row < MAX_ROW; ++row) {
		for (int col = 0; col < MAX_COL; ++col) {
			show_map[row][col] = '*';
		}
	}
	//对于mine_map需要随机生成若干个地雷
	//使用0表示不是地雷，1表示是地雷
	for (int row = 0; row < MAX_ROW; ++row) {
		for (int col = 0; col < MAX_COL; ++col) {
			mine_map[row][col] = '0';
		}
	}
	int n = MINE_COUNT;
	while (n > 0) {
		int row = rand() % MAX_ROW;
		int col = rand() % MAX_COL;
		if (mine_map[row][col] == '1') {
			continue;//该位置已经是地雷，需要重新生成
		}
		mine_map[row][col] = '1';
		--n;
	}
}

void Game() {
	//创建地图，并初始化
	char show_map[MAX_ROW][MAX_COL];
	char mine_map[MAX_ROW][MAX_COL];
	
	
	Init(show_map,mine_map);
	//打印地图
	while (1) {
		PrintMap(show_map);
		PrintMap(mine_map);
		printf("请输入一组坐标(row,col):");
		int row = 0;
		int col = 0;
		scanf("%d %d", &row, &col);
		system("cls");//清屏
		if (row < 0 || row >= MAX_ROW || col < 0 || col >= MAX_COL) {
			printf("您的输入不合法，请重新输入！\n");
			continue;
		}
		if (show_map[row][col] != '*') {
			printf("您输入的位置已经被翻开了，请重新输入！\n");
			continue;
		}
		//判定是否是地雷
		if (mine_map[row][col] == '1') {
			printf("游戏结束，再接再厉！\n");
			PrintMap(mine_map);
			break;
		}
		//判定是否胜利
		int n = Not_Showed(show_map,mine_map);
		if (n == MINE_COUNT) {
			printf("您赢了！\n");
			PrintMap(mine_map);
			break;
		}
		//统计当前位置周围的雷的个数
		Extend_Board(row, col,show_map, mine_map);
	}
}
int main() {
	srand((unsigned int)time(0));
	while (1) {
		int choice = Menu();
		if (choice == 1) {
			Game();
		}
		else if (choice == 0) {
			printf("goodbye\n");
			break;
		}
		else {
			printf("您的输入有误！请输入0或1\n");
		}
	}
	system("pause");
	return 0;
}
