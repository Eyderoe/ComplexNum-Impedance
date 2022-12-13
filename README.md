# ComplexNum-Impedance
a class for calculate complex num and impedance in circuit  
## **support two kinds declare ways**  
>``virnum(2,-7)`` _means 2-7i_\
>``virnum('c',20,'p',10,'k')`` _means 20pF capacitor in 10K(Hz) circuit_\
>``virnum('r',5.1,'1')`` _means 5.1ohm resistor_
## **support basic operation**
``virnum a(1,2)``\
``virnum b(2,3)``
>``a + b`` , ``a += b`` , ``a * b`` , ``a *= b``\
>``a - b`` , ``a -= b`` , ``a / b`` , ``a /= b``\
>``a || b`` _means a parallel with b (in circuit)_\
>``std::cout << a << b``
## **other functions**
``virnum a(1,2)``\
``virnum b('l',20,'u',10,'k')``
>``a.conjugate()`` _will return 1-2i_\
>``a.getLength()`` _will return length_\
>``b.changeFreq(12,'k')`` _change frequency to 12K(Hz)_\
>``changeFreq()`` _only available on capacitor and inductor_
