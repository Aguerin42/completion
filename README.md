completion - Complétion de commandes pour Shell
------------------------------------

La fonction _completion_ permet de compléter une ligne de commande en cours d'édition. Elle cherche dans les chemins d'accès fournis les éléments pouvant compléter le début de la commande donnée et retourne un tableau de chaînes de caractères les contenant.

## Utilisation et compilation

*completion* utilise des fonctions de la [libft][], de la [libag][] et de [environment][] et a besoin de leurs headers pour pouvoir être compilé. Il faut fournir au _Makefile_ le chemin vers le dossier les contenant à l'aide des variables *LIBFT_INC*, *LIBAG_INC* et *ENV_INC*.

	$> make LIBFT_INC=../libft/includes LIBAG_INC=../libag/includes ENV_INC=../environment/includes all

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
[environment]: https://github.com/aguerin42/environment.git
[Doxygen]: https://github.com/doxygen/doxygen
