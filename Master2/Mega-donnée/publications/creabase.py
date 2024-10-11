import sqlite3


try:
    print("Création de la base publications")
    conn = sqlite3.connect('publications.db')
    cur = conn.cursor()
    print("Base de données crée et correctement connectée à SQLite")
    sql = "SELECT sqlite_version();"
    cur.execute(sql)
    res = cur.fetchall()
    print("La version de SQLite est: ", res)
    cur.close()
    conn.close()
    print("La connexion SQLite est fermée")
except sqlite3.Error as error:
    print("Erreur lors de la connexion à SQLite", error)