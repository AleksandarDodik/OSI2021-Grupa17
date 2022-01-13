#define _CRT_SECURE_NO_WARNINGS
#include "Artikal.h"
#include "Prijava.h"

void Artikal::setBarkod(std::string& Barkod)
{
	this->barkod = Barkod;
}

void Artikal::setIme(std::string& Ime)
{
	this->ime = Ime;
}

void Artikal::setCijena(int cijena)
{
	this->cijena = std::to_string(cijena);
}

void Artikal::setKolicina(int kolicina)
{
	this->kolicina = std::to_string(kolicina);
}

void Artikal::setSedmicna(int sedmicna)
{
	this->sedmicna = sedmicna;
}

void Artikal::setMjesecna(int mjesecna)
{
	this->mjesecna = mjesecna;
}

void Artikal::setGodisnja(int godisnja)
{
	this->godisnja = godisnja;
}

std::string Artikal::getBarkod() const
{
	return this->barkod;
}

std::string Artikal::getIme() const
{
	return this->ime;
}

double Artikal::getCijena() const
{
	return atof(this->cijena.c_str());
}

double Artikal::getKolicina()const
{
	return atof(this->kolicina.c_str());
}

double Artikal::getMjesecna() const
{
	return this->mjesecna;
}

double Artikal::getSedmicna() const
{
	return this->sedmicna;
}

double Artikal::getGodisnja() const
{
	return this->godisnja;
}

void Artikal::dodavanjeArtikla()
{
	system("cls");
	std::cout << "\nDodavanje artikla u bazu!(Artikal ako postoji sa istim barkodom dodace se kolicina i postaviti nova cijena)\n";

	std::string ime, barkod, kolicina, cijena;
	std::cout << "\tNaziv: ";
	std::cin.sync();
	std::getline(std::cin, ime);

	std::cout << "\tBarkod: ";
	std::cin.sync();
	std::getline(std::cin, barkod);

	std::cout << "\tKolicina: ";
	std::cin.sync();
	std::getline(std::cin, kolicina);
	
	std::cout << "\tCijena: ";
	std::cin.sync();
	std::getline(std::cin, cijena);

	Artikal novi(ime, barkod, kolicina, cijena);
	Artikal stari;

	int daLiPostoji=novi.provjeraArtikla();

	if (daLiPostoji)
	{
		stari.uzmiPodatkeIzBaze(novi.getIme());
		novi.setKolicina(stari.getKolicina() + novi.getKolicina());
		stari.brisanjeArtikla();
	}

	std::ofstream BazaArtikala;
	BazaArtikala.open("BazaArtikala.csv", std::ios::app);

	if (BazaArtikala.is_open())
	{
		BazaArtikala << novi.getIme() << ',' << novi.getBarkod() << ',' << novi.getCijena() << ',' << novi.getKolicina() << ',' << novi.getSedmicna() << ',' << novi.getMjesecna() << ',' << novi.getGodisnja() << '\n';
		BazaArtikala.close();
	}
	printMeniSef();
}

int Artikal::provjeraArtikla()
{
	std::string _ime, _barkod, _cijena, _kolicina, _sedmicna, _mjesecna, _godisnja;
	std::ifstream BazaArtikala;
	BazaArtikala.open("BazaArtikala.csv");
	if (BazaArtikala.is_open()) 
	{
		while (!BazaArtikala.eof())
		{
			getline(BazaArtikala, _ime, ',');
			getline(BazaArtikala, _barkod, ',');
			getline(BazaArtikala, _cijena, ',');
			getline(BazaArtikala, _kolicina, ',');
			getline(BazaArtikala, _sedmicna, ',');
			getline(BazaArtikala, _mjesecna, ',');
			getline(BazaArtikala, _godisnja);
			if (this->ime.compare(_ime) == 0||this->ime.compare(_barkod)==0)
			{
				BazaArtikala.close();
				return 1;
			}
		}
		BazaArtikala.close();
	}
	return 0;
}

