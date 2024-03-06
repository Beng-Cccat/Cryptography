#include<iostream>
#include<fstream>
#include<string>
#include<math.h>
using namespace std;

char s[17] = { 'E', '4', 'D', '1', '2', 'F', 'B', '8', '3', 'A', '6', 'C', '5', '9', '0', '7', '\0' };
int s1[17];
int Count[16][16];

int L1[4];
int L2[4];
int v[17] = { 0 };
int u[17] = { 0 };

void DectoBin(int* binaryStr, int text) {
	//把十进制转化为四位二进制数

	for (int i = 3; i >= 0; i--) {
		if (text % 2)
			binaryStr[i] = 1;
		else
			binaryStr[i] = 0;
		text /= 2;
	}
}
void linear(string x,string y) {

	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			DectoBin(L1, i);
			DectoBin(L2, j);

			v[4] = L1[0] ^ (y[4] - '0');
			v[5] = L1[1] ^ (y[5] - '0');
			v[6] = L1[2] ^ (y[6] - '0');
			v[7] = L1[3] ^ (y[7] - '0');

			v[12] = L2[0] ^ (y[12] - '0');
			v[13] = L2[1] ^ (y[13] - '0');
			v[14] = L2[2] ^ (y[14] - '0');
			v[15] = L2[3] ^ (y[15] - '0');

			int len1 = v[4] * pow(2, 3) + v[5] * pow(2, 2) + v[6] * pow(2, 1) + v[7] * pow(2, 0);
			DectoBin(u+4, s1[len1]);
			//cout << "len1:" << len1 << " s1[len1]:" << s1[len1] << " u:" << u[4] << u[5] << u[6] << u[7] << endl;

			int len2 = v[12] * pow(2, 3) + v[13] * pow(2, 2) + v[14] * pow(2, 1) + v[15] * pow(2, 0);
			DectoBin(&(u[12]), s1[len2]);
			//cout << "len2:" << len2 << " s1[len2]:" << s1[len2] << " u:" << u[12] << u[13] << u[14] << u[15] << endl;

			int z = (x[4]-'0') ^ (x[6]-'0') ^ (x[7]-'0') ^ u[5] ^ u[7] ^ u[13] ^ u[15];
			//cout << "z:" << z << endl;

			if (z == 0)
				Count[i][j]++;
		}
	}
}
int main() {
	string x;
	string y;
	streampos lastPos = 0;
	int num;
	cout << "Please input num:" << endl;
	cin >> num;
	for (int i = 0; i < 16; i++) {
		if (s[i] >= '0' && s[i] <= '9')
			s1[s[i] - '0'] = i;
		else
			s1[s[i] - 'A' + 10] = i;
	}
	for (int i = 0; i < 16; i++)
		for (int j = 0; j < 16; j++)
			Count[i][j] = 0;
	
	ifstream inputfile; 
	inputfile.open("example2.txt");
	for(int i=0;i<num;i++)
	{
		inputfile.seekg(lastPos);
		getline(inputfile, x);
		getline(inputfile, y);
		lastPos = inputfile.tellg();
		linear(x, y);
	}

	int max = -1;
	int maxkey_1 = 0;
	int maxkey_2 = 0;
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			Count[i][j] = abs(Count[i][j] - num / 2);
			if (Count[i][j] > max) {
				max = Count[i][j];
				maxkey_1 = i;
				maxkey_2 = j;
			}
		}
	}
	int maxkey_L1[4];
	int maxkey_L2[4];
	DectoBin(maxkey_L1, maxkey_1);
	DectoBin(maxkey_L2, maxkey_2);
	cout << "maxkey:" << endl;
	for (int i = 0; i < 4; i++)
		cout << maxkey_L1[i];
	cout << ' ';
	for (int i = 0; i < 4; i++)
		cout << maxkey_L2[i];
	cout << ' ';

}