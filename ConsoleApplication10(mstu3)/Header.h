#pragma once

#include <iostream>
#include <iomanip>

using namespace std;

class Fraction
{
private:
	int a;		// ��������� (������ >= 0)
	int b;		// ����������� (������ > 0)
	int sign;	// ���� ����� (1 ���� -1)

	inline int gcd(int x, int y);							// ������� ���������� ��� ���� �����
	inline int str_to_int(char* str, int left, int right);	// ������� �������������� ��������� � ����� �����

public:
	Fraction();							// ����������� �� ���������
	Fraction(int A, int B);				// ����������� � ��������� ��������� � �����������
	Fraction(double num);				// ����������� �� ������������� �����
	Fraction(char* str);				// ����������� �� ������
	Fraction(const char* str);			// ����������� �� ������ �2
	Fraction(const Fraction& fraction);	// ����������� �����������

	friend istream& operator >> (istream& in, Fraction& fraction);	// ����
	friend ostream& operator << (ostream& out, Fraction& fraction);	// �����

	friend Fraction operator + (Fraction& f1, Fraction& f2);		// ����� + �����
	friend Fraction operator + (Fraction& fraction, int num);		// ����� + �����
	friend Fraction operator + (int num, Fraction& fraction);		// ����� + �����
	friend Fraction operator + (Fraction& fraction, double num);	// ����� + ������������
	friend Fraction operator + (double num, Fraction& fraction);	// ������������ + �����

	Fraction operator += (Fraction fraction);	// ����� += �����
	Fraction operator += (int num);				// ����� += �����
	Fraction operator += (double num);			// ����� += ������������
};