#include "ModularArithmetic.h"

mpz_class ModularArithmetic::modadd(mpz_class a1, mpz_class b1, mpz_class N1)
{
    //declare GMP class wrappers
    mpz_class a;
    mpz_class b;
    mpz_class c;
    mpz_class N;
    
    a=a1;
    b=b1;
    N=N1;
    c=a+b;
    c=c%N;

    //cout << c << endl;
    return c;

}

mpz_class ModularArithmetic::modmult(mpz_class a1, mpz_class b1, mpz_class N1)
{
    //declare GMP class wrappers
    mpz_class a;
    mpz_class b;
    mpz_class c;
    mpz_class N;

    a=a1;
    b=b1;
    N=N1;
    c=a*b;
    c=c%N;

    //cout << c << endl;
    return c;
}

mpz_class ModularArithmetic::moddiv(mpz_class a1, mpz_class b1, mpz_class N1)
{
    mpz_class c;
    mpz_class* euclid;
    euclid = new (nothrow) mpz_class[3];
    assert(euclid!=0);

    euclid = extendedEuclid(N1,b1);
    mpz_class bin;
    mpz_mod(bin.get_mpz_t(),euclid[1].get_mpz_t(),N1.get_mpz_t());
    c=modmult(a1,euclid[1],N1);
    return c;
}

mpz_class ModularArithmetic::modexp(mpz_class a1, mpz_class b1, mpz_class N1)
{
        mpz_class a=a1;
        mpz_class b=b1;
        mpz_class N=N1;
        mpz_class c;
 
        if(b==0)
        {
            return (1%N);
        }
 
        if(b==1)
        {
            return (a%N);
        }
 
        c=modexp(a, b/2, N);
 
        if(b%2!=0)
        {
            return (a % N * c * c)%N;
        }
 
        else
        {
            return (c*c)%N;
        }
    
}

mpz_class* ModularArithmetic::extendedEuclid(mpz_class& a, mpz_class&b)
{
    mpz_class *euclid;
    euclid=new (nothrow) mpz_class[3];

    assert(euclid!=0);

    if(b==0)
    {
        euclid[0]="1";
        euclid[1]="0";
        euclid[2]=a;
        return euclid;
    }

    mpz_class AmodB=a%b;
    euclid=extendedEuclid(b,AmodB);
    mpz_class oldX=euclid[0];
    mpz_class oldY=euclid[1];
    mpz_class z=euclid[2];
    mpz_class AdivB=a/b;

    euclid[0]=oldY;
    euclid[1]=oldX-(AdivB*oldY);
    euclid[2]=z;
    return euclid;



}

mpz_class ModularArithmetic::generateEncryptionExponent(mpz_class P, mpz_class Q)
{
    //encryption exponent e
    mpz_class encryptionExponent;
    mpz_class P1=P;
    mpz_class Q1=Q;
    mpz_class pMinusOne=P-1;
    mpz_class qMinusOne=Q-1;
    mpz_class phi=pMinusOne*qMinusOne;

    bool notRelativelyPrime=true;

    //random number generator object
    mpz_class ran;

    mpz_class gcdResult;

    //the potential number that will be stored in encryptionExponent
    mpz_class number;

    //the random number generator object
    gmp_randclass rr(gmp_randinit_default);

    //seeding the random number generator
    rr.seed(time(NULL));

    while(notRelativelyPrime)
    {
        //set the number of bits the number will be
        ran =rr.get_z_bits(8);
        number=ran.get_ui();

        //cout << "Candidate for the encryption exponent: " << number << endl;
        //cout << "p: " << P1.get_mpz_t() << endl;
        //cout << "q: " << Q1.get_mpz_t() << endl;
        //cout << "p-1: " << pMinusOne.get_mpz_t() << endl;
        //cout << "q-1: " << qMinusOne.get_mpz_t() << endl;
        
        //calculate gcd and store the result of calculation in gcdResult
        mpz_gcd(gcdResult.get_mpz_t(),number.get_mpz_t(),phi.get_mpz_t());

        //cout << "The gcd for " << "phi of n: " << phi << " and " << "the potential encryption exponent " << number << " is " << gcdResult << endl;

        //if gcd(random number chosen,phi)==1
        if(gcdResult==1)
        {
            encryptionExponent=number;
            notRelativelyPrime=false;
        }
    }

    return encryptionExponent;

}

mpz_class ModularArithmetic::generateDecryptionExponent(mpz_class P, mpz_class Q, mpz_class encryptionExponent)
{
    mpz_class decryptionExponent;
    mpz_class phi=(P-1)*(Q-1);

    //Compute d, the modular multiplicative inverse of e (mod φ(n))
    mpz_invert(decryptionExponent.get_mpz_t(),encryptionExponent.get_mpz_t(),phi.get_mpz_t());

    return decryptionExponent;
}

bool ModularArithmetic::isPrime(mpz_class N, int k)
{
    mpz_class N2=N;

    //mpz_probab_prime_p() is a function used to test primality
    //the first parameter is the number we want to test and the second parameter is the number of tests we want to run on the number

    //if the number is prime
    if(mpz_probab_prime_p(N2.get_mpz_t(),k))
    {
        //cout << N2.get_mpz_t() << " is prime" << endl;
        return true;
    }

    //else, the number is not prime
    else
    {
        //cout << N2.get_mpz_t() << " is not prime" << endl;
        return false;
    }
}


mpz_class ModularArithmetic::genPrime(int n)
{
        gmp_randclass prime (gmp_randinit_default);
        prime.seed(time(NULL));
        mpz_class a;
        mpz_class lower_bound=mpz_class(pow(2.0, double(n-1)));
        while (1)
        {
            a=prime.get_z_bits(n);
            if (isPrime(a,n) && a>lower_bound)
            {
                    return a;
            }
        }
}