Artikal& Artikal::uzmiPodatkeIzBaze(const std::string& Ime)
{
	std::string _ime, _barkod, _cijena, _kolicina, _sedmicna, _mjesecna, _godisnja;
	std::ifstream BazaArtikala;
	BazaArtikala.open("BazaArtikala.csv");
	if (BazaArtikala.is_open())
	{
		while (!BazaArtikala.eof())
		{
			getline(BazaArtikala, _ime, ',');
			getline(BazaArtikala, _barkod, ',');
			getline(BazaArtikala, _cijena, ',');
			getline(BazaArtikala, _kolicina, ',');
			getline(BazaArtikala, _sedmicna, ',');
			getline(BazaArtikala, _mjesecna, ',');
			getline(BazaArtikala, _godisnja);
			if (_ime.compare(Ime) == 0||_barkod.compare(Ime)==0)
			{
				this->setIme(_ime);
				this->setBarkod(_barkod);
				this->setCijena(atof(_cijena.c_str()));
				this->setKolicina(atof(_kolicina.c_str()));
				this->setSedmicna(atof(_sedmicna.c_str()));
				this->setMjesecna(atof(_mjesecna.c_str()));
				this->setGodisnja(atof(_godisnja.c_str()));
			}
		}
		BazaArtikala.close();
	}
	return *this;
}

void Artikal::brisanjeArtikla()
{
	//Otvaranje baze naloga za citanje
	std::ifstream BazaArtikala;
	BazaArtikala.open("BazaArtikala.csv");

	std::string _ime, _barkod,_cijena,_kolicina,_sedmicna,_mjesecna,_godisnja;

	//Kreiranje nove baze za upis
	std::ofstream Temp;
	Temp.open("BazaArtikalaTemp.csv", std::ios::app);

	if (BazaArtikala.is_open())
	{
		while (!BazaArtikala.eof())
		{
			getline(BazaArtikala, _ime, ',');
			getline(BazaArtikala, _barkod, ',');
			getline(BazaArtikala, _cijena, ',');
			getline(BazaArtikala, _kolicina, ',');
			getline(BazaArtikala, _sedmicna, ',');
			getline(BazaArtikala, _mjesecna, ',');
			getline(BazaArtikala, _godisnja);

			if (this->ime.compare(_ime) != 0 && _ime.compare("") != 0)
			{
				Temp << _ime << ',' << _barkod << ',' << _cijena << ',' << _kolicina << ',' << _sedmicna << ',' << _mjesecna << ',' << _godisnja << '\n';
			}
		}
		BazaArtikala.close();
	}
	Temp.close();

	//Prepisivanje bez obrisanog naloga
	std::remove("BazaArtikala.csv");

	//Otvaranje Temp za citanje
	std::ifstream Temp2;
	Temp2.open("BazaArtikalaTemp.csv");

	//Kreiranje praznog nalozi.csv za upis
	std::ofstream BazaArtikala2;
	BazaArtikala2.open("BazaArtikala.csv", std::ios::app);
	if (Temp2.is_open())
	{
		while (!Temp2.eof())
		{
			getline(Temp2, _ime, ',');
			getline(Temp2, _barkod, ',');
			getline(Temp2, _cijena, ',');
			getline(Temp2, _kolicina, ',');
			getline(Temp2, _sedmicna, ',');
			getline(Temp2, _mjesecna, ',');
			getline(Temp2, _godisnja);
			if (_ime.compare("") != 0)
				BazaArtikala2 << _ime << ',' << _barkod << ',' << _cijena << ',' << _kolicina<<','<<_sedmicna<<','<<_mjesecna<<','<<_godisnja << '\n';
		}
		Temp2.close();
	}
	BazaArtikala2.close();
	std::remove("BazaArtikalaTemp.csv");
}

void Artikal::izvjestaj()
{
	system("cls");
	std::cout << "\nIzvjestaj:\n" << "1. Sedmicni\n" << "2. Mjesecni\n" << "3. Godisnji\n\n" << "4. Izlaz\n";

	int a;
	do{
		std::cout << "\nUnesite broj: ";
		std::cin.sync();
		std::cin >> a;
		std::cin.get();//Da pokupi enter
	} while (a < 1 && a>4);
	switch (a)
	{
	case 1:
		izradaIzvjestaja(1);
		break;
	case 2:
		izradaIzvjestaja(2);
		break;
	case 3:
		izradaIzvjestaja(3);
		break;
	case 4:
		printMeniSef();
	}
}

