# Projeto-de-Microeletronica

Projeto final do curso de Introdução à Microeletrônica.

O projeto consiste em um ADAC (adicionador - inversor - acumulador controlável) de 4 bits.

## Roteiro de síntese

1. Usando vhdl para descrever o comportamento do ADAC em alto nível geramos manualmente o arquivo: 
`a_adac_4.vhdl`

2. Usando a ferramenta "vasy" geramos o arquivo de vhdl comportamental da Alliance (.vbe):
`vasy -a -I vhdl a_adac_4 b_adac_4_vasy`

3. Usando genpat para fazer o teste do circuito geramos manualmente o arquivo:
`c_adac_4.c`

4. Usando a ferramenta "alliance-genpat" geramos (d_adac_4.pat):
`alliance-genpat -v c_adac_4`

5. Para visualização do padrão gerado em d_adac_4.pat, usamos:
`xpat -l d_adac_4`

6. Usando a ferramenta Asimut para simular o circuito comportamental (.vbe), sem atraso, geramos o arquivo (e_adac_4_res):
`asimut -b -zd b_adac_4_vasy d_adac_4 e_adac_4_res`

7. Para visualização do resultado gerado pelo Asimut, usamos:
`xpat -l e_adac_4_res`

8. Com o boom fazemos a otimização booleana:
`boom -A -d 100 b_adac_4_vasy f_adac_4_boom`

9. Com o proof comprovamos que o novo arquivo (.vbe) é equivalente ao primeiro:
`proof -a -d b_adac_4_vasy f_adac_4_boom`

10. Usando boog geramos o arquivo (.vst) que contém as células da biblioteca sxlib 
`boog -m 2 f_adac_4_boom g_adac_4_boog`

11. Podemos visualizar o circuito usando o xsch:
`xsch -l g_adac_4_boog`

Também podemos gerar um .vst com o boog do arquivo b_adac_4_vasy.vbe para comparar antes e depois de otimizar.

12. Geramos um novo arquivo .c contendo definição de atrasos:
`h_adac_4_delay.c`

13. Geramos um novo arquivo (.pat)
`alliance_genpat -v h_adac_4_delay`

14. Assim, usamos o asimut para realizar o teste do circuito otimizado e com atrasos:
`asimut g_adac_4_boog i_adac_4_delay j_adac_4_delay_res`

15. Para visualização:
`xpat -l j_adac_4_delay_res`

16. Geramos o layout físico usando o alliance-ocp:
`alliance-ocp g_adac_4_boog k_adac_4_layout`

17. Utilizamos nero para fazer o roteamento:
`nero -p k_adac_4_layout g_adac_4_boog l_adac_4_nero`

18. Podemos visualizar o resultado com o graal:
`graal -l l_adac_4_nero`


