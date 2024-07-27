#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <thread>
#include <chrono>
#include <random>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h> 
#include <regex> 
#include<fstream>
#include <sstream>
#include <iomanip>
#include<chrono>

using namespace std;


const int  max_num = 1024;//�N���A�����̐ݒ�

auto scoredis(int board[5][4], int step) {
	int point = 0;
	point = board[4][2];
	cout << "�X�R�A" << "\033[3;33m" << point << "\033[m" << "�@�@�@�萔:" << step << endl;
}

//�����s�񂩂�\���`���ւ̕ϊ�
void display(int board[5][4]) {
	int new_x = board[4][0];
	int new_y = board[4][1];
	cout << "+-----+-----+-----+-----+" << endl;
	for (int i = 0; i < 4; i++) {
		cout << "|";
		for (int j = 0; j < 4; j++) {//�ǉ����������̓_�ŕ\��
			if (i == new_x && j == new_y) {
				if (board[i][j] == 0 || board[i][j] == 2 || board[i][j] == 4 || board[i][j] == 8) {	//0,2,4,8�̏ꍇ(0�̏ꍇ�͑��݂��Ȃ�)
					//	cout << "   " << "\033[31m" << board[i][j] << "\033[m " << " | ";
					cout << "   " << "\033[6;31m" << board[i][j] << "\033[m " << "|";
				}
				else if (board[i][j] == 16 || board[i][j] == 32 || board[i][j] == 64) {				//16,32,64�̏ꍇ
					cout << "  " << "\033[6;31m" << board[i][j] << "\033[m " << "|";
				}
				else if (board[i][j] == 128 || board[i][j] == 256 || board[i][j] == 512) {			//128,256,512�̏ꍇ
					cout << " " << "\033[6;31m" << board[i][j] << "\033[m " << "|";
				}
				else if (board[i][j] == 1024 || board[i][j] == 2048) {								//1024,2048�̏ꍇ
					cout << "" << "\033[6;31m" << board[i][j] << "\033[m " << "|";
				}
				else {
					cout << "�G���[�����ċN�����Ă�������" << endl;									//����ȊO�̏ꍇ�G���[
				}
			}
			else {
				if (board[i][j] == 0) {	//0�̏ꍇ
					cout << "     |";
				}
				else if (board[i][j] == 2 || board[i][j] == 4 || board[i][j] == 8) {				//2,4,8�̏ꍇ
					cout << "   " << board[i][j] << " |";
				}
				else if (board[i][j] == 16 || board[i][j] == 32 || board[i][j] == 64) {				//16,32,64�̏ꍇ
					cout << "  " << board[i][j] << " |";
				}
				else if (board[i][j] == 128 || board[i][j] == 256 || board[i][j] == 512) {			//128,256,512�̏ꍇ
					cout << " " << board[i][j] << " |";
				}
				else if (board[i][j] == 1024 || board[i][j] == 2048) {								//1024,2048�̏ꍇ
					cout << "" << board[i][j] << " |";
				}
				else {
					cout << "�G���[�����ċN�����Ă�������" << endl;									//����ȊO�̏ꍇ�G���[
				}
			}
		}
		cout << endl;
		cout << "+-----+-----+-----+-----+" << endl;
	}
}

void cleardisplay(int board[5][4]) {  //�N���A���̕\��
	cout << "+-----+-----+-----+-----+" << endl;
	for (int i = 0; i < 4; i++) {
		cout << "|";
		for (int j = 0; j < 4; j++) {//�ǉ����������̓_�ŕ\��
			if (board[i][j] == 0 || board[i][j] == 2 || board[i][j] == 4 || board[i][j] == 8) {	//0,2,4,8�̏ꍇ
				//	cout << "   " << "\033[31m" << board[i][j] << "\033[m " << " | ";
				cout << "   " << board[i][j] << " |";
			}
			else if (board[i][j] == 16 || board[i][j] == 32 || board[i][j] == 64) {				//16,32,64�̏ꍇ
				cout << "  " << board[i][j] << " |";
			}
			else if (board[i][j] == 128 || board[i][j] == 256 || board[i][j] == 512) {			//128,256,512�̏ꍇ
				cout << " " << board[i][j] << " |";
			}
			else if (board[i][j] == 1024 || board[i][j] == 2048) {								//1024,2048�̏ꍇ
				cout << "" << "\033[6;34m" << board[i][j] << "\033[m " << "|";
			}
			else {
				cout << "�G���[�����ċN�����Ă�������" << endl;									//����ȊO�̏ꍇ�G���[
			}
		}
		cout << endl;
		cout << "+-----+-----+-----+-----+" << endl;
	}
}

