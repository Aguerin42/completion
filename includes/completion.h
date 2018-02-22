#ifndef COMPLETION_H
# define COMPLETION_H

# include "libft.h"
# include "libag.h"
# include <dirent.h>

char	*insert_backslash(char *command);
char	**completion(const char *word, const char **path);

char	*delete_backslash(char *command);
int		find_end(const char *command, int pos);
int		cut_path_word(const char *command, char **path, char **word);
char	*cut_command(const char *command, int pos);

#endif
