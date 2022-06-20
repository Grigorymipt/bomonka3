#include "Header.h"

int Fraction::gcd(int x, int y)
{
	if (y == 0)
		return x;
	return gcd(y, x % y);
}

int Fraction::str_to_int(char* str, int left, int right)
{
	char* str_ = new char[right - left + 2];
	for (int i = 0; i < right - left + 1; ++i)
		str_[i] = str[i + left];
	str_[right - left + 1] = '\0';
	return atoi(str_);
}

Fraction::Fraction()
{
	a = 0;
	b = 1;
	sign = 1;
}

Fraction::Fraction(int A, int B)
{
	if (B == 0)
		throw invalid_argument("Zero denominator error!");
	else if (B < 0)
		throw invalid_argument("Zero sign error!");
	a = A;
	b = B;
	sign = 1;
	if (A < 0)
	{
		sign = -1;
		a = -a;
	}
	int g = gcd(a, b);
	a /= g;
	b /= g;
}

Fraction::Fraction(double num)
{
	sign = 1;
	if (num < 0)
	{
		num = -num;
		sign = -1;
	}
	int c = 1e9;
	int curr = 1;
	while (num > curr)
	{
		c /= 10;
		curr *= 10;
	}
	a = num * c;
	b = c;
	int g = gcd(a, b);
	a /= g;
	b /= g;
}

Fraction::Fraction(char* str)
{
	int n = strlen(str);
	int slash = -1, space = -1;
	for (int i = 0; i < n; ++i)
		if (str[i] == '/')
			slash = i;
		else if (str[i] == ' ')
			space = i;

	if (slash == -1 && space == -1 && str[0] != '-')
	{
		a = str_to_int(str, 0, strlen(str) - 1);
		b = 1;
		sign = 1;
	}
	else if (slash == -1 && space == -1 && str[0] == '-')
	{
		a = str_to_int(str, 1, strlen(str) - 1);
		b = 1;
		sign = -1;
	}
	else if (slash != -1 && space == -1 && str[0] != '-')
	{
		a = str_to_int(str, 0, slash - 1);
		b = str_to_int(str, slash + 1, strlen(str) - 1);
		sign = 1;
	}
	else if (slash != -1 && space == -1 && str[0] == '-')
	{
		a = str_to_int(str, 1, slash - 1);
		b = str_to_int(str, slash + 1, strlen(str) - 1);
		sign = -1;
	}
	else if (slash != -1 && space != -1 && str[0] != '-')
	{
		int c = str_to_int(str, 0, space);
		a = str_to_int(str, space + 1, slash - 1);
		b = str_to_int(str, slash + 1, strlen(str) - 1);
		a += c * b;
		sign = 1;
	}
	else if (slash != -1 && space != -1 && str[0] == '-')
	{
		int c = str_to_int(str, 1, space);
		a = str_to_int(str, space + 1, slash - 1);
		b = str_to_int(str, slash + 1, strlen(str) - 1);
		a += c * b;
		sign = -1;
	}
	int g = gcd(a, b);
	a /= g;
	b /= g;
}

Fraction::Fraction(const char* str)
{
	char* str_ = new char[strlen(str) + 1];
	strcpy_s(str_, strlen(str) + 1, str);
	*this = Fraction(str_);
}

Fraction::Fraction(const Fraction& fraction)
{
	a = fraction.a;
	b = fraction.b;
	sign = fraction.sign;
}

istream& operator >> (istream& in, Fraction& fraction)
{
	char str[50];
	in.getline(str, 50);
	Fraction tmp(str);
	fraction.a = tmp.a;
	fraction.b = tmp.b;
	fraction.sign = tmp.sign;
	return in;
}

ostream& operator << (ostream& out, Fraction& fraction)
{
	if (fraction.a == 0 || fraction.b == 1)
	{
		cout << fraction.a * fraction.sign;
		return out;
	}
	int c = fraction.a / fraction.b;
	if (c == 0)
		out << fraction.sign * fraction.a << '/' << fraction.b;
	else
		out << fraction.sign * c << ' ' << fraction.a - c * fraction.b << '/' << fraction.b;
	return out;
}

Fraction operator + (Fraction& f1, Fraction& f2)
{
	Fraction answer;
	int nok = f1.b * f2.b / answer.gcd(f1.b, f2.b);
	if (f1.sign == f2.sign)
	{
		answer.a = f1.a * nok / f1.b + f2.a * nok / f2.b;
		answer.sign = f1.sign;
	}
	else
	{
		answer.a = f1.sign * f1.a * nok / f1.b + f2.sign * f2.a * nok / f2.b;
		answer.sign = 1;
		if (answer.a < 0)
		{
			answer.a *= -1;
			answer.sign *= -1;
		}
	}
	answer.b = nok;
	int g = answer.gcd(answer.a, answer.b);
	answer.a /= g;
	answer.b /= g;
	return answer;
}

Fraction operator + (Fraction& fraction, int num)
{
	Fraction second(num, 1);
	Fraction answer = fraction + second;
	return answer;
}

Fraction operator + (int num, Fraction& fraction)
{
	Fraction first(num, 1);
	Fraction answer = first + fraction;
	return answer;
}

Fraction operator + (Fraction& fraction, double num)
{
	Fraction second(num);
	Fraction answer = fraction + second;
	return answer;
}

Fraction operator + (double num, Fraction& fraction)
{
	Fraction first(num);
	Fraction answer = first + fraction;
	return answer;
}

Fraction Fraction::operator += (Fraction fraction)
{
	*this = *this + fraction;
	return *this;
}

Fraction Fraction::operator += (int num)
{
	*this = *this + num;
	return *this;
}

Fraction Fraction::operator += (double num)
{
	*this = *this + num;
	return *this;
}