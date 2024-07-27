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


const int  max_num = 1024;//クリア条件の設定

auto scoredis(int board[5][4], int step) {
	int point = 0;
	point = board[4][2];
	cout << "スコア" << "\033[3;33m" << point << "\033[m" << "　　　手数:" << step << endl;
}

//内部行列から表示形式への変換
void display(int board[5][4]) {
	int new_x = board[4][0];
	int new_y = board[4][1];
	cout << "+-----+-----+-----+-----+" << endl;
	for (int i = 0; i < 4; i++) {
		cout << "|";
		for (int j = 0; j < 4; j++) {//追加した数字の点滅表示
			if (i == new_x && j == new_y) {
				if (board[i][j] == 0 || board[i][j] == 2 || board[i][j] == 4 || board[i][j] == 8) {	//0,2,4,8の場合(0の場合は存在しない)
					//	cout << "   " << "\033[31m" << board[i][j] << "\033[m " << " | ";
					cout << "   " << "\033[6;31m" << board[i][j] << "\033[m " << "|";
				}
				else if (board[i][j] == 16 || board[i][j] == 32 || board[i][j] == 64) {				//16,32,64の場合
					cout << "  " << "\033[6;31m" << board[i][j] << "\033[m " << "|";
				}
				else if (board[i][j] == 128 || board[i][j] == 256 || board[i][j] == 512) {			//128,256,512の場合
					cout << " " << "\033[6;31m" << board[i][j] << "\033[m " << "|";
				}
				else if (board[i][j] == 1024 || board[i][j] == 2048) {								//1024,2048の場合
					cout << "" << "\033[6;31m" << board[i][j] << "\033[m " << "|";
				}
				else {
					cout << "エラー発生再起動してください" << endl;									//それ以外の場合エラー
				}
			}
			else {
				if (board[i][j] == 0) {	//0の場合
					cout << "     |";
				}
				else if (board[i][j] == 2 || board[i][j] == 4 || board[i][j] == 8) {				//2,4,8の場合
					cout << "   " << board[i][j] << " |";
				}
				else if (board[i][j] == 16 || board[i][j] == 32 || board[i][j] == 64) {				//16,32,64の場合
					cout << "  " << board[i][j] << " |";
				}
				else if (board[i][j] == 128 || board[i][j] == 256 || board[i][j] == 512) {			//128,256,512の場合
					cout << " " << board[i][j] << " |";
				}
				else if (board[i][j] == 1024 || board[i][j] == 2048) {								//1024,2048の場合
					cout << "" << board[i][j] << " |";
				}
				else {
					cout << "エラー発生再起動してください" << endl;									//それ以外の場合エラー
				}
			}
		}
		cout << endl;
		cout << "+-----+-----+-----+-----+" << endl;
	}
}

void cleardisplay(int board[5][4]) {  //クリア時の表示
	cout << "+-----+-----+-----+-----+" << endl;
	for (int i = 0; i < 4; i++) {
		cout << "|";
		for (int j = 0; j < 4; j++) {//追加した数字の点滅表示
			if (board[i][j] == 0 || board[i][j] == 2 || board[i][j] == 4 || board[i][j] == 8) {	//0,2,4,8の場合
				//	cout << "   " << "\033[31m" << board[i][j] << "\033[m " << " | ";
				cout << "   " << board[i][j] << " |";
			}
			else if (board[i][j] == 16 || board[i][j] == 32 || board[i][j] == 64) {				//16,32,64の場合
				cout << "  " << board[i][j] << " |";
			}
			else if (board[i][j] == 128 || board[i][j] == 256 || board[i][j] == 512) {			//128,256,512の場合
				cout << " " << board[i][j] << " |";
			}
			else if (board[i][j] == 1024 || board[i][j] == 2048) {								//1024,2048の場合
				cout << "" << "\033[6;34m" << board[i][j] << "\033[m " << "|";
			}
			else {
				cout << "エラー発生再起動してください" << endl;									//それ以外の場合エラー
			}
		}
		cout << endl;
		cout << "+-----+-----+-----+-----+" << endl;
	}
}

