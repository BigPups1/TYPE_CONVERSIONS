#include<iostream>
using std::cout;
using std::endl;
using std::cin;

class Fraction
{
	//Описывает простую дробь.
	int integer;	//Целая часть
	int numerator;	//Числитель
	int denominator;//Знаменатель
public:
	int get_integer() const
	{
		return integer;
	}
	int get_numerator()const
	{
		return numerator;
	}
	int get_denominator()const
	{
		return denominator;
	}
	void set_integer(int integer)
	{
		this->integer = integer;
	}
	void set_numerator(int numerator)
	{
		this->numerator = numerator;
	}
	void set_denominator(int denominator)
	{
		if (denominator != 0)
		{
			this->denominator = denominator;
		}
		else
		{
			this->denominator = 1;
		}
	}

	Fraction& operator()(int integer, int numenator, int denominator)
	{
		set_integer(integer);
		set_numerator(numenator);
		set_denominator(denominator);
		return *this;
	}
	//		Constructors:
	Fraction()
	{
		this->integer = 0;
		this->numerator = 0;
		this->denominator = 1;
		cout << "DefaultConstruct:\t" << this << endl;
	}
	explicit Fraction(int integer)
	{
		this->integer = integer;
		this->numerator = 0;
		this->denominator = 1;
		cout << "SingleArgumentConstructor:\t" << this << endl;
	}
	Fraction(int numerator, int denominator)
	{
		this->integer = 0;
		this->numerator = numerator;
		this->denominator = denominator ? denominator : 1;
		cout << "Constructor:\t" << this << endl;
	}
	Fraction(int integer, int numerator, int denominator)
	{
		this->integer = integer;
		this->numerator = numerator;
		this->denominator = denominator ? denominator : 1;
		/*
			condition ? expression1 : expression2;
		*/
		cout << "Constructor:\t" << this << endl;
	}
	Fraction(const Fraction& other)
	{
		//*this = other;
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyConstructor:" << this << endl;
	}
	~Fraction()
	{
		cout << "Destructor:\t" << this << endl;
	}
	//     Increment/Decrement
	Fraction& operator++()
	{
		this->integer++;
		return *this;
	}
	Fraction operator++(int)
	{
		Fraction buffer = *this;
		this->integer++;
		return buffer;
	}



	//		Operators:
	Fraction& operator=(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyAssignment:" << this << endl;
		return *this;
	}

	Fraction& operator=(int integer)
	{
		this->integer =integer;
		this->numerator = 0;
		this->denominator = 1;
		return *this;
	}


	Fraction operator*(Fraction right) const
	{
		Fraction left = *this;
		left.to_improper();
		right.to_improper();
		Fraction result;
		result.numerator = left.numerator*right.numerator;
		result.denominator = left.denominator*right.denominator;
		result.to_proper();
		return result;
	}
	//         type-cast operators:
	explicit operator int()const
	{
		return integer;
	}
	operator double() const
	{
		//Из простой дроби делает десятичную дробь.
		return integer+(double)numerator/denominator;
	}
	//		Methods:

	Fraction& print()
	{
		if (integer)cout << integer;
		if (numerator)
		{
			if (integer)cout << "(";
			cout << numerator << "/" << denominator;
			if (integer)cout << ")";
		}
		else if (integer == 0)cout << 0;
		cout << endl;
		return *this;
	}

	Fraction& to_improper()
	{
		numerator += integer * denominator;
		integer -= integer;
		return *this;
	}
	Fraction& to_proper()
	{
		integer += numerator / denominator;
		numerator %= denominator;
		return *this;
	}
};

Fraction operator*(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	Fraction result(left.get_numerator()*right.get_numerator(), left.get_denominator()*right.get_denominator());
	/*result.set_numerator(left.get_numerator()*right.get_numerator());
	result.set_denominator(left.get_denominator()*right.get_denominator());*/
	//result.to_proper();
	return result.to_proper();
}

std::ostream& operator<<(std::ostream& os, const Fraction& obj)
{
	if (obj.get_integer())os << obj.get_integer();
	if (obj.get_numerator())
	{
		if (obj.get_integer())os << "(";
		os << obj.get_numerator() << "/" << obj.get_denominator();
		if (obj.get_integer())os << ")";
	}
	if (obj.get_integer() == 0 && obj.get_numerator() == 0)os << 0;
	return os;
}

std::istream& operator>>(std::istream& is, Fraction& obj)
{
	int integer, numenator, denominator;
	is >> integer>> numenator>> denominator;
	obj(integer, numenator, denominator);
	return is;
}

//#define CONSTRUCTORS_CHECK
//#define OPERATORS_CHECK
#define INPUT_OUTPUT_CHECK
#define TYPE_CONVERSIONS

void main()
{
	setlocale(LC_ALL, "");
#ifdef CONSTRUCTORS_CHECK
	double a = 5;
	cout << a << endl;

	Fraction A;		//Default constructor
	A.print();

	Fraction B = 5;	//Single argument constructor
	B.print();

	Fraction C(1, 2);//Constructor
	C.print();

	Fraction D(2, 3, 4);
	D.print();

	Fraction E = D;	//CopyConstructor
	E.print();

	Fraction F;
	F = E;
#endif // CONSTRUCTORS_CHECK

#ifdef OPERATORS_CHECK
	Fraction A(2, 4);
	A.print();
	Fraction B=A++;
	A.print();
	B.print();
	cout << A++<< endl;
	cout << "Введите целую часть, числитель и знаменатель в назвоном порядкеж через пробел: "; cin >> A; cout << endl <<"Ваша дробь: "<< A << endl;
#endif
#ifdef INPUT_OUTPUT_CHECK






#endif // INPUT_OUTPUT_CHECK
#ifdef TYPE_CONVERSIONS
	int a = 2;
	double b = 3.14;
	a = b;
	cout << a << endl;
	Fraction A= (Fraction)4;
	A = (Fraction)5;
	cout << A << endl;
	a = (int)A; //C-like cast notation
	a = int(A); //Functional notation
	cout << a << endl;
	Fraction B(2, 5, 6);
	b = B;
	cout << b << endl;



#endif // TYPE_CONVERSIONS


}