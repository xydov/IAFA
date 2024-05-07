LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.all;
USE IEEE.NUMERIC_STD.ALL;

ENTITY test IS
END ENTITY;

ARCHITECTURE arc OF test IS

	SIGNAL I2, I1, I0, O1, O0 : STD_LOGIC := '0';

BEGIN
	-- test de l'additionneur 1 bit complet
	fddADD1B : ENTITY WORK.ADD1B PORT MAP (I2, I1, I0, O1, O0);

	PROCESS
		TYPE TableDeVerite IS ARRAY(0 TO 7) OF STD_LOGIC_VECTOR(2 DOWNTO 0);
		constant Tdv : TableDeVerite := ("000", "001", "010", "011", "100", "101", "110", "111");
	BEGIN
		FOR I IN Tdv'RANGE LOOP
			I2 <= Tdv(I)(2);
			I1 <= Tdv(I)(1);
			I0 <= Tdv(I)(0);
			WAIT FOR 10 ns;
		END LOOP;
		WAIT;
	END PROCESS;

END ARCHITECTURE;
