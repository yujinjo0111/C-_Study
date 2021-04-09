#include "string.h"
#include <iostream> 
using namespace std;


int main()
{
    String s("abcdef", 6);
    String t("efgh", 4);
    String x = s.Concat(t);
    String y("", 0);

    cout << s << "\n";
    cout << t << "\n";
    cout << x << "\n";
    cout << x.Substr(1, 3) << "\n";
    cout << (!y ? "y is empty\n" : "y is not empty\n");

    String s_same("abcdef", 6);


    if (s == s_same)
    {
        cout << s << " == " << s_same << "\n";
    }
    else
    {
        cout << s << " != " << s_same << "\n";
    }

    if (s == t)
    {
        cout << s << " == " << t << "\n";
    }
    else
    {
        cout << s << " != " << t << "\n";
    }

    String s_sub("def", 3);
    cout << "abcdef 에서 def: " << s.Find(s_sub) << "\n";

    String not_s_sub("efg", 3);
    cout << "abcdef 에서 efg: " << s.Find(not_s_sub) << "\n";


}
