#pragma once
#include<string>
#include<iostream>
//Otvara novi prozor za unos podataka za novi nalog
void Registracija();
//Otvara novi prozor za unos imena i sifre od naloga koji treba biti obrisan
void obrisiNalog();
//Brise nalog iz baze sa poslatim imenom
void brisanjeNaloga(std::string&);
