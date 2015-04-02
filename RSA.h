#ifndef RSA_H
#define RSA_H
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <utility>
#include <gmp.h>
#include <gmpxx.h>

using namespace std;

class RSA
{
    private:
        //the first mpz_class is the N value and the second mpz_class is the d value
        pair<mpz_class, mpz_class> privateKey;

    public:
        //the first mpz_class is the N value and the second mpz_class is the e value 
        pair<mpz_class,mpz_class> publicKey;
        RSA(int n);
        RSA(int n, string filename);
        RSA(string filename);
        pair<mpz_class,mpz_class> makePublicKey(mpz_class n, mpz_class e);
        pair<mpz_class,mpz_class> makePrivateKey(mpz_class n, mpz_class d);
        pair<mpz_class,mpz_class> getPrivateKey();
        mpz_class getPrivateN();
        mpz_class getPrivateD();
        string ASCIIToString(string input);
        string convertToASCII(string letter);
        string encrypt(string m, mpz_class N, mpz_class e);
        string decrypt(mpz_class c);
        void encryptFile(string filename, mpz_class N, mpz_class e);
        void decryptFile(string filename);







};

#endif