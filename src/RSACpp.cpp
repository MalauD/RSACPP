// RSACpp.cpp : définit le point d'entrée de l'application.
//

#include "RSACpp.h"

using namespace std;
//using namespace Dodecahedron;


void Encode(Rsa::Rsa* RsaClass) {
	printf("Please enter public key (n): ");
	int64_t pKey;
	std::cin >> pKey;
	printf("Please enter public key (e): ");
	int64_t peKey;
	std::cin >> peKey;

	Rsa::RsaKey* rsaKeys = new Rsa::RsaKey(pKey, 0, int64_t(peKey));

	printf("Please enter your message: ");
	string message;
	getline(std::cin >> std::ws, message);
	//std::replace(message.begin(), message.end(), ' ', '_');
	printf("Your encrypted message is: \n");
	std::cout << "Size " << message.length() << "o" << "\n";
	std::cout << "- Beginning of the message -" << "\n";
	std::cout << RsaClass->Encode(message, rsaKeys);
	std::cout << "\n" << "- End of the message -" << "\n";
	delete(rsaKeys);
}

void Decode(Rsa::Rsa* RsaClass) {
	printf("Please enter private key (n): ");
	int64_t pKey;
	std::cin >> pKey;
	printf("Please enter private key (d): ");
	int64_t pdIntKey;
	std::cin >> pdIntKey;
	Rsa::RsaKey* rsaKeys = new Rsa::RsaKey(pKey, int64_t(pdIntKey), 0);

	printf("Please enter the encrypted message: ");
	string message;
	getline(std::cin >> std::ws, message);
	std::cout << "- Beginning of the message -" << "\n";
	std::cout << RsaClass->Decode(message, rsaKeys);
	std::cout << "\n" << "- End of the message -" << "\n";
	delete(rsaKeys);
}
//10 25 3 25 24 9 22 2 18 4 2 26 8 9 8




int main()
{
	Rsa::Rsa* MyRsaClass = new Rsa::Rsa();
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
			printf("Enter speed for the creation of the keys :");
			int s;
			std::cin >> s;
			printf("\n");
			MyRsaClass->CreateKeys(s)->print();
			break;
		case 1:
			Encode(MyRsaClass);
			break;
		case 2:
			Decode(MyRsaClass);
			break;
		default:
			break;
		}
	} while (choice != 3);

	delete(MyRsaClass);
}

