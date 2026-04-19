
#include <iostream>

template<typename T>
void adl(T)
{
std::cout << "T";
}

struct S
{
};

template<typename T>
void call_adl(T t)
{
    adl(S()); // Independent, looks up adl now. Compile look up for previously defined adl(T).
    adl(t); // Dependent, looks up adl later when entire file is viewed
}

void adl(S)
{
std::cout << "S";
}

int main ()
{
call_adl(S());
}

// Output: TS
//The first call to adl is a non-dependent call, so it is looked up as if at the definition of the function template. The resolution of the second call is deferred until the template is instantiated because it depends on a template parameter.

//When adl is being looked up as if at the definition of the function template, the only version of adl that exists is the templated adl(T). Specifically, adl(S) does not exist yet, and is not a candidate.

