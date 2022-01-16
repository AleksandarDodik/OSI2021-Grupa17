#include "Prijava.h"
#include "Registracija.h"
#include "Artikal.h"
#include "Racun.h"
#include<iostream>
#include<string>
#include<fstream>

int prijava()
{
	system("cls");

	int daLiPostoji = 0, pokusaji = 0;
	std::string ime, sifra;

	std::cout << "\nPRIJAVA:\n";

	while ((daLiPostoji == 0 || daLiPostoji == 5) && pokusaji < 3)
	{
		pokusaji++;

		std::cout << "\tIme: ";
		std::getline(std::cin, ime);

		std::cout << "\tSifra: ";
		std::getline(std::cin, sifra);

		daLiPostoji = provjeriNalog(ime, sifra);
		if ((daLiPostoji == 0 || daLiPostoji == 5) && pokusaji < 3)
			std::cout << "Ponovite unos!\n";
	}
	if (pokusaji >= 3)
		std::cout << "Iskoristili ste sve pokusaje!\n";

	if (daLiPostoji == 1)
	{
		povecajBrojPrijava(ime);
	}

	if (daLiPostoji == 2)
	{
		povecajBrojPrijava(ime);
		ImeRadnika = ime;
	}

	if (daLiPostoji == 10) {
		promjenaSifre(ime, daLiPostoji);
	}

	if (daLiPostoji == 20) {
		promjenaSifre(ime, daLiPostoji);
		ImeRadnika = ime;
	}
	return daLiPostoji;
}

int provjeriNalog(std::string& ime, std::string& sifra)
{
	std::string br;//Broj prijava nakon kog se mijenja sifra, uzima se iz konfiguracije

	std::ifstream Konfig;
	Konfig.open("Konfiguracija.cfg");

	if (Konfig.is_open())
	{
		getline(Konfig, br, ':');
		getline(Konfig, br);
		Konfig.close();
	}

	std::ifstream Baza;
	std::string temp;

	Baza.open("Nalozi.txt");
	if (Baza.is_open())
	{
		while (!Baza.eof())
		{
			std::string _ime, _sifra, _tipNaloga, _brojPrijava;

			std::getline(Baza, _ime, ',');
			std::getline(Baza, _sifra, ',');
			std::getline(Baza, _tipNaloga, ',');
			std::getline(Baza, _brojPrijava);

			if (ime.compare(_ime) == 0 && sifra.compare(_sifra) == 0 && ime.compare("") != 0 && sifra.compare("") != 0)
			{
				Baza.close();
				if (_tipNaloga.compare("s") == 0 && _brojPrijava.compare(br) == 0)
					return 10;
				if (_tipNaloga.compare("r") == 0 && _brojPrijava.compare(br) == 0)
					return 20;
				if (_tipNaloga.compare("s") == 0)
					return 1;
				if (_tipNaloga.compare("r") == 0)
					return 2;
			}
			if (ime.compare(_ime) == 0 && ime.compare("") != 0 && sifra.compare("") != 0)
			{
				Baza.close();
				return 5;
			}
		}
		Baza.close();
	}
	return 0;
}

int printMeniSef()
{
	int tok = 1;
	while (tok == 1)
	{
		system("cls");

		int a = 0;
		Artikal art;

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
			return 1;
			break;
		case 8:
			tok = 0;
			break;
		}
	}
	return 0;
}

int printMeniRadnik()
{
	int tok = 1;
	while (tok == 1)
	{
		system("cls");

		int a;
		Racun r;

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
			r.dodavanjeArtikala(ImeRadnika);
			break;
		case 2:
			return 1;
			break;
		case 3:
			tok = 0;
			break;
		}
	}
	return 0;
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
	BazaNaloga.open("Nalozi.txt", std::ios::app);

	if (BazaNaloga.is_open())
	{
		BazaNaloga << Ime << ',' << novaSifra << ',' << ((tip == 10) ? 's' : 'r') << ',' << 0 << '\n';
		BazaNaloga.close();
	}


}

void povecajBrojPrijava(std::string& Ime)
{
	std::string _ime, _sifra, _tip, _brojPrijava;
	//Pronalazenje naloga u bazi
	std::ifstream BazaNaloga;
	BazaNaloga.open("Nalozi.txt");

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
	//Upis naloga sa novim brojem prijava
	std::ofstream Temp;
	Temp.open("Nalozi.txt", std::ios::app);

	if (Temp.is_open())
	{
		Temp << _ime << ',' << _sifra << ',' << _tip << ',' << stoi(_brojPrijava) + 1 << '\n';
		Temp.close();
	}

}

