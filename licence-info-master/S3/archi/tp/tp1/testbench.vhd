LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.all;
USE IEEE.NUMERIC_STD.ALL;

ENTITY test IS
END ENTITY;

ARCHITECTURE arc OF test IS

	SIGNAL I2, I1, I0, O3, O2, O1, O0 : STD_LOGIC := '0';

BEGIN
	-- test du circuit TP1_EX1
	--fddTP1EX1 : ENTITY WORK.TP1EX1 PORT MAP (I1, I0, O3, O2, O1, O0);
	--I2 <= '0', '1' AFTER 30 ns;	
	--I1 <= '0', '1' AFTER 20 ns, 'U' AFTER 40 ns, '0' AFTER 50 ns;
	--I0 <= '0', '1' AFTER 10 ns, '0' AFTER 20 ns, '1' AFTER 30 ns, 'U' AFTER 40 ns, '0' AFTER 50 ns;


	-- nouvelle version
	fddTP1EX1 : ENTITY WORK.TP1EX1 PORT MAP (I2, I1, I0, O3, O2, O1, O0);

	PROCESS
		TYPE TableDeVerite IS ARRAY(0 TO 7) OF STD_LOGIC_VECTOR(2 DOWNTO 0);	
		constant Tdv : TableDeVerite :=("000", "001", "010", "011", "100", "101", "110", "111");
	BEGIN
		FOR I IN Tdv'RANGE LOOP
			I2 <= Tdv(I)(2);
			I1 <= Tdv(I)(1);
			I0 <= Tdv(I)(0);
			WAIT FOR 5 ns;
		END LOOP;
		WAIT;
	END PROCESS;
	
END ARCHITECTURE;
