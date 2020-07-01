#include "QInt.h"
//convert từ bit thứ begin đến end

QInt::QInt(string Bin, int type)
{
	if (Bin[0] == '-') {
		Bin = Bin.erase(0, 1);
		if (type == 2) this->BinToStrInt(Bin);
		if (type == 16) this->HexToStrInt(Bin);
		if (type == 10) this->DecToStrInt(Bin);
		*this = this->TwoComplement(*this);
	}
	else {
		if (type == 2) this->BinToStrInt(Bin);
		if (type == 16) this->HexToStrInt(Bin);
		if (type == 10) this->DecToStrInt(Bin);
	}

}
//hàm này để convert string Binary thành 4 số rồi lưu vào data
void QInt::BinToStrInt(string Bin)
{


	if (Bin.size() <= 32) {
		data[0] = 0;
		data[1] = 0;
		data[2] = 0;
		long long S3 = 0; // Gia tri sau khi convert của chuoi bit de luu vao data[3]
		for (int i = Bin.size() - 1; i >= 0; i--) {
			if (Bin[i] == '1') {
				S3 = S3 + pow(2, Bin.size() - i - 1);
			}
		}
		data[3] = S3;
	}
	else if (Bin.size() <= 64) {
		data[0] = 0;
		data[1] = 0;
		int over = Bin.size() - 32;
		long long S2 = 0;
		long long S3 = 0; // Gia tri sau khi convert của chuoi bit de luu vao data[3]
		//-------------
		for (int i = Bin.size() - 1; i >= over; i--) {
			if (Bin[i] == '1') {
				S3 = S3 + pow(2, Bin.size() - i - 1);
			}
		}
		data[3] = S3;
		//-------------
		for (int i = over; i >= 0; i--) {
			if (Bin[i] == '1') {
				S2 = S2 + pow(2, over - i - 1);
			}
		}
		data[2] = S2;
	}
	else if (Bin.size() <= 96) {
		data[0] = 0;
		int over = Bin.size() - 64;
		long long S1 = 0;
		long long S2 = 0;
		long long S3 = 0; // Gia tri sau khi convert của chuoi bit de luu vao data[3]
		//-------------
		for (int i = Bin.size() - 1; i >= Bin.size() - 32; i--) {
			if (Bin[i] == '1') {
				S3 = S3 + pow(2, Bin.size() - i - 1);
			}
		}
		data[3] = S3;
		//-------------
		for (int i = Bin.size() - 33; i >= Bin.size() - 64; i--) {
			if (Bin[i] == '1') {
				S2 = S2 + pow(2, Bin.size() - 33 - i);
			}
		}
		data[2] = S2;
		//-------------
		for (int i = over; i >= 0; i--) {
			if (Bin[i] == '1') {
				S1 = S1 + pow(2, over - i - 1);
			}
		}
		data[1] = S1;
	}
	else {
		int over = Bin.size() - 96;
		//-------------
		long long S0 = 0;
		long long S1 = 0;
		long long S2 = 0;
		long long S3 = 0; // Gia tri sau khi convert của chuoi bit de luu vao data[3]
		//-------------
		for (int i = Bin.size() - 1; i >= Bin.size() - 32; i--) {
			if (Bin[i] == '1') {
				S3 = S3 + pow(2, Bin.size() - i - 1);
			}
		}
		data[3] = S3;
		//-------------
		for (int i = Bin.size() - 33; i >= Bin.size() - 64; i--) {
			if (Bin[i] == '1') {
				S2 = S2 + pow(2, Bin.size() - 33 - i);
			}
		}
		data[2] = S2;
		//-------------
		for (int i = Bin.size() - 65; i >= Bin.size() - 96; i--) {
			if (Bin[i] == '1') {
				S1 = S1 + pow(2, Bin.size() - 65 - i);
			}
		}
		data[1] = S1;
		//-------------
		for (int i = over; i >= 0; i--) {
			if (Bin[i] == '1') {
				S0 = S0 + pow(2, over - i - 1);
			}
		}
		data[0] = S0;
	}
}
//hàm này để convert string Hex thành string Binary rồi
//lại convert thành 4 số rồi lưu vào data
void QInt::HexToStrInt(string num)
{
	string BinString;
	int Size = num.size();
	//change hex to binary
	for (int i = 0; i < Size; i++)
	{
		int temp;
		if (num[i] == 'F')
			temp = 15;
		else if (num[i] == 'E')
			temp = 14;
		else if (num[i] == 'D')
			temp = 13;
		else if (num[i] == 'C')
			temp = 12;
		else if (num[i] == 'B')
			temp = 11;
		else if (num[i] == 'A')
			temp = 10;
		else
			temp = int(num[i]) - int('0');
		bitset<4> tempBin(temp);
		string tempString = tempBin.to_string();
		BinString += tempString;
	}
	this->BinToStrInt(BinString);
}

