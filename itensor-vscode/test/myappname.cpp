#include "itensor/all.h"
#include "itensor/itensor.h"
#include <iomanip>
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;
using namespace itensor;

int main()
{
    int N = 10;
    auto sites = SpinHalf(N, {"ConserveQNs=", false});
    auto ampo = AutoMPO(sites);
    for(int j = 1; j < N; j++)
    {
        ampo += 0.5, "S+", j, "S-", j+1;
        ampo += 0.5, "S-", j, "S+", j+1;
        ampo +=      "Sz", j, "Sz", j+1;
    }

    // 转换AutoMPO类型到MPO
    auto T = toMPO(ampo);
    // PrintData(T(10));
    auto y = inds(T(10));
    print(y);
    print(size(y));
    print(dim(y(2)));

    // 创建函数extractReal，参数为Dense<Real>类型
    auto extractReal = [](Dense<Real> const& d)
    {
        return d.store;
    };

    // ---------ITensor数组输出到：多文件---------------
    // 循环输出每个格点;N要修改
    std::string name_template = "output_data_";
    std::string name_suffix = ".txt";
    for(int t = 1;t <= N;t++)
    {
        auto v = applyFunc(extractReal, T(t).store());
        auto iii = size(v);
        std::ofstream outfile;
        outfile.open(name_template+to_string(t)+name_suffix);
        for(int i = 1;i <= iii;i++) 
        {
            outfile << v[i] << std::endl;
        }
        outfile.close();
    }
    // ------------多文件结束---------
    
    
    // ---------ITensor数组输出到：单文件---------------
    // 循环输出每个格点;N要修改
    std::string name = "output_data.txt";
    std::ofstream outfile;
    outfile.open(name);
    for(int t = 1;t <= N;t++)
    {
        auto v = applyFunc(extractReal, T(t).store());
        auto iii = size(v);
        for(int i = 1;i <= iii;i++) 
        {
            // 数据之间以单空格分割
            outfile << v[i] << " ";
        }
        outfile << std::endl;
    }
    outfile.close();
    // ------------单文件结束---------

    return 0;
}


/*
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
*/


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