#include <iostream>
#include <string>
#include <fstream>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
using namespace std;

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

int** loadMap(int& row, int& col);
void showMap(int** (&map), const int row, const int col);
void deleteMap(int** (&map), const int row);
int Menu();
void menu1(int*** (&movie_map), int movie_num, int** movie_arr, string* movie_name);
void menu2(int*** (&movie_map), int movie_num, int** movie_arr, string* movie_name);
void menu3(int*** (&movie_map), int movie_num, int** movie_arr, string* movie_name);

int main() {

	cout << "202011377 지상준\n" << endl;

	// movie info load
	ifstream fin("movie.txt");

	if (!fin.is_open()) {
		cerr << "파일 오픈 실패";
		exit(0);
	}

	int movie_num = 0;
	fin >> movie_num;

	string* movie_name = new string[movie_num];

	int** movie_arr = new int* [movie_num];

	for (int i = 0; i < movie_num; i++) {
		movie_arr[i] = new int[2];
	}

	for (int i = 0; i < movie_num; i++) {
		fin >> movie_name[i] >> movie_arr[i][0] >> movie_arr[i][1];
	}

	int*** movie_map = new int** [movie_num];

	for (int i = 0; i < movie_num; i++) {
		movie_map[i] = loadMap(movie_arr[i][0], movie_arr[i][1]);
	}

	//showMap(movie_map[0], movie_arr[0][0], movie_arr[0][1]);

	// menu start
	
	int menu = 0;

	while (menu != 4) {
		menu = Menu();
		if (menu == 1) {

			menu1(movie_map, movie_num, movie_arr, movie_name);

		}
		else if (menu == 2) {

			menu2(movie_map, movie_num, movie_arr, movie_name);

		}
		else if (menu == 3) {

			menu3(movie_map, movie_num, movie_arr, movie_name);

		}
	}

	delete[] movie_name;
	movie_name = nullptr;

	for (int i = 0; i < movie_num; i++)
	{
		deleteMap(movie_map[i], movie_arr[i][0]);
	}
	delete[] movie_map;
	movie_map = nullptr;

	deleteMap(movie_arr, movie_num);

	_CrtDumpMemoryLeaks();

	return 0;
}

int** loadMap(int& row, int& col) {

	int** map = new int* [row];

	for (int i = 0; i < row; i++) {
		map[i] = new int[col];
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			map[i][j] = 0;
		}
	}
	

	return map;
}

void showMap(int** (&map), const int row, const int col) {
	for (int i = 0; i < col; i++) {
		cout << '\t' << i + 1;
	}
	cout << endl << endl;

	for (int i = 0; i < row; i++) {
		cout << static_cast<char>('A' + i) << '\t';
		for (int j = 0; j < col; j++) {
			cout << (map[i][j] ? "●" : "○") << '\t';
		}
		cout << endl << endl;
	}
}

void deleteMap(int** (&map), const int row) {
	for (int i = 0; i < row; i++) {
		delete[] map[i];
	}
	delete[] map;
	map = nullptr;
}

int Menu() {
	int menu = 0;
	system("cls");
	cout << "202011377 지상준" << endl << endl;
	cout << "============ 지상준 시네마 ============" << endl;
	cout << "1) 영화 예매  2) 예매 취소 3) 예매 확인 4) 종료" << endl << endl;
	while (true) {
		cout << "메뉴를 선택하세요 : ";
		cin >> menu;
		if (menu > 0 && menu < 5) {
			break;
		}
		else {
			system("cls");
			cout << "202011377 지상준" << endl << endl;
			cout << "============ 지상준 시네마 ============" << endl;
			cout << "1) 영화 예매  2) 예매 취소 3) 예매 확인 4) 종료" << endl << endl;
			cout << "***올바른 메뉴를 입력하세요***" << endl << endl;
		}
	}

	return menu;
}