void QInt::DecToStrInt(string dec)
{
	*this = this->DecToBin(dec);
	string bin;
	bin = this->BinaryToStringBinary(*this);
	BinToStrInt(bin);
}

string QInt::BinToDec(QInt a) // đổi từ hệ 2 sang  hệ 10
{
	string KetQua = "0";
	string Bufffer[128];
	string temp;
	string ChuoiNhiPhan;
	Bufffer[0] = "1";
	for (int i = 1; i < 128; i++)
		Bufffer[i] = sumTwoStringNumber(Bufffer[i - 1], Bufffer[i - 1], temp);
	if (getBit(a.data[0], 31) == 0)
	{
		ChuoiNhiPhan = BinaryToStringBinary(a);
		for (int i = 0; i < 128; i++)
		{
			if (ChuoiNhiPhan[i] == '1')
			{
				sumTwoStringNumber(KetQua, Bufffer[127 - i], temp);
				KetQua = temp;
			}
		}
	}
	else
	{
		ChuoiNhiPhan = BinaryToStringBinary(TwoComplement(a));
		for (int i = 0; i < 128; i++)
		{
			if (ChuoiNhiPhan[i] == '1')
			{
				sumTwoStringNumber(KetQua, Bufffer[127 - i], temp);
				KetQua = temp;
			}
		}
		KetQua.insert(0, 1, '-');
	}
	return KetQua;
}
//
QInt QInt::DecToBin(string s)
{
	bool CheckDauAm = false;
	string temp;
	QInt KetQua;
	string Thuong; // Thương
	string Du; // Dư
	stack<string> StackBin;
	int dem = 0;
	if (s[0] == '-')
	{
		s.erase(0, 1);
		CheckDauAm = true;
	}
	while (s != "0")
	{
		divTwoStringNumber(s, "2", Thuong, Du);
		StackBin.push(Du);
		s = Thuong;
		delete0(s);
		dem++;
	}
	while (!StackBin.empty())
	{
		temp += StackBin.top();
		StackBin.pop();
	}
	Scan(KetQua, temp);
	if (CheckDauAm == true)
		return TwoComplement(KetQua);
	return KetQua;
}


//-----
//Function convert 4bits to hexa
string FbitToHex(string bin) {
	/*if (bin.size() < 4) {
		for (int i = 0; i < 4 - bin.size(); i++) {
			bin = "0" + bin;
		}
	}*/
	string result;
	unsigned int S = 0;
	for (int i = 0; i < bin.size(); i++) {
		if (bin[i] == '1') {
			S = S * 2 + 1;
		}
		else {
			S = S * 2 + 0;
		}
	}
	switch (S)
	{
	case 0:
	{
		result = "0";
		break;
	}
	case 1:
	{
		result = "1";
		break;
	}
	case 2:
	{
		result = "2";
		break;
	}
	case 3:
	{
		result = "3";
		break;
	}
	case 4:
	{
		result = "4";
		break;
	}
	case 5:
	{
		result = "5";
		break;
	}
	case 6:
	{
		result = "7";
		break;
	}
	case 8:
	{
		result = "8";
		break;
	}
	case 9:
	{
		result = "9";
		break;
	}
	case 10:
	{
		result = "A";
		break;
	}
	case 11:
	{
		result = "B";
		break;
	}
	case 12:
	{
		result = "C";
		break;
	}
	case 13:
	{
		result = "D";
		break;
	}
	case 14:
	{
		result = "E";
		break;
	}
	case 15:
	{
		result = "F";
		break;
	}
	default:
		break;
	}
	return result;
}

