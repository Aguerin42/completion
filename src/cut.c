/**
**	\file	cut.c
**	\author	Alexis Guérin
**	\date	19 février 2018
*/

#include "completion.h"

/**
**	\brief	Découpe d'un chemin d'accès
**
**	
*/

int			cut_word_path(const char *command, char **word, char **path)
{
	if (command && word && path)
	{
	}
	return (1);
}

/*
**	Renvoie l'indice du début du mot
*/

static int	find_begin(const char *command, int pos)
{
	int	i;

	i = pos;
	while ((i > 0 && command[i - 1] != ' ')
			|| (i > 1 && command[i - 1] == ' ' && command[i - 2] == '\\'))
		i--;
	return (i);
}

/*
**	Renvoie l'indice de fin du mot + 1 si il existe, ou `pos` sinon
*/

static int	find_end(const char *command, int pos)
{
	int	i;

	i = pos;
	while (command[i] && (command[i] != ' '
			|| (i > 0 && command[i] == ' ' && command[i - 1] == '\\')))
		i++;
	return (i);
}

/**
**	\brief	Découpe d'une commande
**
**	Découpe la partie de la commande sur laquelle la complétion doit
**	être effectuée. La fonction se base sur la position du curseur dans la
**	ligne pour savoir quel partie découper.
**
**	\param	command	- ligne de commande
**	\param	pos		- position du curseur dans la ligne.
**
**	\return	**
*/

char		*cut_command(const char *command, int pos)
{
	char	*res;
	int		b;
	int		e;

	res = NULL;
	if (command && pos >= 0)
	{
		b = find_begin(command, pos);
		e = find_end(command, pos);
		if (e - b > 0)
			if (!(res = ft_strsub(command, b, e - b)))
				ft_putendl_fd("completion: allocation error.", 2);
	}
	return (res);
}
