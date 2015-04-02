#include "RSA.h"
#include "ModularArithmetic.cpp"

RSA::RSA(int n)
{
    mpz_class p;
    mpz_class q;

    //create primes p and q
    p=ModularArithmetic::genPrime(n);
    q=ModularArithmetic::genPrime(n);

    //if p and q are the same, make a new q value
    if(p==q)
    {
        q=ModularArithmetic::genPrime(n);
    }
    
    mpz_class n2=p*q;

    //create the encryption exponent e
    mpz_class encryptionExponent=ModularArithmetic::generateEncryptionExponent(p,q);

    //create the decryption exponent d
    mpz_class decryptionExponent=ModularArithmetic::generateDecryptionExponent(p,q,encryptionExponent);

    auto PublicKey=makePublicKey(n2,encryptionExponent);

    auto PrivateKey=makePrivateKey(n2,decryptionExponent);

}

RSA::RSA(int n, string filename)
{
    ofstream myFile;

    myFile.open(filename);

    mpz_class p;
    mpz_class q;

    //create primes p and q
    p=ModularArithmetic::genPrime(n);
    q=ModularArithmetic::genPrime(n);

    if(p==q)
    {
        q=ModularArithmetic::genPrime(n);
    }

    mpz_class n2=p*q;

    //create the encryption exponent e
    mpz_class encryptionExponent=ModularArithmetic::generateEncryptionExponent(p,q);

    //create the decryption exponent d
    mpz_class decryptionExponent=ModularArithmetic::generateDecryptionExponent(p,q,encryptionExponent);

    auto PublicKey=makePublicKey(n2,encryptionExponent);

    auto PrivateKey=makePrivateKey(n2,decryptionExponent);


    //write both the public and private key to the file
    myFile << "Public key values:" << endl;
    myFile << "N: " << PublicKey.first.get_mpz_t() << endl;
    myFile << endl;
    myFile << "e: " << PublicKey.second.get_mpz_t() << endl;
    myFile << endl;

    myFile << "Private key values:" << endl;
    myFile << "N: " << PrivateKey.first.get_mpz_t() << endl;
    myFile << endl;
    myFile << endl;
    myFile << "d: " << PrivateKey.second.get_mpz_t() << endl;

    myFile.close();


}

RSA::RSA(string filename)
{
     ofstream myFile;

    myFile.open(filename);

    if(myFile.fail())
    {
        throw std::runtime_error("couldn't open file...");
    }

    int n=1024;

    mpz_class p;
    mpz_class q;

    //create primes p and q
    p=ModularArithmetic::genPrime(n);
    q=ModularArithmetic::genPrime(n);

    if(p==q)
    {
        q=ModularArithmetic::genPrime(n);
    }

    mpz_class n2=p*q;

    //create the encryption exponent e
    mpz_class encryptionExponent=ModularArithmetic::generateEncryptionExponent(p,q);

    //create the decryption exponent d
    mpz_class decryptionExponent=ModularArithmetic::generateDecryptionExponent(p,q,encryptionExponent);

    auto PublicKey=makePublicKey(n2,encryptionExponent);
    auto PrivateKey=makePrivateKey(n2,decryptionExponent);

    //write the private key to the file
    myFile << "Private key values:" << endl;
    myFile << "N: " << PrivateKey.first.get_mpz_t() << endl;
    myFile << "d: " << PrivateKey.second.get_mpz_t() << endl;

    myFile.close();

}


pair<mpz_class,mpz_class> RSA::makePublicKey(mpz_class n, mpz_class e)
{
    auto PublicKey=std::make_pair(n,e);

    //use the "this" pointer to refer to publicKey data member in the pubic section of the RSA class
    this->publicKey=PublicKey;

    return PublicKey;
}

pair<mpz_class,mpz_class> RSA::makePrivateKey(mpz_class n, mpz_class d)
{
    auto PrivateKey=std::make_pair(n,d);

    //use the "this" pointer to refer to the privateKey data member in the private section of the RSA class
    this->privateKey=PrivateKey;

    return PrivateKey;
}