void Artikal::izradaIzvjestaja(int a)
{
	int i;
		system("cls");
		std::string ime;
		std::cout << "\nIspis izvjestaja:\n";
		std::cout << "\tNaziv:";
		std::cin.sync();
		std::getline(std::cin, ime);
		Artikal temp;
		temp.setIme(ime);
		if (temp.provjeraArtikla())
		{
			temp.uzmiPodatkeIzBaze(ime);
			if (a == 1)
				std::cout << "Sedmicna prodaja za artikal " << temp.getIme() << " je: " << temp.getSedmicna() << std::endl;
			if(a==2)
				std::cout << "Mjesecna prodaja za artikal " << temp.getIme() << " je: " << temp.getMjesecna() << std::endl;
			if(a==3)
				std::cout << "Sedmicna prodaja za artikal " << temp.getIme() << " je: " << temp.getGodisnja() << std::endl;
		}
		else
		{
			std::cout << "\nArtikal ne postoji u bazi!";
		}
		std::cout << "\n\n1. Ispis novog izvjestaja:\n2.Pocetni meni:\n\nUnesite broj: ";
		std::cin.sync();
		std::cin >> i;
		std::cin.get();
		if (i == 1)
			izvjestaj();
	if (i == 2)
		printMeniSef();
}

void Artikal::obrisiArtikl()
{
	system("cls");

	std::string Ime, Kolicina;
	bool ispravnostKolicine, glavnaProvjera = true;

	std::cout << "\nBRISANJE ARTIKLA\n";
	do
	{
		do
		{
			ispravnostKolicine = true;

			std::cin.sync();
			std::cout << "\tNaziv: ";
			std::getline(std::cin, Ime);

			std::cin.sync();
			std::cout << "\tKolicina: ";
			std::getline(std::cin, Kolicina);
			if (atof(Kolicina.c_str())<0)
			{
				ispravnostKolicine = false;
			}

			if (!ispravnostKolicine)
				std::cout << "Pogresna kolicina!\n";

		} while (!ispravnostKolicine);

		std::ifstream BazaArtikala;
		BazaArtikala.open("BazaArtikala.csv");

		std::string _ime, _barkod,_cijena,_kolicina,_sedmicna,_mjesecna,_godisnja;

		if (BazaArtikala.is_open())
		{
			while (!BazaArtikala.eof())
			{
				getline(BazaArtikala, _ime, ',');
				getline(BazaArtikala, _barkod, ',');
				getline(BazaArtikala, _cijena,',');
				getline(BazaArtikala, _kolicina, ',');
				getline(BazaArtikala, _sedmicna, ',');
				getline(BazaArtikala, _mjesecna, ',');
				getline(BazaArtikala, _godisnja);

				if (!Ime.compare(_ime))
				{
					glavnaProvjera = false;
					break;
				}
				else
					glavnaProvjera = true;
			}
		}
		BazaArtikala.close();
		if (glavnaProvjera)
			std::cout << "Artikal se ne nalazi u Bazi!\n";
	} while (glavnaProvjera);

	if (!glavnaProvjera)
	{
		Artikal temp;
		temp.uzmiPodatkeIzBaze(Ime);
		temp.brisanjeArtikla();
		if (temp.getKolicina() > atof(Kolicina.c_str()))
		{
			std::ofstream BazaArtikala2;
			BazaArtikala2.open("BazaArtikala.csv", std::ios::app);
			int n = temp.getKolicina();
			temp.setKolicina(n - atof(Kolicina.c_str()));
			BazaArtikala2 << temp.getIme() << ',' << temp.getBarkod() << ',' << temp.getCijena() << ',' << temp.getKolicina() << ',' << temp.getSedmicna() << ',' << temp.getMjesecna() << ',' << temp.getGodisnja() << '\n';
			BazaArtikala2.close();
		}
	}
	printMeniSef();
}

