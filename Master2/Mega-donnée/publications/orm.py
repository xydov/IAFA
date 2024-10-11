from sqlalchemy import Column
from sqlalchemy import Table
from sqlalchemy import ForeignKey
from sqlalchemy import Integer
from sqlalchemy import String
from sqlalchemy import select
from sqlalchemy.orm import declarative_base
from sqlalchemy.orm import relationship
from sqlalchemy.orm import Session
from sqlalchemy import create_engine
from sqlalchemy.orm import with_polymorphic
from sqlalchemy.orm import aliased

Base = declarative_base()



class Proceedings(Base):
    __tablename__ = "proceedings"

    keyproc = Column(String(50), primary_key=True) 
    title = Column(String(150))
    location = Column(String(50))
    datep = Column(String(30))
    publisher = Column(String(40))
    year = Column(Integer)

    inproceedings = relationship("Inproceedings", back_populates="proceeding")


    def __repr__(self):
        return f"Proceedings(keyproc={self.keyproc},title={self.title},location={self.location},datep={self.datep},publisher={self.publisher},year={self.year})"


# Classe Mère Publication
class Publication(Base):
    __tablename__ = "publication"
    
    key = Column(String(50), primary_key=True)
    title = Column(String(100))

    def __repr__(self):
        return f"Publication(key={self.key},title={self.title})"
        

# Inproceedings hérite de Publication
class Inproceedings(Publication):
    __tablename__ = "inproceedings"

    key = Column(String(50), ForeignKey("publication.key"), primary_key=True)
    crossref = Column(String(50), ForeignKey("proceedings.keyproc"))
    proceeding = relationship("Proceedings", back_populates="inproceedings")

    def __repr__(self):
        return f"Inproceedings(key={self.key},title={self.title}, crossref(key={self.crossref}))"
    
class Article(Publication):
    __tablename__ = "article"

    key = Column(String(50), ForeignKey("publication.key"), primary_key=True)
    journal = Column(String(50))
    year= Column(Integer)
    volume=Column(Integer)
    numb=Column(Integer)
    pages=Column(Integer)

    def __repr__(self):
        return f"Article(key={self.key},journal={self.journal})"




class Author(Base):
    __tablename__ = "author"

    idAuthor = Column(Integer, primary_key=True) 
    name = Column(String(40))
   
    def __repr__(self):
        return f"Author(idAuthor={self.idAuthor},name={self.name})"

    def __init__(self, idAuthor, name):
        self.idAuthor=idAuthor
        self.name=name



engine = create_engine('sqlite:///publications.db', echo=True, future=True)
session = Session(engine)




# Requête  - Test de l'héritage en partant d'une classe fille
print("******************** Test : Héritage partant de la classe fille  ******************************")
for i in session.query(Inproceedings):
    print(i)
## Requête générée:
# SELECT inproceedings."key" AS inproceedings_key, publication."key" AS publication_key, publication.title AS publication_title, inproceedings.crossref AS inproceedings_crossref 
# FROM publication JOIN inproceedings ON publication."key" = inproceedings."key"

# Requête  - Test de l'héritage en partant de la classe mère
print("******************** Test : Héritage partant de la classe mère  ******************************")
for i in session.query(Publication):
    print(i)
## Requête générée:
# SELECT publication."key" AS publication_key, publication.title AS publication_title 
# FROM publication    
#print("******************** Test : Héritage partant de la classe mère  ******************************")
#for i in session.query(Inproceedings):
#   print(i.proceeding)
print("******************** Test : Héritage partant de la classe mère  ******************************")
#for i in session.query(Proceedings):
#    print(i.inproceedings)

    
