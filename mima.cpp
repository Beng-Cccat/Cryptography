#include<iostream>
#include<iomanip>
#include<math.h>
using namespace std;
float q[27] = { 0.0 ,0.082,0.015,0.028,0.043,0.127,
				0.022,0.02,0.061,0.07,0.002,0.008,
				0.04,0.024,0.067,0.075,0.019,0.001,
				0.06,0.063,0.091,0.028,0.01,0.023,
				0.001,0.02,0.001 };
string str = "0KCCPKBGUFDPHQTYAVINRRTMVGRKDNBVFDETDGILTXRGUDDKOTFMBPVGEGLTGCKQRACQCWDNAWCRXIZAKFTLEWRPTYCQKYVXCHKFTPONCQQRHJVAJUWETMCMSPKQDYHJVDAHCTRLSVSKCGCZQQDZXGSFRLSWCWSJTBHAFSIASPRJAHKJRJUMVGKMITZHFPDISPZLVLGWTFPLKKEBDPGCEBSHCTJRWXBAFSPEZQNRWXCVYCGAONWDDKACKAWBBIKFTIOVKCGGHJVLNHIFFSQESVYCLACNVRWBBIREPBBVFEXOSCDYGZWPFDTKFQIYCWHJVLNHIQIBTKHJVNPIST";
float part[20][27];
float chonghezhishu(int m) {
	string str_part[20];

	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 27; j++)
			part[i][j] = 0;

	for (int i = 1; i <= m; i++) {
		//总共m个字符串
		part[i][0]++;
		int m_now = i;
		str_part[i]=str_part[i] + str[m_now];
		part[i][str[m_now] - 'A' + 1]++;
		while (m_now + m < str.length()) {
			part[i][0]++;
			part[i][str[m_now] - 'A' + 1]++;
			m_now += m;
			str_part[i] = str_part[i] + str[m_now];
		}
	}//part[0]这一行没有实际意义
	for (int i = 1; i <= m; i++)
		cout << "y" << i << "=" << str_part[i] << endl;

	float sum[20] = { 0 };
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <=26; j++) {
			sum[i] += (part[i][j] * (part[i][j]-1))/ (part[i][0] * (part[i][0] - 1));
		}
	}

	cout << "ic分别为：" << endl;
	for (int i = 1; i <= m; i++)
		cout << sum[i] << ' ';
	cout << endl;

	float sum_sum = 0;
	for (int i = 1; i <= m; i++)
		sum_sum += sum[i];

	float ave = sum_sum / m;
	cout << "平均重合指数为："<<ave << endl << endl;
	return ave;
}
void getM(int m,int *k) {
	float Mg[20][27];
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 27; j++)
			Mg[i][j] = 0.0;

	for (int i = 1; i <= m; i++) {//表示第几个字符串
		for (int g = 1; g <= 26; g++) {//表示移位量
			for (int j = 0; j < 26; j++) {//表示第几个英文字母
				int xiabiao = (j + g) % 26;
				Mg[i][g] += q[j+1] * part[i][xiabiao+1] / part[i][0];
			}
		}
	}
	for (int i = 1; i <= m; i++) {
		cout << "i=" << i << ":" << endl;
		for (int j = 1; j <= 26; j++) {
			cout << setw(9)<<left<<Mg[i][j] << ' ';
		}
		cout << endl;
	}

	for (int i = 1; i <= m; i++) {
		Mg[i][0] = Mg[i][1];
		for (int j = 1; j < 26; j++) {
			if (Mg[i][j + 1] > Mg[i][0]) {
				Mg[i][0] = Mg[i][j + 1];
				k[i] = j + 1;
			}
		}
	}
	cout << "密钥K=（";
	for (int i = 1; i < m; i++)
		cout << k[i] << ",";
	cout << k[m]<<")";
}
void solve(int m,int *k) {
	string str1;
	int j = -1;
	for (int i = 1; i < str.length(); i++) {
		j = (j + 1) % m;
		int temp = (str[i] - 'A' - k[j+1]+26) % 26;
		str1 = str1 + (char)('A' + temp);
	}
	cout <<"明文为："<< str1;
}
int main() {
	int m;
	for (int i = 1;; i++) {
		cout << "m=" << i << "时," << endl;
		float ave=chonghezhishu(i);
		if (abs(ave - 0.065) <= 0.003) {
			m = i;
			cout << "所以，m=" << m << endl;
			break;
		}
	}
	int k[20] = { 0 };
	getM(m,k);
	cout << endl << endl;
	solve(m, k);
}