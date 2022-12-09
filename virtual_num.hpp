#include <iostream>
#include <cmath>
const long double rad_per_degree = 57.2957795;
const long double pi = 3.1415926;

/*
a = virnum();   // input: x+y
a = virnum(x, y);   // x+yi
a = virnum('c',1.5,'p',10,'k')  // impedance of 1.5pF in 10K circuits
a.changeFreq(10,'k')  // change frequency to 10k
a.conjugate () // x+yi to x-yi
cout << a
+, +=, -, -=, *, *=, \, \=, ||
 */

class virnum
{
        friend std::ostream & operator << (std::ostream & os, const virnum & temp);
    private:
        long double real;
        long double virtuaI;
        long double num;  // only available in circuit
        int show() const;
    public:
        virnum();   //input: x+y
        virnum(long double, long double);   // (x,y)
        virnum(char, long double, char, long double, char);  //('c',1.5,'p',10,'k') impedance of 1.5pF in 10K circuit
        virnum conjugate () const;
        int changeFreq (long double, char);
        virnum operator + (const virnum &);
        virnum operator += (const virnum &);
        virnum operator - (const virnum &);
        virnum operator -= (const virnum &);
        virnum operator * (const virnum &);
        virnum operator *= (const virnum &);
        virnum operator / (const virnum &);
        virnum operator /= (const virnum &);
        virnum operator || (const virnum &);
};
virnum :: virnum()
{
    std:: cout << "num: ";
    std:: cin >> real;
    getchar();
    std:: cin >> virtuaI;
    num = -1;
}
virnum :: virnum(long double real , long double virtuaI)
{
    this->real = real;
    this->virtuaI = virtuaI;
    num = -1;
}
virnum :: virnum(char kind , long double num , char mult_1 , long double freq=1 , char mult_2='k')
{
    long double w;  //w=2*pi*f
    if (mult_1 == 'k') num *= 1000;
    else if (mult_1 == '1') num *= 1;
    else if(mult_1 == 'm') num *= 1e-3;
    else if(mult_1 == 'u') num *= 1e-6;
    else if(mult_1 == 'n') num *= 1e-9;
    else if(mult_1 == 'p') num *= 1e-12;
    this->num = num;
    if (mult_2 == 'k') freq *= 1000;
    else if(mult_2 == '1') freq *= 1;
    w = 2*pi*freq;
    
    if (kind == 'r')
    {
        real = num;
        virtuaI = 0;
    }
    else if (kind == 'c')
    {
        real = 0;
        virtuaI = -1/(w*num);
    }
    else if (kind == 'l')
    {
        real = 0;
        virtuaI = w*num;
    }
}
int virnum :: show() const
{
    long double length , angle;
    length = real*real + virtuaI * virtuaI;
    length = std::pow(length,0.5);
    angle = std::atan2(virtuaI, real);
    angle *= rad_per_degree;
    std:: cout << real << ((virtuaI >= 0) ? " + " : " - ") << ((virtuaI >= 0) ? virtuaI : -virtuaI) << "i" << std:: endl;
    std::cout << "length: " << length << " angle: " << angle << std::endl;
    return 1;
}
virnum virnum :: conjugate () const
{
    return virnum(real, -virtuaI);
}
virnum virnum :: operator + (const virnum & temp)
{
    virnum sum(0, 0);
    sum.real = real + temp.real;
    sum.virtuaI = virtuaI + temp.virtuaI;
    return sum;
}
virnum virnum :: operator - (const virnum & temp)
{
    virnum sum(0, 0);
    sum.real = real - temp.real;
    sum.virtuaI = virtuaI - temp.virtuaI;
    return sum;
}
virnum virnum :: operator * (const virnum & temp)
{
    virnum multi(0, 0);
    multi.real = real*temp.real - virtuaI * temp.virtuaI;
    multi.virtuaI = real * temp.virtuaI + virtuaI * temp.real;
    return multi;
}
virnum virnum :: operator / (const virnum & temp)
{
    virnum up = (*this) * temp.conjugate();
    long double down = temp.real*temp.real + temp.virtuaI * temp.virtuaI;
    up.real = up.real / down;
    up.virtuaI = up.virtuaI / down;
    return up;
}
virnum virnum :: operator || (const virnum & temp)
{
    virnum up = (*this) * temp;
    virnum down = (*this) + temp;
    return up/down;
}
virnum virnum::operator += (const virnum & temp)
{
    real += temp.real;
    virtuaI += temp.virtuaI;
    return (*this);
}
virnum virnum::operator-=(const virnum & temp)
{
    real -= temp.real;
    virtuaI -= temp.virtuaI;
    return (*this);
}
virnum virnum::operator*=(const virnum& temp)
{
    virnum copy_this (real, virtuaI);
    (*this) = copy_this * temp;
    return (*this);
}

virnum virnum::operator/=(const virnum & temp)
{
    virnum copy_this (real, virtuaI);
    (*this) = copy_this / temp;
    return (*this);
}
std::ostream &operator<<(std::ostream &os, const virnum &temp)
{
    temp.show();
    return os;
}
int virnum::changeFreq(long double freq, char mult='k')
{
    long double w;
    if (mult == '1') freq = freq * 1;
    else if (mult == 'k') freq = freq * 1000;
    w = 2*pi*freq;
    if (virtuaI < 0) virtuaI = -1/(w*num);
    else if (virtuaI > 0) virtuaI = w*num;
    return 0;
}
