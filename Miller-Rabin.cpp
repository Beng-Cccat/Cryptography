#include<iostream>
#include<math.h>
using namespace std;
void get_kt(long long num,long long &k,long long &t) {
	long long num1 = num - 1;
	while (num1 % 2 == 0) {
		num1 /= 2;
		k++;
	}
	t = num1;
}
long long quickmul_mod(long long a, long long b,long long p) {
	long long result = 0;
	while (b) {
		//将b转化成二进制进行快速乘，从最低位开始计算
		if (b % 2==1)
			result = (result + a) % p;
		a = (a + a) % p;
		b /= 2;
	}
	return result;
}
long long quickpow_mod(long long base, long long power, long long p) {
	long long result = 1;
	while (power) {
		//将指数转化为二进制数
		if (power % 2 == 1)
			//此时这一个二进制位是1，对应的数（base）需要乘到result上
			result = quickmul_mod(result, base, p);
		//不管需不需要，base都要乘自身
		base = quickmul_mod(base, base, p);
		//进行下一位二进制数的判断
		power /= 2;
	}
	return result;
}
bool Miller(long long num) {
	if (num == 2)
		return true;
	if (num < 2 || num % 2 == 0)
		return false;
	long long k = 0;
	long long t = 0;
	get_kt(num, k, t);
	long long a[9] = { 2,7,61,325,9375,28178,450775,9780504,1795265022 };

	for (int i = 0; i < 9; i++) {
		if (a[i] > num)
			break;
		bool tag1 = true;//模后全1
		bool tag_n = false;//模后除在0~k-1间有一个num-1
		long long temp = a[i];
		long long temp_temp = quickpow_mod(temp, t, num);
		long long temp_temp_temp;
		for (long long j = 0; j <= k; j++) {
			temp_temp_temp = quickmul_mod(temp_temp, temp_temp, num);
			if (temp_temp != 1) {
				tag1 = false;
				//做不到“模全1”的条件
			}
			if (j != k && temp_temp == num - 1) {
				tag_n = true;
			}
			temp_temp = temp_temp_temp;
		}
		if (temp_temp_temp == 1 && (tag1 || tag_n))
			//最后a^(t*2^k)=1(mod num)且前面的要么全1要么在1~k-1中模出现num-1
			continue;
		else
			return false;
	}
	return true;
}
int main() {
	long long num;
	cin >> num;
	if (Miller(num))
		cout << "Yes";
	else
		cout << "No";

}