auto clearcheck(int checkboard[5][4]) { //クリア条件を満たしているかの判定
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


int overcheck(int checkboard[5][4]) { //ゲームオーバー条件を満たしているかどうかの判定
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

auto add(int baseboard[5][4]) { //初期状態の表示用
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

string keypattern(string key_in) {//移動方向の表示
	string pattern;
	while (1) {
		if (key_in == "w") {
			pattern = "上";
			break;
		}
		else if (key_in == "s") {
			pattern = "下";
			break;
		}
		else if (key_in == "a") {
			pattern = "左";
			break;
		}
		else if (key_in == "d") {
			pattern = "右";
			break;
		}
	}
	return pattern;
}

auto Move_up(int baseboard[5][4]) {//上移動関数
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

auto Move_down(int baseboard[5][4]) {//下移動関数
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

auto Move_left(int baseboard[5][4]) {//左移動関数
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

auto Move_right(int baseboard[5][4]) { //右移動関数
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
		std::cout << "ファイルを開けませんでした。";
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
	int board_s[5][4] = { {0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{5,0,0,0} };//5×4行列の作成(初期状態)
	//4行目までは表示範囲　5行目は追加した数の座標,スコア,手数記録用
	// 
	//int board_s[5][4] = { {512,512,32,64},{128,64,64,4},{2,8,64,16},{512,0,0,0},{0,0,0,0} };//5×4行列の作成(初期状態)
	//int board_s[5][4] = { {512,512,64,32},{16,16,2,4},{8,0,0,0},{0,0,0,0},{0,0,0,0} };//5×4行列の作成(初期状態)
	add(board_s);
	add(board_s);//初期状態に2個数字追加

	cout << "1024ゲーム" << endl;
	cout << "このゲームは2の乗数を合わせてどんどん数を大きくしていくゲームです" << endl;
	cout << "全ての数字を　wで上に移動　　sで下に移動　　aで左に移動　　dで右に移動します" << endl;
	cout << "上下に動かしたときは上または下に同じ数字があったらその数字がまとまり," << endl;
	cout << "左右に動かしたときは左または右に同じ数字があったらその数字がまとまります" << endl;
	cout << "移動後は2,4,8,16,32がランダムな場所に一つ追加されます" << endl;
	cout << "1024ができたらゲームクリア　移動後に数字がまとまらずすべてのマスが埋まっていたらゲームオーバーとなります" << endl;
	cout << "   " << "\033[5m" << "エンターでスタート" << "\033[m " << endl;
	istream::int_type ch;
	while (1) {
		if ((ch = cin.get()) != EOF) {
			break;
		}
	}

	int step = 0;
	int list[21] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };//散らばりの確認用行列

	display(board_s);//初期状態を表示
	board_s[4][2] = 0;

	while (1) {
		int clear_code = clearcheck(board_s);
		if (clear_code == 0) {
			cout << "おめでとう！　ゲームクリア！！" << endl;
			break;
		}

		string cin_key;
		while (1) {
			string input;
			cout << "操作を行ってください　　w：↑　　s：↓　　a：←　　d：→" << endl;
			cout << "操作>" << endl; cin >> cin_key;
			if (cin_key == "w" || cin_key == "s" || cin_key == "a" || cin_key == "d") {
				break;
			}
			else {
				cout << cin_key << "\n" << "もう一度入力してください" << endl;
			}
		}

		cout << keypattern(cin_key) << endl; //移動方向の表示
		cout << endl;
		cout << endl;
		if (cin_key == "w") {
			Move_up(board_s);//上移動関数
		}
		if (cin_key == "s") {
			Move_down(board_s);//下移動関数
		}
		if (cin_key == "a") {
			Move_left(board_s);//左移動関数
		}
		if (cin_key == "d") {
			Move_right(board_s);//右移動関数
		}

		this_thread::sleep_for(chrono::milliseconds(500)); // 動きを遅延させる
		step += 1; //手数+1

		int over_code = overcheck(board_s);
		if (over_code == 0) {
			display(board_s);
			cout << "残念　ゲームオーバー" << endl;
			break;
		}

		add2(board_s, list);
		scoredis(board_s, step);
		display(board_s);
	}
	board_s[4][3] = step;

	char* time_now; //日時取得用
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

	while (getline(datafile, str)) {// ファイルから1行ずつ読み込む
		sregex_token_iterator it(str.begin(), str.end(), rx, -1); // ,で分割するイテレータ
		sregex_token_iterator end; // イテレータの終わり

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
	cout << "今までの最高得点は" << "\033[3;33m" << highscore[0] << "\033[m" << "点" << endl;
	cout << endl;
	cout << "得点記録" << endl;
	for (const auto& score : scores) {
		cout << "得点:" << score.getscore() << "点(手数" << score.getstep() << ",記録日時:" << score.gettime() << ")" << endl;
	}
	//for (int l = 0; l < 21; l++) {
	//	cout << list[l] << ",";
	//}; //散らばり具合の確認
	//remove("example.txt"); //得点記録のリセット用

}