#include <iostream>
#include "./../BigInt/BigInt.h"
#include <string>
#include <random>
#include <tuple>
#include <math.h>
#include <algorithm>
#include <string>
#include <iterator>
#include <sstream>

using namespace Dodecahedron;

namespace Rsa {
	struct RsaKey
	{
		Bigint n;
		Bigint d;
		Bigint e;
		RsaKey(Bigint, Bigint, Bigint);
		void print();
	};

	class Rsa {
		public:
			Rsa();
			std::string Encode(std::string, RsaKey*);
			std::string Decode(std::string, RsaKey*);
			RsaKey* CreateKeys(int speed);
			
	};

	struct BigIntHelper {
		static Bigint Pgcd(Bigint,Bigint);
		static Bigint PhiN(Bigint, Bigint);
		static Bigint GenE(Bigint, Bigint);
		static Bigint InvModulo(Bigint, Bigint);
		static Bigint RandomPrimer(int);
		static Bigint PowModN(uint64_t a, uint64_t b, uint64_t n);
	};
}

