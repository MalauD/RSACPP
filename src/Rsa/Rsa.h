#include <iostream>
#include "./../int64_t/int64_t.h"
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
		int64_t n;
		int64_t d;
		int64_t e;
		RsaKey(int64_t, int64_t, int64_t);
		void print();
	};

	class Rsa {
		public:
			Rsa();
			std::string Encode(std::string, RsaKey*);
			std::string Decode(std::string, RsaKey*);
			RsaKey* CreateKeys(int speed);
			
	};

	struct int64_tHelper {
		static int64_t Pgcd(int64_t,int64_t);
		static int64_t PhiN(int64_t, int64_t);
		static int64_t GenE(int64_t, int64_t);
		static int64_t InvModulo(int64_t, int64_t);
		static int64_t RandomPrimer(int);
		static int64_t PowModN(int64_t a, int64_t b, int64_t n);
	};
}