pair<mpz_class,mpz_class> RSA::getPrivateKey()
{
    return privateKey;
}

mpz_class RSA::getPrivateN()
{
    //returns the N part of the private key since it is the first element in the pair object
    return privateKey.first;
}

mpz_class RSA::getPrivateD()
{
    //returns the d part of the private key since it is the second element in the pair object
    return privateKey.second;
}


string RSA::ASCIIToString(string input)
{
    string input2=input;
    //remove the spaces from the input so we don't have to deal with them later
    input2.erase(std::remove(input2.begin(),input2.end(),' '),input2.end());

    //vecotr to hold the ASCII values we've parsed from the string
    vector<int> asciiValues;

    //the string converted from ASCII values
    string final;

    //to hold the 3 characters at a time that we will be reading from the string
    string temp;

    string temp1;

    //to count the number of integers we've read from the vector
    int count=0;

    //the number we want to convert to from ASCII to string
    int numberToConvert=0;

    char c;

    //if the first number of the ASCII string is 0 and there are not three characters at the front of the string
    if(input2.length()%3!=0)
    {
        //append a 0 to the first two numbers from the ASCII string
        for(auto y=0;y<1;++y)
        {
            temp1=temp1+input2.substr(0,2);
            temp1="0"+temp1;

            //convert the string representation of ASCII values to integers
            stringstream str2(temp1);
            int x;
            str2 >> x;
            //cout << x << endl;

            //add the integers to vector
            asciiValues.push_back(x);
        }

        //start this loop at 2 since we have already looked at the first two 
        //numbers in the code above
        for(auto x=2;x<input2.length();++x)
        {  
            //add characters to string
            temp+=input2[x];

            //if we have read 3 characters into temp, reset its length so we can read in the next 3
            if(temp.length()>=3)
            {
                //remove the zero used for padding if it is there
                if(temp.substr(0,1)=="0")
                {               
                    temp.erase(0,1);
                }
                
                //convert the string representation of ASCII values to integers
                stringstream str(temp);
                int x;
                str >> x;
                //cout << x << endl;

                //add the integers to vector
                asciiValues.push_back(x);

                //reset temp so that we can read in the next 3 characters
                temp="";
            }
            
             
        }
        cout << endl;

        for(auto j=0;j<asciiValues.size();++j)
        {
            numberToConvert+=asciiValues[j];
            count++;

            //if we have added enough numbers for an ASCII value
            if(count==1)
            {
                //convert that ASCII value to char form
                c=static_cast<char>(numberToConvert);
                //cout << c;

                //add the character to the string we are going to return
                final+=c;

                //rest so that we can store the next number in the vector and not add it to the one we just stored
                numberToConvert=0;

                //reset count so that we can read in the next ASCII value
                count=0;
            }
        }
    }

    //else, the ASCII string already starts with a zero
    else
    {
        for(auto x=0;x<input2.length();++x)
        {
            //add characters to string
            temp+=input2[x];

            //if we have read 3 characters into temp, reset its length so we can read in the next 3
            if(temp.length()>=3)
            {
                //convert the string representation of ASCII values to integers
                stringstream str(temp);
                int x;
                str >> x;
                //cout << x << endl;

                //add the integers to vector
                asciiValues.push_back(x);

                //reset temp so that we can read in the next 3 characters
                temp="";
            }
             
        }

        for(auto j=0;j<asciiValues.size();++j)
        {
            numberToConvert+=asciiValues[j];
            count++;

            //if we have added enough numbers for an ASCII value
            if(count==1)
            {
                //convert that ASCII value to char form
                c=static_cast<char>(numberToConvert);
                //cout << c << endl;

                //add the character to the string we are going to return
                final+=c;

                //rest so that we can store the next number in the vector and not add it to the one we just stored
                numberToConvert=0;

                //reset count so that we can read in the next ASCII value
                count=0;
            }
            
        }
    }

    //cout << final << endl;
    return final;
}

