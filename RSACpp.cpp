// RSACpp.cpp : définit le point d'entrée de l'application.
//

#include "RSACpp.h"

using namespace std;


BigInt GeneratePrime() {
	uint64_t nLoop;
	uint64_t nMod;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<uint64_t> rnd(12, 18);




	for (nLoop = rnd(gen); nLoop < 1844674407370955161 - 2; nLoop++) {
		//for (nLoop = 3; nLoop < (100); nLoop++) {
		for (nMod = 2; nMod < nLoop; nMod++) {
			if ((nLoop % nMod) == 0) {
				break;
			}
		}
		if (nMod == nLoop) {
			return BigInt(nLoop);
		}
	}
}

BigInt pgcd(BigInt a, BigInt b)
{
	BigInt r = BigInt(0);

	if (a < b)
		std::swap(a, b);

	if ((r = a % b) == BigInt(0))
		return b;
	else
		return pgcd(b, r);
}

BigInt PhiN(BigInt p , BigInt q) {
	return (p - BigInt(1)) * (q - BigInt(1));
}

BigInt GenE(BigInt Smallest,BigInt PhiN) {
	for (BigInt e = Smallest; e <= PhiN; e++) {
		if (pgcd(PhiN, e) == BigInt(1)) {
			return e;
		}
	}
	throw new std::exception("cannot find E");
}


BigInt modInverse2(BigInt a, BigInt m)
{
	BigInt m0 = m;
	BigInt y = BigInt(0), x = BigInt(1);

	if (m == BigInt(1))
		return BigInt(0);

	while (a > BigInt(1))
	{
		// q is quotient 
		BigInt q = a / m;
		BigInt t = m;

		// m is remainder now, process same as 
		// Euclid's algo 
		m = a % m, a = t;
		t = y;

		// Update y and x 
		y = x - q * y;
		x = t;
	}

	// Make x positive 
	if (x < BigInt(0))
		x += m0;

	return x;
}

BigInt modInverse(BigInt a, BigInt m)
{
	a = a % m;
	for (BigInt x = BigInt(1); x < m; x++)
		if ((a * x) % m == BigInt(1))
			return x;
	throw new std::exception("cannot find inv mod");
}


void CreateKeys() {
	BigInt p = GeneratePrime();
	BigInt q = GeneratePrime();
	if (p == q)
		throw new std::exception("p is equal to q");

	BigInt n = p * q;
	BigInt phiN = PhiN(p, q);

	std::cout << "p: " << p << " q: " << q << " n: " << n << " Phi(n): " << phiN << "\n";

	BigInt e = p < q ? GenE(p, phiN) : GenE(q, phiN);

	std::cout << "e: " << e << "\n";

	BigInt d = modInverse(e, phiN);

	std::cout << "d: " << d << "\n";
}

void Encode() {
	printf("Please enter public key (n): ");
	int pIntKey;
	std::cin >> pIntKey;
	BigInt pKey = BigInt(pIntKey);
	printf("Please enter public key (e): ");
	int peIntKey;
	std::cin >> peIntKey;
	BigInt peKey = BigInt(peIntKey);

	printf("Please enter your message: ");
	string message;
	getline(std::cin >> std::ws, message);
	//std::replace(message.begin(), message.end(), ' ', '_');
	printf("Your encrypted message is: \n");
	std::cout << "Size " << sizeof(message) << "o" << "\n";
	std::cout << "- Beginning of the message -" << "\n";
	for (char c : message) {

		
		int AsciiChar = (int)c;
		if (AsciiChar > 0) {
			BigInt el = pow(BigInt(AsciiChar), peKey);
			//std::cout << el << "\n";
			BigInt EncodedLeter = el % pKey;
			std::cout << EncodedLeter << " ";
		}
		
		
	}
	std::cout << "\n" << "- End of the message -" << "\n";
}

void Decode() {
	printf("Please enter private key (n): ");
	int pIntKey;
	std::cin >> pIntKey;
	BigInt pKey = BigInt(pIntKey);
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
		//BigInt dl = pow(EncodedLettre, d);
		if (std::stoi(str) > 0) {
			BigInt dl = pow(BigInt(str), pdIntKey);
			BigInt DecodedLetter = dl % pKey;
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
	

	//BigInt Lettre = BigInt(4);

	//BigInt el = pow(Lettre, e);
	////std::cout << el << "\n";
	//BigInt EncodedLettre = el % n;

	//std::cout << EncodedLettre << "\n";

	//BigInt dl = pow(EncodedLettre, d);
	////std::cout << dl << "\n";
	//BigInt DecodedLetter = dl % n;

	//

	//std::cout << "DecodeSamere: " <<DecodedLetter << "\n";


	//return 0;
}

