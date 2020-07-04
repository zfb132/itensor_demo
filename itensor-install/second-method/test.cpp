#include "itensor/all.h"
#include "myclass.h"

using namespace itensor;

int main()
{
    auto m = MyClass("m",5);
    println(m);
    auto a = Index(5,"A");
    println("dim(a) = ",dim(a));
    return 0;
}
