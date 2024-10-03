#include <stdio.h>
#include <stdlib.h> // for malloc, free

using namespace std;

#define SIZE 1000 // 1,000 자리 가정 
#define BASE 36
// 36진법 : 0~9, A~Z

void clear(char* s) {
    s[0] = '\0';
}

int my_strlen(char* s) {
    // s 길이 리턴 
    int len = 0;
    while(*(s++)) len++;
    return len;
}

int my_strcmp(char* s1, char* s2) {
    // s1 > s2 : 1, s1 == s2 : 0, s1 < s2 : -1
    int len1 = my_strlen(s1);
    int len2 = my_strlen(s2);

    if(len1 > len2)
        return 1;
    if(len1 < len2)
        return -1;

    for(int i = 0; i < len1; i++) {
        // ascii : 0 : 48, 9 : 57, A : 65, Z : 90
        if(s1[i] > s2[i])
            return 1;
        if(s1[i] < s2[i])
            return -1;
    }
    return 0;
}

void my_strcpy(char* dest, char* src) {
    while((*(dest++) = *(src++)));
}

int charToInt(char c) {
    if(c >= '0' && c <= '9')
        return c - '0';
    if(c >= 'A' && c <= 'Z')
        return c - 'A' + 10;
    return -1;
}

char intToChar(int n) {
    if(n >= 0 && n <= 9)
        return '0' + n;
    if(n >= 10 && n < BASE)
        return 'A' + (n - 10);
    return '?';
}

void add(char* s1, char* s2, char* res) {
    int len1 = my_strlen(s1);
    int len2 = my_strlen(s2);
    int maxLen = len1 > len2 ? len1 : len2;
    int carry = 0;
    int sum = 0;
    int lastIdx = 0;

    clear(res);

    int idx1 = len1 - 1;
    int idx2 = len2 - 1;
    int val1 = 0;
    int val2 = 0;
    while(idx1 >= 0 || idx2 >= 0 || carry) {
        val1 = idx1 >= 0 ? charToInt(s1[idx1--]) : 0;
        val2 = idx2 >= 0 ? charToInt(s2[idx2--]) : 0;
        sum = val1 + val2 + carry;
        carry = sum / BASE;
        sum = sum % BASE;
        res[lastIdx++] = intToChar(sum);
    }

    // result는 0번째가 맨 끝자리 계산 결과로 들어갔으므로 reverse 
    for(int i = 0; i < lastIdx / 2; i++) {
        char c = res[i];
        res[i] = res[lastIdx - i - 1];
        res[lastIdx - i - 1] = c;
    }
    res[lastIdx] = '\0';
}

void sub(char* s1, char* s2, char* res) {
    // res = |s1 - s2|
    char* bigger;
    char* smaller;

    if(my_strcmp(s1, s2) == 1) {
        bigger = s1;
        smaller = s2;
    } else {
        bigger = s2;
        smaller = s1;
    }

    int len1 = my_strlen(bigger);
    int len2 = my_strlen(smaller);
    int borrow = 0;
    int diff = 0;
    int lastIdx = 0;

    clear(res);

    int idx1 = len1 - 1;
    int idx2 = len2 - 1;
    int val1 = 0;
    int val2 = 0;
    while(idx1 >= 0) {
        val1 = charToInt(bigger[idx1--]);
        val2 = idx2 >= 0 ? charToInt(smaller[idx2--]) : 0;
        val1 -= borrow;

        if(val1 < val2) {
            val1 += BASE;
            borrow = 1;
        } else {
            borrow = 0;
        }

        diff = val1 - val2;
        res[lastIdx++] = intToChar(diff);
    }

    // 앞에 0 붙은 거 제거 
    while(lastIdx > 1 && res[lastIdx - 1] == '0') lastIdx--;

    // result는 0번째가 맨 끝자리 계산 결과로 들어갔으므로 reverse 
    for(int i = 0; i < lastIdx / 2; i++) {
        char c = res[i];
        res[i] = res[lastIdx - i - 1];
        res[lastIdx - i - 1] = c;
    }
    res[lastIdx] = '\0';
}

