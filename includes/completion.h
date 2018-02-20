#ifndef COMPLETION_H
# define COMPLETION_H

# include "libft.h"
# include "libag.h"
# include <dirent.h>

char	**completion(const char *word, const char **path);

int		cut_word_path(const char *command, char **path, char **word);
char	*cut_command(const char *command, int pos);

#endif