void Artikal::pregledArtikala()
{
	int i = 1;
	Artikal temp;
	while (i == 1)
	{
		system("cls");
		std::string Ime, _ime="";
		bool provjera = true;
		std::cout << "\nPregled artikla:\n";
		do {
			std::cout << "Unesite ime ili barkod artikla: ";
			std::cin.sync();
			std::getline(std::cin, Ime);
			if (Ime.compare("IZLAZ") == 0)
			{
				provjera = false;
				goto izlaz;
			}
			else
			{

				std::ifstream BazaArtikala;
				BazaArtikala.open("BazaArtikala.csv");

				std::string _barkod, _cijena, _kolicina, _sedmicna, _mjesecna, _godisnja;

				if (BazaArtikala.is_open())
				{
					while (!BazaArtikala.eof())
					{
						getline(BazaArtikala, _ime, ',');
						getline(BazaArtikala, _barkod, ',');
						getline(BazaArtikala, _cijena, ',');
						getline(BazaArtikala, _kolicina, ',');
						getline(BazaArtikala, _sedmicna, ',');
						getline(BazaArtikala, _mjesecna, ',');
						getline(BazaArtikala, _godisnja);

						if (!Ime.compare(_ime) || !Ime.compare(_barkod))
						{
							provjera = false;
							break;
						}
						else
							provjera = true;
					}
				}
				BazaArtikala.close();
				if (provjera)
					std::cout << "Artikal se ne nalazi u Bazi!\n";
			}
		} while (provjera);
		temp.uzmiPodatkeIzBaze(Ime);
		std::cout << "\tNaziv: " << temp.getIme() << "\n\tBarkod: " << temp.getBarkod() << "\n\tCijena: " << temp.getCijena() << "\n\tKolicina: " << temp.getKolicina() << "\n\tVrijednost: " << temp.getCijena() * temp.getKolicina() << std::endl;
		izlaz:
		std::cout << "\n\n1. Novi pregled artikla\n" << "2. Pocetni meni\n";
		std::cout << "\nUnesite broj: ";
		std::cin.sync();
		std::cin >> i;
		std::cin.get();//Da pokupi enter
	}
	if (i == 2)
		printMeniSef();
}

void Artikal::brisanjeKolicineArtikala(double x)
{
	std::ifstream BazaArtikala;
	BazaArtikala.open("BazaArtikala.csv");

	std::string _ime, _barkod, _cijena, _kolicina, _sedmicna, _mjesecna, _godisnja;

	std::ofstream Temp;
	Temp.open("BazaArtikalaTemp.csv", std::ios::app);

	if (BazaArtikala.is_open())
	{
		while (!BazaArtikala.eof())
		{
			getline(BazaArtikala, _ime, ',');
			getline(BazaArtikala, _barkod, ',');
			getline(BazaArtikala, _cijena, ',');
			getline(BazaArtikala, _kolicina, ',');
			getline(BazaArtikala, _sedmicna, ',');
			getline(BazaArtikala, _mjesecna, ',');
			getline(BazaArtikala, _godisnja);

			if (this->ime.compare(_ime) != 0 && _ime.compare("") != 0)
			{
				Temp << _ime << ',' << _barkod << ',' << _cijena << ',' << _kolicina << ',' << _sedmicna << ',' << _mjesecna << ',' << _godisnja << '\n';
			}
			else if (this->ime.compare(_ime) == 0)
			{
				Temp << _ime << ',' << _barkod << ',' << _cijena << ',' << atof(_kolicina.c_str()) - x << ',' << _sedmicna << ',' << _mjesecna << ',' << _godisnja << '\n';
			}
		}
		BazaArtikala.close();
	}
	Temp.close();

	std::remove("BazaArtikala.csv");

	std::ifstream Temp2;
	Temp2.open("BazaArtikalaTemp.csv");

	std::ofstream BazaArtikala2;
	BazaArtikala2.open("BazaArtikala.csv", std::ios::app);
	if (Temp2.is_open())
	{
		while (!Temp2.eof())
		{
			getline(Temp2, _ime, ',');
			getline(Temp2, _barkod, ',');
			getline(Temp2, _cijena, ',');
			getline(Temp2, _kolicina, ',');
			getline(Temp2, _sedmicna, ',');
			getline(Temp2, _mjesecna, ',');
			getline(Temp2, _godisnja);
			if (_ime.compare("") != 0)
				BazaArtikala2 << _ime << ',' << _barkod << ',' << _cijena << ',' << _kolicina << ',' << _sedmicna << ',' << _mjesecna << ',' << _godisnja << '\n';
		}
		Temp2.close();
	}
	BazaArtikala2.close();
	std::remove("BazaArtikalaTemp.csv");
}

