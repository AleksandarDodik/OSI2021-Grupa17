#pragma once
#include<iostream>
#include<stdlib.h>
#include<string>
#include<iomanip>
#include"Artikal.h"
class Racun
{
private:
	std::string naziv, barkod, kolicina;
	double cijenaArtikla, cijenaRacuna, popust;
public:

	Racun();
	Racun(std::string&, std::string&, std::string&, double, double, double);
	void setNaziv(std::string&);
	void setBarkod(std::string&);
	void setKolicina(std::string&);
	void setCijenaArtikla(double);
	void setCijenaRacuna(double);
	void setPopust(double);
	std::string getNaziv();
	std::string getBarkod();
	double getKolicina();
	double getCijenaArtikla();
	double getCijenaRacuna();
	double getPopust();
	void dodavanjeArtikala(std::string&);
	void upisiArtikal(Artikal&, std::string&);
	void kreiranjeRacuna(std::string&, double, double, std::string&);
	void ispisRacuna(std::string&);
};

