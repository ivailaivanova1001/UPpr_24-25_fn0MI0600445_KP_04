// UPpr_24-25_fn0MI0600445_KP_04.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

typedef std::pair<int, int> Rational;
typedef std::vector<Rational> Polynomial;

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

static Rational simplify(const Rational& r)
{
    int numerator = r.first;
    int denumerator = r.second;

    if (denumerator == 0)
    {
        std::cout << "Denominator can't be zero.\n";
        exit(1);
    }

    int gcdValue = gcd(numerator, denumerator);
    numerator /= gcdValue;
    denumerator /= gcdValue;

    if (denumerator < 0)
    {
        numerator = -numerator;
        denumerator = -denumerator;
    }

    return { numerator, denumerator };
}

int string_to_int(const std::string& str)
{
    int result = 0;
    bool isNegative = false;
    size_t start = 0;

    if (str[0] == '-') {
        isNegative = true;
        start = 1;
    }

    for (size_t i = start; i < str.size(); i++)
    {
        if (str[i] < '0' || str[i] > '9') {
            std::cerr << "Error.\n";
            exit(1);
        }
        result = result * 10 + (str[i] - '0');
    }

    if (isNegative) {
        return -result;
    }
    else {
        return result;
    }
}

Rational add_rational(const Rational& a, const Rational& b)
{
    int n1 = a.first, d1 = a.second;
    int n2 = b.first, d2 = b.second;
    int numerator = n1 * d2 + n2 * d1;
    int denominator = d1 * d2;
    return simplify({ numerator, denominator });
}

Rational subtract_rational(const Rational& a, const Rational& b)
{
    int n1 = a.first, d1 = a.second;
    int n2 = b.first, d2 = b.second;
    int numerator = n1 * d2 - n2 * d1;
    int denominator = d1 * d2;
    return simplify({ numerator, denominator });
}

size_t max_val(size_t a, size_t b) 
{
        size_t x = a;
        if (b > a) 
        {
            x = b;
        }
        return x;
}

Polynomial add_polynomials(const Polynomial& p1, const Polynomial& p2)
{
    size_t max_degree = max_val(p1.size(), p2.size());
    Polynomial result(max_degree, { 0, 1 });

    for (size_t i = 0; i < max_degree; i++)
    {
        if (i < p1.size()) result[i] = add_rational(result[i], p1[i]);
        if (i < p2.size()) result[i] = add_rational(result[i], p2[i]);
    }
    return result;
}

Polynomial subtract_polynomials(const Polynomial& p1, const Polynomial& p2)
{
    size_t max_degree = max_val(p1.size(), p2.size());
    Polynomial result(max_degree, { 0, 1 });

    for (size_t i = 0; i < max_degree; i++)
    {
        if (i < p1.size()) result[i] = add_rational(result[i], p1[i]);
        if (i < p2.size()) result[i] = subtract_rational(result[i], p2[i]);
    }
    return result;
}

Polynomial multiply_polynomials(const Polynomial& p1, const Polynomial& p2)
{
    size_t degree1 = p1.size();
    size_t degree2 = p2.size();
    Polynomial result(degree1 + degree2 - 1, { 0, 1 });

    for (size_t i = 0; i < degree1; i++)
    {
        for (size_t j = 0; j < degree2; j++)
        {
            Rational product = { p1[i].first * p2[j].first, p1[i].second * p2[j].second };
            result[i + j] = add_rational(result[i + j], simplify(product));
        }
    }
    return result;
}

std::pair<Polynomial, Polynomial> divide_polynomials(const Polynomial& dividend, const Polynomial& divisor)
{
    if (divisor.empty() || divisor.back().first == 0)
    {
        std::cout << "Division by zero - not allowed.";
        exit(1);
    }

    Polynomial quotient;
    Polynomial remainder = dividend;
    size_t divisor_degree = divisor.size() - 1;

    while (!remainder.empty() && remainder.size() > divisor_degree)
    {
        size_t degree_difference = remainder.size() - divisor_degree - 1;
        Rational leading_term = { remainder.back().first * divisor.back().second,
                                remainder.back().second * divisor.back().first };
        leading_term = simplify(leading_term);

        Polynomial term(degree_difference + 1, { 0, 1 });
        term.back() = leading_term;
        quotient = add_polynomials(quotient, term);

        Polynomial scaled_divisor = multiply_polynomials(term, divisor);
        remainder = subtract_polynomials(remainder, scaled_divisor);

        while (!remainder.empty() && remainder.back().first == 0)
        {
            remainder.pop_back();
        }
    }

    return { quotient, remainder };
}

