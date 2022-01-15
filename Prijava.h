#pragma once
#include<iostream>
#include<string>
#include<fstream>
static std::string ImeRadnika;
//Unos podataka, vraca -1 za neuspjesnu prijavu,1 prijavljen kao sef,2 prijavljen kao radnik,10 sef kome treba promijeniti sifru,20 radnik kome treba promijeniti sifru
int prijava();
//Provjerava da li postoji nalog u bazi, ako ne postoji nalog vraca 0, ako je sef 1 a ako je radnik 2, ako sef mora promjeniti sifru 10, ako radnik mora promjeniti sifru 20
int provjeriNalog(std::string&, std::string&);
//Ispis pocetnog menia za sefa, vraca 1 ako se treba odjaviti
int printMeniSef();
//Ispis pocetnog menia za radnika, vraca 1 ako se treba odjaviti
int printMeniRadnik();
//Promjena sifre naloga
void promjenaSifre(std::string&, int);
//Povecavanje broja prijava naloga
void povecajBrojPrijava(std::string&);
