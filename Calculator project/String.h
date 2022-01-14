#pragma once


#ifndef _STRING_H
#define _STRING_H


class String
{
private:
	char *buffer;
	int length;
	int size;
	void DeepCopy(const char *src, int size = 0); 


public:
	// 생성자
	String();
	String(int size);
	String(char c);
	String(String&);
	String(const char* str);
	String(char* str);
	String(const char* init, int m);
	~String();
	// 연산자 오버로딩
	String& operator=(const String&);
	String& operator=(const char *);
	bool operator==(String t);
	bool operator==(const char *);
	bool operator!=(const char *);
	bool operator!();
	String operator+(const char*);
	char operator[](int idx);
    
    friend ostream& operator<<(ostream& os, const String& x);
	operator char* ();

	bool IsEmpty();
	int Length();

	String Concat(String t);
	String Substr(int i, int j);
	int Find(String pat);
};

String String::operator+(const char* str)
{
	return Concat(String(str));
}

ostream &operator<<(ostream &os, const String &x)
{
    cout << x.buffer;
    return os;
}

char String::operator[](int idx)
{
    return buffer[idx];
}

 
String::String()
{
	buffer = 0;
	size = 0;
	length = 0;
}

String::String(int size)
{
	buffer = new char[size];
	this->size = size;
	length = 0;
}

String::String(char c)
{
	buffer = new char[2];
	buffer[0] = c;
	buffer[1] = '\0';
	size = 2;
	length = 1;
}

String::String(String& s) : String()
{
	DeepCopy(s.buffer, s.size);
}

String::String(const char* str)  : String()
{
	DeepCopy(str);
}

String::String(char* str) : String((const char*)str)
{
}

String::String(const char* init, int m) : String()
{
	DeepCopy(init, m);
}

 

String::~String()
{
	delete[] buffer;
	buffer = 0;
	size = 0;
}

bool String::operator!()
{
	return IsEmpty();
}

bool String::IsEmpty()
{
	if (Length() == 0)
		return true;
	else
		return false;
}

String::operator char* () 
{
	return (char*)buffer;
}

bool String::operator!=(const char * expr)
{
	return !operator==(String(expr));
}

bool String::operator==(const char * expr)
{
	return operator==(String(expr));
}

bool String::operator==(String t)
{
	int pos = 0;
 
	if (Length() != t.Length())
		return false;

	for (pos = 0; pos < Length(); pos++)
	{
		if (buffer[pos] != t.buffer[pos])
			break;
	}

	return (pos == Length()) ? true : false;
}
 

String& String::operator=(const String& s)
{
	DeepCopy(s.buffer, s.size);
	return *this;
}

String& String::operator=(const char* s)
{
	DeepCopy(s);
	return *this;
}

void String::DeepCopy(const char* src, int size)

{

 

	if (this->size > 0)

		delete[] buffer;

 

 

	if( size <= 0 )

	{

		size = 0;

		while (src[size++] != '\0');

	}

 

	buffer = new char[size];

	this->size = size;

 

	for (int i = 0; i < this->size; i++)

	{

		if (src[i] == '\0') length = i;

		buffer[i] = src[i];

	}

 

 

}

String String::Concat(String t)

{

	String result(Length() + t.Length() + 1);

	

	for (int i = 0; i < Length(); i++)

		result.buffer[i] = buffer[i];

 

	for (int i = 0; i < t.Length(); i++)

		result.buffer[Length() + i] = t.buffer[i];

 

	result.buffer[Length() + t.Length()] = '\0';

 

	

 

	return result;

}

String String::Substr(int i, int j)

{
	if (i < 0 || j < 0 || i + j > Length())

		throw "Cannot extract substring.";

 

	String result(j + 1);

 

	for (int pos = 0; pos < j; pos++)

		result.buffer[pos] = buffer[i + pos];

 

	result.buffer[j] = '\0';

 

	return result;

}

int String::Length()

{

	

	if (length > 0 )

		return length;

 

	if (size > 0)

	{

		length = 0;

		for (int i = 0; i < size; i++)

		{

			if (buffer[i] == '\0')

			{

				length = i;

				break;

			}

		}

	}

	return length;

}

int String::Find(String pat)

{

	for (int start = 0; start <= Length() -pat.Length(); start++)

	{

		int j;

		for (j = 0; j < pat.Length() && buffer[start + j] == pat.buffer[j]; j++);

		if (j == pat.Length())  return start;

	}

 

	return -1;

}
 

#endif
