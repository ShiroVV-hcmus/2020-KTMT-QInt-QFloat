// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;



class Qfloat
{
private:
	unsigned int data[4];
public:

	//Hàm tạo
	Qfloat();
	//Hàm hủy
	~Qfloat();
	string DecToBin32bit(unsigned int x)
	{
		//Chuyển sang nhị phân
		string result;
		while (x > 0)
		{
			result.push_back(x % 2 + '0');
			x /= 2;
		}
		reverse(result.begin(), result.end());
		//Nếu chưa đủ 32 bit thì thêm bit 0 vào trước
		while (result.length() < 32)
		{
			result = '0' + result;
		}

		return result;
	}
	//Hàm lấy giá trị của data
	string Getter()
	{
		string result;


		result = "";
		result = result + DecToBin32bit(this->data[0]);
		result = result + DecToBin32bit(this->data[1]);
		result = result + DecToBin32bit(this->data[2]);
		result = result + DecToBin32bit(this->data[3]);
		return result;
	}

	//Hàm đặt giá trị cho data
	void Setter(int a1, int a2, int a3, int a4)
	{
		this->data[0] = a1;
		this->data[1] = a2;
		this->data[2] = a3;
		this->data[3] = a4;
	}

	void printQfloat(Qfloat t)
	{
		cout << t.data[0] << '\t' << t.data[1] << '\t' << t.data[2] << '\t' << t.data[3] << '\n';
	}

};

//Hàm tạo
Qfloat::Qfloat()
{

}


//Hàm hủy
Qfloat::~Qfloat()
{
	for (int i = 0; i < 4; i++)
	{
		if (this->data[i] != 0)
		{
			this->data[i] = 0;
		}
	}
}

//cau a
void ReadBigNumber(char* prefix, char* suffix, char c[], int& sign)
{
	int i;
	if (c[0] == '-')
	{
		sign = 1;
		i = 1;
		while (c[i] != '.' && c[i] != '\0')
		{
			prefix[i - 1] = c[i];
			i++;
		}
		prefix[i - 1] = '\0';
	}
	else
	{
		sign = 0;
		i = 0;
		while (c[i] != '.' && c[i] != '\0')
		{
			prefix[i] = c[i];
			i++;
		}
		prefix[i] = '\0';
	}// đọc phần nguyên của số vừa nhập

	i++;
	int j = 0;
	while (c[i] != '\0')
	{
		suffix[j] = c[i];
		i++;
		j++;
	}// đọc phần thập phân 
	suffix[j] = '\0';
}
//đọc chuỗi nhập vào chia ra thành phần nguyên trước dấu phẩy và phần thập phân sau dấu phẩy

char* DivideBigNumber(char c[], int x)
{
	int lenght = strlen(c);
	char* result = new char[lenght];
	result = c;
	int tmp = 0;
	int quotient;
	int remainder = 0;
	for (int i = 0; i < lenght; i++)
	{
		quotient = ((int)(c[i] - '0') + 10 * remainder) / x;
		remainder = ((int)(c[i] - '0') + 10 * remainder) % x;
		result[tmp] = quotient + '0';
		tmp++;
	}
	result[tmp] = '\0';
	int i = 0;
	while (result[i] == '0')
	{
		for (int j = 0; j < strlen(result); j++)
		{
			result[j] = result[j + 1];
		}
	}
	return result;
}
//chia số nguyên dưới dạng chuỗi cho 1 số nguyên có 1 chữ số

char* MultiplyBigNumber(char c[], int x)
{
	int length = strlen(c);
	int remember = 0;
	int nguyen;
	char* result = new char[length + 1];
	for (int i = length; i > 0; i--)
	{
		nguyen = ((int)(c[i - 1] - '0') * x + remember) % 10;
		remember = ((int)(c[i - 1] - '0') * x + remember) / 10;
		result[i] = '0' + nguyen;
	}// nhân theo từng chữ số từ phải sang trái

	result[length + 1] = '\0';
	if (remember > 0)
	{
		result[0] = remember + '0';
	}
	else
	{
		for (int i = 0; i < strlen(result); i++)
		{
			result[i] = result[i + 1];
		}
	}// kiểm tra số chữ số của kết quả
	return result;
}
//nhân số nguyên dưới dạng chuỗi với 1 số nguyên có 1 chữ số

