#pragma once
#include<iostream>
#include<string>
#include<fstream>
class Artikal
{
private:
	std::string ime, barkod, kolicina, cijena;
	double dnevna, sedmicna, mjesecna, godisnja;
public:
	Artikal() :ime(""), barkod(""), kolicina(""), cijena(""), dnevna(0), sedmicna(0), mjesecna(0), godisnja(0) {};
	void setIme(std::string& ime);
	void setBarkod(std::string& barkod);
	void setKolicina(double kolicina);
	void setCijena(double cijena);
	void setDnevna(double dnevna);
	void setSedmicna(double sedmicna);
	void setMjesecna(double mjesecna);
	void setGodisnja(double godisnja);
	std::string getIme()const;
	std::string getBarkod()const;
	double getKolicina()const;
	double getCijena()const;
	double getDnevna()const;
	double getSedmicna()const;
	double getMjesecna()const;
	double getGodisnja()const;
	Artikal(std::string& Ime, std::string& Barkod, std::string& Kolicina, std::string& Cijena) :ime(Ime), barkod(Barkod), kolicina(Kolicina), cijena(Cijena), dnevna(0), sedmicna(0), mjesecna(0), godisnja(0) {}
	//Ispis podataka o artiklu
	void pregledArtikala();
	void dodavanjeArtikla();
	void obrisiArtikl();
	void brisanjeArtikla();
	void izmjenaIzvjestaja(double);
	void brisanjeKolicineArtikala(double);
	//Ako artikal postoji vraca 1,ako ne vraca 0
	int provjeraArtikla();
	void izvjestaj();
	void izradaIzvjestaja(int);
	void resetovanjeIzvjestaja();
	Artikal& uzmiPodatkeIzBaze(const std::string&);
};

