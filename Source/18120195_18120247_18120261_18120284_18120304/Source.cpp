#include "QInt.h"
#include "QFloat.h"

//---------------------Menu
void menu() {
	int n;
	cout << "n = ";  cin >> n;
	switch (n){
	case 2: {
		string sign;
		string s_pre, s_suf;
		cout << "Pre:  ";  cin >> s_pre;
		cout << "Sign: ";  cin >> sign;
		cout << "Suf:  ";  cin >> s_suf;
		QInt pre(s_pre, 2), suf(s_suf, 2);
		if (sign == "+") {
			QInt result;
			result = pre + suf;
			result.out(n);
			break;
		}
		else if (sign == "-") {
			QInt result;
			result = pre - suf;
			result.out(n);
			break;
		}
		else if (sign == "*") {
			QInt result;
			result = pre * suf;
			result.out(n);
			break;
		}
		else if (sign == "/") {
			QInt result;
			result = pre / suf;
			result.out(n);
			break;
		}
		else if (sign == "<<") {
			int k = stoi(s_suf);
			pre = pre << k;
			pre.out(n);
		}
		else if (sign == ">>") {
			int k = stoi(s_suf);
			pre = pre >> k;
			pre.out(n);
		}
		else if (s_pre == "10") {
			QInt result(sign, 2);
			cout << result.getData(3) << endl;
		}
		else if (s_pre == "16") {
			QInt result(sign, 2);
			cout << result.ToHex() << endl;
		}
		break;
	}
	case 10: {
		string num;
		string bin;
		string sign;
		cout << "Pre: "; cin >> num;
		cout << "Sign: "; cin >> sign;
		cout << "Suf: "; cin >> bin;
		QInt pre(num, 10);
		QInt suf(bin, 10);
		if (sign == "+") {
			QInt result;
			result = pre + suf;
			result.out(n);
			break;
		}
		else if (sign == "-") {
			QInt result;
			result = pre - suf;
			result.out(n);
			break;
		}
		else if (sign == "*") {
			QInt result;
			result = pre * suf;
			result.out(n);
			break;
		}
		else if (sign == "/") {
			QInt result;
			result = pre / suf;
			result.out(n);
			break;
		}
		else if (sign == "<<") {
			int k = stoi(bin);
			pre = pre << k;
			pre.out(n);
		}
		else if (sign == ">>") {
			int k = stoi(bin);
			pre = pre >> k;
			pre.out(n);
		}
		else if (num == "2") {
			QInt result(sign, 10);
			cout << result.QInttoString(result) << endl;
		}
		else if (num == "16") {
			QInt result(sign, 10);
			cout << result.ToHex() << endl;
		}
	}
	case 16: {
		string sign;
		string s_pre, s_suf;
		cout << "Pre:  ";  cin >> s_pre;
		cout << "Sign: ";  cin >> sign;
		cout << "Suf:  ";  cin >> s_suf;
		QInt pre(s_pre, 16), suf(s_suf, 16);
		if (sign == "+") {
			QInt result;
			result = pre + suf;
			result.out(n);
			break;
		}
		else if (sign == "-") {
			QInt result;
			result = pre - suf;
			result.out(n);
			break;
		}
		else if (sign == "*") {
			QInt result;
			result = pre * suf;
			result.out(n);
			break;
		}
		else if (sign == "/") {
			QInt result;
			result = pre / suf;
			result.out(n);
			break;
		}
		else if (sign == "<<") {
			int k = stoi(s_suf);
			pre = pre << k;
			pre.out(n);
		}
		else if (sign == ">>") {
			int k = stoi(s_suf);
			pre = pre >> k;
			pre.out(n);
		}
		else if (s_pre == "10") {
			QInt result(sign, 16);
			cout << result.BinToDec(result) << endl;
		}
		else if (s_pre == "2") {
			QInt result(sign, 16);
			cout << result.QInttoString(result) << endl;
		}
	}
	}
}
//clear x to y
void clearXtoY(int x1, int y1, int x2, int y2) {
	for (int i = x1; i < x2; i++) {
		for (int j = y1; j <= y2; j++) {
			gotoXY(i, j); cout << " ";
		}
	}

}
//check string có đúng định dạng hay không
int checkString(int x, int y, int numeral, string& s) {
	// x và y lưu vị trí bắt đầu của string để xoá

	int flag = 0;
	bool check;
	do {
		check = 0;
		if (numeral == 2) {
			for (int i = 0; i < s.length(); i++) {
				if (i == 0 && s[0] == '-') continue;
				if (s[i] != '1' && s[i] != '0') {
					check = 1;
					break;
				}
			}
		}
		else if (numeral == 10) {
			for (int i = 0; i < s.length(); i++) {
				if (i == 0 && s[0] == '-') continue;
				if (s[i] < '0' || s[i] > '9') {
					check = 1;
					break;
				}
			}
		}
		else if (numeral == 16) {
			for (int i = 0; i < s.length(); i++) {
				if (i == 0 && s[0] == '-') continue;
				if (s[i] != '0' && s[i] != '1' && s[i] != '2' && s[i] != '3' &&
					s[i] != '4' && s[i] != '5' && s[i] != '6' && s[i] != '7' &&
					s[i] != '8' && s[i] != '9' && s[i] != 'A' && s[i] != 'B' &&
					s[i] != 'C' && s[i] != 'D' && s[i] != 'E' && s[i] != 'F') {
					check = 1;
					break;
				}
			}
		}
		if (check == 1) {
			clearXtoY(x, y, x + s.length(), y);
			gotoXY(x, y);
			cin >> s;
		}
	} while (check);
	return 1;
}
//check dấu được input có hợp lệ hay ko
int checkSign(int x, int y, string& sign) {
	int flag = 0;
	do {
		if (sign != "+" && sign != "-" && sign != "*" && sign != "/" &&
			sign != ">>" && sign != "<<" && sign != "ror" && sign != "rol" &&
			sign != "&" && sign != "|" && sign != "^" && sign != "~") {
			clearXtoY(x, y, x + sign.length(), y);
			gotoXY(x, y);
			cin >> sign;
		}
		else {
			flag = 1;
		}
	} while (!flag);
	return 1;
}
// menu
bool _menu_UI(int n, string sign, string s_pre, string s_suf) {

	QInt pre(s_pre, n), suf(s_suf, n);
	if (sign == "+") {
		QInt result;
		result = pre + suf;
		result.out(n);
	}
	else if (sign == "-") {
		QInt result;
		result = pre - suf;
		result.out(n);
	}
	else if (sign == "*") {
		QInt result;
		result = pre * suf;
		result.out(n);
	}
	else if (sign == "/") {
		QInt result;
		result = pre / suf;
		result.out(n);
	}
	else if (sign == "<<") {
		int k = stoi(s_suf);
		pre = pre << k;
		pre.out(n);
	}
	else if (sign == ">>") {
		int k = stoi(s_suf);
		pre = pre >> k;
	}
	else if (sign == "&") { //AND
		QInt result;
		result = pre & suf;
		result.out(n);
	}
	else if (sign == "|") { //OR
		QInt result;
		result = pre | suf;
		result.out(n);
	}
	else if (sign == "^") { //XOR
		QInt result;
		result = pre ^ suf;
		result.out(n);
	}
	else if (sign == "~") { //NOT
		QInt result;
		result = ~suf;
		gotoXY(0, 16); result.out(n);
	}
	else if (n == 2 && s_pre == "10") {
		QInt result(sign, 2);
		cout << result.BinToDec(result) << endl;
	}
	else if (n == 2 && s_pre == "16") {
		QInt result(sign, 2);
		cout << result.ToHex() << endl;
	}
	else if (n == 10 && s_pre == "2") {
		QInt result(sign, 10);
		cout << result.QInttoString(result) << endl;
	}
	else if (n == 10 && s_pre == "16") {
		QInt result(sign, 10);
		cout << result.ToHex() << endl;
	}
	else if (n == 16 && s_pre == "10") {
		QInt result(sign, 16);
		cout << result.BinToDec(result) << endl;
	}
	else if (n == 16 && s_pre == "2") {
		QInt result(sign, 16);
		cout << result.QInttoString(result) << endl;
	}
	else if (sign == ">") {
		if (pre > suf) return true;
		return false;
	}
	else if (sign == "<") {
		if (pre < suf) return true;
		return false;
	}
	else if (sign == ">=") {
		if (pre >= suf) return true;
		return false;
	}
	else if (sign == "<=") {
		if (pre <= suf) return true;
		return false;
	}
	else if (sign == "==") {
		if (pre == suf) return true;
		return false;
	}
	return true;
}
//in cái dòng title
void printTitle() {
	cout << "!-------------------------------------------------!" << endl;
	cout << "                  CALCULATOR" << endl;
	cout << "!-------------------------------------------------!" << endl;
}
//Chức năng chuyển đổi
void convert(int numeral) {
	string x;
	int y;
	TextColor(7);
	gotoXY(6, 20); cout << "Number: "; cin >> x;
	checkString(14, 20, numeral, x);
	gotoXY(6, 22); cout << "Numerral: "; cin >> y;
	while (y != 2 && y != 10 & y != 16) {
		clearXtoY(16, 22, 30, 22);
		gotoXY(6, 22); cout << "Numerral: "; cin >> y;
	}
	QInt q_x(x, numeral);
	if (y == 2) {
		gotoXY(6, 24); cout << q_x.QInttoString(q_x) << endl;
	}
	else if (y == 16) {
		gotoXY(6, 24); cout << q_x.ToHex() << endl;
	}
	else if (y == 10) {
		int line = 10;
		gotoXY(6, 24);
		cout << q_x.BinToDec(q_x) << endl;
	}
	//quit
	TextColor(11); gotoXY(6, 28); cout << "Pres ESC to quit.";
	char k;
	int flag = 1;
	do {
		TextColor(11); gotoXY(6, 28); cout << "Pres ESC to quit.";
		k = _getch();
		if (k == 27) {
			clearXtoY(0, 20, 200, 29);
			return;
		}
	} while (flag == 1);
}
//Chức năng so sánh
void compare(int numeral) {
	string x, y;
	TextColor(7);
	gotoXY(6, 20); cout << "First number: "; cin >> x;
	checkString(79, 6, numeral, x);
	gotoXY(6, 22); cout << "Second number: "; cin >> y;
	checkString(80, 8, numeral, y);
	QInt q_x(x, numeral);
	QInt q_y(y, numeral);
	if (q_x > q_y) {
		TextColor(9); gotoXY(6, 24); cout << x << " > " << y;
	}
	else if (q_x < q_y) {
		TextColor(9); gotoXY(6, 24); cout << x << " < " << y;
	}
	else {
		TextColor(9); gotoXY(6, 24); cout << x << " = " << y;
	}
	TextColor(11); gotoXY(6, 26); cout << "Pres ESC to quit.";
	char k;
	int flag = 1;
	do {
		TextColor(11); gotoXY(6, 26); cout << "Pres ESC to quit.";
		k = _getch();
		if (k == 27) {
			clearXtoY(0, 20, 200, 29);
			return;
		}
	} while (flag == 1);

}
//chức năng tính toán
void cal(int numeral) {
	string sign;
	string s_pre, s_suf;
	TextColor(7);
	gotoXY(6, 20);  cout << "First number: ";  cin >> s_pre;
	checkString(21, 20, numeral, s_pre);
	gotoXY(6, 22);  cout << "Sign: ";  cin >> sign;
	checkSign(13, 22, sign);
	gotoXY(6, 24); cout << "Second number: ";  cin >> s_suf;
	checkString(22, 24, numeral, s_suf);
	gotoXY(6, 26);
	cout << s_pre << " " << sign << " " << s_suf << " = "; _menu_UI(numeral, sign, s_pre, s_suf);
	//quit
	TextColor(11); gotoXY(6, 28); cout << "Pres ESC to quit.";
	char k;
	int flag = 1;
	do {
		TextColor(11); gotoXY(6, 28); cout << "Pres ESC to quit.";
		k = _getch();
		if (k == 27) {
			clearXtoY(0, 20, 200, 29);
			return;
		}
	} while (flag == 1);
}
//dich va xoay 
void rotateBlaBla(int numeral) {
	string sign = "";
	string s_pre;
	int s_suf;
	TextColor(7);
	gotoXY(6, 20);  cout << ">> << RoR RoL: ";  cin >> sign;
	gotoXY(6, 22);  cout << "Number:  ";  cin >> s_pre;
	gotoXY(6, 24); cout << "k:  ";  cin >> s_suf;
	QInt q(s_pre, numeral);
	gotoXY(6, 26);	cout << s_pre << " " << sign << " " << s_suf << " = ";
	if (sign == ">>") {
		q = q >> s_suf;
		q.out(numeral);
	}
	else if (sign == "<<") {
		q = q << s_suf;
		q.out(numeral);
	}
	else if (sign == "ror") {
		for (int i = 0; i < s_suf; i++) {
			q = q.ror();
		}
		q.out(numeral);
	}
	else if (sign == "rol") {
		for (int i = 0; i < s_suf; i++) {
			q = q.rol();
		}
		q.out(numeral);
	}
	//quit
	TextColor(11); gotoXY(6, 28); cout << "Pres ESC to quit.";
	char k;
	int flag = 1;
	do {
		TextColor(11); gotoXY(6, 28); cout << "Pres ESC to quit.";
		k = _getch();
		if (k == 27) {
			clearXtoY(0, 20, 200, 29);
			return;
		}
	} while (flag == 1);
}
//and or xor not
void manipulationBit(int numeral) {
	string sign;
	string s_pre, s_suf;
	TextColor(7);
	gotoXY(6, 20);  cout << "Sign: ";  cin >> sign;
	if (sign != "~") {
		gotoXY(6, 22);  cout << "Pre:  ";  cin >> s_pre;
	}
	gotoXY(6, 24); cout << "Suf:  ";  cin >> s_suf;
	gotoXY(6, 26);
	cout << s_pre << " " << sign << " " << s_suf << " = ";
	_menu_UI(numeral, sign, s_pre, s_suf);
	//quit
	//TextColor(11); gotoXY(6, 28); cout << "Pres ESC to quit.";
	char k;
	int flag = 1;
	do {
		TextColor(11); //gotoXY(6, 28); cout << "Pres ESC to quit.";
		k = _getch();
		if (k == 27) {
			clearXtoY(0, 20, 200, 29);
			return;
		}
	} while (flag == 1);
}
//In ra các lựa chọn
void printChoose() {
	TextColor(7);
	gotoXY(30, 6);  cout << "1. Converting." << endl;
	gotoXY(30, 8);  cout << "2. Compare." << endl;
	gotoXY(30, 10); cout << "3. + - * /." << endl;
	gotoXY(30, 12); cout << "4. >> << ror rol." << endl;
	gotoXY(30, 14); cout << "5. AND OR XOR NOT" << endl;
	gotoXY(55, 6); cout << " -->> ";
}
//Hàm chọn lựa
int choose(int num) {
	printChoose();
	int line[5] = { 6 , 8, 10 , 12, 14 };
	int line_i = 0;
	char key;
	do {
		if (_kbhit()) {
			key = _getch();
			if (key == 'S' || key == 's') {
				TextColor(11); gotoXY(55, line[line_i]); cout << "      ";
				if (line_i == 4) {
					line_i = -1;
				}
				line_i = line_i + 1;
				TextColor(11); gotoXY(55, line[line_i]); cout << " -->> ";
			}
			if (key == 'W' || key == 'w') {
				TextColor(11); gotoXY(55, line[line_i]); cout << "      ";
				if (line_i == 0) {
					line_i = 5;
				}
				line_i = line_i - 1;
				TextColor(11); gotoXY(55, line[line_i]); cout << " -->> ";
			}
			if (key == 13 && line_i == 1) {
				compare(num);
			}
			else if (key == 13 && line_i == 0) {
				convert(num);
			}
			else if (key == 13 && line_i == 2) {
				cal(num);
			}
			else if (key == 13 && line_i == 3) {
				rotateBlaBla(num);
			}
			else if (key == 13 && line_i == 4) {
				manipulationBit(num);
			}
			if (key == 27) {
				clrscr();
				printTitle();
				gotoXY(6, 6); cout << "BIN:" << endl;
				gotoXY(6, 8); cout << "DEC:" << endl;
				gotoXY(6, 10); cout << "HEX:" << endl;
				TextColor(9);  gotoXY(0, 30); cout << "=> Press W or S  to choose. ." << endl;
				TextColor(9);  gotoXY(0, 32); cout << "=> Press ENTER to confirm. ." << endl;
				TextColor(9);  gotoXY(0, 34); cout << "=> Press ESC to quit a level. ." << endl;
				int line[3] = { 6 , 8, 10 };
				int line_i = 0;
				TextColor(11); gotoXY(16, 6); cout << " -->> ";
				char key;
				do {
					if (_kbhit()) {
						key = _getch();
						if (key == 'S' || key == 's') {
							TextColor(11); gotoXY(16, line[line_i]); cout << "      ";
							if (line_i == 2) {
								line_i = -1;
							}
							line_i = line_i + 1;
							TextColor(11); gotoXY(16, line[line_i]); cout << " -->> ";
						}
						if (key == 'W' || key == 'w') {
							TextColor(11); gotoXY(16, line[line_i]); cout << "      ";
							if (line_i == 0) {
								line_i = 3;
							}
							line_i = line_i - 1;
							TextColor(11); gotoXY(16, line[line_i]); cout << " -->> ";
						}
						if (key == 13) {
							int num = 0;
							if (line_i == 0) {
								num = 2;
							}
							else if (line_i == 1) {
								num = 10;
							}
							else num = 16;
							choose(num);
						}
						if (key == 27) {
							return 0;
						}
					}
				} while (1);
			}
		}
	} while (1);

	return 0;
}
//Hàm chọn cơ số (2, 10, 16)
int chooseNumeral() {
	gotoXY(6, 6); cout << "BIN:" << endl;
	gotoXY(6, 8); cout << "DEC:" << endl;
	gotoXY(6, 10); cout << "HEX:" << endl;
	TextColor(9);  gotoXY(0, 30); cout << "=> Press W or S  to choose." << endl;
	TextColor(9);  gotoXY(0, 32); cout << "=> Press ENTER to confirm. ." << endl;
	TextColor(9);  gotoXY(0, 34); cout << "=> Press ESC to quit a level. ." << endl;
	int line[3] = { 6 , 8, 10 };
	int line_i = 0;
	TextColor(11); gotoXY(16, 6); cout << " -->> ";
	char key;
	do {
		if (_kbhit()) {
			key = _getch();
			if (key == 'S' || key == 's') {
				TextColor(11); gotoXY(16, line[line_i]); cout << "      ";
				if (line_i == 2) {
					line_i = -1;
				}
				line_i = line_i + 1;
				TextColor(11); gotoXY(16, line[line_i]); cout << " -->> ";
			}
			if (key == 'W' || key == 'w') {
				TextColor(11); gotoXY(16, line[line_i]); cout << "      ";
				if (line_i == 0) {
					line_i = 3;
				}
				line_i = line_i - 1;
				TextColor(11); gotoXY(16, line[line_i]); cout << " -->> ";
			}
			if (key == 13) {
				int num = 0;
				if (line_i == 0) {
					num = 2;
				}
				else if (line_i == 1) {
					num = 10;
				}
				else num = 16;
				choose(num);
			}
			if (key == 27) {
				return 0;
			}
		}
	} while (1);

	return 1;
}
//Giao diện
void UserInterface() {
	clrscr();
	printTitle();
	chooseNumeral();
}