char* MinusBigNumber(char a[], char b[])
{
	int length1 = strlen(a);
	int length2 = strlen(b);
	int remember = 0;
	char* result = new char[length1];
	int i = 0;
	while (i < length2 || remember != 0)
	{
		if (i < length2)
		{
			if (a[length1 - 1 - i] - b[length2 - 1 - i] + remember < 0)
			{
				result[length1 - 1 - i] = 10 + a[length1 - 1 - i] - b[length2 - 1 - i] + remember + '0';
				remember = -1;
			}
			else
			{
				result[length1 - 1 - i] = a[length1 - 1 - i] - b[length2 - 1 - i] + remember + '0';
				remember = 0;
			}
		}
		else
		{
			if (a[length1 - 1 - i] + remember < '0')
			{
				result[length1 - 1 - i] = a[length1 - 1 - i] + 10 + remember;
				remember = -1;
			}
			else
			{
				result[length1 - 1 - i] = a[length1 - 1 - i] + remember;
				remember = 0;
			}
		}
		i++;
	} // trừ từ trái qua phải từng chữ số
	result[length1] = '\0';
	int tmp = 0;
	while (result[tmp] == '0')
	{
		for (int i = 0; i < strlen(result); i++)
		{
			result[i] = result[i + 1];
		}
	}// xóa các số 0 nằm ở đầu kết quả
	return result;
}
// trừ 2 số dưới dạng chuỗi (số a > số b)

char* BigNumberToBin(char c[])
{
	char* result = new char[128];
	char* tmp = new char[128];
	int length;
	int i = 0;
	while (strlen(c) > 0)
	{
		length = strlen(c);
		if (c[length - 1] == '1' || c[length - 1] == '3' || c[length - 1] == '5' || c[length - 1] == '7' || c[length - 1] == '9')
		{
			tmp[i] = '1';
		}
		else
		{
			tmp[i] = '0';
		}
		i++;
		c = DivideBigNumber(c, 2);
	}// chia cho 2 cho đến khi bằng 0, xét các số dư vào mảng tmp
	for (int j = 0; j <= i; j++)
	{
		result[j] = tmp[i - 1 - j];
	}// đảo ngược mảng tmp ta được chuỗi nhị phân
	result[i] = '\0';
	delete tmp;
	return result;
}
// chuyển đổi 1 số thập phân dưới dạng chuỗi về chuỗi nhị phân

char* Ten_Exponent(int x)
{
	char* result = new char[x + 1];
	result[0] = '1';
	for (int i = 1; i <= x; i++)
	{
		result[i] = '0';
	}
	result[x + 1] = '\0';
	return result;
}
// tạo ra sô 10^x dưới dạng chuỗi

char* FractionToBin(char c[])
{
	char* result = new char[128];
	char* tmp = new char[128];
	int i = 0;
	while (strlen(c) > 0 && i < 127)
	{
		if (c[0] < '5')
		{
			result[i] = '0';
			c = MultiplyBigNumber(c, 2);
		}// nếu c * 2 < 1 thì viết 0
		else
		{
			result[i] = '1';
			tmp = Ten_Exponent(strlen(c));
			c = MultiplyBigNumber(c, 2);
			c = MinusBigNumber(c, tmp);
		}// nếu c * 2 > 1 thì viết 1
		i++;
	}
	result[i] = '\0';
	return result;
}
// chuyển phần sau dấu phẩy thành chuỗi nhị phân

char* IntToBin(int x)
{
	char* result = new char[15];
	int count;
	char* tmp = new char[15];
	int i = 0;
	while (x != 0)
	{
		if (x % 2 == 1)
		{
			tmp[i] = '1';
		}
		else
		{
			tmp[i] = '0';
		}
		x = x / 2;
		i++;
	}// chia 2 cho đến khi = 0, lưu số dư vào mảng tmp
	int a = 15 - i;
	while (a > 0)
	{
		result[a - 1] = '0';
		a--;
	}// gán các số 0 nếu chưa đủ 15 bit

	for (int j = 0; j < i; j++)
	{
		result[15 - i + j] = tmp[i - 1 - j];
	}// đảo ngược mảng tmp ta được số nhị phân
	result[15] = '\0';
	return result;
}
// chuyển đôi 1 số nguyên về chuỗi nhị phân

