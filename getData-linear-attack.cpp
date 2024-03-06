#include <iostream>
#include<fstream>
#include <cstring>
#include<math.h>
#include<random>
using namespace std;

char s[17] = { 'E', '4', 'D', '1', '2', 'F', 'B', '8', '3', 'A', '6', 'C', '5', '9', '0', '7', '\0' };
int p[17] = { 0, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, 4, 8, 12, 16 };

void output(char* s);

ofstream outputfile;
int BintoDec(char* s, int length) {
    int dec = 0;
    for (int i = 0; i < length; i++) {
        if (s[i] == '0')
            continue;
        dec += pow(2, length - 1 - i);
    }
    return dec;
}

void HextoBin(char* binaryStr, char s) {
    int text;
    if (s <= 'Z' && s >= 'A')
        text = s - 'A' + 10;
    else
        text = s - '0';

    for (int i = 3; i >= 0; i--) {
        if (text % 2)
            binaryStr[i] = '1';
        else
            binaryStr[i] = '0';
        text /= 2;
    }
    binaryStr[4] = '\0';
}
void input_x(char* x) {
    for (int i = 0; i < 16; i++) {
        char y;
        cin >> y;
        if (y > '9' || y < '0')
            i--;
        else
            x[i] = y;
    }
    x[16] = '\0';
}

void input_K(char* K) {
    for (int i = 0; i < 32; i++) {
        char y;
        std::cin >> y;
        if (y > '9' || y < '0')
            i--;
        else
            K[i] = y;
    }
    K[32] = '\0';
}

char xor_x1x2(char x1, char x2) {
    if (x1 == x2)
        return '0';
    else
        return '1';
}

void get_u(char* u, char* w, char* K) {
    for (int i = 0; i < 16; i++)
        u[i] = xor_x1x2(w[i], K[i]);
    u[16] = '\0';
    cout << "u:";
    output(u);

}

void get_y(char* y, char* v, char* K) {
    for (int i = 0; i < 16; i++)
        y[i] = xor_x1x2(v[i], K[i]);
    y[16] = '\0';
    cout << endl << "y:";
    output(y);
    outputfile << y << endl;
}

void get_v(char* v, char* u) {

    for (int i = 0; i < 4; i++) {
        char u_content[5];
        memcpy(u_content, u + 4 * i, 4);
        u_content[4] = '\0';
        int decnum = BintoDec(u_content, 4);
        char tempptr = s[decnum];
        HextoBin(v + i * 4, tempptr);
        //在四次循环后完成v的转化
    }
    v[16] = '\0';
    cout << "v:";
    output(v);
}

void get_w(char* w, char* v) {
    for (int i = 0; i < 16; i++) {
        w[i] = *(v + p[i + 1] - 1);
        //v下标从1开始计数，但是实际存是从0开始，所以要减1
        //p的下标也从1开始有意义，所以要加1
    }
    w[16] = '\0';
    cout << "w:";
    output(w);
}
void output(char* s) {
    for (int i = 0; i < strlen(s); i++) {
        cout << s[i];
        if ((i + 1) % 4 == 0)
            cout << ' ';
    }
    cout << endl;
}
int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(0, 1);
    int num;
    cout << "Please input K:" << endl;
    char K[33];
    input_K(K);
    cout << "please input number:" << endl;
    cin >> num;
    outputfile.open("example2.txt");
    for (int ii = 0; ii < num; ii++)
    {
        char x[17];


        cout << "Please input x:" << endl;
        for (int i = 0; i < 16; i++)
            x[i] = distribution(gen) + '0';
        x[16] = '\0';
        //input_x(x);
        cout << x << endl;
        outputfile << x << endl;

        char temp_w[17];
        char temp_K[17];
        char temp_u[17];
        char temp_v[17];
        memcpy(temp_w, x, 17);

        for (int r = 1; r < 5; r++) {//表示轮数
            cout << endl << "round" << r << ":" << endl;
            memcpy(temp_K, K + 4 * (r - 1), 16);
            temp_K[16] = '\0';
            cout << "k:";
            output(temp_K);
            get_u(temp_u, temp_w, temp_K);
            get_v(temp_v, temp_u);
            if (r != 4)
                get_w(temp_w, temp_v);
        }
        cout << endl << "round5:" << endl;
        memcpy(temp_K, K + 16, 16);
        temp_K[16] = '\0';
        cout << "k:";
        output(temp_K);
        char y[17];
        get_y(y, temp_v, temp_K);
    }
}
