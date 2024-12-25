drop table write;
drop table author;
drop table inproceedings;
drop table proceedings;
drop table article;
drop table publication;



create table publication(
	key varchar2(50) constraint pk_publication primary key,
	title varchar2(100)
	);


create table article (
	key varchar2(50) constraint pk_article primary key,
	journal varchar2(50),
  year number(4),
	volume number(2),
	numb number(3),
	pages varchar2(10),
	constraint fk_article_publication foreign key(key) references publication(key)
);



create table proceedings (
	keyproc varchar2(50) constraint pk_proceedings primary key,
	title varchar2(150),
	location varchar2(50),
	datep varchar2(30),
	publisher varchar2(40),
	year number(4)
);

create table inproceedings (
	key varchar2(50) constraint pk_inproceedings primary key,
	crossref varchar2(50) constraint fk_inproceedings_proceedings references proceedings(keyproc),
	constraint fk_inproceedings_publication foreign key(key) references publication(key)
	);
	
create table author(
	idAuthor number constraint pk_author primary key,
	name varchar2(40)

);

create table write(
	idAuthor number constraint fk_write_author references author(idAuthor),
	key varchar2(250) constraint fk_write_publication references publication(key),
	constraint pk_write primary key (idAuthor, key)
	);
	

begin transaction;

insert into publication values ('journals-ir-BlankeL11','Specificity aboutness in XML retrieval.');
insert into publication values ('journals-sigir-JaimesLV11','First international workshop on social media engagement (SoME 2011).');
insert into publication values ('journals-ir-WeerkampBR11','Blog feed search with a post index.');
insert into publication values ('journals-sigir-BoscarinoHJMRW11','DIR 2011: the eleventh Dutch-Belgian information retrieval workshop.');
insert into publication values ('conf-iir-CaputoPL11','A Query Algebra for Quantum Information Retrieval.');	
insert into publication values ('conf-iir-BuccioNMO11','Quantum Contextual Information Access and Retrieval.');
insert into publication values ('conf-iir-ZucconAG11','Investigating Subspace Distances in Semantic Spaces.');
insert into publication values ('conf-ercimdl-BronHR11','Linking Archives Using Document Enrichment and Term Selection.');
insert into publication values ('conf-ercimdl-HubertCSP11','Query Operators Shown Beneficial for Improving Search Results.');	
insert into publication values ('conf-airs-SushmitaPL10','Dynamics of Genre and Domain Intents.');
insert into publication values ('conf-cikm-SushmitaJLV10','Factors affecting click-through behavior in aggregated search interfaces.');
insert into publication values ('conf-cikm-ZaragozaCB10','Web search solved?: all result rankings the same?');
insert into publication values ('conf-cikm-CoffmanW10','A framework for evaluating database keyword search strategies.');
insert into publication values ('conf-ecai-CumminsLO10','Learning Aggregation Functions for Expert Search.');
insert into publication values ('conf-ecai-ChangHL10','Designing a Successful Adaptive Agent for TAC Ad Auction.');
insert into publication values ('conf-ecai-PradaCN10','Introducing Personality into Team Dynamics.');
insert into publication values ('conf-sigir-DiazLS10','From federated to aggregated search.');
insert into publication values ('conf-sigir-CarmelY10','Estimating the query difficulty for information retrieval.');
insert into publication values ('conf-sigir-MeijR10','Supervised query modeling using wikipedia.');
insert into publication values ('conf-sigir-OstergrenYE10','The value of visual elements in web search.');


insert into article values ('journals-ir-BlankeL11','Inf. Retr.',  2011, 14,  1, '68-88');
insert into article values ('journals-sigir-JaimesLV11','SIGIR Forum',  2011, 45,  1, '56-62');
insert into article values ('journals-ir-WeerkampBR11','Inf. Retr.',  2011, 14,  5, '515-545');
insert into article values ('journals-sigir-BoscarinoHJMRW11','SIGIR Forum',  2011, 45,  1, '42-44');


