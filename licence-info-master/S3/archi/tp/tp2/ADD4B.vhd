LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;

ENTITY add_1b IS
	PORT (	a, b, c IN STD_LOGIC;
		S, R	OUT STD_LOGIC);
END ENTITY add_1b;

ARCHITECTURE add_1b_fd OF add_1b IS
	BEGIN
		S <= a XOR b XOR c;
		R <= 		(a AND b)
		      	OR	(a AND c)
			OR 	(b AND c);
	COMPONENT
	-- ici et non en haut
END ARCHITECTURE add_1b_fd;

