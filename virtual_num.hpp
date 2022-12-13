#include <iostream>
#include <cmath>
const long double rad_per_degree = 57.29577951308232;
const long double pi = 3.14159265358979;

class virnum
{
        friend std::ostream & operator << (std::ostream & os, const virnum & temp);
    private:
        long double real{};
        long double virtuaI{};
        long double num{};  // only available in circuit
        int show() const;
    public:
        virnum();
        virnum(long double, long double);
        virnum(char, long double, char, long double, char);
        virnum conjugate () const;
        int changeFreq (long double, char);
        long double getLength();
        virnum operator + (const virnum &) const;
        virnum operator += (const virnum &);
        virnum operator - (const virnum &) const;
        virnum operator -= (const virnum &);
        virnum operator * (const virnum &) const;
        virnum operator *= (const virnum &);
        virnum operator / (const virnum &) const;
        virnum operator /= (const virnum &);
        virnum operator || (const virnum &) const;
};
virnum :: virnum()
{
    std:: cout << "num: ";
    std:: cin >> real;
    std::cin.get();
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
    if ('k' == mult_1) num *= 1000;
    else if ('1' == mult_1) num *= 1;
    else if('m' == mult_1) num *= 1e-3;
    else if('u' == mult_1) num *= 1e-6;
    else if('n' == mult_1) num *= 1e-9;
    else if('p' == mult_1) num *= 1e-12;
    else std::cout << "unrecognized unit: " << mult_1 << std::endl;
    this->num = num;
    if ('k' == mult_2 || 'K' == mult_2) freq *= 1000;
    else if('1' == mult_2) freq *= 1;
    else if('M' == mult_2) freq *= 1e+6;
    else std::cout << "unrecognized unit: " << mult_2 << std::endl;
    w = 2*pi*freq;
    
    if ('r' == kind || 'R' == kind)
    {
        real = num;
        virtuaI = 0;
    }
    else if ('c' == kind || 'C' == kind)
    {
        real = 0;
        virtuaI = -1/(w*num);
    }
    else if ('l' == kind || 'L' == kind)
    {
        real = 0;
        virtuaI = w*num;
    }
    else
        std::cout << "unrecognized kind: " << kind << std::endl;
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
    return {real, -virtuaI};
}
virnum virnum :: operator + (const virnum & temp) const
{
    virnum sum(0, 0);
    sum.real = real + temp.real;
    sum.virtuaI = virtuaI + temp.virtuaI;
    return sum;
}
virnum virnum :: operator - (const virnum & temp) const
{
    virnum sum(0, 0);
    sum.real = real - temp.real;
    sum.virtuaI = virtuaI - temp.virtuaI;
    return sum;
}
virnum virnum :: operator * (const virnum & temp) const
{
    virnum multi(0, 0);
    multi.real = real*temp.real - virtuaI * temp.virtuaI;
    multi.virtuaI = real * temp.virtuaI + virtuaI * temp.real;
    return multi;
}
virnum virnum :: operator / (const virnum & temp) const
{
    virnum up = *this * temp.conjugate();
    long double down = temp.real*temp.real + temp.virtuaI * temp.virtuaI;
    up.real = up.real / down;
    up.virtuaI = up.virtuaI / down;
    return up;
}
virnum virnum :: operator || (const virnum & temp) const
{
    virnum up = *this * temp;
    virnum down = *this + temp;
    return up/down;
}
virnum virnum::operator += (const virnum & temp)
{
    real += temp.real;
    virtuaI += temp.virtuaI;
    return *this;
}
virnum virnum::operator-=(const virnum & temp)
{
    real -= temp.real;
    virtuaI -= temp.virtuaI;
    return *this;
}
virnum virnum::operator*=(const virnum& temp)
{
    virnum copy_this (real, virtuaI);
    *this = copy_this * temp;
    return *this;
}
virnum virnum::operator/=(const virnum & temp)
{
    virnum copy_this (real, virtuaI);
    *this = copy_this / temp;
    return *this;
}
std::ostream &operator<<(std::ostream &os, const virnum &temp)
{
    temp.show();
    return os;
}
int virnum::changeFreq(long double freq, char mult='k')
{
    long double w;
    if (-1 == num)
    {
        std::cout << "Warning! ChangeFreq to a num" << std::endl;
        return 1;
    }
    if ('1' == mult) freq = freq * 1;
    else if ('k' == mult || 'K' == mult) freq = freq * 1000;
    else if ('M' == mult) freq = freq * 1e+6;
    else std::cout << "unrecognized unit: " << mult << std::endl;
    w = 2*pi*freq;
    if (virtuaI < 0) virtuaI = -1/(w*num);
    else if (virtuaI > 0) virtuaI = w*num;
    return 0;
}
long double virnum::getLength()
{
    long double length;
    length = real*real + virtuaI * virtuaI;
    length = std::pow(length,0.5);
    return length;
}
