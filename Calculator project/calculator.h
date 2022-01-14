#include <iostream>
#include <stdio.h>
using namespace std;

/*

# Calculator 의 오류 정의


0. 부호로 쓰이는 +나 -는 없다고 생각함.

1. 연산자가 연속으로 있을 경우 -> DoubleOperatorError
ex) 3+*4
ex) 4-+5

2. 괄호가 안닫히거나 안열린 경우 -> InvalidBracketError
ex) (3+4*5
ex) 3*4+5)

3. 연산자와 ) 괄호가 붙어있을 경우 -> InvalidOperatorBracketError
ex) 4+)
ex) 4+1+5*)

4. 연산자로 시작할 경우 -> StartOperatorError 
ex) *4-3
ex) +5-3

5. 괄호 두개가 붙어 있는 경우 -> EmptyBracketError
ex) 3+()+5

6. 숫자, 연산자, 괄호 외의 문자가 있는 경우 -> InvalidTextError
ex) 3 + 5 
ex) 3*5@1
ex) {(3+5)*4}

7. 문자열이 비어있는 경우 -> EmptyStringError

*/

#define DoubleOperatorError 1
#define InvalidBracketError 2
#define InvalidOperatorBracketError 3
#define StartOperatorError 4
#define EmptyBracketError 5
#define InvalidTextError 6
#define EmptyStringError 7

class Calculator 
{
private: 
   List<String> tokens; 
   List<String> postfixTokens;
   int errCode;
   int value;
   char str[20];
   String postfix;
   String infix;
   int makePostFix();
   int evaluation();
   Stack<String> stack;
   int isOperator(char c);
   void parseExpressionToTokens(String s);
   void convertTokensToPostfix();
   
public: 
   int getErrorCode();
   int setExpression(const char* expr);   
                          
   String getPostFix();  
   int getValue();                  
                                            
   
};

int Calculator::getValue()
{
   return value;
}
String Calculator::getPostFix()
{
   return postfix;
}

int Calculator::makePostFix()
{
   parseExpressionToTokens(infix);
   cout << "Parsing: "; tokens.print();
   convertTokensToPostfix();
   cout << "Postfix: "; postfixTokens.print();
   evaluation();
   cout << "Result: " << value << "\n";
   return 0;
}


// postfix 수식을 스택을 통해 계산하는 과정
int Calculator::evaluation()
{
   for (int i = 0; i < postfixTokens.length(); i++)
   {
      String s = postfixTokens.getItem(i);
      // 연산자일 경우 스택에서 두개를 빼서 결과값을 다시 스택에 넣어줌
      if (isOperator(s[0]))
      {
         int y = atoi((char*)stack.Top());
         stack.Pop();
         int x = atoi((char*)stack.Top());
         stack.Pop();
         
         // int -> char* 로 형변환 하기 위해 (itoa함수는 비표준 이므로 sprintf사용)
         if (s == "+")
         {
            sprintf(str, "%d", x + y);
         }
         else if (s == "-")
         {
            sprintf(str, "%d", x - y);
         }
         else if (s == "*")
         {
            sprintf(str, "%d", x * y);
         }
         else if (s == "/")
         {
            sprintf(str, "%d", x / y);
         }
         stack.Push(String(str));
      }
      else 
      {
         stack.Push(s);
      }
   }
   // postfix 계산값을 구함
   value = atoi((char*)stack.Top());
   stack.Pop();
   return 0;
}

int Calculator::getErrorCode()
{
   return errCode;
}

// Stack 을 사용해 infix 로 만든 Token으로 postfix 수식을 만드는 함수
void Calculator::convertTokensToPostfix()
{
   // 스택으로 적절한 때에 Pop, 괄호처리를 해주면 postfix 수식으로 만들 수 있음
   for (int i = 0; i < tokens.length(); i++)
   {
      String s = tokens.getItem(i);
      
      // 여는 괄호일 경우
      if (s == "(")
      {
         stack.Push(s);
      }
      // 닫는 괄호일 경우
      else if (s == ")")
      {
         // 여는 괄호를 만날때까지 pop
         while (!stack.IsEmpty() && stack.Top() != "(")
         {
            postfix = (postfix == "" ? postfix : postfix + String(" "));
            postfix = postfix + stack.Top();
            postfixTokens.addItem(stack.Top());
            stack.Pop();
         }
         stack.Pop();
      }
      // + 나 - 일 경우 (우선순위 낮음)
      else if (s == "+" || s == "-")
      {
         while (!stack.IsEmpty() && stack.Top() != "(")
         {
            postfix = (postfix == "" ? postfix : postfix + String(" "));
            postfix = postfix + stack.Top();
            postfixTokens.addItem(stack.Top());
            stack.Pop();
         }
         stack.Push(s);
      }
      // * 나 / 일 경우 (우선순위 높음)
      else if (s == "*" || s == "/") 
      {
         while (!stack.IsEmpty() && stack.Top() != "(" && stack.Top() != "+" && stack.Top() != "-")
         {
            postfix = (postfix == "" ? postfix : postfix + String(" "));
            postfix = postfix + stack.Top();
            postfixTokens.addItem(stack.Top());
            stack.Pop();
         }
         stack.Push(s);
      }
      // 숫자일 경우
      else 
      {
         postfix = (postfix == "" ? postfix : postfix + String(" "));
         postfix = postfix + s;
         postfixTokens.addItem(s);
      }
   }
   
   // 스택이 비어 있지 않은 경우 비어줌
   while (!stack.IsEmpty())
   {
      postfix = (postfix == "" ? postfix : postfix + String(" "));
      postfix = postfix + stack.Top();
      postfixTokens.addItem(stack.Top());
      stack.Pop();
   }
}

