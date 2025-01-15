// UPpr_24-25_fn0MI0600445_KP_04.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int gcd(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }

    if (a < 0)
    {
        return -a;
    }
    else
    {
        return a;
    }
}
static int string_to_int(const std::string& str) 
{
    int result = 0;
    bool isNegative = false;
    size_t start = 0;

    if (str[0] == '-') 
    {
        isNegative = true;
        start = 1;
    }

    for (size_t i = start; i < str.size(); i++) 
    {
        if (str[i] < '0' || str[i] > '9') 
        {
            std::cerr << "Error.\n";
            exit(1);
        }
        result = result * 10 + (str[i] - '0');
    }

    if (isNegative) 
    {
        return -result;
    }
    else {
        return result;
    }
}

int main() {

    std::cout << "\nWelcome!\n";
    std::cout << "..........................................................\n";
    std::cout << "................Polynomial calculator.....................\n";
    std::cout << "..........................................................\n";
    std::cout << "\nChoose one of the following functionalities:\n";
    std::cout << "1) Add polynomials\n";
    std::cout << "2) Subtract polynomials\n";
    std::cout << "3) Multiply polynomials\n";
    std::cout << "4) Divide polynomials\n";
    std::cout << "5) Multiply polynomial by scalar\n";
    std::cout << "6) Find value of polynomial at a given number\n";
    std::cout << "7) Find GCD of two polynomials\n";
    std::cout << "8) Display Vieta's formulas for a given polynomial\n";
    std::cout << "9) Represent polynomial in powers of(x + a)\n";
    std::cout << "10) Factor polynomial and find its rational roots\n";
    std::cout << "11) Quit program\n";
    std::cout << "..........................................................\n";
    std::cout << "\nEnter your option here: ";

    int option;

    do 
    {
        std::cin >> option;

        switch (option) 
        {
        case 1: 
        {
            std::cout << "Polynomial P(x)\n";
            //continue with function that read the first polynomial

            std::cout << "\nPolynomial G(x)\n";
            //continue with function that read the second polynomial

            //continue with function P(x) + G(x)

            std::cout << "P(x) + G(x)= ";

            //contine by printing the sum

            std::cout << "\nEnter a new option: ";
            break;
        }
        case 2: 
        {
            std::cout << "Polynomial P(x)\n";
            //continue with function that read the first polynomial

            std::cout << "\nPolynomial G(x)\n";
            //continue with function that read the second polynomial

            //continue with function P(x) - G(x)

            std::cout << "P(x) - G(x)= ";

            //contine by printing the diff

            std::cout << "\nEnter a new option: ";
            break;
        }
        case 3: 
        {
            std::cout << "Polynomial P(x)\n";
            //continue with function that read the first polynomial

            std::cout << "\nPolynomial G(x)\n";
            //continue with function that read the second polynomial

            //continue with function P(x) *  G(x)

            std::cout << "P(x) * G(x)= ";

            //continue by printing the *

            std::cout << "\nEnter a new option: ";
            break;
        }
        case 4: 
        {
            std::cout << "Polynomial P(x)\n";
            //continue with function that read the first polynomial

            std::cout << "\nPolynomial G(x)\n";
            //continue with function that read the second polynomial

            // function for quotient and remainder
            std::cout << "Quotient: ";

            // printing the quotient;
            std::cout << "Remainder: ";
            // printing the remainder;

            std::cout << "\nEnter a new option: ";
            break;
        }
        case 5:
        {
            std::cout << "Polynomial P(x)\n";
            //continue with function that read the first polynomial

            std::cout << "Enter scalar value: ";
            int scalar;
            std::cin >> scalar;

            //цикъл, с който скалара се умножава с всеки коефициент

            std::cout << "P(x) * " << scalar << " = ";
            
            // printing the new polynomial

            std::cout << "\nEnter a new option: ";
            break;
        }
        case 6: 
        {
            std::cout << "Polynomial P(x)\n";
            //continue with function that read the first polynomial

            std::cout << "Enter the value of x: ";
            int x;
            std::cin >> x;

            //цикъл

            std::cout << "P(" << x << ") = ";  // <<function;
           
            std::cout << "\nEnter a new option: ";
            break;
        }
        case 7: 
        {
            std::cout << "Polynomial P(x)\n";
            //continue with function that read the first polynomial

            std::cout << "\nPolynomial G(x)\n";
            //continue with function that read the first polynomial

           //while for gcd

            std::cout << "GCD(P(x), G(x)) = ";
            //continue with function that read the gcd polynomial
            std::cout << "\nEnter a new option: ";
            break;
        }
        case 8: 
        {
            std::cout << "Polynomial P(x)\n";
            //continue with function that read the first polynomial

             {
                //proverka za viet
                std::cout << "Invalid polynomial for Vieta's formulas";
                break;
            }

            std::cout << "Vieta's formulas coefficients:";

            // print coefficient before every x^
            std::cout << "\nEnter a new option: ";
            break;
        }
        case 9: 
        {
            std::cout << "Polynomial P(x)\n";
            //continue with function that read the first polynomial

            std::cout << "Enter the value of a: ";
            int a;
            std::cin >> a;

            std::cout << "P(x + " << a << ") = ";
            //print

            std::cout << "\nEnter a new option: ";
            break;
        }
        case 10:
        {
            std::cout << "Polynomial P(x)\n";
            //continue with function that read the first polynomial
            
            {
                //proverka
                std::cout << "Invalid polynomial for factorization.\n";
                break;
            }
            //....

            std::cout << "\nEnter a new option: ";
            break;

        }
        case 11:
            std::cout << "\nGoodbye!\n";
            break;
        default:
            std::cout << "\nPlease try again.\n";
        }
    } while (option != 11);
    return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
