#pragma once
#include<iostream>
#include<string>
#include<fstream>
static std::string ImeRadnika;
void prijava();
int provjeriNalog(std::string&, std::string&);
void printMeniSef();
void printMeniRadnik();
void promjenaSifre(std::string&, int);
void povecajBrojPrijava(std::string&);