//
int n;
//Number16bytes.exe QInt_input.txt QInt_output.txt 1
//Number16bytes.exe QFloat_input.txt QFloat_output.txt 2
int main(int argc, char* argv[]) {
	//clrscr();	
	
	if (argc != 1) {
		if (argv[3][0] == '1') {
			QInt q;
			q.workFile(argv);
			_getch();
		}
		else if (argv[3][0] == '2') {
			int k;
			do
			{
				k = 1;
				switch (k)
				{
				case 1:
					system("cls");
					ReadFile(argv);
					break;
				case 2:
					system("cls");
					User();
					break;
				default:
					break;
				}
			} while (k != 0);
		}
	}
	clrscr();
	
	cout << "Nhap 0 de thoat chuong trinh." << endl;
	cout << "Nhap 1: QInt" << endl;
	cout << "Nhap 2: QFloat" << endl;
	cin >> n;
	clrscr();
	if (n == 1) {
		UserInterface();
	}
	else if (n == 2) {
		int k;
		do
		{
			system("cls");
			cout << "Nhap 0 de thoat chuong trinh." << endl;
			cout << "Nhap 1 de doc file test." << endl;
			cout << "Nhap 2 de vao giao dien nguoi dung" << endl;
			cin >> k;
			switch (k)
			{
			case 1:
				system("cls");
				ReadFile(argv);
				break;
			case 2:
				system("cls");
				User();
				break;
			default:
				break;
			}
		} while (k != 0);
	}
	return 0;
}
/*
console
....... 2
*/