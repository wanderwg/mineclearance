#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int Menu() {
	printf("***********************\n");
	printf("       ɨ����Ϸ       \n");
	printf(" 1.��ʼ��Ϸ 0.������Ϸ \n");
	printf("***********************\n");
	printf("   ����������ѡ��    \n");
	int choice = 0;
	scanf("%d", &choice);
	return choice;
}

#define MAX_ROW 9
#define MAX_COL 9
#define MINE_COUNT 10

void PrintMap(char map[MAX_ROW][MAX_COL]) {//��ӡ��ͼ
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
	//���ݵ�ǰλ���ж���Χ�˸������м������ף�����������ָ��µ�show_map��
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
	if (n == 0) {//��ǰλ����Χ����Ϊ0ʱ��չ
		show_map[row][col] = ' ';//��չ��λ�ô�ӡΪ�ո�
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
	//����show_map��Ҫ����Ϊ*
	for (int row = 0; row < MAX_ROW; ++row) {
		for (int col = 0; col < MAX_COL; ++col) {
			show_map[row][col] = '*';
		}
	}
	//����mine_map��Ҫ����������ɸ�����
	//ʹ��0��ʾ���ǵ��ף�1��ʾ�ǵ���
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
			continue;//��λ���Ѿ��ǵ��ף���Ҫ��������
		}
		mine_map[row][col] = '1';
		--n;
	}
}

void Game() {
	//������ͼ������ʼ��
	char show_map[MAX_ROW][MAX_COL];
	char mine_map[MAX_ROW][MAX_COL];
	
	
	Init(show_map,mine_map);
	//��ӡ��ͼ
	while (1) {
		PrintMap(show_map);
		PrintMap(mine_map);
		printf("������һ������(row,col):");
		int row = 0;
		int col = 0;
		scanf("%d %d", &row, &col);
		system("cls");//����
		if (row < 0 || row >= MAX_ROW || col < 0 || col >= MAX_COL) {
			printf("�������벻�Ϸ������������룡\n");
			continue;
		}
		if (show_map[row][col] != '*') {
			printf("�������λ���Ѿ��������ˣ����������룡\n");
			continue;
		}
		//�ж��Ƿ��ǵ���
		if (mine_map[row][col] == '1') {
			printf("��Ϸ�������ٽ�������\n");
			PrintMap(mine_map);
			break;
		}
		//�ж��Ƿ�ʤ��
		int n = Not_Showed(show_map,mine_map);
		if (n == MINE_COUNT) {
			printf("��Ӯ�ˣ�\n");
			PrintMap(mine_map);
			break;
		}
		//ͳ�Ƶ�ǰλ����Χ���׵ĸ���
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
			printf("������������������0��1\n");
		}
	}
	system("pause");
	return 0;
}
