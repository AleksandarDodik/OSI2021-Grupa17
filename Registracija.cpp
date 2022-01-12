#include "Registracija.h"
#include "Prijava.h"
#include<iostream>
#include<string>
#include<fstream>

void Registracija()
{
	system("cls");

	std::string Ime, Sifra1, Sifra2, Tip;
	bool ispravnostImena, ispravnostSifre, ispravnostTipa = false, glavnaProvjera = true;

	std::cout << "\nREGISTRACIJA:\n\n";
	std::cout << "Unesite ime i sifru duzu od 4 karaktera!\n";
	do
	{
		do
		{
			ispravnostImena = true;
			ispravnostSifre = true;

			std::cin.sync();
			std::cout << "\tKorisnicko ime: ";
			std::getline(std::cin, Ime);
			if (Ime.length() < 4)
				ispravnostImena = false;

			std::cin.sync();
			std::cout << "\tSifra: ";
			std::getline(std::cin, Sifra1);
			if (Sifra1.length() < 4)
				ispravnostSifre = false;

			std::cin.sync();
			std::cout << "\tPonovljena sifra: ";
			std::getline(std::cin, Sifra2);
			if (Sifra1.compare(Sifra2) != 0)
			{
				ispravnostSifre = false;
			}

			std::cin.sync();
			std::cout << "\tTip naloga[s|r]: ";
			std::getline(std::cin, Tip);
			if (Tip.compare("s") == 0 || Tip.compare("S") == 0 || Tip.compare("r") == 0 || Tip.compare("R") == 0)
				ispravnostTipa = true;

			if (!ispravnostImena)
				std::cout << "Prekratko ime!\n";
			if (!ispravnostSifre)
				std::cout << "Pogresna sifra!\n";
			if (!ispravnostTipa)
				std::cout << "Pogresan tip naloga!\n";

		} while (!ispravnostImena || !ispravnostSifre || !ispravnostTipa);

		std::ifstream BazaNaloga;
		BazaNaloga.open("nalozi.csv");

		std::string _ime, _sifra, _tip;

		if (BazaNaloga.is_open())
		{
			while (!BazaNaloga.eof())
			{
				getline(BazaNaloga, _ime, ',');
				getline(BazaNaloga, _sifra, ',');
				getline(BazaNaloga, _tip);

				if (!Ime.compare(_ime))
				{
					std::cout << "\nNalog vec postoji!\n";
					glavnaProvjera = false;
					break;
				}
				else
					glavnaProvjera = true;
			}
		}
		BazaNaloga.close();
	} while (!glavnaProvjera);

	std::ofstream BazaNaloga;
	BazaNaloga.open("nalozi.csv", std::ios::app);

	if (glavnaProvjera)
	{
		BazaNaloga << Ime << ',' << Sifra1 << ',' << Tip << ',' << '0' << '\n';
	}
	BazaNaloga.close();

	std::string _ime, _sifra, _tip, _brPrijava;
	std::ifstream Baza;
	Baza.open("nalozi.csv");
	if (Baza.is_open())
	{
		while (!Baza.eof())
		{
			getline(Baza, _ime, ',');
			getline(Baza, _sifra, ',');
			getline(Baza, _tip, ',');
			getline(Baza, _brPrijava);
			if (_ime.compare("admin") == 0 && Tip.compare("s") == 0)
			{
				Baza.close();
				brisanjeNaloga(_ime);
			}
		}
		Baza.close();
	}
	printMeniSef();

}

void obrisiNalog() {
	system("cls");

	std::string Ime, Sifra1, Sifra2, Tip;
	bool ispravnostImena, ispravnostSifre, glavnaProvjera = true;

	std::cout << "\nBRISANJE NALOGA\n";
	do
	{
		do
		{
			ispravnostImena = true;
			ispravnostSifre = true;

			std::cin.sync();
			std::cout << "\tKorisnicko ime: ";
			std::getline(std::cin, Ime);
			if (Ime.length() < 4)
				ispravnostImena = false;

			std::cin.sync();
			std::cout << "\tSifra: ";
			std::getline(std::cin, Sifra1);
			if (Sifra1.length() < 4)
				ispravnostSifre = false;

			std::cin.sync();
			std::cout << "\tPonovljena sifra: ";
			std::getline(std::cin, Sifra2);
			if (Sifra1.compare(Sifra2) != 0)
			{
				ispravnostSifre = false;
			}

			if (!ispravnostImena)
				std::cout << "Pogresno ime!\n";
			if (!ispravnostSifre)
				std::cout << "Pogresna sifra!\n";

		} while (!ispravnostImena || !ispravnostSifre);

		std::ifstream BazaNaloga;
		BazaNaloga.open("nalozi.csv");

		std::string _ime, _sifra, _tip, _brojPrijava;

		if (BazaNaloga.is_open())
		{
			while (!BazaNaloga.eof())
			{
				getline(BazaNaloga, _ime, ',');
				getline(BazaNaloga, _sifra, ',');
				getline(BazaNaloga, _tip, ',');
				getline(BazaNaloga, _brojPrijava);

				if (!Ime.compare(_ime) && !Sifra1.compare(_sifra))
				{
					glavnaProvjera = false;
					break;
				}
				else
					glavnaProvjera = true;
			}
		}
		BazaNaloga.close();
		if (glavnaProvjera)
			std::cout << "Nalog se ne nalazi u Bazi!\n";
	} while (glavnaProvjera);

	if (!glavnaProvjera)
	{
		brisanjeNaloga(Ime);
	}
	printMeniSef();
}

void brisanjeNaloga(std::string& Ime)
{
	//Otvaranje baze naloga za citanje
	std::ifstream BazaNaloga;
	BazaNaloga.open("nalozi.csv");

	std::string _ime, _sifra, _tip, _brojPrijava;

	//Kreiranje nove baze za upis
	std::ofstream Temp;
	Temp.open("NaloziTemp.csv", std::ios::app);

	if (BazaNaloga.is_open())
	{
		while (!BazaNaloga.eof())
		{
			getline(BazaNaloga, _ime, ',');
			getline(BazaNaloga, _sifra, ',');
			getline(BazaNaloga, _tip, ',');
			getline(BazaNaloga, _brojPrijava);

			if (Ime.compare(_ime) != 0 && _ime.compare("") != 0)
			{
				Temp << _ime << ',' << _sifra << ',' << _tip << ',' << _brojPrijava << '\n';
			}
		}
		BazaNaloga.close();
	}
	Temp.close();

	//Prepisivanje bez obrisanog naloga
	std::remove("nalozi.csv");

	//Otvaranje Temp za citanje
	std::ifstream Temp2;
	Temp2.open("NaloziTemp.csv");

	//Kreiranje praznog nalozi.csv za upis
	std::ofstream BazaNaloga2;
	BazaNaloga2.open("nalozi.csv", std::ios::app);
	if (Temp2.is_open())
	{
		while (!Temp2.eof())
		{
			getline(Temp2, _ime, ',');
			getline(Temp2, _sifra, ',');
			getline(Temp2, _tip, ',');
			getline(Temp2, _brojPrijava);
			if (_ime.compare("") != 0)
				BazaNaloga2 << _ime << ',' << _sifra << ',' << _tip << ',' << _brojPrijava << '\n';
		}
		BazaNaloga2.close();
	}
	Temp2.close();
	std::remove("NaloziTemp.csv");

}