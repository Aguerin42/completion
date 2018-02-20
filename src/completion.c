/**
**	\file	completion.c
**	\author	Alexis Guérin
**	\date	19 février 2018
*/

#include "completion.h"

static void	del(void *content, size_t content_size)
{
	if (content)
		ft_memdel(&content);
	if (content_size)
		NULL;
}

static char	**list_to_tab(t_list *list)
{
	int		len;
	int		i;
	char	**tab;

	len = ft_lstcount(list);
	if ((tab = (char**)ft_memalloc(sizeof(char*) * (len + 1))))
	{
		i = -1;
		while (++i < len && tab)
		{
			if (!(tab[i] = ft_strdup((char*)list->content)))
			{
				ag_strdeldouble(&tab);
				ft_putendl_fd("completion: allocation error.", 2);
			}
			list = list->next;
		}
	}
	else
		ft_putendl_fd("completion: allocation error.", 2);
	return (tab);
}

static void	complete(const char *word, const char *path, t_list **list)
{
	int				len;
	DIR				*pdir;
	struct dirent	*dir;
	t_list			*node;

	if (!access(path, R_OK) && (pdir = opendir(path)))
	{
		len = ft_strlen(word);
		while ((dir = readdir(pdir)))
			if ((word[0] && ag_strnequ(word, dir->d_name, len)) ||
				(!word[0] && dir->d_name[0] != '.'))
			{
				if (!(node = ft_lstnew(dir->d_name, ft_strlen(dir->d_name) + 1)))
					ft_putendl_fd("completion: allocation error.", 2);
				if (!*list)
					*list = node;
				else
					if (!(*list = ft_lstaddalpha(list, node)))
						ft_putendl_fd("completion: allocation error.", 2);
			}
		closedir(pdir);
	}
}

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

char		**completion(const char *word, const char **path)
{
	int		i;
	char 	**res;
	t_list	*list;

	res = NULL;
	if (word && path && path[0])
	{
		i = -1;
		list = NULL;
		while (path[++i])
			complete(word, path[i], &list);
		list ? res = list_to_tab(list) : NULL;
		i = -1;
		while (res && res[++i])
			ft_putendl(res[i]);
		list ? ft_lstdel(&list, del) : NULL;
	}
	return (res);
}