// mul : 카라츠바 빠른 곱셈 이용 
// X = X_high * B^m + X_low (B : base, m : 길이 절반)
// Y = Y_high * B^m + Y_low 
// XY = Z2 * B^2m + Z1 * B^m + Z0
// Z0 = X_low * Y_low
// Z2 = X_high * Y_high
// Z1 = (X_high + X_low) * (Y_high + Y_low) - Z2 - Z0
// 곱셈에 대해서 재귀로 반복 

void shift_left(char* s, int n, char* res) {
    // n칸 왼쪽으로 밀기 (base^n 곱한 것)
    int len = my_strlen(s);
    for(int i = 0; i < len; i++) {
        res[i] = s[i];
    }
    for(int i = len; i < (len + n); i++) {
        res[i] = '0';
    }
    res[len + n] = '\0';
}

void split_number(char* s, int m, char* high, char* low) {
    // m번째 기준으로 high, low 나누기 
    int len = my_strlen(s);
    int highLen = len - m;

    for(int i = 0; i < highLen; i++) {
        high[i] = s[i];
    }
    high[highLen] = '\0';

    int j = 0;
    for(int i = highLen; i < len; i++) {
        low[j++] = s[i];
    }
    low[j] = '\0';
}

void simple_mul(char* s1, char* s2, char* res) {
    // 작은 값일 때는 그냥 곱셈으로 처리 (쪼개는 시간보다 그냥 곱하는 게 더 빠름)
    int len1 = my_strlen(s1);
    int len2 = my_strlen(s2);
    int len = len1 + len2;

    int* tmp = (int*)malloc(len * sizeof(int));

    int i = 0;
    int j = 0;
    int val1 = 0;
    int val2 = 0;

    for(i = 0; i < len; i++) {
        tmp[i] = 0;
    }

    for(i = len1 - 1; i >= 0; i--) {
        val1 = charToInt(s1[i]);
        for(j = len2 - 1; j >= 0; j--) {
            val2 = charToInt(s2[j]);
            tmp[i + j + 1] += (val1 * val2);
        }
    }

    // carry 처리 
    for(i = len - 1; i > 0; i--) {
        tmp[i-1] += (tmp[i] / BASE);
        tmp[i] %= BASE;
    }

    // tmp : int로 저장 중 
    // string으로 변환 
    int lastIdx = 0;
    int start = 0;
    
    while((start < len) && (tmp[start] == 0)) start++;
    if(start == len) {
        res[0] = '0';
        res[1] = '\0';
    } else {
        for(i = start; i < len; i++) {
            res[lastIdx++] = intToChar(tmp[i]);
        }
        res[lastIdx] = '\0';
    }

    free(tmp);
}

