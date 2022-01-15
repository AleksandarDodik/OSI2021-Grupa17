#include "Prijava.h"
#include "Registracija.h"
#include "Racun.h"
#include "Artikal.h"
int main()
{
	int prijavljivanje, tok = 1;
	Artikal art;
	art.resetovanjeIzvjestaja();
	while (tok == 1)
	{
		tok = 0;
		prijavljivanje = prijava();
		if (prijavljivanje != -1)
		{
			if (prijavljivanje == 1 || prijavljivanje == 10)
				tok = printMeniSef();
			if (prijavljivanje == 2 || prijavljivanje == 20)
				tok = printMeniRadnik();
		}
	}
	system("PAUSE");
	return 0;
}