void Artikal::izmjenaIzvjestaja(double x)
{
	std::string ime, barkod, cijena, kolicina, sedmicna, mjesecna, godisnja;
	std::ofstream BazaArtikalaTemp;
	BazaArtikalaTemp.open("BazaArtikalaTemp.csv", std::ios::app);
	std::ifstream BazaArtikala;
	BazaArtikala.open("BazaArtikala.csv");
	if (BazaArtikala.is_open())
	{
		while (!BazaArtikala.eof())
		{
			getline(BazaArtikala, ime, ',');
			getline(BazaArtikala, barkod, ',');
			getline(BazaArtikala, cijena, ',');
			getline(BazaArtikala, kolicina, ',');
			getline(BazaArtikala, sedmicna, ',');
			getline(BazaArtikala, mjesecna, ',');
			getline(BazaArtikala, godisnja);
			if (ime.compare("") != 0)
			{
				if (ime.compare("Artikal")==0 || ime.compare(this->ime)!=0)
				{
					BazaArtikalaTemp << ime << ',' << barkod << ',' << cijena << ',' << kolicina << ',' << sedmicna << ',' << mjesecna << ',' << godisnja << '\n';
				}
				else
				{
						BazaArtikalaTemp << ime << ',' << barkod << ',' << cijena << ',' << kolicina << ',' << atof(sedmicna.c_str()) + x << ',' << atof(mjesecna.c_str()) + x << ',' << atof(godisnja.c_str()) + x << '\n';
				}
				}
			}
		BazaArtikala.close();
	}
	BazaArtikalaTemp.close();
	std::remove("BazaArtikala.csv");
	std::ifstream BazaArtikalaTemp2;
	BazaArtikalaTemp2.open("BazaArtikalaTemp.csv");
	std::ofstream BazaArtikala2;
	BazaArtikala2.open("BazaArtikala.csv", std::ios::app);
	if (BazaArtikalaTemp2.is_open())
	{
		while (!BazaArtikalaTemp2.eof())
		{
			getline(BazaArtikalaTemp2, ime, ',');
			getline(BazaArtikalaTemp2, barkod, ',');
			getline(BazaArtikalaTemp2, cijena, ',');
			getline(BazaArtikalaTemp2, kolicina, ',');
			getline(BazaArtikalaTemp2, sedmicna, ',');
			getline(BazaArtikalaTemp2, mjesecna, ',');
			getline(BazaArtikalaTemp2, godisnja);
			if (ime.compare("") != 0)
			{
				BazaArtikala2 << ime << ',' << barkod << ',' << cijena << ',' << kolicina << ',' << sedmicna << ',' << mjesecna << ',' << godisnja << '\n';
			}
		}
		BazaArtikalaTemp2.close();
	}
	BazaArtikala2.close();
	std::remove("BazaArtikalaTemp.csv");
}