char* AddBin(char a[], int x)
{
	char* c = new char[15];
	int length1 = strlen(a);
	char* result = new char[length1];

	c = IntToBin(x);
	//chuyển số trừ qua nhị phân (<= 15 bit)
	int length2 = strlen(c);
	int remember = 0;
	int i = 0;
	while (i < length2 || remember != 0)
	{
		if (i < length2)
		{
			result[length1 - 1 - i] = (a[length1 - 1 - i] + c[length2 - 1 - i] + remember - 2 * '0') % 2 + '0';
			if ((a[length1 - 1 - i] + c[length2 - 1 - i] + remember - 2 * '0') > 1)
			{
				remember = 1;
			}
			else
			{
				remember = 0;
			}
		}
		else
		{
			result[length1 - 1 - i] = (a[length1 - 1 - i] + remember - '0') % 2 + '0';
			if ((a[length1 - 1 - i] + remember - '0') > 1)
			{
				remember = 1;
			}
			else
			{
				remember = 0;
			}
		}
		i++;
	}// cộng từng chữ số từ trái qua phải
	if (i < length1)
	{
		for (int j = 0; j < length1 - i; j++)
		{
			result[j] = a[j];
		}
	}// gán các chữ số chưa cộng còn lại của số bị trừ vào kết quả
	result[length1] = '\0';
	return result;
}
// phép cộng nhị phân của 1 chuỗi nhị phân với 1 số nguyên

char* MinusBin(char a[], int x)
{
	char* c = new char[15];
	int length1 = strlen(a);
	char* result = new char[length1];
	c = IntToBin(x);
	// chuyển số trừ qua nhị phân (> 15 bit)
	int tmp = 0;
	while (c[tmp] == '0')
	{
		for (int j = 0; j < strlen(c); j++)
		{
			c[j] = c[j + 1];
		}
	}// xóa các số 0 thừa ở số trừ sau khi chuyển đổi
	int length2 = strlen(c);
	int remember = 0; // biến nhớ
	int i = 0;
	while (i < length2 || remember != 0)
	{
		if (i < length2)
		{
			if ((a[length1 - 1 - i] - c[length2 - 1 - i] + remember) < 0)
			{
				result[length1 - 1 - i] = 2 + a[length1 - 1 - i] - c[length2 - 1 - i] + remember + '0';
				remember = -1;
			}
			else
			{
				result[length1 - 1 - i] = a[length1 - 1 - i] - c[length2 - 1 - i] + remember + '0';
				remember = 0;
			}
		}
		else
		{
			if (a[length1 - 1 - i] + remember - '0' < 0)
			{
				result[length1 - 1 - i] = 2 + a[length1 - 1 - i] + remember;
				remember = -1;
			}
			else
			{
				result[length1 - 1 - i] = a[length1 - 1 - i] + remember;
				remember = 0;
			}
		}
		i++;
	}//trừ từng chữ số từ trái qua phải 
	if (i < length1)
	{
		for (int j = 0; j < length1 - i; j++)
		{
			result[j] = a[j];
		}
	}// gán các chữ số chưa bị trừ còn lại của số bị trừ vào kết quả

	result[length1] = '\0';
	return result;
}
// phép trừ nhị phân của 1 chuỗi nhị phân cho 1 số nguyên

char* QuadrulplePrecision(char* prefix, char* suffix, int sign)
{
	int const1 = 15;
	int const2 = 112;

	char* result = new char[128];
	result[0] = sign + '0';
	int count = 1;
	int K = pow(2, const1 - 1) - 1;
	int E = 0;
	// mảng tạm để lưu các số ở trong fraction
	char* tmp = new char[112];
	int counttp = 0;

	if (prefix[0] == '0' && strlen(prefix) == 1)
	{
		while (suffix[E] != '1' && suffix[E] != '\0')
		{
			E++;
		}
		E = -1 - E;
	}
	else
	{
		E = strlen(prefix) - 1;
	}// tính số mũ
	if (E == -128)
	{
		while (count < 128)
		{
			result[count] = '0';
			count++;
		}
	}// trường hợp input = 0
	else
	{
		int exp = E + K;
		char* exponent = new char[15];
		exponent = IntToBin(exp);
		for (int i = 0; i < 15; i++)
		{
			result[count] = exponent[i];
			count++;
		}

		if (E > 0)
		{
			for (int i = 0; i < E; i++)
			{
				tmp[counttp] = prefix[i + 1];
				counttp++;
			}
			for (int i = 0; i < strlen(suffix) && counttp < 112; i++)
			{
				tmp[counttp] = suffix[i];
				counttp++;
			}
		}
		else
		{
			for (int i = -E; i < strlen(suffix) && counttp < 112; i++)
			{
				tmp[counttp] = suffix[i];
				counttp++;
			}
		}
		// lưu các bit vào mảng fraction theo từng trường hợp
		tmp[112] = '\0';
		if (strlen(suffix) > (112 - E) && strlen(suffix) <= 127)
		{
			if (sign == 1)
			{
				tmp = MinusBin(tmp, 1);
			}
			else
			{
				tmp = AddBin(tmp, 1);
			}
		}// xử lí nếu phần thập phân chuyển về nhị phân lặp lại vô hạn tuần hoàn
		else
		{
			for (int i = strlen(suffix) + E; i < 112; i++)
			{
				tmp[i] = '0';
			}
		}// thêm các bit 0 nếu tmp chưa đủ 112 bit

		for (int i = 0; i < 112; i++)
		{
			result[count] = tmp[i];
			count++;
		}
		// gán các bit của tmp vỏ kết quả
	}
	result[128] = '\0';

	return result;
}
// hàm chuyển đổi chuỗi số thập phân về dãy 128 bit


