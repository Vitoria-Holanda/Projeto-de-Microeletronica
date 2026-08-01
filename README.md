# Projeto-de-Microeletronica

Projeto final do curso de Introdução à Microeletrônica.

O projeto consiste em um ADAC (adicionador - inversor - acumulador controlável) de 4 bits.

## Roteiro de síntese

Usando vhdl para descrever o comportamento do ADAC em alto nível geramos manualmente o arquivo: 
`adac_4.vhdl`

Usando a ferramenta "vasy" geramos o arquivo de vhdl comportamental da Alliance (.vbe):
`vasy -V -I vhdl -a adac_4`

Usando genpat para fazer o teste do circuito geramos manualmente o arquivo:
`adac_4.c`

Usando a ferramenta "alliance-genpat" geramos o arquivo (adac_4.pat):
`alliance-genpat -v adac_4`

Para visualização do padrão gerado em adac_4.pat, usamos:
`xpat -l adac_4`

Usando a ferramenta Asimut para simular o circuito comportamental (.vbe), sem atraso, geramos o arquivo (adac_4_res):
`asimut -b -zd adac_4 adac_4 adac_4_res`

Para visualização do resultado gerado pelo Asimut, usamos:
`xpat -l adac_4_res`
