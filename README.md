completion - Complétion de commandes pour Shell
------------------------------------

_completion_ fournit des fonctions de complétion d'une ligne de commande et de découpe d'un chemin d'accès.

## Utilisation et compilation

*completion* utilise des fonctions de la [libft][], de la [libag][] et de la [liberror][] et a besoin de leurs headers pour pouvoir être compilé. Il faut fournir au _Makefile_ le chemin vers le dossier les contenant à l'aide des variables *LIBFT_INC*, *LIBAG_INC* et *ERROR_INC*.

	$> make LIBFT_INC=../libft/includes LIBAG_INC=../libag/includes ERROR_INC=../error/includes all

La documentation peut être créée avec la commande suivante :

	$> make doxygen

La documentation est générée grâce à [Doxygen][]. Le _Makefile_ utilise l'alias `doxygen` pour faire appel à l'exécutable, mais si celui-ci n'est pas défini il faut utiliser la commande :

	$> make doxygen DOXYGEN=/CHEMIN/VERS/EXECUTABLE/DE/DOXYGEN

## Sources

- [marionpatrick.free.fr - Manipulation clavier](http://marionpatrick.free.fr/man_html/html/tuto_shell.html#chp1.1)
- [Wikipedia.org - Command-line completion](https://en.wikipedia.org/wiki/Command-line_completion)
- [readdir(3) - Linux man page](https://linux.die.net/man/3/readdir)
- [StackOverflow - Does readdir() guarantee an order?](https://stackoverflow.com/questions/8977441/does-readdir-guarantee-an-order)

[libft]: https://github.com/aguerin42/libft.git
[libag]: https://github.com/aguerin42/libag.git
[liberror]: https://github.com/mtacnet/error
[Doxygen]: https://github.com/doxygen/doxygen