unsigned int Bin32bitToDec(char* c)
{
	unsigned int result = 0;
	for (int i = 31; i >= 0; i--)
	{
		//Nếu bit i = 1 thì cộng thêm 2^(31 - i) vào kết quả
		if (c[i] == '1')
		{
			result += pow(2, 31 - i);
		}
	}
	return result;
}
//Hàm chuyển dãy 32 bit kiểu Binary qua Int để thêm vào phần tử của QFloat

int BinToDec(char c[])
{
	int length = strlen(c);
	int result = 0;
	for (int i = length - 1; i >= 0; i--)
	{
		if (c[i] == '1')
		{
			result += pow(2, length - 1 - i);
		}
	}
	return result;
}
// chuyển số nhị phân sang thập phân


char* ScanQfloat(Qfloat& q, char c[])
{
	int sign;

	char* result = new char[128];
	char* prefix = new char[128];
	char* suffix = new char[128];

	ReadBigNumber(prefix, suffix, c, sign);

	prefix = BigNumberToBin(prefix);
	suffix = FractionToBin(suffix);

	result = QuadrulplePrecision(prefix, suffix, sign);
	char* part1 = new char[32];
	char* part2 = new char[32];
	char* part3 = new char[32];
	char* part4 = new char[32];

	int i = 0, count = 0;

	//Chia dãy 128 bit thành 4 phần 
	for (i = 0; i < 32; i++)
	{
		part1[count] = result[i];
		count++;
	}

	count = 0;
	for (i = 32; i < 64; i++)
	{
		part2[count] = result[i];
		count++;
	}

	count = 0;
	for (i = 64; i < 96; i++)
	{
		part3[count] = result[i];
		count++;
	}

	count = 0;
	for (i = 96; i < 128; i++)
	{
		part4[count] = result[i];
		count++;
	}

	//Cho kết quả vào QFloat bằng hàm Bit32bitToDec
	q.Setter(Bin32bitToDec(part1), Bin32bitToDec(part2), Bin32bitToDec(part3), Bin32bitToDec(part4));
	return result;
}

//cau b
void ReadBit(char c[], char* exponent, char* fraction, int& sign)
{
	sign = c[0] - '0';
	int i = 1;
	for (; i < 15; i++)
	{
		exponent[i - 1] = c[i];
	}
	for (; i < 128; i++)
	{
		fraction[i - 16] = c[i];
	}
}

//Hàm chuyển 1 số nguyên int sang 1 nhị phân 32 bit


void PrintQFloat(Qfloat q)
{
	string result;

	result = q.Getter();

	cout << result << endl;
}

char* ReadFraction(char c[])
{
	char* result = NULL;
	int length = strlen(c);
	int i = length - 1;
	while (c[i] != '0')
	{
		i--;
	}

	return result;
}

char* Set128Bit(char s[])
{
	char* result = new char[128];
	int length = strlen(s);
	for (int i = 0; i < length; i++)
	{
		result[127 - i] = s[length - 1 - i];
	}
	result[128] = '\0';
	return result;
}// nếu chuỗi chưa đủ 128 bit thêm các bit 0 bên phải cho đủ 128 bit

