import sqlite3
  
try:
      
    sqliteConnection = sqlite3.connect('publications.db')

    print("Connecté à la base Publications")
  
    # Récupération de toutes les tables
    sql_query = "SELECT name FROM sqlite_master WHERE type='table';"
  
    # L'objet cursor va contenir le résultat de la requête
    cursor = sqliteConnection.cursor()
    cursor.execute(sql_query)

    # Parcours du curseur
    print("Liste de toutes les tables")
    print("------------------------------------------------\n")
    print(cursor.fetchall())
    print("\n")

    print("Affichage des tables")
    print("------------------------------------------------")
    cursor2=sqliteConnection.cursor()
    for row in cursor.execute(sql_query):
        print("----"+row[0])
        sql_query2="select * from "+row[0]+";"
        for row2 in cursor2.execute(sql_query2):
            print(row2)


  
except sqlite3.Error as error:
    print("Problème dans l'exécution de la requête", error)
      
finally:
    
    if sqliteConnection:
        sqliteConnection.close()
        print("Fermeture de la connexion")