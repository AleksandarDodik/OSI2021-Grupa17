#include "Prijava.h"
#include "Artikal.h"
#include<iostream>
#include<string>
#include<fstream>
void prijava()
{
	system("cls");
	int daLiPostoji = -1, pokusaji = 0;
	std::string ime, sifra;
	std::cout << "\nPRIJAVA:\n";

	while (daLiPostoji == -1 && pokusaji < 3)
	{
		pokusaji++;

		std::cout << "\tIme: ";
		std::getline(std::cin, ime);

		std::cout << "\tSifra: ";
		std::getline(std::cin, sifra);

		daLiPostoji = provjeriNalog(ime, sifra);
		if (daLiPostoji == -1)
			std::cout << "Ponovite unos!\n";
	}
	if (pokusaji >= 3)
		std::cout << "Iskoristili ste sve pokusaje!\n";

	if (daLiPostoji == 1)
	{
		povecajBrojPrijava(ime);
		printMeniSef();
	}

	if (daLiPostoji == 2)
	{
		povecajBrojPrijava(ime);
		printMeniRadnik();
	}

	if (daLiPostoji == 10) {
		promjenaSifre(ime, daLiPostoji);
		printMeniSef();
	}

	if (daLiPostoji == 20) {
		promjenaSifre(ime, daLiPostoji);
		printMeniRadnik();
	}
}

//Ako ne postoji nalog vraca 0, ako je sef 1 a ako je radnik 2, ako sef mora promjeniti sifru 10, ako radnik mora promjeniti sifru 20
int provjeriNalog(std::string& ime, std::string& sifra)
{
	std::ifstream Baza;
	std::string temp;

	Baza.open("nalozi.csv");

	while (Baza.good())
	{
		std::string _ime, _sifra, _tipNaloga, _brojPrijava;

		std::getline(Baza, _ime, ',');
		std::getline(Baza, _sifra, ',');
		std::getline(Baza, _tipNaloga, ',');
		std::getline(Baza, _brojPrijava);

		if (ime.compare(_ime) == 0 && sifra.compare(_sifra) == 0 && ime.compare("") != 0 && sifra.compare("") != 0)
		{
			Baza.close();
			if (_tipNaloga.compare("s") == 0 && _brojPrijava.compare("10") == 0)
				return 10;
			if (_tipNaloga.compare("r") == 0 && _brojPrijava.compare("10") == 0)
				return 20;
			if (_tipNaloga.compare("s") == 0)
				return 1;
			if (_tipNaloga.compare("r") == 0)
				return 2;
		}
	}
	Baza.close();
	return -1;

}