#ifndef MODULARARITHMETIC_H
#define MODULARARITHMETIC_H
#include <iostream>
#include <vector>
#include <cstdlib>
#include <unistd.h>
#include <cmath>
#include <stdio.h>
#include <random>
#include <string>
#include <assert.h>
#include <fstream>
#include <sstream>
#include <time.h>
#include <gmp.h>
#include <gmpxx.h>

using namespace std;

class ModularArithmetic
{
    public:
       static mpz_class modadd(mpz_class a1, mpz_class b1, mpz_class N1);
       static mpz_class modmult(mpz_class a1, mpz_class b1, mpz_class N1);
       static mpz_class moddiv(mpz_class a1, mpz_class b1, mpz_class N1);
       static mpz_class modexp(mpz_class a1, mpz_class b1, mpz_class N1);
       static mpz_class* extendedEuclid(mpz_class& a, mpz_class&b);
       static mpz_class generateEncryptionExponent(mpz_class P, mpz_class Q);
       static mpz_class generateDecryptionExponent(mpz_class P, mpz_class Q, mpz_class encryptionExponent);
       static bool isPrime(mpz_class N, int k);
       static mpz_class genPrime(int n);
};

#endif