/*Sẵn trong kiểu Qint là chứa mã hoá kiểu Dec của dãy 32it
nên ta convert nó từ "mã hoá" về Bin, rồi conver từ Bin về Hex
*/
string QInt::ToHex()
{
	string s;
	string KetQua;
	for (int i = 0; i < 128; i++)
	{
		if (getBit((*this).data[i / 32], 32 - i % 32 - 1) == 1)
			s = s + "1";
		else
			s = s + "0";
		if (s.length() == 4)
		{
			if (s == "0000")
				KetQua += "0";
			else if (s == "0001")
				KetQua += "1";
			else if (s == "0010")
				KetQua += "2";
			else if (s == "0011")
				KetQua += "3";
			else if (s == "0100")
				KetQua += "4";
			else if (s == "0101")
				KetQua += "5";
			else if (s == "0110")
				KetQua += "6";
			else if (s == "0111")
				KetQua += "7";
			else if (s == "1000")
				KetQua += "8";
			else if (s == "1001")
				KetQua += "9";
			else if (s == "1010")
				KetQua += "A";
			else if (s == "1011")
				KetQua += "B";
			else if (s == "1100")
				KetQua += "C";
			else if (s == "1101")
				KetQua += "D";
			else if (s == "1110")
				KetQua += "E";
			else if (s == "1111")
				KetQua += "F";
			s = "";
		}
	}
	delete0(KetQua);
	return KetQua;
}

