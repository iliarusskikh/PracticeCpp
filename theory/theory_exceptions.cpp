#include <iostream>
using namespace std;

int main()
{
    try
    {
       throw 'a';
    }
    catch (int param)
    {
        cout << "int exception\n";
    }
    catch (...)
    {
        cout << "default exception\n"; //called
    }
    cout << "After Exception";//called
    return 0;
}


/*
#include <iostream>
using namespace std;

int main()
{
    try
    {
        try
        {
            throw 20;
        }
        catch (int n)
        {
            cout << "Inner Catch\n";
            throw;//re-throw again
        }
    }
    catch (int x)
    {
        cout << "Outer Catch\n";//here!
    }
    return 0;
}
*/
