#include <stdio.h>
#include <string.h>

#define MAX_CHARA_NOM 31
#define MAX_CHARA_PRENOM 21
#define MAX_CHARA_MAIL 255

struct sContact // 1.1
{
    /* data */
    const char Nom[MAX_CHARA_NOM];
    const char Prenom[MAX_CHARA_PRENOM];
    const char Mail[MAX_CHARA_MAIL];
};

void AfficherContact1(struct sContact Contact) // 1.2
{
    printf("%s\n", Contact.Nom);
    printf("%s\n", Contact.Prenom);
    printf("%s\n", Contact.Mail);
}

void AfficherContact2(const struct sContact *pContact)
{
    printf("%s\n", pContact->Nom);
    printf("%s\n", pContact->Prenom);
    printf("%s\n", pContact->Mail);
}

void VidageTamponEntree(void)
{
    while (getchar()!=’\n’);    
}

void LireLigne(char Ch[], int LongueurMax)
{
    /*
    int longueur
    fgets(ch, longueurMax+1, stdin)
    longueur = strlen(ch)
    if (ch[longeur-1]=='\n')
    {

    }else {
                                                                                                    
    }
}

int main(void)
{
    struct sContact Contact = {  // 1.3
        "nom",
        "prenom",
        "mail@lol.lil"
    };
    //struct sContact *pContact = NULL;

    AfficherContact1(Contact);
    // donne adresse au pointeur
    // AfficherContact2(..; ici)
    AfficherContact2(&Contact);
    return 0;
}