#include <stdio.h>
#include "genpat.h"

int tempo = 0;
int clk = 0;
int last_clk = 1;

int a = 0;
int sel0 = 0;
int sel1 = 0;
int cin = 0;

int acc = 0;
int cout = 0;

char *inttostr(inteiro)
int inteiro;
{
    char *str;
    str = (char *) mbkalloc (32 * sizeof(char));
    sprintf(str, "%d", inteiro);
    return(str);
}

int inv4(int x){
    return (~x) & 0xF;
}

/* Modelo comportamental do ADAC_4, espelhando o adac_4.vhdl */
void adac_4(int a, int sel0, int sel1, int cin, int clk){
    int result;

    if (clk == 1 && last_clk == 0){

        if (sel0 == 0 && sel1 == 0){
            /* Instrucao 00: copia A para ACC */
            acc  = a & 0xF;
            cout = 0;
        }
        else if (sel0 == 0 && sel1 == 1){
            /* Instrucao 01: soma A + ACC + Cin */
            result = a + acc + cin;
            acc  = result & 0xF;
            cout = (result >> 4) & 1;
        }
        else if (sel0 == 1 && sel1 == 0){
            /* Instrucao 10: copia NOT(A) para ACC */
            acc  = inv4(a);
            cout = 0;
        }
        else {
            /* Instrucao 11: subtrai A de ACC (ACC <= ACC - A) */
            result = acc - a;
            cout = (acc < a) ? 1 : 0; /* equivalente a result_temp(4) na subtracao de 5 bits */
            acc  = result & 0xF;
        }
    }
}

/* Aplica um estimulo e registra um ciclo completo de clock (0 -> 1) */
void aplicar(int va, int vsel0, int vsel1, int vcin){
    a = va; sel0 = vsel0; sel1 = vsel1; cin = vcin;

    for (clk = 0; clk < 2; clk++){
        adac_4(a, sel0, sel1, cin, clk);

        AFFECT(inttostr(tempo), "clk",  inttostr(clk));
        AFFECT(inttostr(tempo), "a",    inttostr(a));
        AFFECT(inttostr(tempo), "sel0", inttostr(sel0));
        AFFECT(inttostr(tempo), "sel1", inttostr(sel1));
        AFFECT(inttostr(tempo), "cin",  inttostr(cin));
        AFFECT(inttostr(tempo), "s",    inttostr(acc));
        AFFECT(inttostr(tempo), "cout", inttostr(cout));

        tempo++;
        last_clk = clk;
    }
}

main() {

    int i;

    DEF_GENPAT("adac_4");

    DECLAR("vdd",  ":2", "B", IN,  "",           "");
    DECLAR("vss",  ":2", "B", IN,  "",           "");
    DECLAR("clk",  ":2", "B", IN,  "",           "");
    DECLAR("a",    ":2", "X", IN,  "3 downto 0", "");
    DECLAR("sel0", ":2", "B", IN,  "",           "");
    DECLAR("sel1", ":2", "B", IN,  "",           "");
    DECLAR("cin",  ":2", "B", IN,  "",           "");
    DECLAR("s",    ":2", "X", OUT, "3 downto 0", "");
    DECLAR("cout", ":2", "B", OUT, "",           "");

    AFFECT("0", "vdd", "0b1");
    AFFECT("0", "vss", "0b0");

    /* --- SET: zera o acumulador copiando A = 0 --- */
    LABEL("set");
    aplicar(0, 0, 0, 0);

    /* --- COPY (sel0=0, sel1=0): ACC <= A --- */
    LABEL("copy");
    for (i = 0; i < 16; i++)
        aplicar(i, 0, 0, 0);

    /* --- SUM (sel0=0, sel1=1): ACC <= A + ACC + Cin, com Cin = 0 --- */
    LABEL("sum");
    aplicar(0, 0, 0, 0); /* zera ACC antes de somar */
    for (i = 0; i < 16; i++)
        aplicar(i, 0, 1, 0);

    /* --- SUM com Cin = 1 --- */
    LABEL("sum_cin");
    aplicar(0, 0, 0, 0);
    for (i = 0; i < 16; i++)
        aplicar(i, 0, 1, 1);

    /* --- INVERT (sel0=1, sel1=0): ACC <= NOT A --- */
    LABEL("invert");
    for (i = 0; i < 16; i++)
        aplicar(i, 1, 0, 0);

    /* --- SUBTRACT (sel0=1, sel1=1): ACC <= ACC - A --- */
    LABEL("subtract");
    aplicar(15, 0, 0, 0); /* seta ACC = 15 antes de subtrair */
    for (i = 0; i < 16; i++)
        aplicar(i, 1, 1, 0);

    SAV_GENPAT();
    return 0;
}