void print_polynomial(const Polynomial& p)
{
    bool first = true;
    for (size_t i = p.size(); i-- > 0;)
    {
        if (p[i].first != 0)
        {
            if (!first)
                std::cout << " + ";
            if (i == 0)
            {
                std::cout << p[i].first;
            }
            else if (p[i].second == 1)
            {
                std::cout << p[i].first << "x^" << i;
            }
            else
            {
                std::cout << "(" << p[i].first << "/" << p[i].second << ")x^" << i;
            }
            first = false;
        }
    }
    if (first)
        std::cout << "0";
    std::cout << std::endl;
}

Polynomial read_polynomial()
{
    int degree;
    std::cout << "\nEnter the degree of the polynomial: ";
    std::cin >> degree;

    Polynomial p(degree + 1, { 0, 1 });

    for (int i = degree; i >= 0; i--)
    {
        std::string rational;
        int numerator = 0;
        int denumerator = 1;
        std::cout << "Enter coefficient before x^" << i << " : ";
        std::cin >> rational;

        size_t slashPos = rational.find('/');
        if (slashPos != std::string::npos)
        {
            numerator = string_to_int(rational.substr(0, slashPos));
            denumerator = string_to_int(rational.substr(slashPos + 1));
        }
        else
        {
            numerator = string_to_int(rational);
            denumerator = 1;
        }

        p[i] = simplify({ numerator, denumerator });
    }

    std::cout << "Polynomial entered: ";
    print_polynomial(p);

    return p;
}

void print_menu() {
    const char* menu[] = {
        "Welcome!",
        "..........................................................",
        "................Polynomial calculator.....................",
        "..........................................................",
        "\nChoose one of the following functionalities:",
        "..........................................................",
        "1) Add polynomials",
        "2) Subtract polynomials",
        "3) Multiply polynomials",
        "4) Divide polynomials",
        "5) Multiply polynomial by scalar",
        "6) Find value of polynomial at a given number",
        "7) Find GCD of two polynomials",
        "8) Display Vieta's formulas for a given polynomial",
        "9) Represent polynomial in powers of(x + a)",
        "10) Factor polynomial and find its rational roots",
        "11) Quit program",
        "..........................................................",
        "\nEnter your option here: "
    };
    for (int i = 0; i < sizeof(menu) / sizeof(menu[0]); ++i)
    {
        std::cout << menu[i] << std::endl;
    }
}


void add_polynomials()
{
    std::cout << "Polynomial P(x)\n";
    Polynomial p1 = read_polynomial();

    std::cout << "\nPolynomial G(x)\n";
    Polynomial p2 = read_polynomial();

    Polynomial sum = add_polynomials(p1, p2);
    std::cout << "P(x) + G(x)= ";
    print_polynomial(sum);

    std::cout << "\nEnter a new option: ";
}

void subtract_polynomials()
{
    std::cout << "Polynomial P(x)\n";
    Polynomial p1 = read_polynomial();

    std::cout << "\nPolynomial G(x)\n";
    Polynomial p2 = read_polynomial();

    Polynomial difference = subtract_polynomials(p1, p2);
    std::cout << "P(x) - G(x)= ";
    print_polynomial(difference);

    std::cout << "\nEnter a new option: ";
}

void multiply_polynomials()
{
    std::cout << "Polynomial P(x)";
    Polynomial p1 = read_polynomial();

    std::cout << "\nPolynomial G(x)";
    Polynomial p2 = read_polynomial();

    Polynomial product = multiply_polynomials(p1, p2);
    std::cout << "P(x) * G(x)= ";
    print_polynomial(product);

    std::cout << "\nEnter a new option: ";
}

void divide_polynomials()
{
    std::cout << "Polynomial P(x)";
    Polynomial p1 = read_polynomial();

    std::cout << "\nPolynomial G(x)";
    Polynomial p2 = read_polynomial();

    std::pair<Polynomial, Polynomial> divisionResult = divide_polynomials(p1, p2);
    Polynomial quotient = divisionResult.first;
    Polynomial remainder = divisionResult.second;

    std::cout << "Quotient: ";
    print_polynomial(quotient);

    std::cout << "Remainder: ";
    print_polynomial(remainder);

    std::cout << "\nEnter a new option: ";
}
void multiply_by_scalar()
{
    std::cout << "Polynomial P(x)";
    Polynomial p = read_polynomial();

    std::cout << "\nEnter a scalar:";
    int scalar;
    std::cin >> scalar;

    for (size_t i = 0; i < p.size(); i++)
    {
        p[i].first *= scalar;
        p[i] = simplify(p[i]);
    }

    std::cout << "P(x) * " << scalar << " = ";
    print_polynomial(p);

    std::cout << "\nEnter a new option: ";
}

void evaluate_polynomial()
{
    std::cout << "Polynomial P(x)";
    Polynomial p = read_polynomial();

    std::cout << "Enter a value for x: ";
    int x;
    std::cin >> x;

    Rational result = { 0, 1 };
    Rational power = { 1, 1 };

    for (size_t i = 0; i < p.size(); i++)
    {
        result = add_rational(result, { p[i].first * power.first, p[i].second * power.second });
        power.first *= x;
    }

    result = simplify(result);
    std::cout << "P(" << x << ") = " << result.first;
    if (result.second != 1)
    {
        std::cout << "/" << result.second;
    }
    std::cout << "\nEnter a new option: ";
}