string RSA::convertToASCII(string letter)
{  
    string line;
    string final;
    char temp;
    char ascii2;
    for (auto i=0;i<letter.length();++i)
    {
        //convert each letter to its own string using stringstream
        char x=letter[i];
        stringstream ss;
        string line;
        ss << int(x);
        line=ss.str();

        //if the ASCII number has only two digits, append a 0 to the front so it has three
        if(int(x)<100)
        {
            line="0"+line;
        }
        final+=line;
        final+=' ';
    }
    return final;
}


string RSA::encrypt(string m, mpz_class N, mpz_class e)
{
    cout << "The plain text is: " << m << endl;
    cout << endl;

    string messageCopy;
    string message=convertToASCII(m);

    cout << "The ASCII version of the plain text is: " << message << endl;
    cout << endl;

    mpz_class m1;
    m1.set_str(message,10);

    mpz_class N1=N;
    mpz_class e2=e;
    mpz_class c;

    //encrypt the mesage by doing c=m1^e2 mod N1 and generate c
    mpz_powm(c.get_mpz_t(), m1.get_mpz_t(), e2.get_mpz_t(), N1.get_mpz_t());

    return c.get_str();
}

string RSA::decrypt(mpz_class c)
{
    mpz_class m;
    mpz_class c1=c;

    //get d and N values for decrypting
    mpz_class d=getPrivateD();
    mpz_class N=getPrivateN();

    //decrypt the message by calculating m=c^d mod N
    mpz_powm(m.get_mpz_t(), c1.get_mpz_t(), d.get_mpz_t(), N.get_mpz_t());

    cout << "Turning the following ASCII to text:" << endl;
    cout << m.get_str() << endl;

    string plainText=ASCIIToString(m.get_str());

    return plainText;

}

void RSA::encryptFile(string filename, mpz_class N, mpz_class e)
{
    mpz_class N1=N;
    mpz_class e1=e;

    N1=publicKey.first;
    e1=publicKey.second;

    //the string we will store what we are reading from the file
    string line;
    string text;

    ifstream fileWeAreReadingFrom;
    ofstream fileWeAreWritingTo;

    fileWeAreReadingFrom.open(filename);

    //check for file failing to open
    if(fileWeAreReadingFrom.fail())
    {
        throw std::runtime_error("Couldn't open file you are trying to read from...");
    }

    //while we are not at the end of the file
    while(!fileWeAreReadingFrom.eof())
    {
        getline(fileWeAreReadingFrom,line);

        //each time we read a line, apped it to the string text
        //so that by the time we finish reading the entire file, it is stored in text
        text+=line;
        //cout << line << endl;
    }

    //encrypt the text from the file we were reading from
    string encryptedText=encrypt(text,N1,e1);

    cout << "Your encrypted text that will be written to the file is:" << endl;
    cout << encryptedText << endl;

    fileWeAreWritingTo.open(filename+".enc");

    //check for file failing to open
    if(fileWeAreWritingTo.fail())
    {
        throw std::runtime_error("Couldn't open file you are trying to write to...");
    }

    //write the encrypted text to the file
    fileWeAreWritingTo << encryptedText << endl;

    fileWeAreWritingTo.close();

}

void RSA::decryptFile(string filename)
{
    
    string line;

    //where we will store what we read from the file
    string text;

    ifstream fileWeAreReadingFrom;

    fileWeAreReadingFrom.open(filename);

    if(fileWeAreReadingFrom.fail())
    {
        throw std::runtime_error("Couldn't open the file you wanted to read from...");
    }

     //while we are not at the end of the file
    while(!fileWeAreReadingFrom.eof())
    {
        getline(fileWeAreReadingFrom,line);

        //each time we read a line, apped it to the string text
        //so that by the time we finish reading the entire file, it is stored in text
        text+=line;
        //cout << line << endl;
    }

    //cout << "Going to decrypt: " << text << endl;

    mpz_class encrypted_text;
    encrypted_text.set_str(text,10);

    cout << "Going to decrypt: " << encrypted_text.get_str() << endl;

    string plainText=decrypt(encrypted_text);

    cout << "The plain text is:" << endl;
    cout << plainText << endl;

    fileWeAreReadingFrom.close();

}