
DROP table Ecurie;
DROP table Circuit;
DROP table Pilote;


-- script de creation des tables de la base F1
CREATE TABLE PILOTE( 
nuPilote number(5) constraint pk_pilote Primary key, 
nomPilote varchar2(20), 
prenomPilote varchar2(20),
nationalite varchar2(20)
);

CREATE TABLE CIRCUIT (
nuCi number(5) constraint pk_circuit primary key,
nomCi varchar2(20),
paysCi varchar2(20)
);


create table Ecurie (
nuEcurie number(5) constraint pk_ecurie Primary key,
nomEcurie varchar2(20)
);


INSERT INTO PILOTE VALUES (1, 'HAMILTON','Lewis', 'Royaume-Uni');    
INSERT INTO PILOTE VALUES (2, 'MASSA', 'Felipe', 'Bresil');
INSERT INTO PILOTE VALUES (3, 'RAIKKONEN','Kimi', 'Finlande');
INSERT INTO PILOTE VALUES (4, 'KUBICA', 'Robert', 'Pologne');
INSERT INTO PILOTE VALUES (5, 'SCHUMACHER', 'Mickael', 'Allemagne');
INSERT INTO PILOTE VALUES (6, 'ALONSO','Fernando', 'Espagne'); 
INSERT INTO PILOTE VALUES (7, 'FISICHELLA', 'Giancarlo','Italie');

INSERT INTO CIRCUIT values (1, 'Silverstone','Grande-Bretagne');
INSERT INTO CIRCUIT values (2, 'Gilles-Villeneuve','Canada');
INSERT INTO CIRCUIT values (3, 'Shangai','Chine');

INSERT INTO ECURIE values (1, 'Ferrari');
INSERT INTO ECURIE values (2, 'McLarenMercedes');
INSERT INTO ECURIE values (3, 'Renault');
INSERT INTO ECURIE values (4, 'WilliamsBMW');
INSERT INTO ECURIE values (5, 'Force India');




commit;