auto clearcheck(int checkboard[5][4]) { //�N���A�����𖞂����Ă��邩�̔���
	int clear_check = 1;
	std::vector<int> pair_spacex;
	std::vector<int> pair_spacey;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (checkboard[i][j] == max_num) {
				pair_spacex.push_back(i);
				pair_spacey.push_back(j);
				clear_check = 0;
			}
		}
	}
	return clear_check;
}


int overcheck(int checkboard[5][4]) { //�Q�[���I�[�o�[�����𖞂����Ă��邩�ǂ����̔���
	std::vector<int> pair_spacex;
	std::vector<int> pair_spacey;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (checkboard[i][j] == 0) {
				pair_spacex.push_back(i);
				pair_spacey.push_back(j);
			}
		}
	}
	int over_check = 0;
	if (size(pair_spacex) == 0) {
		over_check = 0;
		return over_check;
	}
	else if (size(pair_spacex) != 0) {
		over_check = 1;
		return over_check;
	}
}

auto add(int baseboard[5][4]) { //������Ԃ̕\���p
	std::vector<int> pair_spacex;
	std::vector<int> pair_spacey;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (baseboard[i][j] == 0) {
				pair_spacex.push_back(i);
				pair_spacey.push_back(j);
			}
		}
	}
	srand(time(0));
	int ad1 = rand() % pair_spacex.size() + 0;
	int ad2 = rand() % 100 + 1;
	if (0 < ad2 && ad2 < 50) {
		baseboard[pair_spacex[ad1]][pair_spacey[ad1]] = 2;
	}
	if (50 <= ad2 && ad2 < 85) {
		baseboard[pair_spacex[ad1]][pair_spacey[ad1]] = 4;
	}
	if (85 <= ad2 && ad2 < 95) {
		baseboard[pair_spacex[ad1]][pair_spacey[ad1]] = 8;
	}
	if (95 <= ad2 && ad2 <= 100) {
		baseboard[pair_spacex[ad1]][pair_spacey[ad1]] = 16;
	}
	return baseboard;
}

int GetRandom(int min, int max){
	return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}



auto add2(int baseboard[5][4], int list[21]) {
	std::vector<int> pair_spacex;
	std::vector<int> pair_spacey;
	std::vector<int> filled;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (baseboard[i][j] == 0) {
				pair_spacex.push_back(i);
				pair_spacey.push_back(j);
			}
			else if (baseboard[i][j] != 0) {
				filled.push_back(baseboard[i][j]);
			}
		}
	}

	srand(time(0));
	int ad1 = rand() % pair_spacex.size() + 0;
	sort(filled.rbegin(), filled.rend());
	int lim1 = 0;
	int lim2 = 1;
	if (filled[0] < 16) {
		lim1 = 9;
	}
	if (filled[0] >= 16 && filled[0] < 64) {
		lim1 = 15;
	}
	if (filled[0] >= 64) {
		lim1 = 20;
	}

	int ad2 = rand() % lim1;
	list[ad2] += 1;
	if (0 <= ad2 && ad2 <= 12) {
		baseboard[pair_spacex[ad1]][pair_spacey[ad1]] = 2;
	}
	else if (12 < ad2 && ad2 <= 16) {
		baseboard[pair_spacex[ad1]][pair_spacey[ad1]] = 4;
	}
	else if (16 < ad2 && ad2 <= 19) {
		baseboard[pair_spacex[ad1]][pair_spacey[ad1]] = 8;
	}
	else if (19 < ad2 && ad2 <= 20) {
		baseboard[pair_spacex[ad1]][pair_spacey[ad1]] = 16;
	}
	baseboard[4][0] = pair_spacex[ad1];
	baseboard[4][1] = pair_spacey[ad1];
	return baseboard;
}

string keypattern(string key_in) {//�ړ������̕\��
	string pattern;
	while (1) {
		if (key_in == "w") {
			pattern = "��";
			break;
		}
		else if (key_in == "s") {
			pattern = "��";
			break;
		}
		else if (key_in == "a") {
			pattern = "��";
			break;
		}
		else if (key_in == "d") {
			pattern = "�E";
			break;
		}
	}
	return pattern;
}

auto Move_up(int baseboard[5][4]) {//��ړ��֐�
	for (int l = 0; l < 2; l++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 3; k++) {
				for (int i = 0; i < 3; i++) {
					if (baseboard[i][j] == 0) {
						baseboard[i][j] = baseboard[i + 1][j];
						baseboard[i + 1][j] = 0;
					}
				}
			}
		}
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 3; k++) {
				for (int i = 0; i < 3; i++) {
					if (baseboard[i][j] == baseboard[i + 1][j]) {
						baseboard[4][2] += baseboard[i][j];
						baseboard[i][j] = baseboard[i][j] * 2;
						baseboard[i + 1][j] = 0;
					}
				}
			}
		}
	}
	return baseboard;
}

