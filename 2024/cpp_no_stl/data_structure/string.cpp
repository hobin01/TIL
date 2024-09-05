#include <iostream>

using namespace std;

class String {
private:
    char* data;
    size_t _size;

    // cstring 같은 거 include 못 해서 부가적인 구현 필요 (strcpy, strlen 같은 거)
    // 문자열 길이 구하기 
    size_t strlen(const char* str) {
        size_t len = 0;
        while(str[len] != '\0')
            len++;
        return len;
    }

    void strcpy(char* dest, const char* src) {
        size_t i = 0;
        while(src[i] != '\0') {
            dest[i] = src[i];
            i++;
        }
        dest[i] = '\0';
        _size = i;
    }

    void strcat(char* dest, const char* src) {
        size_t destLen = strlen(dest);
        size_t i = 0;
        while(src[i] != '\0') {
            dest[destLen + i] = src[i];
            i++;
        }
        dest[destLen + i] = '\0';
        _size = destLen + i;
    }

    // char*를 string에 넣기 위함
    void copy(const char* src) {
        if(src) {
            _size = strlen(src);
            data = new char[_size + 1];
            strcpy(data, src);
        } else {
            _size = 0;
            data = new char[1];
            data[0] = '\0';
        }
    }

public:
    String() : data(new char[1]), _size(0) {
        data[0] = '\0';
    }

    ~String() {
        delete[] data;
    }

    // char*, String에 대한 복사
    String(const char* str) {
        copy(str);
    }

    String(const String& str) {
        copy(str.data);
    }

    // char* 값 가져오기 
    const char* toCstring() {
        return data;
    }

    // 연산자 오버라이딩 
    String& operator=(const String& str) {
        // 자기 대입 방지
        if(this != &str) {
            delete[] data;
            copy(str.data);
        }
        return *this;
    }

    char& operator[](size_t index) {
        if(index >= _size) {
            throw out_of_range("[index] error : out of range");
        }
        return data[index];
    }

    String& operator+=(char c) {
        char tmp[2] = {c, '\0'};
        strcat(this->data, tmp);
        return *this;
    }

    String& operator+=(const String& str) {
        char* newStr = new char[_size + str._size + 1];
        strcpy(newStr, data);
        strcat(newStr, str.data);

        delete[] data;
        data = newStr;
        _size += str._size;

        return *this;
    }

    size_t size() {
        return _size;
    }

    String substr(size_t start, size_t len) {
        if(start >= _size) {
            return String();
        }

        size_t maxLen = _size - start;
        if(len > maxLen)
            len = maxLen;

        char* sub = new char[len + 1];
        for(size_t i = 0; i < len; i++) {
            sub[i] = data[start + i];
        }
        sub[len] = '\0';
        String res(sub);
        delete[] sub;

        return res;
    }
};

int main() {
    
}