char* PowerOf2(int x)
{
	char* result = NULL;
	if (x > 0)
	{
		result = new char[1];
		result[0] = '1';
		result[1] = '\0';
		for (int i = 0; i < x; i++)
		{
			result = MultiplyBigNumber(result, 2);
		}
	}
	if (x < 0)
	{
		result = new char[-x + 1];
		result = Ten_Exponent(-x);
		for (int i = 0; i < -x; i++)
		{
			result = DivideBigNumber(result, 2);
		}
		int length = strlen(result);
		for (int i = 0; i < length; i++)
		{
			result[-x - 1 - i] = result[length - 1 - i];
		}
		result[x] = '\0';
		for (int i = 0; i < -x - length; i++)
		{
			result[i] = '0';
		}
		result[-x] = '\0';
	}
	if (x == 0)
	{
		result = new char[1];
		result[0] = '1';
		result[1] = '\0';
	}
	return result;
}

char* AddSuffix(char* a, char* b)
{
	int length1 = strlen(a);
	int length2 = strlen(b);
	int remember = 0;
	char* result = new char[length2];

	for (int i = length1; i < length2; i++)
	{
		result[i] = b[i];
	}

	for (int i = length1 - 1; i >= 0; i--)
	{
		if ((a[i] + b[i] + remember - 2 * '0') > 9)
		{
			result[i] = a[i] + b[i] + remember - 10 - '0';
			remember = 1;
		}
		else
		{
			result[i] = a[i] + b[i] + remember - '0';
			remember = 0;
		}
	}
	result[length2] = '\0';
	return result;
}
// cong phan thap phan

char* AddPrefix(char* a, char* b)
{
	int length1 = strlen(a);
	int length2 = strlen(b);
	int remember = 0;
	char* result = new char[length1 + 1];
	for (int i = 0; i < length1; i++)
	{
		result[i + 1] = a[i];
	}
	result[length1 + 1] = '\0';

	int i = 0;
	while (i < length2 || remember != 0)
	{
		if (i < length2)
		{
			if (a[length1 - 1 - i] + b[length2 - 1 - i] + remember - 2 * '0' > 9)
			{
				result[length1 - i] = a[length1 - 1 - i] + b[length2 - 1 - i] + remember - '0' - 10;
				remember = 1;
			}
			else
			{
				result[length1 - i] = a[length1 - 1 - i] + b[length2 - 1 - i] + remember - '0';
				remember = 0;
			}
		}
		else
		{
			if (length1 - 1 - i >= 0)
			{
				if (a[length1 - 1 - i] + remember > '9')
				{
					result[length1 - i] = a[length1 - 1 - i] - 10 + remember;
					remember = 1;
				}
				else
				{
					result[length1 - i] = a[length1 - 1 - i] + remember;
					remember = 0;
				}
			}
			else
			{
				result[length1 - i] = '0' + remember;
				remember = 0;
			}
		}
		i++;
	}
	if (i <= length1)
	{
		for (int j = 0; j < length1; j++)
		{
			result[j] = result[j + 1];
		}
		result[length1] = '\0';
	}
	return result;
}
// cong phan nguyen

char* ReadPrefix(char* a)
{
	char* result = new char[1];
	result[0] = '0';
	result[1] = '\0';
	int length = strlen(a);

	char* tmp;
	for (int i = 0; i < length; i++)
	{
		if (a[length - 1 - i] == '1')
		{
			tmp = PowerOf2(i);
			result = AddPrefix(tmp, result);
		}
	}
	return result;
}

//Hàm kiểm tra các phần tử của chuỗi có cùng 1 kí tự không
bool Check(char* s, char a)
{
	int length = strlen(s);
	for (int i = 0; i < length; i++)
	{
		if (s[i] != a)
		{
			return false;
		}
	}
	return true;
}

