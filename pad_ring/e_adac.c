#include <genlib.h>
#define POWER "vdde","vdd","vsse","vss", NULL

int main(void){
    int i;
    
    GENLIB_DEF_LOFIG("f_adac_chip");

    GENLIB_LOCON("a[3:0]", IN, "a[3:0]"); 
    GENLIB_LOCON("s[3:0]", OUT, "s[3:0]");
    GENLIB_LOCON("sel0", IN, "sel0");
    GENLIB_LOCON("sel1", IN, "sel1");
    GENLIB_LOCON("cin", IN, "cin");
    GENLIB_LOCON("cout", OUT, "cout");
    GENLIB_LOCON("clk", IN, "clk");
    
    GENLIB_LOCON("vdd", IN, "vdd"); 
    GENLIB_LOCON("vss", IN, "vss");
    GENLIB_LOCON("vdde", IN, "vdde"); 
    GENLIB_LOCON("vsse", IN, "vsse");

    // 1. Núcleo (agora recebe o cki de forma isolada)
    GENLIB_LOINSE("a_adac_core", "core",
        "vdd => vdd",
        "vss => vss",
        "a[3:0] => ai[3:0]",
        "sel0 => sel0i",
        "sel1 => sel1i",
        "cin => cini",
        "clk => cki", // Vai direto e unicamente para o p_ck
        "s[3:0] => si[3:0]",
        "cout => couti", 
        NULL);

    // 2. Pads de dados e controle (agora usam ck_ring na lateral)
    for(i=0; i<4; i++){
        GENLIB_LOINS("pi_sp", GENLIB_NAME("p_a%d",i), GENLIB_ELM("a",i), GENLIB_ELM("ai",i), "ck_ring", POWER);
        GENLIB_LOINS("po_sp", GENLIB_NAME("p_s%d",i), GENLIB_ELM("si",i), GENLIB_ELM("s",i), "ck_ring", POWER);
    }

    GENLIB_LOINS("pi_sp", "p_sel0", "sel0", "sel0i", "ck_ring", POWER);
    GENLIB_LOINS("pi_sp", "p_sel1", "sel1", "sel1i", "ck_ring", POWER);
    GENLIB_LOINS("pi_sp", "p_cin", "cin", "cini", "ck_ring", POWER);
    GENLIB_LOINS("po_sp", "p_cout", "couti", "cout", "ck_ring", POWER);

    // 3. O Pad de Clock (substituído por pi_sp para injetar cki no núcleo e encostar no ck_ring)
    GENLIB_LOINS("pi_sp", "p_ck", "clk", "cki", "ck_ring", POWER);

    // 4. Pads de Alimentação (também atualizados para o ck_ring)
    GENLIB_LOINS("pvddick_sp", "p_vddick0", "ckc", "ck_ring", POWER);
    GENLIB_LOINS("pvssick_sp", "p_vssick0", "ckc", "ck_ring", POWER);
    GENLIB_LOINS("pvddeck_sp", "p_vddeck0", "ckc", "ck_ring", POWER);
    GENLIB_LOINS("pvsseck_sp", "p_vsseck0", "ckc", "ck_ring", POWER);

    GENLIB_SAVE_LOFIG();
    return 0;
}
