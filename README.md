# ComplexNum-Impedance
a class for calculate complex num and impedance in circuit  
## **support two kinds declare ways**  
>``virnum(2,-7)`` _means 2-7i_\
``virnum('c',20,'p',10,'k')`` _means 20pF capacitor in 10K(Hz) circuit_
## **support basic operation**
``virnum a(1,2)``\
``virnum b(2,3)``
>``a + b`` , ``a += b``\
>``a - b`` , ``a -= b``\
>``a * b`` , ``a *= b``\
>``a / b`` , ``a /= b``\
>``a || b`` _means a parallel with b_\
>``std::cout << a << b``
## **other functions**
``virnum a(1,2)``\
``virnum b('l',20,'u',10,'k')``
>``a.conjugate()`` _will return 1-2i_\
>``b.changeFreq(12,'k')`` _change frequency to 10KHz_\
>``changeFreq()`` _only available on capacitor and inductor_
