﻿#ifndef DODECAHEDRON_BIGINT_H_
#define DODECAHEDRON_BIGINT_H_

#include <vector>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>

namespace Dodecahedron
{
	class __fft;
	class Bigint
	{
	public:
		class arithmetic_error : public std::runtime_error
		{
		public:
			explicit arithmetic_error(const std::string& what_arg)
				: std::runtime_error(what_arg) {}
		};
		friend class __fft;

	private:
		std::vector<int> number;
		// don't modify this directly through const. use flip_positive
		mutable bool positive;
		static const int default_base = 100000000;
		static const int default_digits_per_element = 8;

	public:
		//Constructors
		Bigint();
		Bigint(long long);
		Bigint(const std::string&);
		Bigint(const Bigint& b);

		//Adding
		Bigint operator+(Bigint const&) const;
		Bigint& operator+=(Bigint const&);
		Bigint& operator++() { return *this += 1; }
		Bigint operator++(int) { Bigint bk(*this); ++* this; return bk; }

		//Subtraction
		Bigint operator-(Bigint const&) const;
		Bigint& operator-=(Bigint const&);
		Bigint& operator--() { return *this -= 1; }
		Bigint operator--(int) { Bigint bk(*this); --* this; return bk; }

		//Multiplication
		Bigint operator*(Bigint const&) const;
		Bigint& operator*=(Bigint const&);
		bool force_fft;

		//Division & modulo operation
		Bigint operator/(Bigint const&) const;
		Bigint& operator/=(Bigint const&);
		Bigint operator%(Bigint const&) const;
		Bigint& operator%=(Bigint const&);
		friend void sub_number(Bigint const&, Bigint const&, Bigint&);
		friend void divide(Bigint, Bigint const&, Bigint&, Bigint&);

		//Compare
		bool operator<(const Bigint&) const;
		bool operator>(const Bigint&) const;
		bool operator<=(const Bigint&) const;
		bool operator>=(const Bigint&) const;
		bool operator==(const Bigint&) const;
		bool operator!=(const Bigint&) const;

		//Allocation
		Bigint& operator=(const long long);

		//Input&Output
		friend std::istream& operator>>(std::istream&, Bigint&);
		friend std::ostream& operator<<(std::ostream&, Bigint const&);

		//Helpers
		void clear();
		Bigint& abs();

		//Power
		Bigint& pow(int const);

		//Trivia
		int digits() const;
		uint64_t mod(uint64_t a);
		int trailing_zeros() const;
		int to_builtin() const { return number.empty() ? 0 : number.front(); }
	private:
		int segment_length(int) const;
		Bigint pow(int const, std::map<int, Bigint>&);
		int compare(Bigint const&) const; //0 a == b, -1 a < b, 1 a > b
		void flip_positive() const;
		void delete_precode_zero();
	};

	Bigint abs(Bigint);
	std::string to_string(Bigint const&);
	Bigint factorial(int);
	Bigint pow(Bigint, int const);
}

#endif