# ComplexNum-Impedance
a class for calculate complex num and impedance in circuit  
## **two declare ways**  
>``virnum(2,-7)`` _means 2-7i_\
>``virnum('c',20,'p',10,'k')`` _means 20pF capacitor in 10K(Hz) circuit_\
>``virnum('r',5.1,'1')`` _means 5.1ohm resistor_
## **basic operation**
``virnum a(1,2)``\
``virnum b(2,3)``
>``a + b`` , ``a += b`` , ``a * b`` , ``a *= b``\
>``a - b`` , ``a -= b`` , ``a / b`` , ``a /= b``\
>``a ^ (int)`` , ``a ^= (int)``\
>``a || b`` _means a parallel with b (in circuit)_\
>``a.Re()`` , ``a.Im()``\
>``std::cout << a << b``
## **scientific**
``virnum a(1,2)``
>``a.Exp()`` _Exp(Z) = e^x (cos(y)+isin(y))_\
>``a.ln()`` _ln(Z) = ln|Z| + i argZ_
## **other functions**
``virnum a(1,2)``\
``virnum b('l',20,'u',10,'k')``
>``a.conjugate()`` _will return 1-2i_\
>``a.getLength()`` , ``a.getAngle()`` , ``a.getRadAngle()``\
>``b.changeFreq(12,'k')`` _change frequency to 12K(Hz)_\
>``changeFreq()`` _only available on capacitor and inductor_