void Artikal::resetovanjeIzvjestaja()
{
	int sRazlika = 0, mRazlika = 0, gRazlika = 0;
	std::string sDan, sMjes, sGod, temp;
	std::string mDan, mMjes, mGod;
	std::string gDan, gMjes, gGod;
	std::ifstream Konfig;
	Konfig.open("Konfiguracija.cfg");
	if (Konfig.is_open())
	{
		while (!Konfig.eof())
		{
			getline(Konfig, temp);
			if (temp.compare("IZVJESTAJ:") == 0)
			{
				getline(Konfig, temp, ':');
				getline(Konfig, sDan, '/');
				getline(Konfig, sMjes, '/');
				getline(Konfig, sGod);
				getline(Konfig, temp, ':');
				getline(Konfig, mDan, '/');
				getline(Konfig, mMjes, '/');
				getline(Konfig, mGod);
				getline(Konfig, temp, ':');
				getline(Konfig, gDan, '/');
				getline(Konfig, gMjes, '/');
				getline(Konfig, gGod);
			}
		}
		Konfig.close();
	}
	time_t t = time(0);
	tm* tPtr = localtime(&t);
	sRazlika = (((tPtr->tm_year) + 1900) * 365 + ((tPtr->tm_mon) + 1) * 31 + (tPtr->tm_mday)) - ((std::stoi(sGod.c_str())) * 365 + (std::stoi(sMjes.c_str())) * 31 + std::stoi(sDan.c_str()));
	mRazlika = (((tPtr->tm_year) + 1900) * 365 + ((tPtr->tm_mon) + 1) * 31 + (tPtr->tm_mday)) - ((std::stoi(mGod.c_str())) * 365 + (std::stoi(mMjes.c_str())) * 31 + std::stoi(mDan.c_str()));
	gRazlika = (((tPtr->tm_year) + 1900) * 365 + ((tPtr->tm_mon) + 1) * 31 + (tPtr->tm_mday)) - ((std::stoi(gGod.c_str())) * 365 + (std::stoi(gMjes.c_str())) * 31 + std::stoi(gDan.c_str()));

	std::string ime, barkod, cijena, kolicina, sedmicna, mjesecna, godisnja;
	std::ofstream BazaArtikalaTemp;
	BazaArtikalaTemp.open("BazaArtikalaTemp.csv", std::ios::app);
	std::ifstream BazaArtikala;
	BazaArtikala.open("BazaArtikala.csv");
	if (BazaArtikala.is_open())
	{
		while (!BazaArtikala.eof())
		{
			getline(BazaArtikala, ime, ',');
			getline(BazaArtikala, barkod, ',');
			getline(BazaArtikala, cijena, ',');
			getline(BazaArtikala, kolicina, ',');
			getline(BazaArtikala, sedmicna, ',');
			getline(BazaArtikala, mjesecna, ',');
			getline(BazaArtikala, godisnja);
			if (ime.compare("") != 0)
			{
				if (ime.compare("Artikal") == 0)
				{
					BazaArtikalaTemp << ime << ',' << barkod << ',' << cijena << ',' << kolicina << ',' << sedmicna << ',' << mjesecna << ',' << godisnja << '\n';
				}
				else
				{
					if (sRazlika >= 7 && mRazlika >= 31 && gRazlika >= 365)
						BazaArtikalaTemp << ime << ',' << barkod << ',' << cijena << ',' << kolicina << ',' << '0' << ',' << '0' << ',' << '0' << '\n';
					if (sRazlika >= 7 && mRazlika >= 31 && gRazlika < 365)
						BazaArtikalaTemp << ime << ',' << barkod << ',' << cijena << ',' << kolicina << ',' << '0' << ',' << '0' << ',' << godisnja << '\n';
					if (sRazlika >= 7 && mRazlika < 31 && gRazlika < 365)
						BazaArtikalaTemp << ime << ',' << barkod << ',' << cijena << ',' << kolicina << ',' << '0' << ',' << mjesecna << ',' << godisnja << '\n';
					if (sRazlika < 7)
						BazaArtikalaTemp << ime << ',' << barkod << ',' << cijena << ',' << kolicina << ',' << sedmicna << ',' << mjesecna << ',' << godisnja << '\n';
				}
			}
		}
		BazaArtikala.close();
	}
	BazaArtikalaTemp.close();
	std::remove("BazaArtikala.csv");
	std::ifstream BazaArtikalaTemp2;
	BazaArtikalaTemp2.open("BazaArtikalaTemp.csv");
	std::ofstream BazaArtikala2;
	BazaArtikala2.open("BazaArtikala.csv", std::ios::app);
	if (BazaArtikalaTemp2.is_open())
	{
		while (!BazaArtikalaTemp2.eof())
		{
			getline(BazaArtikalaTemp2, ime, ',');
			getline(BazaArtikalaTemp2, barkod, ',');
			getline(BazaArtikalaTemp2, cijena, ',');
			getline(BazaArtikalaTemp2, kolicina, ',');
			getline(BazaArtikalaTemp2, sedmicna, ',');
			getline(BazaArtikalaTemp2, mjesecna, ',');
			getline(BazaArtikalaTemp2, godisnja);
			if (ime.compare("") != 0)
			{
				BazaArtikala2 << ime << ',' << barkod << ',' << cijena << ',' << kolicina << ',' << sedmicna << ',' << mjesecna << ',' << godisnja << '\n';
			}
		}
		BazaArtikalaTemp2.close();
	}
	BazaArtikala2.close();
	std::remove("BazaArtikalaTemp.csv");

	std::string red1, red2, red3;
	std::ifstream Konfig2;
	Konfig2.open("Konfiguracija.cfg");
	std::ofstream KonfigTemp;
	KonfigTemp.open("KonfiguracijaTemp.cfg", std::ios::app);
	if (Konfig2.is_open())
	{
		while (!Konfig2.eof())
		{
			getline(Konfig2, temp);
			if (temp.compare("") != 0)
			{
				if (temp.compare("IZVJESTAJ:") == 0)
				{
					getline(Konfig2, red1);
					getline(Konfig2, red2);
					getline(Konfig2, red3);
					if (sRazlika >= 7 && mRazlika >= 31 && gRazlika >= 365)
					{
						KonfigTemp << "IZVJESTAJ:" << '\n';
						KonfigTemp << "Poslednji sedmicni reset:" << (tPtr->tm_mday) << '/' << (tPtr->tm_mon) + 1 << '/' << (tPtr->tm_year) + 1900 << '\n';
						KonfigTemp << "Poslednji mjesecni reset:" << (tPtr->tm_mday) << '/' << (tPtr->tm_mon) + 1 << '/' << (tPtr->tm_year) + 1900 << '\n';
						KonfigTemp << "Poslednji godisnji reset:" << (tPtr->tm_mday) << '/' << (tPtr->tm_mon) + 1 << '/' << (tPtr->tm_year) + 1900 << '\n';
					}
					if (sRazlika >= 7 && mRazlika >= 31 && gRazlika < 365)
					{
						KonfigTemp << "IZVJESTAJ:" << '\n';
						KonfigTemp << "Poslednji sedmicni reset:" << (tPtr->tm_mday) << '/' << (tPtr->tm_mon) + 1 << '/' << (tPtr->tm_year) + 1900 << '\n';
						KonfigTemp << "Poslednji mjesecni reset:" << (tPtr->tm_mday) << '/' << (tPtr->tm_mon) + 1 << '/' << (tPtr->tm_year) + 1900 << '\n';
						KonfigTemp << red3;
					}
					if (sRazlika >= 7 && mRazlika < 31 && gRazlika < 365)
					{
						KonfigTemp << "IZVJESTAJ:" << '\n';
						KonfigTemp << "Poslednji sedmicni reset:" << (tPtr->tm_mday) << '/' << (tPtr->tm_mon) + 1 << '/' << (tPtr->tm_year) + 1900 << '\n';
						KonfigTemp << red2 << '\n';
						KonfigTemp << red3 << '\n';
					}
					if (sRazlika < 7)
					{
						KonfigTemp << "IZVJESTAJ:" << '\n';
						KonfigTemp << red1 << '\n';
						KonfigTemp << red2 << '\n';
						KonfigTemp << red3 << '\n';
					}
				}
				else
				{
					KonfigTemp << temp << '\n';
				}
			}
		}
		Konfig2.close();
	}
	KonfigTemp.close();
	std::remove("Konfiguracija.cfg");
	std::ifstream Konfig3;
	Konfig3.open("KonfiguracijaTemp.cfg");
	std::ofstream Konfig4;
	Konfig4.open("Konfiguracija.cfg", std::ios::app);
	if (Konfig3.is_open())
	{
		while (!Konfig3.eof())
		{
			getline(Konfig3, temp);
			if (temp.compare("") != 0)
			{
				Konfig4 << temp << '\n';
			}
		}
		Konfig3.close();
	}
	Konfig4.close();
	std::remove("KonfiguracijaTemp.cfg");
}