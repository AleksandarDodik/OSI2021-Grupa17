#pragma once
#include<iostream>
#include<string>
#include<fstream>
class Artikal
{
private:
	std::string ime, barkod,kolicina, cijena;
	int sedmicna, mjesecna, godisnja;
public:
	Artikal() :ime(""), barkod(""), kolicina(""), cijena(""), sedmicna(0), mjesecna(0), godisnja(0) {};
	void setIme(std::string& ime);
	void setBarkod(std::string& barkod);
	void setKolicina(int kolicina);
	void setCijena(int cijena);
	void setSedmicna(int sedmicna);
	void setMjesecna(int mjesecna);
	void setGodisnja(int godisnja);
	std::string getIme()const;
	std::string getBarkod()const;
	double getKolicina()const;
	double getCijena()const;
	double getSedmicna()const;
	double getMjesecna()const;
	double getGodisnja()const;
	Artikal(std::string& Ime, std::string& Barkod, std::string& Kolicina, std::string& Cijena) :ime(Ime), barkod(Barkod), kolicina(Kolicina), cijena(Cijena),sedmicna(0),mjesecna(0),godisnja(0) {}
	void pregledArtikala();
	void dodavanjeArtikla();
	void obrisiArtikl();
	void brisanjeArtikla();
	void izmjenaIzvjestaja(double);
	void brisanjeKolicineArtikala(double);
	int provjeraArtikla();
	void izvjestaj();
	void izradaIzvjestaja(int);
	void resetovanjeIzvjestaja();
	Artikal& uzmiPodatkeIzBaze(const std::string&);

};