string QInt::ToBin()
{
	string result;
	/*for (int i = 3; i > 0; i--) {
		result = this->DecToBin(this->data[i]) + result;
	}*/
	return result;
}
//Operator =
QInt QInt::operator=(const QInt& num)
{
	for (int i = 0; i <= 3; i++) {
		this->data[i] = num.data[i];
	}
	return *this;
}
//Operator +
QInt QInt::operator+(QInt& a)
{
	QInt c;
	c.data[0] = c.data[1] = c.data[2] = c.data[3] = 0;
	bool Remember = 0;
	int temp;
	for (int i = 127; i >= 0; i--)
	{
		temp = subTwoBit(Remember, getBit(this->data[i / 32], 32 - i % 32 - 1), getBit(a.data[i / 32], 32 - i % 32 - 1));
		if (temp == 1)
		{
			turnOnBit(c.data[i / 32], 32 - i % 32 - 1);
		}
	}
	return c;
}
//toán tử trừ
QInt QInt::operator-(QInt& num)
{
	QInt a = *this;
	QInt b = TwoComplement(num);
	return a + b;
}
//toán từ nhân
QInt QInt::operator*(QInt& num)
{
	QInt M = *this;
	QInt Q = num;
	int check = 0;
	string m_ = BinToDec(M);
	string q_ = BinToDec(Q);
	if (m_[0] == '-' && q_[0] == '-')
	{
		M = TwoComplement(M);
		Q = TwoComplement(Q);
	}
	else if (m_[0] == '-')
	{
		M = TwoComplement(M);
		check = 1;
	}
	else if (q_[0] == '-')
	{
		Q = TwoComplement(Q);
		check = 1;
	}

	string shift_temp;
	int n1;
	int k, temp;
	string A = "";
	string C = "0";
	string shift = "";
	for (int i = 0; i < 128; i++)
	{
		if (getBit(Q.data[i / 32], 32 - i % 32 - 1) == 1)
		{
			k = 128 - i;
			break;
		}
	}
	for (int i = 0; i < 128; i++)
	{
		if (getBit(M.data[i / 32], 32 - i % 32 - 1) == 1)
		{
			temp = 128 - i;
			break;
		}
	}
	int q1, m1;
	string q = QInttoString(Q);
	string m = QInttoString(M);
	q1 = q.length();
	m1 = m.length();
	if (k < temp)
		k = temp;// cập nhập số bit 
	for (int i = 0; i < k; i++)
		A += "0"; // khởi tạo A bằng k bit 0
	n1 = A.length();
	int count = k;
	while (k > 0)
	{
		if (getBit(Q.data[127 / 32], 32 - 127 % 32 - 1) == 1)
		{
			QInt A_temp;
			Scan(A_temp, A);
			A_temp = M + A_temp;//error operator +
			A = QInttoString(A_temp);
			if (A.length() < count)
			{
				A.insert(0, count - A.length(), '0');
			}
		}
		string Q_temp = QInttoString(Q);
		if (Q_temp.length() < count) {
			Q_temp.insert(0, count - Q_temp.length(), '0');
		}
		shift = C + A + Q_temp;
		shift_temp = shift_right(shift, 1);
		if (shift_temp.length() > 2 * count + 1) {
			shift_temp.erase(0, 1);
		}
		A = shift_temp.substr(1, count);
		Q_temp = shift_temp.substr(count + 1, count);
		Scan(Q, Q_temp);
		C = shift_temp[0];
		k--;
		if (k == 1)
		{
			shift_temp = shift_temp.erase(0, 1);
		}
	}
	if (shift_temp.length() > 128)
		return (DecToBin("9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"));
	QInt KQ;
	Scan(KQ, shift_temp);
	if (check == 1) {
		KQ = TwoComplement(KQ);
	}
	return KQ;
}
//toán tử chia
QInt QInt::operator/(QInt& num)
{
	QInt a = *this;
	QInt KQ;
	QInt temp1;
	string A;
	bool CheckDauAm_1 = false;
	bool CheckDauAm_2 = false;
	A.insert(0, 128, '0');
	int k = 128;
	if (getBit(a.data[0], 31) == 1)
	{
		a = TwoComplement(a);
		CheckDauAm_1 = true;
	}
	if (getBit(num.data[0], 31) == 1)
	{
		num = TwoComplement(num);
		CheckDauAm_2 = true;
	}
	string Q = BinaryToStringBinary(a);
	while (k > 0)
	{
		for (int i = 0; i < A.length() - 1; i++)
			A[i] = A[i + 1];
		A[A.length() - 1] = Q[0];
		Q.erase(0, 1);
		Q = Q + '0';
		Scan(temp1, A);
		temp1 = temp1 - num;
		if (getBit(temp1.data[0], 31) == 1)
		{
			Q[Q.length() - 1] = '0';
			temp1 = temp1 + num;
		}
		else
			Q[Q.length() - 1] = '1';
		A = BinaryToStringBinary(temp1);
		k--;
	}
	Scan(KQ, Q);
	if (CheckDauAm_1 == true)
	{
		if (CheckDauAm_2 == false)
			return TwoComplement(KQ);
		else
			return KQ;
	}
	if (CheckDauAm_2 == true)
	{
		if (CheckDauAm_1 == false)
			return TwoComplement(KQ);
		else
			return KQ;
	}
	return KQ;
}
//toán tử và
QInt QInt::operator&(QInt& num)
{
	QInt result;
	bool bit1, bit2;
	for (int i = 0; i < 128; i++) {
		bit1 = getBit((*this).data[i / 32], i % 32);
		bit2 = getBit(num.data[i / 32], i % 32);
		if (bit1 & bit2 == 1) {
			turnOnBit(result.data[i / 32], i % 32);
		}
	}
	return result;
}
//toán tử or
QInt QInt::operator|(QInt& num)
{
	QInt result;
	bool bit1, bit2;
	for (int i = 0; i < 128; i++) {
		bit1 = getBit((*this).data[i / 32], i % 32);
		bit2 = getBit(num.data[i / 32], i % 32);
		if (bit1 | bit2 == 1) {
			turnOnBit(result.data[i / 32], i % 32);
		}
	}
	return result;
}
//toán tử xor
QInt QInt::operator^(QInt& num)
{
	QInt result;
	bool bit1, bit2;
	for (int i = 0; i < 128; i++) {
		bit1 = getBit((*this).data[i / 32], i % 32);
		bit2 = getBit(num.data[i / 32], i % 32);
		if (bit1 ^ bit2 == 1) {
			turnOnBit(result.data[i / 32], i % 32);
		}
	}
	return result;
}
//tóan tử not
QInt QInt::operator~()
{
	QInt result;
	bool temp;
	for (int i = 0; i < 128; i++)
	{
		temp = getBit((*this).data[i / 32], i % 32);
		if (temp == 0)
			turnOnBit(result.data[i / 32], i % 32);
	}
	return result;
}
//toán tử dịch trái k bit
QInt QInt::operator<<(int k)
{
	if (k >= 128)
		return (DecToBin("0"));
	string str = BinaryToStringBinary((*this));
	string temp = str;
	temp.erase(0, k);
	temp.insert(temp.length(), k, '0');
	QInt KQ;
	Scan(KQ, temp);
	return KQ;

}
//toán tử dịch phải k bit
QInt QInt::operator>>(int k)
{
	if (k >= 128)
	{
		if (getBit((*this).data[0], 31) == 0)
			return DecToBin("0");
		else
			return DecToBin("-1");
	}
	string str = BinaryToStringBinary((*this));
	string temp = str;
	temp.erase(temp.length() - k);
	if (temp[0] == '0') {
		temp.insert(0, k, '0');
	}
	else
		temp.insert(0, k, '1');
	QInt KQ;
	Scan(KQ, temp);
	return KQ;

}
//xoay bit trái
QInt QInt::rol()
{
	int first = 0;
	QInt result;
	bool temp;
	for (int i = 1; i < 128; i++)
	{
		temp = getBit((*this).data[i / 32], i % 32);
		if (temp == 1) {
			turnOnBit(result.data[i / 32], i % 32 + 1);
		}
	}
	return result;
}
//xoay bit phải
QInt QInt::ror()
{
	int first = 0;
	QInt result;
	bool temp;
	for (int i = 1; i < 128; i++)
	{
		temp = getBit((*this).data[i / 32], i % 32);
		if (temp == 1) {
			turnOnBit(result.data[i / 32], i % 32 - 1);
		}
	}

	return result;
}
//toán tử so sánh
bool QInt::operator==(QInt& num)
{
	string n1 = this->QInttoString(*this);
	string n2 = this->QInttoString(num);
	if (n1.length() > n2.length()) return false;
	else if (n1.length() < n2.length()) return false;
	else if (n1.length() == n2.length()) {
		for (int i = 0; i < n1.length(); i++) {
			if (n1[i] != n2[i])return false;
		}
		return true;
	}
}
// so sánh lớn hơn
bool QInt::operator>(QInt& num)
{
	string n1 = this->QInttoString(*this);
	string n2 = this->QInttoString(num);
	if (n1.length() > n2.length()) return true;
	else if (n1.length() < n2.length()) return false;
	else if (n1.length() == n2.length()) {
		for (int i = 0; i < n1.length(); i++) {
			if (n1[i] <= n2[i])return false;
		}
		return true;
	}
}
// so sánh nhỏ hơn
bool QInt::operator<(QInt& num)
{
	string n1 = this->QInttoString(*this);
	string n2 = this->QInttoString(num);
	if (n1.length() < n2.length()) return true;
	else if (n1.length() > n2.length()) return false;
	else if (n1.length() == n2.length()) {
		for (int i = 0; i < n1.length(); i++) {
			if (n1[i] >= n2[i])return false;
		}
		return true;
	}
}
// so sánh lớn hơn hoặc bằng
bool QInt::operator>=(QInt& num)
{
	if ((*this) > num || (*this) == num) return true;
	return false;
}
// so sánh nhỏ hơn hoặc bằng
bool QInt::operator<=(QInt& num)
{
	if ((*this) < num || (*this) == num) return true;
	return false;
}

/*ostream& operator<<(ostream& out, QInt& q)
{
	out << "Save: " << q.data[0] << " - " << q.data[1] << " - " << q.data[2] << " - " << q.data[3] << endl;
	out << "Bin:  " << q.QInttoString(q) << endl;
	out << "Hex:  " << q.ToHex() << endl;
	return out;
}

istream& QInt::operator>>(istream& in)
{
	// TODO: insert return statement here
	cout << "Enter  ";
	cout << "Enter  ";
	return in;
}*/