// 수식을 Token으로 파싱하는 함수
void Calculator::parseExpressionToTokens(String s)
{
   int s_idx = 0;
   for (int i = 0; i < s.Length(); i++)
   {
      // 연산자일 경우
      if (isOperator(s[i]))
      {
         if ('0' <= s[i - 1] && s[i - 1] <= '9')
         {
            tokens.addItem(s.Substr(s_idx, i-s_idx));
         }
         tokens.addItem(s.Substr(i, 1));
         s_idx = i + 1;
      }
      
      // 여는 괄호일 경우
      else if (s[i] == '(')
      {
         tokens.addItem(s.Substr(i, 1));
         s_idx = i + 1;
      }
      
      // 닫는 괄호일 경우
      else if (s[i] == ')')
      {
         if ('0' <= s[i - 1] && s[i - 1] <= '9')
         {
            tokens.addItem(s.Substr(s_idx, i-s_idx));
         }
         tokens.addItem(s.Substr(i, 1));
         s_idx = i + 1;
      }
      
      // 숫자일 경우
      else 
      {
         continue;
      }
   }
   tokens.removeAt(0);
   tokens.removeAt(tokens.length() - 1);
}

int Calculator::setExpression(const char* expr)
{
   postfix = String("");
   // 문자열을 "(" + expr + ")" 형태로 만들어 숫자로 끝나는 케이스를 처리함
   String s("(");
   s = s + String(expr);
   s = s + String(")");
   tokens.clear();
   postfixTokens.clear();
   
   // 문자열이 비어있는 경우 에러 처리
   if (s.IsEmpty())
   {
      errCode = EmptyStringError;
      return 1;
   }
   
   // 문자열의 첫 글자가 연산자인 경우 에러 처리
   if (isOperator(s[0]))
   {
      errCode = StartOperatorError;
      return 1;
   }
   
   
   for (int i = 0; i < s.Length() - 1; i++)
   {
      // 연산자와 )가 붙어있는 경우 에러 처리
      if (isOperator(s[i]) && s[i + 1] == ')') 
      {
         errCode = InvalidOperatorBracketError;
         return 1;
      }
      
      // 연산자가 두개가 붙어있는 경우 에러 처리
      if (isOperator(s[i]) && isOperator(s[i + 1])) 
      {
         errCode = DoubleOperatorError;
         return 1;
      }
      
      // 괄호가 두개 붙어있을 경우 에러 처리
      if (s[i] == '(' && s[i + 1] == ')')
      {
         errCode = EmptyBracketError;
         return 1;
      }
   }
   

   int cnt = 0;
   for (int i = 0; i < s.Length(); i++)
   {
      // 이상한 문자가 들어있을 경우 에러 처리
      if (!isOperator(s[i]) && !('0' <= s[i] && s[i] <= '9') && s[i] != '(' && s[i] != ')')
      {
         errCode = InvalidTextError;
         return 1;
      }
      
      if (s[i] == '(')
         cnt++;
      
      else if (s[i] == ')')
         cnt--;
      
      // 연 괄호보다 닫는 괄호가 더 많을 경우 에러 처리
      if (cnt < 0) 
      {
         errCode = InvalidBracketError;
         return 1;
      }
   }
   
   // 안닫힌 괄호가 있을 경우 에러 처리
   if (cnt != 0)
   {
      errCode = InvalidBracketError;
      return 1;
   }
   
    
    
   // Can assume there is no error
   infix = s;    
   makePostFix();
   evaluation();
   
   return 0;
}

// char 문자 하나를 받아 연산자인지 확인하는 함수
int Calculator::isOperator(char c)
{
   return (c == '*' || c == '/' || c == '+' || c == '-');
}
