#include <iostream>
#include<time.h>
#include<math.h>
using namespace std;


int exp_modular(int a, int b, int M) {
    int r = 1;


    while (b > 0) {
        if (b % 2) {
            r = (r * a) % M;
        }
        a = (a * a) % M;
        b = b / 2;
    }
    return r;

}

bool witness(int a, int n, int t, int u) {
    int aux2;
    int aux = exp_modular(a, u, n);

    if (aux == 1 || aux == (n - 1))
        return false;

    for (int i = 1; i < t; i++) {
        aux = exp_modular(aux, 2, n);
        if (aux == n - 1)
            return false;

    }

    return true;
}


bool MILLER_RABIN(int n, int s) {
    int a;
    int aux = n - 1;
    int ele = 1;
    int t = 0;

    while (aux % 2 == 0) {
        aux = aux / 2;
        ele = ele * 2;
        t++;
    }

    int u = (n - 1) / ele;

    for (int j = 1; j < s; j++) {
        a = rand() % (n - 1) + 1;
        if (witness(a, n, t, u))
            return true;
    }
    return false;

}

int random_bits(int b) {
    float a = pow((float)2, (float)b);
    
    int r = rand() % ((int)a - 1);

    while (r % 2 == 0) {
        r = rand() % ((int)a - 1);
    }

    return r;

}

int generate_p_candidate(int b) {
    int n = random_bits(b);
    int m = ((int)pow((float)2, (float)b)) + 1;
    
    return n;

}

int generate_prime(int b) {
    int s = 20;
    int n = generate_p_candidate(b);
    bool buc=true;
    buc = MILLER_RABIN(n, s);

    while (buc != false) {
        n = n + 2;
        buc = MILLER_RABIN(n, s);
    }


    return n;
}

int main() {
    srand(time(NULL));

    cout << generate_prime(8);

    

}