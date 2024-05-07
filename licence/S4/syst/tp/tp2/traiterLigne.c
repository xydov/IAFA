
#include "matrice.h"
#include "traiterLigne.h"

unsigned traiterLigne(int uneLigne[], unsigned nbCol,
                      unsigned v1, unsigned v2)
{
    /// \brief réalise le traitement d’une ligne uneLigne contenant nbCcolonnes
    /// \brief et retourne une valeur précisant si cette ligne contient v1,v2 ou v1 et v2.
    /// \return  0: aucun trouve, 1: V1 trouve, 2: v2 trouve et 3: v1 et v2 trouve

    int gotV1 = 0;
    int gotV2 = 0;
    int tr;

    for (int i = 0; i < nbCol; i++)
    {
        if (uneLigne[i] == v1)
        {
            gotV1 ++;
        } else if (uneLigne[i] == v2)
        {
            gotV2++;
        }
    }

    if (gotV1 == 0 && gotV2 == 0)
    {
        tr = 0;
    }
    else if (gotV1 > 0 && gotV2 == 0)
    {
        tr = 1;
    }
    else if (gotV1 == 0 && gotV2 > 0)
    {
        tr = 2;
    }
    else if (gotV1 > 0 && gotV2 > 0)
    {
        tr = 3;
    }

    return tr;
}
