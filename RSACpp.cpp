// RSACpp.cpp : définit le point d'entrée de l'application.
//

#include "RSACpp.h"

using namespace std;
using namespace Dodecahedron;

Bigint GeneratePrime() {
	uint64_t nLoop;
	uint64_t nMod;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<uint64_t> rnd(200, 1000);




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

Bigint pgcd(Bigint a, Bigint b)
{
	Bigint r = Bigint(0);

	if (a < b)
		std::swap(a, b);

	if ((r = a % b) == Bigint(0))
		return b;
	else
		return pgcd(b, r);
}

Bigint PhiN(Bigint p , Bigint q) {
	return (p - Bigint(1)) * (q - Bigint(1));
}

Bigint GenE(Bigint Smallest,Bigint PhiN) {
	for (Bigint e = Smallest; e <= PhiN; e++) {
		if (pgcd(PhiN, e) == Bigint(1)) {
			return e;
		}
	}
	throw new std::exception("cannot find E");
}


Bigint modInverse2(Bigint a, Bigint m)
{
	Bigint m0 = m;
	Bigint y = Bigint(0), x = Bigint(1);

	if (m == Bigint(1))
		return Bigint(0);

	while (a > Bigint(1))
	{
		// q is quotient 
		Bigint q = a / m;
		Bigint t = m;

		// m is remainder now, process same as 
		// Euclid's algo 
		m = a % m, a = t;
		t = y;

		// Update y and x 
		y = x - q * y;
		x = t;
	}

	// Make x positive 
	if (x < Bigint(0))
		x += m0;

	return x;
}

Bigint modInverse(Bigint a, Bigint m)
{
	a = a % m;
	for (Bigint x = Bigint(1); x < m; x++)
		if ((a * x) % m == Bigint(1))
			return x;
	throw new std::exception("cannot find inv mod");
}


void CreateKeys() {
	Bigint p = GeneratePrime();
	Bigint q = GeneratePrime();
	if (p == q)
		throw new std::exception("p is equal to q");

	Bigint n = p * q;
	Bigint phiN = PhiN(p, q);

	std::cout << "p: " << p << " q: " << q << " n: " << n << " Phi(n): " << phiN << "\n";

	Bigint e = p < q ? GenE(p, phiN) : GenE(q, phiN);

	std::cout << "e: " << e << "\n";

	Bigint d = modInverse(e, phiN);

	std::cout << "d: " << d << "\n";
}

void Encode() {
	printf("Please enter public key (n): ");
	int pIntKey;
	std::cin >> pIntKey;
	Bigint pKey = Bigint(pIntKey);
	printf("Please enter public key (e): ");
	int peIntKey;
	std::cin >> peIntKey;
	Bigint peKey = Bigint(peIntKey);

	printf("Please enter your message: ");
	string message;
	getline(std::cin >> std::ws, message);
	//std::replace(message.begin(), message.end(), ' ', '_');
	printf("Your encrypted message is: \n");
	std::cout << "Size " << sizeof(message) << "o" << "\n";
	std::cout << "- Beginning of the message -" << "\n";
	for (char c : message) {

		
		int AsciiChar = (int)c;
		if (AsciiChar > 0){
			Bigint BigAscii = AsciiChar;
			//std::cout << el << "\n";
			Bigint EncodedLeter = BigAscii.pow(peIntKey) % pKey;
			std::cout << EncodedLeter << " ";
		}
		
		
	}
	std::cout << "\n" << "- End of the message -" << "\n";
}

void Decode() {
	printf("Please enter private key (n): ");
	int pIntKey;
	std::cin >> pIntKey;
	Bigint pKey = Bigint(pIntKey);
	printf("Please enter private key (d): ");
	int pdIntKey;
	std::cin >> pdIntKey;
	printf("Please enter the encrypted message: ");
	string message;
	getline(std::cin >> std::ws, message);

	std::istringstream iss(message);
	std::vector<std::string> splitedMessage((std::istream_iterator<std::string>(iss)),
		std::istream_iterator<std::string>());

	std::cout << "- Beginning of the message -" << "\n";
	for (string str : splitedMessage) {
		//Bigint dl = pow(EncodedLettre, d);
		if (std::stoi(str) > 0) {
			Bigint dl = pow(Bigint(str), pdIntKey);
			Bigint DecodedLetter = dl % pKey;
			//std::cout << "(" << DecodedLetter << ")";
			std::stringstream ss;
			ss << DecodedLetter;
			std::cout << (char)std::stoi(ss.str());
		}
		
	}
	std::cout << "\n" << "- End of the message -" << "\n";
}
//10 25 3 25 24 9 22 2 18 4 2 26 8 9 8

int main()
{
	int choice;
	do {
		printf("0 -> Create key \n");
		printf("1 -> Encode message \n");
		printf("2 -> Decode message \n");
		printf("3 -> Quit \nYour choice: ");
		std::cin >> choice;
		switch (choice)
		{
		case 0:
			CreateKeys();
			break;
		case 1:
			Encode();
			break;
		case 2:
			Decode();
			break;
		default:
			break;
		}
	} while (choice != 3);
	

	//Bigint Lettre = Bigint(4);

	//Bigint el = pow(Lettre, e);
	////std::cout << el << "\n";
	//Bigint EncodedLettre = el % n;

	//std::cout << EncodedLettre << "\n";

	//Bigint dl = pow(EncodedLettre, d);
	////std::cout << dl << "\n";
	//Bigint DecodedLetter = dl % n;

	//

	//std::cout << "DecodeSamere: " <<DecodedLetter << "\n";


	//return 0;
}

