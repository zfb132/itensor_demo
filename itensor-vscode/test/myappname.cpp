#include "itensor/all.h"
#include "itensor/mps/mps.h"

using namespace itensor;


int main()
{
const auto PI_D=3.1415926535897932384;
Real theta=PI_D/4;

auto i=Index(2);

auto U=ITensor(i,prime(i)),
     H=ITensor(prime(i),prime(i,2));

U.set(i(1),prime(i(1)),cos(theta));
U.set(i(2),prime(i(1)),-sin(theta));
U.set(i(1),prime(i(2)),sin(theta));
U.set(i(2),prime(i(2)),cos(theta));

H.set(prime(i(1)),prime(i(1),2),0.);
H.set(prime(i(2)),prime(i(1),2),1.);
H.set(prime(i(1)),prime(i(2),2),1.);
H.set(prime(i(2)),prime(i(2),2),0.);

println(U);
println(swapPrime(U,0,1));
println(prime(swapPrime(U,0,1)));
println(prime(swapPrime(conj(U),0,1),2));

auto ans=U*H*prime(prime(swapPrime(U,0,1)));
println(ans);
ans.mapPrime(3,1);

println(ans);
return 0;
}

/*
#include "itensor/all.h"
#include "myclass.h"
using namespace itensor;
int main()
{
    auto s1 = Index(2,"Site");
    auto s2 = Index(2,"Site");
    // auto T = randomITensor(s1,s2);
    auto T = ITensor(s1,s2);
    T.set(s1=1,s2=2,0.7);
    PrintData(norm(T));
    return 0;
}
*/

