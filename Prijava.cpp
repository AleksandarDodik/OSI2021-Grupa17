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
void printMeniSef()
{
	int a;
	Artikal art;
	system("cls");
	std::cout << "-----------------------\n";
	std::cout << "1. Pregled artikala\n" << "2. Dodavanje artikla\n" << "3. Brisanje artikla\n" << "4. Izvjestaj o prodaji\n\n" << "5. Kreiranje naloga\n" << "6. Brisanje naloga\n\n" << "7. Odjavi se\n" << "8. Zatvori aplikaciju\n";
	std::cout << "-----------------------\n";
	do {
		std::cout << "Unesite broj: ";
		std::cin.sync();
		std::cin >> a;
		std::cin.get();//Da pokupi enter
	} while (a < 1 || a>8);
	switch (a)
	{
	case 1:
		art.pregledArtikala();
		break;
	case 2:
		art.dodavanjeArtikla();
		break;
	case 3:
		art.obrisiArtikl();
		break;
	case 4:
		art.izvjestaj();
		break;
	case 5:
		Registracija();
		break;
	case 6:
		obrisiNalog();
		break;
	case 7:
		prijava();
		break;
	case 8:
		break;
	}
}

void printMeniRadnik()
{
	int a;
	Racun r;
	system("cls");
	std::cout << "-----------------------\n";
	std::cout << "1. Kreiraj novi racun\n\n" << "2. Odjavi se\n" << "3.Zatvori aplikaciju\n";
	std::cout << "-----------------------\n";
	do {
		std::cout << "Unesite broj: ";
		std::cin.sync();
		std::cin >> a;
		std::cin.get();//Da pokupi enter
	} while (a < 1 || a>3);
	switch (a)
	{
	case 1:
		r.dodavanjeArtikala();
		break;
	case 2:
		prijava();
		break;
	case 3:
		break;
	}
}

void promjenaSifre(std::string& Ime, int tip)
{
	system("cls");
	std::cout << "Promjena sifre za nalog: " << Ime << std::endl;

	std::string novaSifra, ponovljenaSifra;
	do {
		std::cout << "\tNova sifra: ";
		std::getline(std::cin, novaSifra);

		std::cout << "\tPonvoljena nova sifra: ";
		std::getline(std::cin, ponovljenaSifra);
		if (novaSifra.compare(ponovljenaSifra) != 0)
			std::cout << "Sifre su razlicite!\n";
	} while (novaSifra.compare(ponovljenaSifra) != 0);

	brisanjeNaloga(Ime);

	std::ofstream BazaNaloga;
	BazaNaloga.open("nalozi.csv", std::ios::app);
	if (BazaNaloga.is_open())
	{
		BazaNaloga << Ime << ',' << novaSifra << ',' << ((tip == 10) ? 's' : 'r') << ',' << 0 << '\n';
		BazaNaloga.close();
	}


}

void povecajBrojPrijava(std::string& Ime)
{
	std::string _ime, _sifra, _tip, _brojPrijava;
	//Otvaranje Temp za citanje
	std::ifstream BazaNaloga;
	BazaNaloga.open("nalozi.csv");

	if (BazaNaloga.is_open())
	{
		while (!BazaNaloga.eof())
		{
			getline(BazaNaloga, _ime, ',');
			getline(BazaNaloga, _sifra, ',');
			getline(BazaNaloga, _tip, ',');
			getline(BazaNaloga, _brojPrijava);
			if (_ime.compare(Ime) == 0)
				break;
		}
		BazaNaloga.close();
	}

	brisanjeNaloga(_ime);

	std::ofstream Temp;
	Temp.open("nalozi.csv", std::ios::app);
	if (Temp.is_open())
	{
		Temp << _ime << ',' << _sifra << ',' << _tip << ',' << stoi(_brojPrijava) + 1 << '\n';
		Temp.close();
	}

}
