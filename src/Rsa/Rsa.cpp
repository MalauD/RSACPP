#include "Rsa.h"

Rsa::Rsa::Rsa()
{

}

std::string Rsa::Rsa::Encode(std::string msg, RsaKey* key)
{
	std::ostringstream oss;

	for (char c : msg) {
		int AsciiChar = (int)c;
		if (AsciiChar > 0) {
			int64_t BigAscii = AsciiChar;
			int64_t EncodedLeter = int64_tHelper::PowModN(BigAscii.to_builtin(),key->e.to_builtin(),key->n.to_builtin());
			oss << EncodedLeter << " ";
		}
	}
	 

	return oss.str();
}

std::string Rsa::Rsa::Decode(std::string message, RsaKey* key)
{
	std::ostringstream oss;

	std::istringstream iss(message);
	std::vector<std::string> splitedMessage((std::istream_iterator<std::string>(iss)),
		std::istream_iterator<std::string>());

	for (std::string str : splitedMessage) {
		//int64_t dl = pow(EncodedLettre, d);
		if (std::stoi(str) > 0) {
			int64_t DecodedLetter = int64_tHelper::PowModN(int64_t(str).to_builtin(),key->d.to_builtin(),key->n.to_builtin());
			//std::cout << "(" << DecodedLetter << ")";
			oss << static_cast<char>(DecodedLetter.to_builtin());
		}

	}

	return oss.str();
}

Rsa::RsaKey* Rsa::Rsa::CreateKeys(int speed)
{
	int64_t p = int64_tHelper::RandomPrimer(speed);
	int64_t q = int64_tHelper::RandomPrimer(speed);
	if (p == q)
		throw new std::exception("p is equal to q");

	int64_t n = p * q;
	int64_t phiN = int64_tHelper::PhiN(p, q);

	int64_t e = p < q ? int64_tHelper::GenE(p, phiN) : int64_tHelper::GenE(q, phiN);

	int64_t d = int64_tHelper::InvModulo(e, phiN);

	return new RsaKey(n, d, e);
}

int64_t Rsa::int64_tHelper::Pgcd(int64_t a, int64_t b)
{
	int64_t r = int64_t(0);

	if (a < b)
		std::swap(a, b);

	if ((r = a % b) == int64_t(0))
		return b;
	else
		return Pgcd(b, r);
}

int64_t Rsa::int64_tHelper::PhiN(int64_t p, int64_t q)
{
	return (p - int64_t(1)) * (q - int64_t(1));
}

int64_t Rsa::int64_tHelper::GenE(int64_t Smallest, int64_t PhiN)
{
	for (int64_t e = Smallest; e <= PhiN; e++) {
		if (Pgcd(PhiN, e) == int64_t(1)) {
			return e;
		}
	}
	throw new std::exception("cannot find E");
}

int64_t Rsa::int64_tHelper::InvModulo(int64_t a , int64_t m)
{
	int64_t m0 = m;
	int64_t y = int64_t(0), x = int64_t(1);

	if (m == int64_t(1))
		return int64_t(0);

	while (a > int64_t(1))
	{
		int64_t q = a / m;
		int64_t t = m;

		m = a % m, a = t;
		t = y;

		y = x - q * y;
		x = t;
	}

	if (x < int64_t(0))
		x += m0;

	return x;
}

int64_t Rsa::int64_tHelper::RandomPrimer(int speed)
{
	int64_t nLoop;
	int64_t nMod;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int64_t> rnd(20 * speed, 100 * speed);


	for (nLoop = rnd(gen); nLoop < 1844674407370955161 - 2; nLoop++) {
		//for (nLoop = 3; nLoop < (100); nLoop++) {
		for (nMod = 2; nMod < nLoop; nMod++) {
			if ((nLoop % nMod) == 0) {
				break;
			}
		}
		if (nMod == nLoop) {
			return int64_t(nLoop);
		}
	}
}

int64_t Rsa::int64_tHelper::PowModN(int64_t a, int64_t b, int64_t n) {
	a = a % n;
	int64_t c = 1;
	for (int64_t i = 1; i <= b; i++) {
		c = (c * a % n);
		if (i % (b / 10) == 0) 
			std::cout << b / i * 100 << "%\r";		
	}
		

	return c;
}

Rsa::RsaKey::RsaKey(int64_t nn, int64_t dd, int64_t ee)
{
	n = nn;
	d = dd;
	e = ee;
}



void Rsa::RsaKey::print()
{
	std::cout << "n: " << n << " d: " << d << " e: " << e << "\n";
}
