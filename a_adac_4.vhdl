library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity adac_4 is
port
(
    A    : in std_logic_vector (3 downto 0); -- Entrada A de 4 bits
    sel0 : in std_logic;                     -- Sinal de seleção 0
    sel1 : in std_logic;                     -- Sinal de seleção 1
    Cin  : in std_logic;                     -- Carry In
    clk  : in std_logic;                     -- Clock para o acumulador
    S    : out std_logic_vector (3 downto 0);-- Saída (resultado) de 4 bits
    Cout : out std_logic;                    -- Carry Out (indica overflow)
    Vdd  : in std_logic;                     -- Alimentação
    Vss  : in std_logic                      -- Terra
);
end adac_4;

architecture adac_behavioral of adac_4 is
    -- Sinal interno que representa o registrador Acumulador (ACC)
    signal ACC : unsigned(3 downto 0);
begin
    
    -- O 'process' descreve o comportamento sensível a mudanças de sinais (aqui, o clock)
    process(clk)
        -- Variáveis temporárias de 5 bits para lidar com o carry de saída (overflow)
        variable result_temp : unsigned(4 downto 0);
        variable Cin_temp    : unsigned(4 downto 0);
    begin
        
	if rising_edge(clk) then
            
            -- Prepara o Cin para poder ser somado junto às variáveis de múltiplos bits
            Cin_temp := "00000";
            Cin_temp(0) := Cin;
            
            if sel0 = '0' and sel1 = '0' then
                -- Instrução 0 0: Copia A para ACC
                ACC <= unsigned(A);
                Cout <= '0';
                
            elsif sel0 = '0' and sel1 = '1' then
                -- Instrução 0 1: Soma A com ACC e grava em ACC
                -- O bit extra '0' previne erro de tamanho na soma, permitindo capturar o Cout
                result_temp := ('0' & unsigned(A)) + ('0' & ACC) + Cin_temp;
                ACC <= result_temp(3 downto 0);
                Cout <= result_temp(4);
                
            elsif sel0 = '1' and sel1 = '0' then
                -- Instrução 1 0: Copia ~A (inversor) para ACC
                ACC <= not unsigned(A);
                Cout <= '0';
                
            elsif sel0 = '1' and sel1 = '1' then
                -- Instrução 1 1: Subtrai A de ACC e grava em ACC
                result_temp := ('0' & ACC) - ('0' & unsigned(A));
                ACC <= result_temp(3 downto 0);
                Cout <= result_temp(4);
                
            end if;
        end if;
    end process;

    S <= std_logic_vector(ACC);

end adac_behavioral;
