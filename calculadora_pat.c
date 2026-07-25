#include <stdio.h>
#include "genpat.h"

int main (){
	DEF_GENPAT("calculadora");
	
	DECLAR("clk",	":2", "B", "IN", " ", "");
	DECLAR("sel0",	":2", "B", "IN", " ", "");
	DELCAR("sel1",	":2", "B", "IN", " ", "");
	DECLAR("a",	":2", "X", "IN", "3 downto 0", "");

	DECLAR("s",	":2", "X", "OUT",  "3 downto 0", "");
	DECLAR("cout",	":2", "B", "OUT",  " ", "");

	A_SAV();
	
	A_SAV();
	A_SAV();
	A_SAV();

	A_SAV();
	A_SAV();
	A_SAV();

	A_SAV();
	A_SAV();
	A_SAV();

	A_SAV();
	A_SAV();
	A_SAV();

	SAV_GENPAT();
	return 0;
}

