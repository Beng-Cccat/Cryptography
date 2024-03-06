#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std;

const int q = 13;

long long quickmul_mod(long long a, long long b, long long p) {
	long long result = 0;
	while (b) {
		//将b转化成二进制进行快速乘，从最低位开始计算
		if (b % 2 == 1)
			result = (result + a) % p;
		a = (a + a) % p;
		b /= 2;
	}
	return result;
}

long long Tobinary(long long m, long long* b) {
	long long a[40] = { 0 };
	long long count = 0;
	while (m != 0) {
		a[count] = m % 2;
		m /= 2;
		count++;
	}
	for (long long i = 0; i < count; i++) {
		b[i] = a[count - i - 1];
	}
	return count;
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

long long inv(long long a, long long b) {
	return quickpow_mod(a, b - 2, b);
}

long long inverse(long long a, long long b) {
	long long r0, r1;
	r0 = a >= b ? a : b;
	r1 = a <= b ? a : b;
	long long s0, s1, t0, t1;
	s0 = t1 = 1;
	s1 = t0 = 0;
	long long ri, si, ti, q;
	ri = r1;
	si = s1;
	ti = t1;
	while (true) {
		q = r0 / r1;
		ri = r0 - r1 * q;
		if (ri == 0) {
			break;
		}
		r0 = r1;
		r1 = ri;
		si = s0 - q * s1;
		s0 = s1;
		s1 = si;
		ti = t0 - q * t1;
		t0 = t1;
		t1 = ti;
	}
	if (si < 0) {
		if (a >= b) {
			si += b;
		}
		else {
			si += a;
		}
	}
	if (ti < 0) {
		if (a <= b) {
			ti += b;
		}
		else {
			ti += a;
		}
	}
	if (a >= b) {
		return si;
	}
	else {
		return ti;
	}
}

class point {
public:
	long long x;
	long long y;
	point() {};
	point(long long x, long long y) {
		this->x = x;
		this->y = y;
	}
	void print() {
		cout << setw(2) << "(" << setw(2) << x << setw(2) << "," << setw(2) << y << setw(2) << ")" << setw(2) << ' ';
	}
};

class E {
public:
	long long p;
	long long a;
	long long b;
	E() {};
	E(long long p, long long a, long long b) {
		this->p = p;
		this->a = a;
		this->b = b;
	}
	point add_PQ(point P, point Q) {
		point K;

		//判断其中有没有无穷远点
		if (P.x == -1 && P.y == -1 && Q.x != -1 && Q.y != -1) {
			K.x = Q.x;
			K.y = Q.y;
			return K;
		}
		else if (P.x != -1 && P.y != -1 && Q.x == -1 && Q.y == -1) {
			K.x = P.x;
			K.y = P.y;
			return K;
		}
		else if (P.x == -1 && P.y == -1 && Q.x == -1 && Q.y == -1) {
			K.x = -1;
			K.y = -1;
			return K;
		}

		//判断两者是否反相
		if ((P.y + Q.y) % p == 0 && P.x == Q.x) {
			K.x = -1;
			K.y = -1;
			return K;
		}//P=-Q，相加为无穷远点O

		//常规情况
		long long k_son;
		long long k_mother;

		//确定k的分子分母
		//P和Q重合（坐标相同），无法定义直线，使用极限的方法
		if (P.x == Q.x) {
			k_son = 3 * quickmul_mod(P.x, P.x, p) + a;
			k_mother = 2 * P.y;
		}
		else {//P.x!=Q.x
			k_son = Q.y - P.y;
			k_mother = Q.x - P.x;
		}

		//确定正负
		long long sign;
		if (k_son >= 0 && k_mother >= 0 || k_son < 0 && k_mother < 0)
			sign = 1;
		else sign = -1;

		//取正
		k_son = abs(k_son);
		k_mother = abs(k_mother);

		//得到k的值
		long long k;
		if (k_mother != 1)//没有逆元
			k = quickmul_mod(k_son, inverse(k_mother, p), p) % p;
		else
			k = quickmul_mod(k_son, 1, p) % p;
		k *= sign;

		//得到最终的横纵坐标
		//K.x = (quickmul_mod(k, k, p) - P.x % p - Q.x % p)%p;
		K.x = (k * k - P.x - Q.x) % p;
		//K.y = (quickmul_mod(k, (P.x - K.x), p) - P.y % p)%p;
		K.y = (k * (P.x - K.x) - P.y) % p;
		if (K.x < 0)
			K.x += p;
		if (K.y < 0)
			K.y += p;

		//返回值
		return K;
	}
	point add_mul_PQ(point P, long long m1) {
		long long b[40] = { 0 };
		long long m = Tobinary(m1, b);
		//b[0]-b[m-1]是binary（M->L)
		point K;
		K.x = -1;
		K.y = -1;
		for (long long i = 0; i < m; i++) {
			//比如2的表示为[1,0,....]
			K = add_PQ(K, K);
			if ((b[i]) == 1)
				K = add_PQ(K, P);
		}
		return K;
	}
};

point getmA(int m,point A) {
	E e;
	e.p = 11;
	e.a = 1;
	e.b = 6;
	
	point result = e.add_mul_PQ(A, m);
	return result;
}
int main() {
	/*long long p, a, b;
	E e;
	cin >> a >> b >> p;
	e.p = p;
	e.a = a;
	e.b = b;

	point P;
	cin >> P.x >> P.y;

	long long k;
	//cout << "k=";
	cin >> k;
	point K1 = e.add_mul_PQ(P, k);
	//cout << "add_mul_PQ(P, " << k << ") = (" << K1.x << ", " << K1.y << ")" << endl;
	cout << K1.x << ' ' << K1.y;
	*/
	point A;
	cin >> A.x >> A.y;
	

	int	m, x, k;
	cin >> m >> x >> k;

	point B=getmA(m, A);
	//cout << "B:"<<B.x << ' '<< B.y << endl;
	point kA = getmA(k, A);
	//cout << "kA:" << kA.x << ' '<< kA.y << endl;

	int u = kA.x;
	//cout << "u=" << u << endl;
	int v = kA.y;
	//cout << "v=" << v << endl;

	int r = u % q;
	//cout << "r=" << r << endl;
	int hash_value = quickpow_mod(2, x, q);
	//cout << "hash_value=" << hash_value << endl;
	//cout << "inverse=" << inverse(k, q) << endl;
	int s = quickmul_mod(inverse(k, q), (hash_value + m * r), q);
	//cout << "s=" << s << endl;

	cout << r << ' ' << s;
}