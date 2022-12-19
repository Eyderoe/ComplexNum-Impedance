#include <iostream>
#include <cmath>
#include <graphics.h>
const long double vir_radPerDegree = 57.29577951308232;
const long double vir_pi = 3.14159265358979;
const long double vir_e = 2.71828182845904;

class virgui
{
    private:
        int screen_x;
        int screen_y;
        int block_x;
        int block_y;
        int grid() const;
        int screen() const;
        int scale(int);
        int spot(long double *);
    public:
        explicit virgui(int);
        int draw(long double,long double,long double,long double,long double *,int);
        int getX() const;
};
int virgui::grid() const
{
    int init_x=0 , init_y=screen_y , i;
    setlinecolor(GREEN);
    i = -1;
    while (init_x <= screen_x)
    {
        setlinestyle(PS_DASH,1);
        if ((i+1)%5 == 0)
            setlinestyle(PS_DASH,2);
        line(init_x,0,init_x,screen_y);
        init_x += 50;
        i += 1;
    }
    setlinecolor(BLUE);
    i = -1;
    while (init_y >= 0)
    {
        setlinestyle(PS_DASH,1);
        if ((i+1)%5 == 0)
            setlinestyle(PS_DASH,2);
        line(0,init_y,screen_x,init_y);
        init_y -= 50;
        i += 1;
    }
    return 0;
}
int virgui::screen() const
{
    initgraph(screen_x, screen_y);
    setbkcolor(WHITE);
    cleardevice();
    return 0;
}
int virgui::draw(long double miX,long double maX,long double miY,long double maY,long double * fx,int mode)
{
    screen();
    grid();
    scale(mode);
    spot(fx);
    std::cin.get();
    return 0;
}
virgui::virgui(int x)
{
    screen_x = x;
    screen_y = x * 0.75;
    block_x = screen_x/50;
    block_y = screen_y/50;
}
int virgui::scale(int mode)
{
    return 0;
}
int virgui::getX() const
{
    return screen_x;
}
int virgui::spot(long double * fx)
{
    return 0;
}