insert into proceedings values ('conf-iir-2011','Proceedings of the 2nd Italian Information Retrieval (IIR) Workshop, ','Milan, Italy',' January 27-28, 2011','CEUR-WS.org', 2011);
insert into proceedings values ('conf-ercimdl-2011','Research and Advanced Technology for Digital Libraries - International Conference on Theory and Practice of Digital Libraries, TPDL 2011, ','Berlin, Germany','September 26-28, 2011','Springer', 2011);
insert into proceedings values ('conf-ercimdl-2010','Research and Advanced Technology for Digital Libraries, 14th European Conference, ECDL 2010, ','Glasgow, UK','September 6-10, 2010','Springer', 2010);
insert into proceedings values ('conf-airs-2010','Information Retrieval Technology - 6th Asia Information Retrieval Societies Conference, AIRS 2010, Taipei, Taiwan, December 1-3, 2010. Proceedings','','','Springer', 2010);
insert into proceedings values ('conf-cikm-2010','Proceedings of the 19th ACM Conference on Information and Knowledge Management, CIKM 2010, ','Toronto, Ontario, Canada','October 26-30, 2010','ACM', 2010);
insert into proceedings values ('conf-ecai-2010','ECAI 2010 - 19th European Conference on Artificial Intelligence, ','Lisbon, Portugal','August 16-20, 2010','IOS Press', 2010);
insert into proceedings values ('conf-sigir-2010','Proceeding of the 33rd International ACM SIGIR Conference on Research and Development in Information Retrieval, SIGIR 2010, ','Geneva, Switzerland','July 19-23, 2010','ACM', 2010);


insert into inproceedings values ('conf-iir-CaputoPL11','conf-iir-2011');
insert into inproceedings values ('conf-iir-BuccioNMO11','conf-iir-2011');
insert into inproceedings values ('conf-iir-ZucconAG11','conf-iir-2011');
insert into inproceedings values ('conf-ercimdl-BronHR11','conf-ercimdl-2011');
insert into inproceedings values ('conf-ercimdl-HubertCSP11','conf-ercimdl-2011');
insert into inproceedings values ('conf-airs-SushmitaPL10','conf-airs-2010');
insert into inproceedings values ('conf-cikm-SushmitaJLV10','conf-cikm-2010');
insert into inproceedings values ('conf-cikm-ZaragozaCB10','conf-cikm-2010');
insert into inproceedings values ('conf-cikm-CoffmanW10','conf-cikm-2010');
insert into inproceedings values ('conf-ecai-CumminsLO10','conf-ecai-2010');
insert into inproceedings values ('conf-ecai-ChangHL10','conf-ecai-2010');
insert into inproceedings values ('conf-ecai-PradaCN10','conf-ecai-2010');
insert into inproceedings values ('conf-sigir-DiazLS10','conf-sigir-2010');
insert into inproceedings values ('conf-sigir-CarmelY10','conf-sigir-2010');
insert into inproceedings values ('conf-sigir-MeijR10','conf-sigir-2010');
insert into inproceedings values ('conf-sigir-OstergrenYE10','conf-sigir-2010');

insert into author values (1,'Annalina Caputo');
insert into author values (2,'Benjamin Piwowarski');
insert into author values (3,'Mounia Lalmas');
insert into write values (1,'conf-iir-CaputoPL11');
insert into write values (2,'conf-iir-CaputoPL11');
insert into write values (3,'conf-iir-CaputoPL11');

insert into author values (4,'Emanuele Di Buccio');
insert into author values (5,'Giorgio Maria Di Nunzio');
insert into author values (6,'Massimo Melucci');
insert into author values (7,'Nicola Orio');
insert into write values (4,'conf-iir-BuccioNMO11');
insert into write values (5,'conf-iir-BuccioNMO11');
insert into write values (6,'conf-iir-BuccioNMO11');
insert into write values (7,'conf-iir-BuccioNMO11');

insert into author values (8,'Guido Zuccon');
insert into author values (9,'Leif Azzopardi');
insert into author values (10,'Enrico Gasco');
insert into write values (8,'conf-iir-ZucconAG11');
insert into write values (9,'conf-iir-ZucconAG11');
insert into write values (10,'conf-iir-ZucconAG11');



insert into author values (13,'Tobias Blanke');
insert into write values (13,'journals-ir-BlankeL11');
insert into write values (3,'journals-ir-BlankeL11');

insert into author values (14,'Alejandro Jaimes');
insert into author values (15,'Yana Volkovich');
insert into write values (14,'journals-sigir-JaimesLV11');
insert into write values (3,'journals-sigir-JaimesLV11');
insert into write values (15,'journals-sigir-JaimesLV11');



insert into author values (16,'Wouter Weerkamp');
insert into author values (17,'Krisztian Balog');
insert into author values (18,'Maarten de Rijke');
insert into write values (16,'journals-ir-WeerkampBR11');
insert into write values (17,'journals-ir-WeerkampBR11');
insert into write values (18,'journals-ir-WeerkampBR11');

