#pragma once

#include <iostream>
#include <iomanip>

using namespace std;

class Fraction
{
private:
	int a;		// числитель (всегда >= 0)
	int b;		// знаменатель (всегда > 0)
	int sign;	// знак дроби (1 либо -1)

	inline int gcd(int x, int y);							// функция нахождения НОД двух чисел
	inline int str_to_int(char* str, int left, int right);	// функция преобразования подстроки в целое число

public:
	Fraction();							// конструктор по умолчанию
	Fraction(int A, int B);				// конструктор с указанием числителя и знаменателя
	Fraction(double num);				// конструктор от вещественного числа
	Fraction(char* str);				// конструктор от строки
	Fraction(const char* str);			// конструктор от строки №2
	Fraction(const Fraction& fraction);	// конструктор копирования

	friend istream& operator >> (istream& in, Fraction& fraction);	// ввод
	friend ostream& operator << (ostream& out, Fraction& fraction);	// вывод

	friend Fraction operator + (Fraction& f1, Fraction& f2);		// дробь + дробь
	friend Fraction operator + (Fraction& fraction, int num);		// дробь + целое
	friend Fraction operator + (int num, Fraction& fraction);		// целое + дробь
	friend Fraction operator + (Fraction& fraction, double num);	// дробь + вещественное
	friend Fraction operator + (double num, Fraction& fraction);	// вещественное + дробь

	Fraction operator += (Fraction fraction);	// дробь += дробь
	Fraction operator += (int num);				// дробь += целое
	Fraction operator += (double num);			// дробь += вещественное
};