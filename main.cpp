#include <iostream>
#include <random>
#include <fstream>
#include <ctime>
#define N 30000
#define MAX 1000005
#define SIZE (MAX/2)+5
using namespace std;
bool ciur[SIZE];
int prime[MAX],cnt;

ofstream fout("grader_test1.in");

string gen_random(const int len) {
    char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    string tmp_s;
    tmp_s.reserve(len);
    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    return tmp_s;
}

long long putere(long long a, long long b){
    long long ans = 1;
    for(int i = 1; i <= b; i++){
        ans *= a;
    }
    return ans;
}

long long sub1(long long n){
    long long suma = n+1;
    for(int i = 2; i < n; i++){
        if(n%i == 0){
            suma += i;
        }
    }
    return suma;
}

long long sub2(long long n){
    long long suma = n+1;
    for(int i = 2; i <= sqrt(n); i++){
        if(n%i == 0){
            suma += i;
            if(i != n/i){
                suma += n/i;
            }
        }
    }
    return suma;
}

long long sub3(long long n){
    long long suma = 1;
    long long d = 2,p;
    while(n > 1)
    {
        p = 0;
        while(n % d == 0)
        {
            ++p;
            n /= d;
        }
        if(p)
            suma *= (putere(d, p+1)-1)/(d-1);
        ++ d;
        if(n>1 && d * d > n){
            d = n;
        }
    }
    return suma;
}

long long calcul(long long n){
    long long suma = 1;
    int i = 1;
    while(i <= cnt && prime[i]*prime[i] <= n){
        int p = 0;
        if(n%prime[i] == 0){
            p = 0;
            long long d = prime[i];
            while(n%prime[i] == 0){
                n /= prime[i];
                p++;
            }
            /// d ^ p
            suma *= (putere(d, p+1)-1)/(d-1);
        }
        i++;
    }
    if(n > 1){
        /// n ^ 1
        suma *= (putere(n, 2)-1)/(n-1);
    }
    return suma;
}

int main()
{
    srand(time(NULL));
    mt19937 gen(time(nullptr));
    uniform_int_distribution<int64_t> dis(1, 1000000000);
    prime[++cnt] = 2;
    for(int i = 1; i <= MAX/2; i++){
        if(ciur[i] == 0){
            prime[++cnt] = 2*i+1;
            for(int j = 3*i+1; j <= MAX/2; j += 2*i+1){
                ciur[j] = 0;
            }
        }
    }
    fout << N;
    for(int i = 0; i < N; i++){
        long long val = dis(gen);
        long long sum = sub1(val);
        //cout << i << "\n";
        //fout << gen_random(30) << " " << val << "\n";
    }
    return 0;
}
/// TLE: 0.5 sec
/// SUBTASK 1: -
/// SUBTASK 2: 28.158 s
/// SUBTASK 3: 1.210 s
/// SUBTASK 4: 0.460 s