class virnum
{
        friend std::ostream & operator << (std::ostream & os, const virnum & temp);
    private:
        long double real{};
        long double virtuaI{};
        long double num{};  // only available in circuit
        int show() const;
        long double getDB() const;
        long double transMult(long double,char) const;
        int acAnaly(long double,long double,int);
    public:
        // declare
        virnum();
        virnum(long double, long double);
        virnum(char, long double, char, long double, char);
        // function
        virnum conjugate () const;
        virnum Exp() const;
        virnum ln() const;
        virnum quichFactorial(long long n);
        int changeFreq (long double, char);
        long double getLength() const;
        long double getAngle() const;
        long double getRadAngle() const;
        long double Re() const;
        long double Im() const;
        // gui
        int acAnaly_length(long double, char, long double, char);
        int acAnaly_db(long double, char, long double, char);
        int acAnaly_degree(long double, char, long double, char);
        // overload
        virnum operator ^ (long long) const;
        virnum operator ^= (long long);
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
    char a;
    std:: cout << "num: ";
    std:: cin >> real;
    std::cin.get(a);
    std:: cin >> virtuaI;
    if (a == '+') virtuaI = +virtuaI;
    if (a == '-') virtuaI = -virtuaI;
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
    num = transMult(num,mult_1);
    this->num = num;
    freq = transMult(freq,mult_2);
    w = 2*vir_pi*freq;
    
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
    std:: cout << Re() << ((Im() >= 0) ? " + " : " - ") << ((Im() >= 0) ? Im() : -Im()) << "i" << std:: endl;
    std::cout << "length: " << getLength() << " angle: " << getAngle() << std::endl;
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
    freq = transMult(freq,mult);
    w = 2*vir_pi*freq;
    if (virtuaI < 0) virtuaI = -1/(w*num);
    else if (virtuaI > 0) virtuaI = w*num;
    return 0;
}
long double virnum::getLength() const
{
    long double length;
    length = real*real + virtuaI * virtuaI;
    length = sqrtl(length);
    return length;
}
virnum virnum::Exp() const
{   // Exp(Z) = e^x (cos(y)+isin(y))
    long double length;
    length = powl(vir_e,real);
    return {length* cosl(virtuaI),length* sinl(virtuaI)};
}
long double virnum::Re() const
{
    return real;
}
long double virnum::Im() const
{
    return virtuaI;
}
virnum virnum::ln() const
{   //ln(Z) = ln|Z| + i argZ
    //Ln(Z) = ln(Z) + i 2kpi
    return {logl(getLength()),getRadAngle()};
}
long double virnum::getAngle() const
{
    long double angle;
    angle = atan2l(virtuaI, real);
    angle *= vir_radPerDegree;
    return angle;
}
long double virnum::getRadAngle() const
{
    long double angle;
    angle = atan2l(virtuaI, real);
    return angle;
}
virnum virnum::operator ^ (long long n) const
{
    if (0 == n)
    {
        return {1,0};
    }
    else if (0 < n)
    {
        virnum a = *this;
        for (long long i = 1; i <= n-1; ++i)
        {
            a *= *this;
        }
        return a;
    }
    else
    {
        return virnum(1, 0) / ((*this) ^ (-n));
    }
}
virnum virnum::operator ^= (long long n)
{
    virnum cal = *this ^ n;
    real = cal.Re();
    virtuaI = cal.Im();
    return cal;
}
virnum virnum::quichFactorial(long long n)
{
    long double length;
    length = powl(getLength(),n);
    *this = {length*cosl(n*getRadAngle()),length*sinl(n*getRadAngle())};
    return *this;
}
long double virnum::transMult(long double numy, char mult) const
{
    if ('k' == mult or 'K'==mult) numy *= 1e+3;
    else if ('M' == mult) numy *= 1e+6;
    else if ('G' == mult) numy *= 1e+9;
    else if ('1' == mult) numy *= 1;
    else if('m' == mult) numy *= 1e-3;
    else if('u' == mult) numy *= 1e-6;
    else if('n' == mult) numy *= 1e-9;
    else if('p' == mult) numy *= 1e-12;
    else std::cout << "unrecognized unit: " << mult << std::endl;
    return numy;
}
int virnum::acAnaly_length(long double miHz,char miMult,long double maHz,char maMult)
{
    miHz = transMult(miHz,miMult);
    maHz = transMult(maHz,maMult);
    acAnaly(miHz,maHz,1);
    return 0;
}
int virnum::acAnaly_db(long double miHz,char miMult,long double maHz,char maMult)
{
    miHz = transMult(miHz,miMult);
    maHz = transMult(maHz,maMult);
    acAnaly(miHz,maHz,2);
    return 0;
}
int virnum::acAnaly_degree(long double miHz,char miMult,long double maHz,char maMult)
{
    miHz = transMult(miHz,miMult);
    maHz = transMult(maHz,maMult);
    acAnaly(miHz,maHz,0);
    return 0;
}
int virnum::acAnaly(long double miHz, long double maHz, int mode)
{
    virgui a(800);
    int screen_x , i;
    long double step , *fx , x , fxMin , fxMax;
    screen_x = a.getX();
    step = (maHz-miHz)/(screen_x-1);
    fx = new long double [screen_x];
    x = miHz;
    for (i = 0; i < screen_x; ++i)
    {
        (*this).changeFreq(x,1);
        if (mode == 0)
            fx[i] = (*this).getAngle();
        else if (mode == 1)
            fx[i] = (*this).getLength();
        else
            fx[i] = (*this).getDB();
    }
    fxMin = fx[0];
    fxMax = fx[0];
    for (i = 0; i < screen_x; ++i)
    {
        if (fx[i] > fxMax)
            fxMax = fx[i];
        if (fx[i] < fxMin)
            fxMin = fx[i];
    }
    a.draw(miHz,maHz,fxMin,fxMax,fx,mode);
    return 0;
}
long double virnum::getDB() const
{
    long double length , db;
    length = real*real + virtuaI * virtuaI;
    length = sqrtl(length);
    db = 20* log10l(length);
    return db;
}
