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
			Bigint BigAscii = AsciiChar;
			Bigint EncodedLeter = BigIntHelper::PowModN(BigAscii.to_builtin(),key->e.to_builtin(),key->n.to_builtin());
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
		//Bigint dl = pow(EncodedLettre, d);
		if (std::stoi(str) > 0) {
			Bigint DecodedLetter = BigIntHelper::PowModN(Bigint(str).to_builtin(),key->d.to_builtin(),key->n.to_builtin());
			//std::cout << "(" << DecodedLetter << ")";
			oss << static_cast<char>(DecodedLetter.to_builtin());
		}

	}

	return oss.str();
}

Rsa::RsaKey* Rsa::Rsa::CreateKeys(int speed)
{
	Bigint p = BigIntHelper::RandomPrimer(speed);
	Bigint q = BigIntHelper::RandomPrimer(speed);
	if (p == q)
		throw new std::exception("p is equal to q");

	Bigint n = p * q;
	Bigint phiN = BigIntHelper::PhiN(p, q);

	Bigint e = p < q ? BigIntHelper::GenE(p, phiN) : BigIntHelper::GenE(q, phiN);

	Bigint d = BigIntHelper::InvModulo(e, phiN);

	return new RsaKey(n, d, e);
}

Bigint Rsa::BigIntHelper::Pgcd(Bigint a, Bigint b)
{
	Bigint r = Bigint(0);

	if (a < b)
		std::swap(a, b);

	if ((r = a % b) == Bigint(0))
		return b;
	else
		return Pgcd(b, r);
}

Bigint Rsa::BigIntHelper::PhiN(Bigint p, Bigint q)
{
	return (p - Bigint(1)) * (q - Bigint(1));
}

Bigint Rsa::BigIntHelper::GenE(Bigint Smallest, Bigint PhiN)
{
	for (Bigint e = Smallest; e <= PhiN; e++) {
		if (Pgcd(PhiN, e) == Bigint(1)) {
			return e;
		}
	}
	throw new std::exception("cannot find E");
}

Bigint Rsa::BigIntHelper::InvModulo(Bigint a , Bigint m)
{
	Bigint m0 = m;
	Bigint y = Bigint(0), x = Bigint(1);

	if (m == Bigint(1))
		return Bigint(0);

	while (a > Bigint(1))
	{
		Bigint q = a / m;
		Bigint t = m;

		m = a % m, a = t;
		t = y;

		y = x - q * y;
		x = t;
	}

	if (x < Bigint(0))
		x += m0;

	return x;
}

Bigint Rsa::BigIntHelper::RandomPrimer(int speed)
{
	uint64_t nLoop;
	uint64_t nMod;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<uint64_t> rnd(200 * speed, 1000 * speed);


	for (nLoop = rnd(gen); nLoop < 1844674407370955161 - 2; nLoop++) {
		//for (nLoop = 3; nLoop < (100); nLoop++) {
		for (nMod = 2; nMod < nLoop; nMod++) {
			if ((nLoop % nMod) == 0) {
				break;
			}
		}
		if (nMod == nLoop) {
			return Bigint(nLoop);
		}
	}
}

Bigint Rsa::BigIntHelper::PowModN(uint64_t a, uint64_t b, uint64_t n) {
	a = a % n;
	uint64_t c = 1;
	for (uint64_t i = 1; i <= b; i++)
		c = (c * a % n);

	return Bigint(c);
}

Rsa::RsaKey::RsaKey(Bigint nn, Bigint dd, Bigint ee)
{
	n = nn;
	d = dd;
	e = ee;
}



void Rsa::RsaKey::print()
{
	std::cout << "n: " << n << " d: " << d << " e: " << e << "\n";
}
