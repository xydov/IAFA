#ifndef _EX_H_
#define _EX_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include <unistd.h>
#include <sys/types.h> /* types implémentés différemment selon la version d’Unix */
#include <sys/stat.h> /* constantes symboliques pour les droits d’accès */
#include <dirent.h> /* repertory access */
#include <fcntl.h> /* constantes symboliques pour les différents types d’ouverture */

#define ERROR_STAT 1
#define ERROR_OPENDIR 2
#define ERROR_READDIR 3
#define ERROR_CLOSINGDIR 4

#endif