void find_gcd()
{
    std::cout << "Polynomial P(x)";
    Polynomial p1 = read_polynomial();

    std::cout << "Polynomial G(x)";
    Polynomial p2 = read_polynomial();

    while (!p2.empty() && p2.back().first != 0)
    {
        Polynomial remainder = subtract_polynomials(p1, multiply_polynomials(p2, divide_polynomials(p1, p2).first));
        p1 = p2;
        p2 = remainder;
    }

    std::cout << "GCD(P(x), G(x)) = ";
    print_polynomial(p1);

    std::cout << "\nEnter a new option: ";
}

void vieta_formulas()
{
    std::cout << "Polynomial P(x)";
    Polynomial p = read_polynomial();

    size_t degree = p.size() - 1;
    if (degree == 0 || p.back().first == 0)
    {
        std::cout << "Invalid polynomial for Vieta's formulas";
    }

    Rational leading_coefficient = p.back();
    std::cout << "Vieta's formulas coefficients:";

    for (size_t i = 0; i < degree; i++)
    {
        Rational term = simplify({ p[i].first, leading_coefficient.first });
        std::cout << "Coefficient of x^" << i << " = " << term.first;
        if (term.second != 1) {
            std::cout << "/" << term.second;
        }
        std::cout << " ";
    }
    std::cout << "\nEnter a new option: ";
}

void in_powers()
{
    std::cout << "Polynomial P(x)";
    Polynomial p = read_polynomial();

    std::cout << "Enter the value of a: ";
    int a;
    std::cin >> a;

    Polynomial shifted(p.size(), { 0, 1 });

    for (size_t i = 0; i < p.size(); i++)
    {
        Rational coeff = p[i];
        for (size_t j = 0; j <= i; j++)
        {
            shifted[j].first += coeff.first;
            shifted[j].second = coeff.second;
        }
    }

    std::cout << "P(x + " << a << ") = ";
    print_polynomial(shifted);

    std::cout << "\nEnter a new option: ";
}

void factor_polynomial()
{
    std::cout << "Polynomial P(x)\n";
    Polynomial p = read_polynomial();


    if (p.empty() || p.back().first == 0)
    {
        std::cout << "Invalid polynomial for factorization.\n";
    }

    int constant_term = p[0].first;
    int leading_coeff = p.back().first;

    if (p.size() == 1)
    {
        std::cout << "This is a constant polynomial.\n";
        std::cout << "Rational roots: ";
        if (constant_term == 0)
        {
            std::cout << "All numbers\n";
        }
        else
        {
            std::cout << "None\n";
        }
    }

    std::vector<int> possible_numerators;
    std::vector<int> possible_denominators;

    for (int i = 1; i <= abs(constant_term); i++)
    {
        if (constant_term % i == 0)
        {
            possible_numerators.push_back(i);
            possible_numerators.push_back(-i);
        }
    }

    for (int i = 1; i <= abs(leading_coeff); i++)
    {
        if (leading_coeff % i == 0)
        {
            possible_denominators.push_back(i);
        }
    }

    std::cout << "Possible rational roots:\n";
    for (int numerator : possible_numerators)
    {
        for (int denumerator : possible_denominators)
        {
            Rational root = simplify({ numerator, denumerator });
            Rational value = { 0, 1 };
            Rational power = { 1, 1 };

            for (size_t i = 0; i < p.size(); i++)
            {
                value = add_rational(value, { p[i].first * power.first, p[i].second * power.second });
                power.first *= root.first;
                power.second *= root.second;
                power = simplify(power);
            }

            if (value.first == 0)
            {
                std::cout << root.first;
                if (root.second != 1)
                {
                    std::cout << "/" << root.second;
                }
                std::cout << "\n";
            }
        }
    }
    std::cout << "\nEnter a new option: ";
}

void case_function(int option)
{
    switch (option)
    {
    case 1: add_polynomials(); break;
    case 2: subtract_polynomials(); break;
    case 3: multiply_polynomials(); break;
    case 4: divide_polynomials(); break;
    case 5: multiply_by_scalar(); break;
    case 6: evaluate_polynomial(); break;
    case 7: find_gcd(); break;
    case 8: vieta_formulas(); break;
    case 9: in_powers(); break;
    case 10: factor_polynomial(); break;
    case 11:
        std::cout << "\nGoodbye!\n";
        break;

    default:
        std::cout << "Invalid option. Please try again." << std::endl;
    }
}

int main()
{
    print_menu();

    int option;
    do
    {
        std::cin >> option;
        case_function(option);
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