char* Bin128bitToDec(char* s)
{
	if (strlen(s) < 128)
	{
		s = Set128Bit(s);
	}

	int sign;
	if (s[0] == '0')
	{
		sign = 0;
	}
	else
	{
		sign = 1;
	}//xác định bit dấu

	char* exponent = new char[15];
	for (int i = 1; i < 16; i++)
	{
		exponent[i - 1] = s[i];
	}
	exponent[15] = '\0';
	//xác định phần mũ

	char* fraction = new char[112];
	for (int i = 16; i < 128; i++)
	{
		fraction[i - 16] = s[i];
	}
	char* a = new char[20];
	fraction[112] = '\0';
	if ((Check(exponent, '0')) && Check(fraction, '0'))
	{
		a[0] = '0';
		a[1] = '\0';
		return a;
	}

	if ((Check(exponent, '1')) && !Check(fraction, '0'))
	{
		a[0] = 'N';
		a[1] = 'a';
		a[2] = 'N';
		a[3] = '\0';
		return a;
	}

	if ((Check(exponent, '0')) && !Check(fraction, '0'))
	{
		a[0] = 'D';
		a[1] = 'e';
		a[2] = 'n';
		a[3] = 'o';
		a[4] = 'r';
		a[5] = 'm';
		a[6] = 'a';
		a[7] = 'l';
		a[8] = 'i';
		a[9] = 'z';
		a[10] = 'e';
		a[11] = 'd';
		a[12] = '\0';
		return a;
	}

	if ((Check(exponent, '1')) && Check(fraction, '0'))
	{
		a[0] = 'I';
		a[1] = 'n';
		a[2] = 'f';
		a[3] = 'i';
		a[4] = 'n';
		a[5] = 'i';
		a[6] = 't';
		a[7] = 'y';
		a[8] = '\0';
		return a;
	}
	// xac dinh phan fraction

	int exp = BinToDec(exponent);
	int E = exp - pow(2, 14) + 1;

	char* pre = new char[abs(E)]; // phần trc dấu phẩy
	pre[0] = '0';
	pre[1] = '\0';
	char* suf = new char[abs(E)]; // phần sau dấu phẩy
	suf[0] = '0';
	suf[1] = '\0';
	char* tmp = new char[abs(E)];
	tmp[0] = '0';
	tmp[1] = '\0';

	tmp = PowerOf2(E);
	if (E >= 0)
	{
		pre = AddPrefix(tmp, pre);
	}
	else
	{
		suf = AddSuffix(suf, tmp);
	}

	int j = 0;
	for (; j < E; j++)
	{
		if (fraction[j] == '1')
		{
			tmp = PowerOf2(E - 1 - j);
			pre = AddPrefix(pre, tmp);
		}
	}

	for (; j < 112; j++)
	{
		if (fraction[j] == '1')
		{
			tmp = PowerOf2(E - 1 - j);
			suf = AddSuffix(suf, tmp);
		}
	}

	int length = strlen(pre) + strlen(suf) + 2;
	char* result = new char[length];
	int count = 0;
	if (sign == 1)
	{
		result[count] = '-';
		count++;
	}
	for (int i = 0; i < strlen(pre); i++)
	{
		result[count] = pre[i];
		count++;
	}
	result[count] = '.';
	count++;
	for (int i = 0; i < strlen(suf); i++)
	{
		result[count] = suf[i];
		count++;
	}
	result[count] = '\0';
	return result;
}

//Hàm người dùng
void User()
{
	int k;
	char* base10 = new char[1000];
	char* base2 = new char[1000];
	do
	{
		system("cls");
		cout << "------------USER------------" << endl;
		cout << "Nhap 0 de thoat giao dien nguoi dung." << endl;
		cout << "Nhap 1 de chuyen so thu co so 10 sang co so 2." << endl;
		cout << "Nhap 2 de chuyen so thu co so 2 sang co so 10." << endl;
		cin >> k;
		Qfloat q;
		switch (k)
		{
		case 1:
			system("cls");
			cout << "			~~~~~10->2~~~~~" << endl;
			cout << "Nhap so can chuyen: ";
			cin >> base10;
			cout << "Ket qua la: ";
			cout<< ScanQfloat(q, base10);
			cout << endl;
			system("pause");
			break;
		case 2:
			system("cls");
			cout << "			~~~~~2->10~~~~~" << endl;
			cout << "Nhap so can chuyen: ";
			cin >> base2;
			base2 = Bin128bitToDec(base2);
			cout << "Ket qua la: " << base2 << endl;
			system("pause");
			break;
		default:
			break;
		}
	} while (k != 0);
}

//Hàm đọc giá trị từ file và thực hiện sau đó in ra màn hình
void ReadFile(char* argv[])
{
	fstream f;
	fstream fw;
	int base1, base2;
	Qfloat q;
	char* c = NULL;
	f.open(argv[1], ios_base::in);
	fw.open(argv[2], ios::out);
	if (!f)
	{
		cout << "Khong mo duoc file!!!" << endl;
		system("pause");
		return;
	}
	while (!f.eof())
	{
		f >> base1;
		f >> base2;
		c = new char[200];
		f >> c;
		c[strlen(c)] = '\0';
		if ((base1 == 10) && (base2 == 2))
		{
			fw << ScanQfloat(q, c);//?
			fw << endl;
		}
		if ((base1 == 2) && (base2 == 10))
		{
			c = Bin128bitToDec(c);
			fw << c << endl;
		}
	}
	f.close();
	fw.close();
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
