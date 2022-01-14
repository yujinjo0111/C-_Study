#include "stack.h"
#include "List.h"
#include "String.h"
#include "Calculator.h"
using namespace std;

int main()
{
   Calculator c;
   char expr[1000];

   
   cout << "수식을 입력하시오 : ";
   cin.getline(expr, 1000);
   
   if ( !c.setExpression(expr) )
   {
      String postfix = c.getPostFix();
      try 
      {
          cout << "후위표기식 : " << postfix  << "\n결과값 : " << c.getValue() << endl;
      } 
      catch (const char* errmsg)
      {
         cout << errmsg << endl;
   
      }
   }
}
