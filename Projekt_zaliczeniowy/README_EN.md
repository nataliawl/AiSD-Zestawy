=========================================================================

Author: Natalia Wlodyka,                              Krakow, December 28, 2025

=========================================================================



\* Contents:

============



The "Projekt\_Wielomiany" (Polynomial\_Project) directory contains programs that implement polynomials using a singly linked list.



The directory contains the following program:

\- main.cpp – a program that invokes and verifies the functionality of the "Poly" class.

\- polynomial.h – contains the "Term" structure, the "Poly" class, and its methods.



\* Description of the "Term" structure:

======================



The "Term" structure implements a monomial, which is a component of a polynomial.

It is displayed in the format shown in this example of a monomial with a coefficient of 5 and a degree of 2: 5\*x^2.



This structure contains:

\- value – the coefficient of the monomial

\- variable – the degree of the monomial

\- next – a pointer to the next monomial



\* Description of the "Poly" class:

======================



The "Poly" class implements polynomials using the "Term" structure, based on a singly linked list. They will be displayed in the following format:

1\*x^3 + -4\*x^2 + 3\*x^1 + -5\*x^0



This class contains:

\- head, tail – pointers to the first and last element of the polynomial

\- degree – the degree of the polynomial



\* Poly class functions:

======================

\- copy operator – `Poly(other Poly)` and `poly = other\_poly` –

copy constructors

\- `+` operator – addition of two polynomials, e.g., poly3 = poly1 + poly2

\- `-` operator – subtraction of polynomials, e.g., poly3 = poly1 - poly2

\- `\*` operator – multiplication of polynomials, e.g., poly3 = poly1 \* poly2

\- `==` and `!=` operators – comparison of two polynomials by subtracting one from the other

\- `horner` – calculating the value of the polynomial for a given `x`

\- `display` – displaying the polynomial, e.g., 10\*x^4 + 2\*x^3 + 5\*x^2 + 6\*x^1

\- `add\_term` – adding a monomial to an existing polynomial. This functionality is used for the initial creation of polynomials:

\- remove\_term – removes a monomial from an existing polynomial

\- empty – checks whether the polynomial contains any monomials

\- if\_degree – checks whether the polynomial contains a monomial of a given degree

\- operator\[] – retrieves the coefficient for a given power

\- get\_degree – returns the degree of the polynomial

\- clear – "clears" the polynomial



\--------------------------------------------------------------------------



\* How to run the program:

========================



The directory contains a Makefile for compiling, linking, and running the

aforementioned programs, as well as for cleaning the directory and

creating an archive of its contents.



\-> To run the program, execute the following command in your shell:

make



\-> To clean the directory (remove unnecessary files), execute:

make clean



==========================================================================

