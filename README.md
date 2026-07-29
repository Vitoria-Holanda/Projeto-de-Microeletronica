# Projeto-de-Microeletronica

Projeto final do curso de Introdução à Microeletrônica.

O projeto consiste em um ADAC (adicionador - inversor - acumulador controlável) de 4 bits.

## Roteiro de síntese

Usando vhdl para descrever o comportamento do ADAC em alto nível geramos manualmente o arquivo: 
`adac_4.vhdl`

Usando a ferramenta "vasy" geramos o arquivo de vhdl comportamental da Alliance (.vbe):
`vasy -V -I vhdl -a adac_4`