void menu1(int*** (&movie_map), int movie_num, int** movie_arr, string* movie_name) {
	system("cls");
	cout << "202011377 지상준\n" << endl;
	cout << "============ 영화 예매 ============" << endl;

	int r_num;
	for (int i = 0; i < movie_num; i++) {
		int count = 0;
		for (int x = 0; x < movie_arr[i][0]; x++) {
			for (int y = 0; y < movie_arr[i][1]; y++) {
				if (movie_map[i][x][y] == 0)
					count++;
			}
		}
		if (count == 0) {
			cout << i + 1 << ") " << movie_name[i] << "\t\t" << "매진" << endl;
		}
		else {
			cout << i + 1 << ") " << movie_name[i] << "\t\t" << count << "/" << movie_arr[i][0] * movie_arr[i][1] << endl;
		}
	}

	cout << endl << "예매할 영화를 선택하세요 : ";
	cin >> r_num;
	while (!(0 < r_num && r_num < movie_num + 1)) {
		cout << "올바른 예매할 영화를 선택하세요 : ";
		cin >> r_num;
	}
	r_num = r_num - 1;

	system("cls");
	cout << "202011377 지상준\n" << endl;
	cout << "============ 영화 예매 ============" << endl;
	showMap(movie_map[r_num], movie_arr[r_num][0], movie_arr[r_num][1]);

	int count = 0;
	for (int x = 0; x < movie_arr[r_num][0]; x++) {
		for (int y = 0; y < movie_arr[r_num][1]; y++) {
			if (movie_map[r_num][x][y] == 0)
				count++;
		}
	}

	if (count == 0) {
		cout << "매진된 영화입니다!";
		system("pause");
	}
	else {
		while (true) {
			cout << "예매할 좌석을 선택하세요(ex. A1) : ";
			char x, y;
			cin >> x >> y;

			if (x - 'A' >= 0 && x - 'A' <= movie_arr[r_num][0] - 1 && y - '1' >= 0 && y - '1' <= movie_arr[r_num][1] - 1) {
				if (movie_map[r_num][x - 'A'][y - '1'] == 1) {
					cout << "이미 예약된 자리입니다.\n";
				}
				else {
					movie_map[r_num][x - 'A'][y - '1'] = 1;
					cout << "예약이 완료되었습니다.\t" << "예약 번호 : " << r_num << x - 'A' << y - '1' << endl;
				}
				cout << endl;
				system("pause");
				break;
			}
			else {
				cout << "올바른 좌석번호를 입력하세요!\n";
			}
		}
	}
}

void menu2(int*** (&movie_map), int movie_num, int** movie_arr, string* movie_name) {
	system("cls");
	cout << "202011377 지상준\n" << endl;
	cout << "============ 예매 취소 ============" << endl;
	cout << "취소할 예약 번호를 입력해주세요 : ";
	int reserve_num;
	cin >> reserve_num;
	int page, row, col;
	col = reserve_num % 10;
	page = reserve_num / 100;
	row = ((reserve_num - col) % 100) / 10;
	if (page < movie_num) {
		if (row < movie_arr[page][0] && col < movie_arr[page][1]) {
			if (movie_map[page][row][col] == 1) {
				movie_map[page][row][col] = 0;
				cout << "예약 취소가 완료되었습니다." << endl;
				//showMap(movie_map[page], movie_arr[page][0], movie_arr[page][1]);
			}
			else {
				cout << endl << "존재하지 않는 예약 번호입니다." << endl;
			}
		}
		else {
			cout << endl << "존재하지 않는 예약 번호입니다." << endl;
		}
	}
	else {
		cout << endl << "존재하지 않는 예약 번호입니다." << endl;
	}
	cout << endl;
	system("pause");
}

void menu3(int*** (&movie_map), int movie_num, int** movie_arr, string* movie_name) {
	system("cls");
	cout << "202011377 지상준\n" << endl;
	cout << "============ 예약 확인 ============" << endl;
	cout << "예약 번호를 입력해주세요 : ";
	int reserve_num;
	cin >> reserve_num;
	int page, row, col;
	col = reserve_num % 10;
	page = reserve_num / 100;
	row = ((reserve_num - col) % 100) / 10;
	if (page < movie_num) {
		if (row < movie_arr[page][0] && col < movie_arr[page][1]) {
			if (movie_map[page][row][col] == 1) {
				cout << "예매하신 영화 : " << movie_name[page] << endl;
				char row_ch = 'A' + row;
				cout << "예매하신 좌석 : " << row_ch << col + 1 << endl;
				cout << "============ 영화 예매 좌석 ============" << endl;
				for (int i = 0; i < movie_arr[page][1]; i++) {
					cout << '\t' << i + 1;
				}
				cout << endl << endl;

				for (int i = 0; i < movie_arr[page][0]; i++) {
					cout << static_cast<char>('A' + i) << '\t';
					for (int j = 0; j < movie_arr[page][1]; j++) {
						cout << (movie_map[page][i][j] ? "★" : "○") << '\t';
					}
					cout << endl << endl;
				}
			}
			else {
				cout << endl << "존재하지 않는 예약 번호입니다." << endl;
			}
		}
		else {
			cout << endl << "존재하지 않는 예약 번호입니다." << endl;
		}
	}
	else {
		cout << endl << "존재하지 않는 예약 번호입니다." << endl;
	}
	cout << endl;
	system("pause");
}
