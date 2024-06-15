#include "BigNumbers/BigFloat.h"
#include "BigNumbers/BigFloat.cpp"
#include "BigNumbers/BigInteger.h"
#include "BigNumbers/BigInteger.cpp"
#include <iostream>
#include <chrono>

#define all(x) x.begin(), x.end()
void show(BigInteger a) {
    std::string temp;
    temp = a.toString();
    std::cout << temp << std::endl;
}

void show(BigFloat a, int x) {
    std::string temp;
    temp = a.toString(x);
    std::cout << temp << std::endl;
}

BigFloat calculate_pi(int idx) {
    clock_t start, finish;
    start = clock();
    BigFloat Pi("0");
    BigFloat deg_16("1");
    std::string prec = "0.";
    int idx1 = idx;
    while (idx1 > 0) {
        prec += '0';
        --idx1;
    }
    prec += '1';
    BigFloat prc(prec);
    BigFloat res("0");
    BigFloat k("0");
    do  {
        res = (BigFloat("1") / deg_16);
        BigFloat res1 = (BigFloat("4") / (BigFloat("8") * k + BigFloat("1"))) - (BigFloat("2") / (BigFloat("8") * k + BigFloat("4"))) -
                        (BigFloat("1") / (BigFloat("8") * k + BigFloat("5"))) - (BigFloat("1") / (BigFloat("8") * k + BigFloat("6")));
        res = res * res1;
        Pi = Pi + res;
        deg_16 = deg_16 * BigInteger("16");
        k = k + BigFloat("1");
    } while(res > prc);
    finish = clock();
    double duration = (double)(finish - start) / CLOCKS_PER_SEC;
    std::cout<<duration<<std::endl;
    return Pi;
}
int main(){
   // BigFloat r1("1");
   // BigFloat r2("1");
   // BigFloat r3("3.1417123456789");
   // BigFloat r4 = "9"_bf;

    //Bigoat222 r5("1000000000000000000000000000000");
    BigInteger r1("19318598135138595138598135818395819385193759137591395818395813051305801385081395813058130851395801385901835081358");
    BigInteger r2("109102390192058103859103951359138591039509138591385091385091830581935809138590183509809139851903850913850918309581309580913850138598109358");
    BigInteger r3 = r1*r2;
    //r3.change_precision(10);
    show(r3);
    //r3.delete_leadings_zeroes();
   // BigFloat r5 = r1/r2;
    //show(r5, 0);
    return 0;
}
