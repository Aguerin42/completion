/**
**	\file	cut.c
**	\author	Alexis Guérin
**	\date	19 février 2018
*/

#include "completion.h"

/**
**	\brief	Suppression des backslash
**
**	La fonction supprime les backslash précédents les espaces.
**
**	\param	command	- partie de la ligne de commande
**
**	\return	**ligne** dont les backslash ont été supprimés
**			ou **NULL** en cas d'erreur
*/

char		*delete_backslash(char *command)
{
	int		i;
	int		len;

	if (command)
	{
		len = ft_strlen(command);
		i = -1;
		while (command[++i])
			if (command[i] == '\\')
			{
				ft_memmove(&command[i], &command[i + 1],
							ft_strlen(&command[i + 1]));
				command[--len] = '\0';
			}
	}
	return (command);
}

/**
**	\brief	Découpe d'un chemin d'accès
**
**	Prend en entrée une partie de ligne de commande et sépare le chemin
**	d'accès du nom de l'élément à compléter.
**
**	\param	command	- partie de la commande à compléter
**	\param	path	- pointeur sur chaîne où allouer le chemin d'accès
**	\param	word	- pointeur sur chaîne où allouer le mot à compléter
**
**	\return **0** en cas de succès ou une valeur **non nulle** en cas d'erreur
*/

int			cut_word_path(const char *command, char **path, char **word)
{
	int		i;
	char	*c;

	if (command && word && path)
	{
		i = 0;
		if ((c = ft_strrchr(command, '/')))
		{
			if (!(*path = ft_strsub(command, 0, c - command + 1)))
				return (ft_putendl_fd("completion: allocation error.", 2));
			if (!(*word = ft_strsub(c + 1, 0, ft_strlen(c + 1))))
				return (ft_putendl_fd("completion: allocation error.", 2));
		}
		else
		{
			*path = NULL;
			if (!(*word = ft_strsub(command, 0, ft_strlen(command))))
				return (ft_putendl_fd("completion: allocation error.", 2));
		}
		return (0);
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