insert into author values (19,'Corrado Boscarino');
insert into author values (20,'Katja Hofmann');
insert into author values (21,'Valentin Jijkoun');
insert into author values (22,'Edgar Meij');
insert into write values (19,'journals-sigir-BoscarinoHJMRW11');
insert into write values (20,'journals-sigir-BoscarinoHJMRW11');
insert into write values (21,'journals-sigir-BoscarinoHJMRW11');
insert into write values (22,'journals-sigir-BoscarinoHJMRW11');
insert into write values (18,'journals-sigir-BoscarinoHJMRW11');
insert into write values (16,'journals-sigir-BoscarinoHJMRW11');

insert into author values (23,'Marc Bron');
insert into author values (24,'Bouke Huurnink');
insert into write values (23,'conf-ercimdl-BronHR11');
insert into write values (24,'conf-ercimdl-BronHR11');
insert into write values (18,'conf-ercimdl-BronHR11');

insert into author values (25,'Gilles Hubert');
insert into author values (26,'Guillaume Cabanac');
insert into author values (27,'Christian Sallaberry');
insert into author values (28,'Damien Palacio');
insert into write values (25,'conf-ercimdl-HubertCSP11');
insert into write values (26,'conf-ercimdl-HubertCSP11');
insert into write values (27,'conf-ercimdl-HubertCSP11');
insert into write values (28,'conf-ercimdl-HubertCSP11');






insert into author values (33,'Shanu Sushmita');
insert into write values (33,'conf-airs-SushmitaPL10');
insert into write values (2,'conf-airs-SushmitaPL10');
insert into write values (3,'conf-airs-SushmitaPL10');

insert into author values (34,'Hideo Joho');
insert into author values (35,'Robert Villa');
insert into write values (33,'conf-cikm-SushmitaJLV10');
insert into write values (34,'conf-cikm-SushmitaJLV10');
insert into write values (3,'conf-cikm-SushmitaJLV10');
insert into write values (35,'conf-cikm-SushmitaJLV10');


insert into author values (36,'Hugo Zaragoza');
insert into author values (37,'Berkant Barla Cambazoglu');
insert into author values (38,'Ricardo A. Baeza-Yates');
insert into write values (36,'conf-cikm-ZaragozaCB10');
insert into write values (37,'conf-cikm-ZaragozaCB10');
insert into write values (38,'conf-cikm-ZaragozaCB10');

insert into author values (39,'Joel Coffman');
insert into author values (40,'Alfred C. Weaver');
insert into write values (39,'conf-cikm-CoffmanW10');
insert into write values (40,'conf-cikm-CoffmanW10');

insert into author values (41,'Ronan Cummins');
insert into author values (42,'Colm O''Riordan');
insert into write values (41,'conf-ecai-CumminsLO10');
insert into write values (3,'conf-ecai-CumminsLO10');
insert into write values (42,'conf-ecai-CumminsLO10');


insert into author values (43,'Meng Chang');
insert into author values (44,'Minghua He');
insert into author values (45,'Xudong Luo');
insert into write values (43,'conf-ecai-ChangHL10');
insert into write values (44,'conf-ecai-ChangHL10');
insert into write values (45,'conf-ecai-ChangHL10');

insert into author values (46,'Rui Prada');
insert into author values (47,'Jo&#227;o Camilo');
insert into author values (48,'Maria Augusta Silveira Netto Nunes');
insert into write values (46,'conf-ecai-PradaCN10');
insert into write values (47,'conf-ecai-PradaCN10');
insert into write values (48,'conf-ecai-PradaCN10');

insert into author values (49,'Fernando Diaz');
insert into author values (50,'Milad Shokouhi');
insert into write values (49,'conf-sigir-DiazLS10');
insert into write values (3,'conf-sigir-DiazLS10');
insert into write values (50,'conf-sigir-DiazLS10');

insert into author values (51,'David Carmel');
insert into author values (52,'Elad Yom-Tov');
insert into write values (51,'conf-sigir-CarmelY10');
insert into write values (52,'conf-sigir-CarmelY10');

insert into write values (22,'conf-sigir-MeijR10');
insert into write values (18,'conf-sigir-MeijR10');

insert into author values (53,'Marilyn Ostergren');
insert into author values (54,'Seung-yon Yu');
insert into author values (55,'Efthimis N. Efthimiadis');
insert into write values (53,'conf-sigir-OstergrenYE10');
insert into write values (54,'conf-sigir-OstergrenYE10');
insert into write values (55,'conf-sigir-OstergrenYE10');

commit;