void karatsuba(char* x, char* y, char* z) {
    // z = x * y
    // using karatsuba algorithm

    int len_x = my_strlen(x);
    int len_y = my_strlen(y);

    // simple 적용 케이스 : 2자리 이하 
    // 실제로는 십진수 기준 10자리 정도를 기준점으로 잡음
    int base_len = 2;
    if(len_x <= base_len || len_y <= base_len) {
        simple_mul(x, y, z);
        return;
    }

    int n = len_x > len_y ? len_x : len_y;
    int m = n / 2;

    // 계산 시 같은 길이 맞추기 위해 패딩 처리 
    char x_padded[SIZE] = {0, };
    char y_padded[SIZE] = {0, };
    int pad_x = n - len_x;
    int pad_y = n - len_y;

    for(int i = 0; i < pad_x; i++) x_padded[i] = '0';
    my_strcpy(x_padded + pad_x, x);

    for(int i = 0; i < pad_y; i++) y_padded[i] = '0';
    my_strcpy(y_padded + pad_y, y);

    // 쪼개기 
    char x_high[SIZE] = {0, };
    char x_low[SIZE] = {0, };
    char y_high[SIZE] = {0, };
    char y_low[SIZE] = {0, };

    split_number(x_padded, m, x_high, x_low);
    split_number(y_padded, m, y_high, y_low);

    // z0, z1, z2 계산 
    char z0[SIZE * 2] = {0, };
    char z1[SIZE * 2] = {0, };
    char z2[SIZE * 2] = {0, };

    // z 계산 시 사용될 임시값
    char tmp1[SIZE] = {0, }; // x_high + x_low
    char tmp2[SIZE] = {0, }; // y_high + y_low
    char tmp3[SIZE * 2] = {0, }; // z1 = tmp1 * tmp2, z1 = z1 - z2 - z0

    // z0 = x_low * y_low 
    karatsuba(x_low, y_low, z0);

    // z2 = x_high * y_high
    karatsuba(x_high, y_high, z2);

    // x_high + x_low
    add(x_high, x_low, tmp1);
    
    // y_high + y_low
    add(y_high, y_low, tmp2);

    // z1 = tmp1 * tmp2
    karatsuba(tmp1, tmp2, z1);

    // z1 = z1 - z2 - z0
    sub(z1, z2, tmp3);
    sub(tmp3, z0, z1);

    // z = x * y = z2 * B^2m + z1 * B^m + z0
    shift_left(z2, 2 * m, tmp1);
    shift_left(z1, m, tmp2);
    add(tmp1, tmp2, tmp3);
    add(tmp3, z0, z);
}

void mul(char* s1, char* s2, char* res) {
    clear(res);
    karatsuba(s1, s2, res);
}

////////////////////////
// for test
void strToInt(char* s, int& num) {
    int len = my_strlen(s);
    int res = 0;
    for(int i = 0; i < len; i++) {
        res = res * BASE + charToInt(s[i]);
    }
    num = res;
}

void intToStr(int num, char* s) {
    clear(s);

    int idx = 0;
    while(num > 0) {
        s[idx++] = intToChar(num % BASE);
        num /= BASE;
    }

    for(int i = 0; i < idx / 2; i++) {
        char c = s[i];
        s[i] = s[idx - i - 1];
        s[idx - i - 1] = c;
    }
    s[idx] = '\0';
}

int main() {

    char* s1[3] = {"123", "ABC", "Z9"};
    char* s2[3] = {"A", "123", "ZZZZ"};

    char res[SIZE*2] = {0, };
    char tmp[SIZE*2] = {0, };

    int num1, num2;

    printf("----add test----\n");
    for(int i = 0; i < 3; i++) {
        printf("s1 : %s, s2 : %s\n", s1[i], s2[i]);

        strToInt(s1[i], num1);
        strToInt(s2[i], num2);

        printf("num1 : %d, num2 : %d\n", num1, num2);

        add(s1[i], s2[i], res);

        intToStr(num1 + num2, tmp);
        
        printf("s1 + s2 : %s\n", res);
        printf("num1 + num2 : %s\n", tmp);
    }

    printf("----sub test----\n");
    for(int i = 0; i < 3; i++) {
        printf("s1 : %s, s2 : %s\n", s1[i], s2[i]);

        strToInt(s1[i], num1);
        strToInt(s2[i], num2);

        printf("num1 : %d, num2 : %d\n", num1, num2);

        sub(s1[i], s2[i], res);

        if(num1 > num2) intToStr(num1 - num2, tmp);
        else intToStr(num2 - num1, tmp);
        
        printf("|s1 - s2| : %s\n", res);
        printf("|num1 - num2| : %s\n", tmp);
    }

    printf("----mul test----\n");
    for(int i = 0; i < 3; i++) {
        printf("s1 : %s, s2 : %s\n", s1[i], s2[i]);

        strToInt(s1[i], num1);
        strToInt(s2[i], num2);

        printf("num1 : %d, num2 : %d\n", num1, num2);

        mul(s1[i], s2[i], res);

        intToStr(num1 * num2, tmp);
        
        printf("s1 * s2 : %s\n", res);
        printf("num1 * num2 : %s\n", tmp);
    }
}