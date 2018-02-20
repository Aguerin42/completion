/**
**	\file	completion.c
**	\author	Alexis Guérin
**	\date	19 février 2018
*/

#include "completion.h"

/**
**	\brief	Complétion d'une ligne de commande
**
**	La fonction reçoit un mot à compléter et les chemins d'accès où chercher
**	des éléments pouvant le compléter. Si le mot de contient pas de
**	caractère (que son premier caractère est `\0`), la fonction renvoie tous
**	les éléments contenus dans les dossiers indiqués dans le `path`.
**
**	\param	word	- mot à compléter
**	\param	path	- chemin(s) d'accès vers le ou les dossiers où chercher
**					des éléments pour la complétion
**
**	\return	**tableaux de chaînes de caractères** contenant le nom des
**			éléments pouvant compléter le mot (le tableau est vide si aucun
**			élément n'a été trouvé),
**			ou **NULL** en cas d'erreur.
*/

char	**completion(const char *word, const char **path)
{
	char **res;

	res = NULL;
	if (word && path)
	{
	}
	return (res);
}
