#pragma once
#ifndef _QINT_H_
#define _QINT_H_
#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include<sstream>
#include <stack>
#include "console.h"
#include <cstdlib>
#include <conio.h>
#include <fstream>
#include <stdio.h>
using namespace std;

#define DEFAULT_TYPE		10



class QInt
{
protected:
	unsigned int data[4];
public:
	//-----Nhóm hàm khởi tạo và huỷ -----
	QInt() {
		//cout << "Creating..." << endl;
		for (int i = 0; i < 4; i++) {
			data[i] = 0;
		}
	}
	QInt(string Bin, int type);
	~QInt() { return; }
	//-----
	//get data i
	unsigned getData(int i) {
		return this->data[i];
	}
	// lấy giá trị bit tại vị trí i
	bool getBit(unsigned int x, int i) 
	{
		return (x >> i) & 1;
	}
	// đặt giá trị value = 0/1 cho bit i
	bool setBit(unsigned int x, int i, bool value) {

	}
	// bật bit 1 tại vị trí i
	void turnOnBit(unsigned int& x, int i) 
	{
		x = x | (1 << i);
	}
	// gán giá trị 0 tại bit thứ i
	void turnOffBit(unsigned int& x, int i) 
	{
		x = x & !(1 << i);
	}
	// hàm xử lý cộng hai bit có lưu biến nhớ
	bool subTwoBit(bool& Remember, bool a, bool b) 
	{
		bool result;
		result = a ^ b;
		if (Remember == 1)
		{
			if (result == 0)
			{
				result = 1;
				Remember = 0;
			}
			else
			{
				result = 0;
				Remember = 1;
			}

		}
		if (a == 1 && b == 1)
			Remember = 1;
		return result;
	}
	// đưa một chuỗi các ký tự '0' vào a
	void Scan(QInt& a, string s) 
	{
		a.data[0] = a.data[1] = a.data[2] = a.data[3] = 0;
		if (s.length() > 128)
			s = s.substr(s.length() - 128, 128);
		else
			s.insert(s.begin(), 128 - s.length(), '0');
		for (int i = 0; i < 128; i++)
		{
			if (s[i] == '1')
			{
				turnOnBit(a.data[i / 32], 32 - i % 32 - 1);
			}
		}
	}
	//-----Nhóm hàm convert
	//chuyển số QInt ra chuỗi bit nhưng loại bỏ các số 0 thừa
	string QInttoString(QInt a) // 
	{
		int vt, check = 0;
		string result = "";
		for (int i = 0; i < 128; i++)
		{
			if (getBit(a.data[i / 32], 32 - i % 32 - 1) == 1)
			{
				vt = i;
				check = 1;
				break;
			}
		}
		if (check == 0) return result;
		for (int i = vt; i < 128; i++)
		{
			if (getBit(a.data[i / 32], 32 - i % 32 - 1) == 1)
			{
				result += "1";
			}
			else
			{
				result += "0";
			}
		}
		return result;
	}
	//Hàm convert Bin to Int để lưu vào class
	void BinToStrInt(string Bin);
	//Hàm convert Hex to Int để lưu vào class
	void HexToStrInt(string hex);
	//Hàm convert Dec to Int để lưu vào class
	void DecToStrInt(string dec);
	//data[4] sang chuỗi nhị nhân
	string BinaryToStringBinary(QInt a) 
	{
		string result;
		for (int i = 0; i < 128; i++)
		{
			if (getBit(a.data[i / 32], 32 - i % 32 - 1) == 1)
				result = result + "1";
			else
				result = result + "0";
		}
		return result;
	}
	//------
	//Hàm convert Bin to Dec 
	string BinToDec(QInt a);
	//Hàm convert Dec to Bin 
	QInt DecToBin(string s);
	//Hàm convert Bin to Hex để in ra
	string ToHex();
	//Hàm convert Hex to Bin
	string ToBin();
	//-----
	// so sánh hai chuỗi số thập phân, nếu a> b trả về 1, bằng trả về 0, nhỏ hơn trả về -1
	int compareTwoStringNumber(string a, string b) 
	{
		delete0(a);
		delete0(b);
		int n = a.length();
		int m = b.length();
		if (n > m)
			return 1;
		if (n < m)
			return -1;
		for (int i = 0; i < n; i++)
		{
			if (a[i] < b[i])
				return -1;
			else if (a[i] > b[i])
				return 1;
		}
		return 0;
	}
	// xóa các số 0 thừa ở đầu chuỗi
	void delete0(string& a) 
	{
		if (a[0] != '-')
		{
			for (int i = 0; i < a.length() - 1; i++)
			{
				if (a[i] == '0')
				{
					if (a[i + 1] == '0')
					{
						a.erase(i, 1);
						i--;
					}
					else
					{
						a.erase(i, 1);
						break;
					}
				}
				else
					break;
			}
		}
		else
		{
			for (int i = 1; i < a.length() - 1; i++)
			{
				if (a[i] == '0')
				{
					if (a[i + 1] == '0')
					{
						a.erase(i, 1);
						i--;
					}
					else
					{
						a.erase(i, 1);
						break;
					}
				}
				else
					break;
			}
		}
	}
	// hàm cộng hai ký tự trong phạm vi từ '0' đến '9'
	char sumMiniNum(char a, char b, int& Remember) 
	{
		int temp = (a - 48) + (b - 48) + Remember;
		Remember = temp / 10;
		return (temp % 10 + 48);
	}
	// hàm trừ hai ký tự trong phạm vi từ '0' đến '9'
	char subMiniNum(char a, char b, int& Remember) 
	{
		int temp = 10 + (a - 48) - (b - 48) - Remember;
		Remember = 1 - temp / 10;
		return (temp % 10 + 48);
	}
	// hàm cộng hai chuỗi số thập phân
	string sumTwoStringNumber(string a, string b, string& KetQua) 
	{
		int n, m;
		int pos;
		int Remember = 0;
		char temp;
		KetQua = "";
		delete0(a);
		delete0(b);
		n = a.length();
		m = b.length();
		for (int i = m - 1; i >= 0; i--)
		{
			temp = sumMiniNum(a[n - 1], b[i], Remember);
			KetQua.insert(0, 1, temp);
			n--;
			if (n == 0)
				break;
		}
		n = a.length();
		m = b.length();
		if (n > m)
		{
			pos = n - m - 1;
			for (int i = pos; i >= 0; i--)
			{
				temp = sumMiniNum(a[i], '0', Remember);
				KetQua.insert(0, 1, temp);
			}
			KetQua.insert(0, 1, Remember + 48);
		}
		else if (n < m)
		{
			pos = m - n - 1;
			for (int i = pos; i >= 0; i--)
			{
				temp = sumMiniNum(b[i], '0', Remember);
				KetQua.insert(0, 1, temp);
			}
			KetQua.insert(0, 1, Remember + 48);
		}
		else
			KetQua.insert(0, 1, Remember + 48);
		delete0(KetQua);
		return KetQua;
	}
	// hàm trừ hai chuỗi số
	string subTwoStringNumber(string a, string b, string& KetQua) 
	{
		int n, m;
		int Remember = 0;
		char temp;
		KetQua = "";
		delete0(a);
		delete0(b);
		n = a.length();
		m = b.length();
		for (int i = m - 1; i >= 0; i--)
		{
			temp = subMiniNum(a[n - 1], b[i], Remember);
			KetQua.insert(0, 1, temp);
			n--;
		}
		n = a.length();
		for (int i = n - m - 1; i >= 0; i--)
		{
			temp = subMiniNum(a[i], '0', Remember);
			KetQua.insert(0, 1, temp);
		}
		delete0(KetQua);
		return KetQua;
	}
	// hàm chia hai chuỗi số thập phân
	string divTwoStringNumber(string a, string b, string& KetQua, string& Du) 
	{
		int n = a.length();
		int m = b.length();
		int i = b.length();
		string p = a.substr(0, i);

		Du = "";
		KetQua = "";
		while (i - 1 < n)
		{
			KetQua += '0';
			while (compareTwoStringNumber(p, b) >= 0)
			{
				KetQua[KetQua.length() - 1]++;
				subTwoStringNumber(p, b, Du);
				p = Du;
			}
			Du = p;
			i++;
			if (i - 1 < n)
				p += a[i - 1];
		}
		delete0(Du);
		delete0(KetQua);
		return KetQua;
	}
	//----- Operator -----
	//Copy operator (=)
	QInt operator=(const QInt& num);
	//Operator +
	QInt operator+(QInt& num);
	//Operator -
	QInt operator-(QInt& num);
	//Operator *
	QInt operator*(QInt& num);
	//Operator /
	QInt operator/(QInt& num);
	//----- Thao tác trên Bit
	//Operator & AND
	QInt operator&(QInt& num);
	//Operator | OR
	QInt operator|(QInt& num);
	//Operator ^ XOR
	QInt operator^(QInt& num);
	//Operator ~ NOT
	QInt operator~();
	//Operator << (Shift Left)
	QInt operator<<(int k);
	//Operator >> (Shift Right)
	QInt operator>>(int k);
	//Operator << (cout)	
	//friend ostream& operator<<(ostream& output, QInt& q);
	//Operator >> (cin)
	//istream& operator >> (istream& in);
	//Hàm xoay trái Rotate Left
	QInt rol();
	//Hàm xoay trái Rotate Right
	QInt ror();
	//------
	//------ Nhóm hàm so sánh
	//operator ==
	bool operator==(QInt& num);
	//Operator >
	bool operator>(QInt& num);
	//Operator <
	bool operator<(QInt& num);
	//Operator >=
	bool operator>=(QInt& num);
	//Operator <=
	bool operator<=(QInt& num);
	// đảo bit của x tại vị trí i
	void inverseBit(unsigned int& x, int i) 
	{
		x = x ^ (1 << i);
	}
	//lấy bù 2
	QInt TwoComplement(QInt a) // hàm lấy số bù 2
	{
		for (int i = 0; i < 128; i++)
		{
			inverseBit(a.data[i / 32], i % 32); // số bù 1
		}
		QInt temp;
		temp.data[0] = temp.data[1] = temp.data[2] = 0;
		temp.data[3] = 1;
		a = a + temp; // số bù 1 cộng cho 1 là số bù 2
		return a;
	}
	//-----
	// hàm dịch phải k bit biểu diễn theo chuỗi
	string shift_right(string str, int k) { 
		string temp = str;
		temp.erase(temp.length() - k);
		if (temp[0] == '0') {
			temp.insert(0, k, '0');
		}
		else
			temp.insert(0, k, '1');
		return temp;
	}
	//output, mình cũng chả hiểu sao 
	//cái operator shift_right và cout lại xung đột
	//làm mình phải viết cái hàm này
	string out(int n){
		QInt q = *this;
		if (q.data[3] == 0) {
			cout << 0 << endl;
			return "0";
		}
		else {
			if (n == 10) {
				cout << q.BinToDec(q) << endl;
				return q.BinToDec(q);
			}
			if (n == 2) { 
				cout << q.QInttoString(q) << endl; 
				return q.QInttoString(q);
			}
			if (n == 16) { 
				cout << q.ToHex() << endl;
				return q.ToHex();
			}
		}
	}
	//File
	void workFile(char* argv[])
	{
		ifstream ifs;
		//ifs.open(argv[1]);
		ifs.open(argv[1]);
		ofstream ofs;
		//ofs.open(argv[2]);
		ofs.open(argv[2]);
		int n; // He so cua 2 so can cong
		// Khuc nay t ko biet ghi file sao nen m ghi gium t nhe
		string sign; // Dau
		string s_pre, s_suf = "0"; // 2 so can cong		
		while (!ifs.eof())
		{
			s_suf = "0";
			ifs >> n;
			//cout << n << endl;
			ifs >> s_pre;
			//cout << s_pre << endl;
			ifs >> sign;
			//cout << sign << endl;
			if (sign == "+" || sign == "-" || sign == "*" || sign == "/" ||
				sign == ">>" || sign == "<<" || sign == "ror" || sign == "rol" ||
				sign == "&" || sign == "|" || sign == "^" || sign == "~" ||
				sign == ">" || sign == "<" || sign == ">=" || sign == "<=" || sign == "==") {
				ifs >> s_suf;
			}
			//cout << s_suf << endl;
			QInt pre(s_pre, n), suf(s_suf, n);
			if (sign == "+") {
				QInt result;
				result = pre + suf;
				result.out(n);
				ofs << result.out(n) << endl;
			}
			else if (sign == "-") {
				QInt result;
				result = pre - suf;
				result.out(n);
				ofs << result.out(n) << endl;
			}
			else if (sign == "*") {
				QInt result;
				result = pre * suf;
				result.out(n);
				ofs << result.out(n) << endl;
			}
			else if (sign == "/") {
				QInt result;
				result = pre / suf;
				result.out(n);
				ofs << result.out(n) << endl;
			}
			else if (sign == "<<") {
				int k = stoi(s_suf);
				pre = pre << k;
				pre.out(n);
				ofs << pre.out(n) << endl;
			}
			else if (sign == ">>") {
				int k = stoi(s_suf);
				pre = pre >> k;
				ofs << pre.out(n) << endl;
			}
			else if (sign == "&") { //AND
				QInt result;
				result = pre & suf;
				result.out(n);
				ofs << pre.out(n) << endl;
			}
			else if (sign == "|") { //OR
				QInt result;
				result = pre | suf;
				result.out(n);
				ofs << pre.out(n) << endl;
			}
			else if (sign == "^") { //XOR
				QInt result;
				result = pre ^ suf;
				result.out(n);
				ofs << result.out(n) << endl;
			}
			else if (sign == "~") { //NOT
				QInt result;
				result = ~ suf;
				result.out(n); 
				ofs << result.out(n) << endl;
			}
			else if (n == 2 && s_pre == "10" && s_suf=="0") {
				QInt result(sign, 2);
				cout << result.BinToDec(result) << endl;
				ofs << result.BinToDec(result) << endl;
			}
			else if (n == 2 && s_pre == "16" && s_suf == "0") {
				QInt result(sign, 2);
				cout << result.ToHex() << endl;
				ofs << result.ToHex() << endl;
			}
			else if (n == 10 && s_pre == "2" && s_suf == "0") {
				QInt result(sign, 10);
				cout << result.QInttoString(result) << endl;
				ofs << result.QInttoString(result) << endl;
			}
			else if (n == 10 && s_pre == "16" && s_suf == "0") {
				QInt result(sign, 10);
				cout << result.ToHex() << endl;
				ofs << result.ToHex() << endl;
			}
			else if (n == 16 && s_pre == "10" && s_suf == "0") {
				QInt result(sign, 16);
				cout << result.BinToDec(result) << endl;
				ofs << result.BinToDec(result) << endl;
			}
			else if (n == 16 && s_pre == "2" && s_suf == "0") {
				QInt result(sign, 16);
				cout << result.QInttoString(result) << endl;
				ofs << result.QInttoString(result) << endl;
			}
			else if (sign == ">") {
				if (pre > suf) ofs << "true" << endl;
				else ofs << "false" << endl;
			}
			else if (sign == "<") {
				if (pre < suf) ofs << "true" << endl;
				else ofs << "false" << endl;
			}
			else if (sign == ">=") {
				if (pre >= suf) ofs << "true" << endl;
				else ofs << "false" << endl;
			}
			else if (sign == "<=") {
				if (pre <= suf) ofs << "true" << endl;
				else ofs << "false" << endl;
			}
			else if (sign == "==") {
				if (pre == suf) ofs << "true" << endl;
				else ofs << "false" << endl;
			}
			else if (sign == "ror") {
				QInt q(s_pre, n);
				q = q.ror();
				ofs << q.out(n) << endl;
			}
			else if (sign == "rol") {
				QInt q(s_pre, n);
				q = q.rol();
				ofs << q.out(n) << endl;
			}
			//return true;
		}
		ifs.close();
		ofs.close();
	}
};	

string FbitToHex(string bin);


#endif