auto Move_down(int baseboard[5][4]) {//���ړ��֐�
	for (int l = 0; l < 2; l++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 3; k++) {
				for (int i = 3; i > 0; i--) {
					if (baseboard[i][j] == 0) {
						baseboard[i][j] = baseboard[i - 1][j];
						baseboard[i - 1][j] = 0;
					}
				}
			}
		}
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 3; k++) {
				for (int i = 3; i > 0; i--) {
					if (baseboard[i][j] == baseboard[i - 1][j]) {
						baseboard[4][2] += baseboard[i][j];
						baseboard[i][j] = baseboard[i][j] * 2;
						baseboard[i - 1][j] = 0;
					}
				}
			}
		}
	}
	return baseboard;
}

auto Move_left(int baseboard[5][4]) {//���ړ��֐�
	for (int l = 0; l < 2; l++) {
		for (int i = 0; i < 4; i++) {
			for (int k = 0; k < 3; k++) {
				for (int j = 0; j < 3; j++) {
					if (baseboard[i][j] == 0) {
						baseboard[i][j] = baseboard[i][j + 1];
						baseboard[i][j + 1] = 0;
					}
				}
			}
		}
		for (int i = 0; i < 4; i++) {
			for (int k = 0; k < 3; k++) {
				for (int j = 0; j < 3; j++) {
					if (baseboard[i][j] == baseboard[i][j + 1]) {
						baseboard[4][2] += baseboard[i][j];
						baseboard[i][j] = baseboard[i][j] * 2;
						baseboard[i][j + 1] = 0;
					}
				}
			}
		}
	}
	return baseboard;
}

auto Move_right(int baseboard[5][4]) { //�E�ړ��֐�
	for (int l = 0; l < 2; l++) {
		for (int i = 0; i < 4; i++) {
			for (int k = 0; k < 3; k++) {
				for (int j = 3; j > 0; j--) {
					if (baseboard[i][j] == 0) {
						baseboard[i][j] = baseboard[i][j - 1];
						baseboard[i][j - 1] = 0;
					}
				}
			}
		}
		for (int i = 0; i < 4; i++) {
			for (int k = 0; k < 3; k++) {
				for (int j = 3; j > 0; j--) {
					if (baseboard[i][j] == baseboard[i][j - 1]) {
						baseboard[4][2] += baseboard[i][j];
						baseboard[i][j] = baseboard[i][j] * 2;
						baseboard[i][j - 1] = 0;
					}
				}
			}
		}
	}
	return baseboard;
}

int fileo(int board[5][4], char* time) {
	std::ofstream file("example.txt", std::ios::app);
	if (file.is_open()) {
		file << board[4][2] << "," << board[4][3] << "," << time << endl;
		file.close();
	}
	else {
		std::cout << "�t�@�C�����J���܂���ł����B";
	}
	return 0;
}

class SCORE {
	int score_f;
	int step_f;
	string time_f;
public:
	void setscore(const int& newscore_f) { score_f = newscore_f; }
	int getscore() const { return score_f; }
	void setstep(int newstep_f) { step_f = newstep_f; }
	int getstep() const { return step_f; }
	void settime(const string& newtime_f) { time_f = newtime_f; }
	string gettime() const { return time_f; }
};



