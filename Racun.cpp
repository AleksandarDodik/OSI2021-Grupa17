#define _CRT_SECURE_NO_WARNINGS
#include "Racun.h"
#include "Prijava.h"
#include "Artikal.h"
#include <ctime>
Racun::Racun() :naziv(""), barkod(""), kolicina(""), cijenaArtikla(0), cijenaRacuna(0), popust(0) {}
Racun::Racun(std::string& Naziv, std::string& Barkod, std::string& Kolicina, double CijenaArtikla, double CijenaRacuna, double Popust) : naziv(Naziv), barkod(Barkod), kolicina(Kolicina), cijenaArtikla(CijenaArtikla), cijenaRacuna(CijenaRacuna), popust(Popust) {}
void Racun::setNaziv(std::string& naziv)
{
	this->naziv = naziv;
}

void Racun::setBarkod(std::string& barkod)
{
	this->barkod = barkod;
}

void Racun::setKolicina(std::string& kolicina)
{
	this->kolicina = kolicina;
}

void Racun::setCijenaArtikla(double cijena)
{
	this->cijenaArtikla = cijena;
}

void Racun::setCijenaRacuna(double cijena)
{
	this->cijenaRacuna = cijena;
}

void Racun::setPopust(double popust)
{
	this->popust = popust;
}

std::string Racun::getNaziv()
{
	return this->naziv;
}

std::string Racun::getBarkod()
{
	return this->naziv;
}

double Racun::getKolicina()
{
	return atof((this->kolicina).c_str());
}

double Racun::getCijenaArtikla()
{
	return this->cijenaArtikla;
}

double Racun::getCijenaRacuna()
{
	return this->cijenaRacuna;
}

double Racun::getPopust()
{
	return this->popust;
}

void Racun::dodavanjeArtikala(std::string& imeRadnika)
{
	bool tok = true;
	Artikal art;
	std::string naziv, kolicina, popust, uplata;
	system("cls");
	std::cout << "\nKreiranje racuna:\n(Unesite ime ili barkod artikla, za ispis racuna unesite RACUN, za izlaz unesite IZLAZ)\n";
	do
	{
		std::cout << "\tNaziv: ";
		std::cin.sync();
		std::getline(std::cin, naziv);
		art.setIme(naziv);
		art.setBarkod(naziv);//zbog provjere mora biti
		if (art.provjeraArtikla())
		{
			std::cout << "\tKolicina: ";
			std::getline(std::cin, kolicina);
			art.uzmiPodatkeIzBaze(naziv);
			upisiArtikal(art, kolicina);
			art.brisanjeKolicineArtikala(atof(kolicina.c_str()));
			art.izmjenaIzvjestaja(atof(kolicina.c_str()));
			std::cout << "\n";
		}
		else if (naziv.compare("RACUN") == 0 || naziv.compare("IZLAZ") == 0)
			tok = false;
		else
			std::cout << "Ponovite unos!\n";
	} while (tok);
	if (naziv.compare("RACUN") == 0)
	{
		std::cout << "\tPopust:";
		std::getline(std::cin, popust);
		std::cout << "\tUplaceno:";
		std::getline(std::cin, uplata);

		time_t t = time(0);
		tm* tPtr = localtime(&t);

		std::string imeRacuna;
		imeRacuna += "./Racuni/" + std::to_string((tPtr->tm_year) + 1900) + "_" + std::to_string((tPtr->tm_mon) + 1) + "_" + std::to_string(tPtr->tm_mday) + "_" + std::to_string(tPtr->tm_hour) + "_" + std::to_string(tPtr->tm_min) + "_" + std::to_string(tPtr->tm_sec) + ".txt";

		kreiranjeRacuna(imeRacuna, atof((popust).c_str()), atof((uplata).c_str()), imeRadnika);
		ispisRacuna(imeRacuna);
	}
	std::cin.get();//Da pokupi enter
}

void Racun::upisiArtikal(Artikal& art, std::string& kolicina)
{
	std::ofstream Racun;
	Racun.open("Racun.csv", std::ios::app);
	if (Racun.is_open())
	{
		Racun << art.getIme() << ',' << kolicina << ',' << art.getCijena() << ',' << atof((kolicina).c_str()) * art.getCijena() << '\n';
		Racun.close();
	}
}

void Racun::ispisRacuna(std::string& imeRacuna)
{
	system("cls");
	std::string temp;
	std::ifstream Racun;
	Racun.open(imeRacuna);
	if (Racun.is_open())
	{
		while (!Racun.eof())
		{
			getline(Racun, temp);
			std::cout << temp << std::endl;

		}
		Racun.close();
	}

}

