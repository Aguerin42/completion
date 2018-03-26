/**
**	\file	completion.c
**	\author	Alexis Guérin
**	\date	19 février 2018
*/

#include "completion.h"

/**
**	\brief	Insertion de backslash avant les espaces
**
**	\param	command	- commande à modifier
**
**	\return **chaîne** modifiée ou **NULL** en cas d'erreur
*/

char		*insert_backslash(char *command)
{
	int		i;
	int		b;
	int		len;

	if (command)
	{
		i = -1;
		b = 0;
		while (command[++i])
			if (command[i] == ' ')
				b++;
		len = ft_strlen(command);
		if (b && (command = ag_memrealloc(command, len, len + b + 1)))
		{
			i = -1;
			while (command[++i])
				if (command[i] == ' ')
				{
					ft_memmove(&command[i + 1], &command[i], len + b - i);
					command[i++] = '\\';
				}
		}
		else if (b && !command)
		{
			ft_putchar_fd(2, '\n');
			sh_error(1, "completion");
		}
	}
	return (command);
}

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
				ft_putchar_fd(2, '\n');
				sh_error(1, "completion");
			}
			list = list->next;
		}
	}
	else
	{
		ft_putchar_fd(2, '\n');
		sh_error(1, "completion");
	}
	return (tab);
}

static t_list	*new_node(const char *path, char *name)
{
	int		dir;
	char	*complete;
	t_list	*node;

	node = NULL;
	if ((complete = ft_strnew(ft_strlen(path) + ft_strlen(name))))
	{
		complete = ft_strcpy(complete, path);
		complete = ft_strcat(complete, name);
		dir = isdir(complete);
		if (!(node = ft_lstnew(name, ft_strlen(name) + 1 + dir)))
		{
			ft_putchar_fd(2, '\n');
			sh_error(1, "completion");
		}
		if (dir)
			node->content = ft_strcat(node->content, "/");
		ft_strdel(&complete);
	}
	else
	{
		ft_putchar_fd(2, '\n');
		sh_error(1, "completion");
	}
	return (node);
}

static void	complete(const char *word, const char *path, t_list **list)
{
	int				len;
	DIR				*pdir;
	struct dirent	*dir;
	t_list			*node;

	if (!access(path, R_OK) && (pdir = opendir(path)))
	{
		if ((len = ft_strlen(word)) && word[len - 1] == '\\')
			len--;
		while ((dir = readdir(pdir)))
			if ((word[0] && ag_strnequ(word, dir->d_name, len)) ||
				(!word[0] && dir->d_name[0] != '.'))
			{
				node = new_node(path, dir->d_name);
				if (!(*list))
					*list = node;
				else if (!(*list = ft_lstaddalpha(list, node)))
				{
					ft_putchar_fd(2, '\n');
					sh_error(1, "completion");
				}
			}
		closedir(pdir);
	}
}

static void	complete_env(const char *word, const char *env, t_list **list)
{
	int		len;
	char	*egal;
	t_list	*node;

	egal = ft_strchr(env, '=');
	len = ft_strlen(word);
	if (((!egal || len <= (egal - env))) && ft_strnequ(word, env, len))
	{
		if ((node = ft_lstnew(NULL, 0)))
		{
			node->content =
			ft_strsub(env, 0, egal ? egal - env : (int)ft_strlen(env));
			node->content_size = ft_strlen(node->content) + 1;
			if (!(*list))
				*list = node;
			else if (!(*list = ft_lstaddalpha(list, node)))
			{
				ft_putchar_fd(2, '\n');
				sh_error(1, "completion");
			}
		}
		else
		{
			ft_putchar_fd(2, '\n');
			sh_error(1, "completion");
		}
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
**	\param	builtin	- builtins du Shell (peut être `NULL`)
**	\param	var		- variables locales et d'environnement (peut être `NULL`)
**
**	\return	**tableaux de chaînes de caractères** contenant le nom des
**			éléments pouvant compléter le mot (le tableau est vide si aucun
**			élément n'a été trouvé),
**			ou **NULL** en cas d'erreur.
*/

char		**completion(const char *word, const char **path,
							const char **builtin, const char **var)
{
	int		i;
	char	**res;
	t_list	*list;

	res = NULL;
	if (word)
	{
		list = NULL;
		i = -1;
		while (path && path[++i])
			complete(word, path[i], &list);
		i = -1;
		while (builtin && builtin[++i])
			complete_env(word, builtin[i], &list);
		i = -1;
		while (var && var[++i])
			complete_env(word, var[i], &list);
		list ? res = list_to_tab(list) : NULL;
		list ? ft_lstdel(&list, del) : NULL;
	}
	return (res);
}