int main(int argc, char* args[]) {
	int board_s[5][4] = { {0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{5,0,0,0} };//5�~4�s��̍쐬(�������)
	//4�s�ڂ܂ł͕\���͈́@5�s�ڂ͒ǉ��������̍��W,�X�R�A,�萔�L�^�p
	// 
	//int board_s[5][4] = { {512,512,32,64},{128,64,64,4},{2,8,64,16},{512,0,0,0},{0,0,0,0} };//5�~4�s��̍쐬(�������)
	//int board_s[5][4] = { {512,512,64,32},{16,16,2,4},{8,0,0,0},{0,0,0,0},{0,0,0,0} };//5�~4�s��̍쐬(�������)
	add(board_s);
	add(board_s);//������Ԃ�2�����ǉ�

	cout << "1024�Q�[��" << endl;
	cout << "���̃Q�[����2�̏搔�����킹�Ăǂ�ǂ񐔂�傫�����Ă����Q�[���ł�" << endl;
	cout << "�S�Ă̐������@w�ŏ�Ɉړ��@�@s�ŉ��Ɉړ��@�@a�ō��Ɉړ��@�@d�ŉE�Ɉړ����܂�" << endl;
	cout << "�㉺�ɓ��������Ƃ��͏�܂��͉��ɓ����������������炻�̐������܂Ƃ܂�," << endl;
	cout << "���E�ɓ��������Ƃ��͍��܂��͉E�ɓ����������������炻�̐������܂Ƃ܂�܂�" << endl;
	cout << "�ړ����2,4,8,16,32�������_���ȏꏊ�Ɉ�ǉ�����܂�" << endl;
	cout << "1024���ł�����Q�[���N���A�@�ړ���ɐ������܂Ƃ܂炸���ׂẴ}�X�����܂��Ă�����Q�[���I�[�o�[�ƂȂ�܂�" << endl;
	cout << "   " << "\033[5m" << "�G���^�[�ŃX�^�[�g" << "\033[m " << endl;
	istream::int_type ch;
	while (1) {
		if ((ch = cin.get()) != EOF) {
			break;
		}
	}

	int step = 0;
	int list[21] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };//�U��΂�̊m�F�p�s��

	display(board_s);//������Ԃ�\��
	board_s[4][2] = 0;

	while (1) {
		int clear_code = clearcheck(board_s);
		if (clear_code == 0) {
			cout << "���߂łƂ��I�@�Q�[���N���A�I�I" << endl;
			break;
		}

		string cin_key;
		while (1) {
			string input;
			cout << "������s���Ă��������@�@w�F���@�@s�F���@�@a�F���@�@d�F��" << endl;
			cout << "����>" << endl; cin >> cin_key;
			if (cin_key == "w" || cin_key == "s" || cin_key == "a" || cin_key == "d") {
				break;
			}
			else {
				cout << cin_key << "\n" << "������x���͂��Ă�������" << endl;
			}
		}

		cout << keypattern(cin_key) << endl; //�ړ������̕\��
		cout << endl;
		cout << endl;
		if (cin_key == "w") {
			Move_up(board_s);//��ړ��֐�
		}
		if (cin_key == "s") {
			Move_down(board_s);//���ړ��֐�
		}
		if (cin_key == "a") {
			Move_left(board_s);//���ړ��֐�
		}
		if (cin_key == "d") {
			Move_right(board_s);//�E�ړ��֐�
		}

		this_thread::sleep_for(chrono::milliseconds(500)); // ������x��������
		step += 1; //�萔+1

		int over_code = overcheck(board_s);
		if (over_code == 0) {
			display(board_s);
			cout << "�c�O�@�Q�[���I�[�o�[" << endl;
			break;
		}

		add2(board_s, list);
		scoredis(board_s, step);
		display(board_s);
	}
	board_s[4][3] = step;

	char* time_now; //�����擾�p
	time_t t = time(NULL);
	struct tm local;
	localtime_s(&local, &t);
	char buf[128];
	strftime(buf, sizeof(buf), "%Y%m%d%H%M%S", &local);
	time_now = buf;

	fileo(board_s, time_now);

	ifstream datafile("example.txt");
	regex rx(R"(,)");
	string str;
	vector<SCORE> scores;
	vector<int> highscore;

	while (getline(datafile, str)) {// �t�@�C������1�s���ǂݍ���
		sregex_token_iterator it(str.begin(), str.end(), rx, -1); // ,�ŕ�������C�e���[�^
		sregex_token_iterator end; // �C�e���[�^�̏I���

		if (it != end) {
			SCORE score;
			highscore.push_back(stoi(*it));
			score.setscore(stoi(*it++));
			if (it != end) {
				score.setstep(stoi(*it++));
				if (it != end) {
					score.settime(*it++);
					scores.push_back(score);
				}
			}
		}
	}

	datafile.close();

	scoredis(board_s, step);
	cleardisplay(board_s);

	cout << endl;
	sort(highscore.rbegin(), highscore.rend());
	cout << "���܂ł̍ō����_��" << "\033[3;33m" << highscore[0] << "\033[m" << "�_" << endl;
	cout << endl;
	cout << "���_�L�^" << endl;
	for (const auto& score : scores) {
		cout << "���_:" << score.getscore() << "�_(�萔" << score.getstep() << ",�L�^����:" << score.gettime() << ")" << endl;
	}
	//for (int l = 0; l < 21; l++) {
	//	cout << list[l] << ",";
	//}; //�U��΂��̊m�F
	//remove("example.txt"); //���_�L�^�̃��Z�b�g�p

}