void Racun::kreiranjeRacuna(std::string& imeRacuna, double popust, double uplata, std::string& imeRadnika)
{

	std::ofstream Racun;
	Racun.open(imeRacuna, std::ios::trunc);
	std::ifstream Konfig;
	std::string a, b, c;
	int sirina;
	Konfig.open("Konfiguracija.cfg");
	if (Konfig.is_open())
	{
		while (!Konfig.eof())
		{
			getline(Konfig, a);
			if (a.compare("HEDER1:") == 0)
			{
				Racun << "------------------------------------\n";
				do
				{
					getline(Konfig, b);
					if (b.compare("HEDER1:") != 0)
					{
						sirina = (36 - b.size()) / 2 + b.size();
						Racun << std::setw(sirina) << b << '\n';
					}
				} while (b.compare("HEDER1:") != 0);
			}
			if (a.compare("HEDER2:") == 0)
			{
				Racun << '\n';
				do
				{
					getline(Konfig, b);
					if (b.compare("HEDER2:") != 0)
						Racun << b << '\n';
				} while (b.compare("HEDER2:") != 0);
			}
			if (a.compare("HEDER3:") == 0)
			{
				Racun << "------------------------------------\n";
				do
				{
					getline(Konfig, b);
					if (b.compare("HEDER3:") != 0)
					{
						sirina = (36 - b.size()) / 2 + b.size();
						Racun << std::setw(sirina) << b << '\n';
					}
				} while (b.compare("HEDER3:") != 0);
				Racun << "------------------------------------\n";
			}
		}
		Konfig.close();
	}

	std::ifstream RacunBaza;
	RacunBaza.open("Racun.csv");
	std::string ime, kolicina, cijena, ukupno;
	double cijenaBezPdv, Pdv, cijenaSaPdv = 0;
	if (RacunBaza.is_open())
	{
		while (!RacunBaza.eof())
		{
			getline(RacunBaza, ime, ',');
			getline(RacunBaza, kolicina, ',');
			getline(RacunBaza, cijena, ',');
			getline(RacunBaza, ukupno);
			if (ime.compare("") != 0)
			{
				cijenaSaPdv += atof((ukupno).c_str());
				Racun << ime << '\n';
				Racun << std::setw(5) << kolicina << 'x' << std::setw(11) << cijena << std::setw(17) << ukupno << std::setw(2) << 'E' << '\n';
			}
		}
		Racun << "------------------------------------\n";
		RacunBaza.close();
	}
	cijenaBezPdv = cijenaSaPdv / 1.17;
	Pdv = cijenaSaPdv - cijenaBezPdv;
	Racun << "CE: 17,00%" << '\n';
	Racun << "PE:" << std::setw(33) << std::fixed << std::setprecision(2) << Pdv << '\n';
	Racun << "PU:" << std::setw(33) << std::fixed << std::setprecision(2) << Pdv << '\n';
	Racun << "EE:" << std::setw(33) << std::fixed << std::setprecision(2) << cijenaSaPdv << '\n';
	Racun << "EU:" << std::setw(33) << std::fixed << std::setprecision(2) << cijenaSaPdv << '\n';
	Racun << "EB:" << std::setw(33) << std::fixed << std::setprecision(2) << cijenaBezPdv << '\n';
	Racun << "------------------------------------\n";
	Racun << "POPUST:" << std::setw(28) << std::fixed << std::setprecision(2) << popust << '%' << '\n';
	Racun << "ZA UPLATU:" << std::setw(26) << std::fixed << std::setprecision(2) << cijenaSaPdv - (cijenaSaPdv * (popust / 100)) << '\n';
	Racun << "GOTOVINA:" << std::setw(27) << std::fixed << std::setprecision(2) << cijenaSaPdv - (cijenaSaPdv * (popust / 100)) << '\n';
	Racun << "UPLACENO:" << std::setw(27) << std::fixed << std::setprecision(2) << uplata << '\n';
	Racun << "POVRAT:" << std::setw(29) << std::fixed << std::setprecision(2) << uplata - (cijenaSaPdv - (cijenaSaPdv * (popust / 100))) << '\n';
	std::time_t t = std::time(0);
	std::tm* tPtr = std::localtime(&t);
	Racun << std::setfill('0') << std::setw(2) << (tPtr->tm_mday) << '.' << std::setfill('0') << std::setw(2) << (tPtr->tm_mon) + 1 << '.' << (tPtr->tm_year) + 1900 << '-' << std::setfill('0') << std::setw(2) << (tPtr->tm_hour) << ':' << std::setfill('0') << std::setw(2) << (tPtr->tm_min) << '\n';
	Racun << "------------------------------------\n";
	Racun << std::setfill(' ') << std::setw((36 - imeRadnika.size()) / 2 + imeRadnika.size()) << imeRadnika << '\n';
	Racun << "------------------------------------\n";
	std::remove("Racun.csv");
	Racun.close();
}
