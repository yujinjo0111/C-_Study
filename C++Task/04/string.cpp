
#include "string.h"

#include <iostream>
using namespace std;

// String class를 cout << 으로 출력하기 위해 오버로딩
ostream& operator<<(ostream& os, const String& x)
{
    cout << x.str;
    return os;
}

// 인자 없는 생성자
String::String()
{
    length = 0;
    str = nullptr;
}

// 크기 m 만큼의 char 배열을 동적할당하는 생성자
String::String(int m)
{
    length = m;
    str = new char[m+1];
    for (int i = 0; i < m+1; i++)
        str[i] = '\0';
}

// 문자열 리터럴과 그 크기 m 을 받는 생성자 
String::String(const char* init, int m) : String(m)
{
    for (int i = 0; i < m; i++)
    {
        this->str[i] = init[i];
    }
}

// 두 String이 동일한지 비교하는 연산자 오버로딩 
bool String::operator==(String t)
{
    // 두 문자열의 길이가 다를 경우 동일할 수 없으므로 false를 반환
    if (this->length != t.length)
    {
        return false;
    }
    // 두 문자열이 같은지 확인
    else
    {
        for (int i = 0; i < this->length; i++)
        {
            // 한 글자라도 다르면 무조건 false 반환
            if (this->str[i] != t.str[i])
            {
                return false;
            }
        }
        // 전부 같을 경우 true 반환
        return true;
    }
}

// String이 빈문자열이면 true, 아니면 false
bool String::operator!()
{
    return (this->length == 0);
}

// String의 length를 반환하는 함수
int String::Length()
{
    return this->length;
}

// 두 개의 String을 붙인 String을 반환하는 함수
String String::Concat(String t)
{
    // 두 문자열 길이의 합만큼의 String 생성
    String ret(this->length + t.length);

    // 두 문자열을 각각 ret 에 대입 후 반환
    for (int i = 0; i < this->length; i++)
    {
        ret.str[i] = this->str[i];
    }

    for (int i = 0; i < t.length; i++)
    {
        ret.str[this->length + i] = t.str[i];
    }

    return ret;
}

/// [i, j) 구간의 substring을 반환하는 함수
String String::Substr(int i, int j)
{
    // i, j과 유효하지 않을 경우 빈 문자열 반환
    if (i > j || i < 0)
    {
        return String();
    }

    // j - i 길이의 String을 만들고 대입 후 반환
    String ret(j - i);
    for (int k = i; k < j; k++)
    {
        ret.str[k - i] = this->str[k];
    }

    return ret;
}

// 다른 String을 포함하고 있는지 확인하고 있으면 그 index를 반환하는 함수
int String::Find(String pat)
{
    for (int i = 0; i < this->length; i++)
    {
        // this와 pat가 동일한 부분의 길이를 구함
        int same_length = 0;
        for (int j = i; j < this->length && j < i + pat.length; j++)
        {
            if (this->str[j] == pat.str[j - i])
            {
                same_length++;
            }

        }

        // 동일한 부분의 길이가 pat의 길이와 같으면 반환 
        if (same_length == pat.length)
        {
            return i;
        }
    }
    return -1;
}
<string.h>
#include <iostream>
using namespace std;

class String
{
private:
    int length;
    char* str;

public:
    String();
    String(int m);
    String(const char* init, int m);
    bool operator==(String t);
    bool operator!();
    int Length();
    String Concat(String t);
    String Substr(int i, int j);
    int Find(String pat);

    friend ostream& operator<<(ostream& os, const String& x);
};
