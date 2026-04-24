#include "libft.h"
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
// #include <error.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

enum flags {
	MR,
	L,
	A,
	R,
	T,
};

typedef struct	s_context {
	char	**arguments;
	short	flags_set;
}	t_context;

void	free_ctx(t_context* ctx, int ret) {
	int	i;

	i = 0;
	if (ctx && ctx->arguments) {
		while (ctx->arguments[i]) {
			free(ctx->arguments[i]);
			i++;
		}
		free(ctx->arguments);
	}
	exit(ret);
}

int	is_flag_set(short flag, int i) {
	return (flag & (1 << i));
}

void	set_bit(short *flags, int i) {
	*flags = *flags | (1 << i);
}

int	set_flags(int ac, char **av, t_context *ctx) {
	int	i;
	int	j;

	i = 1;
	ctx->flags_set = 0;
	while (i < ac) {
		if (av[i][0] == '-') {
			j = 1;
			while (av[i][j]) {
				if (av[i][j] == 'R')
					set_bit(&ctx->flags_set, MR);
				else if (av[i][j] == 'r')
					set_bit(&ctx->flags_set, R);
				else if (av[i][j] == 'l')
					set_bit(&ctx->flags_set, L);
				else if (av[i][j] == 'a')
					set_bit(&ctx->flags_set, A);
				else if (av[i][j] == 't')
					set_bit(&ctx->flags_set, T);
				j++;
			}
		} else {
			break;
		}
		i++;
	}
	return i;
}

void	parse_args(int ac, char **av, t_context *ctx) {
	int	i;
	int	j;

	i = set_flags(ac, av, ctx);

	if (ac == 1 || i == ac) {
		ctx->arguments = malloc(sizeof(char*) * 2);
		if (!ctx->arguments)
			free_ctx(ctx, 1);
		ctx->arguments[0] = ft_strdup(".");
		if (!ctx->arguments[0]) {
			free_ctx(ctx, 1);
		}
		ctx->arguments[1] = NULL;
		return ;
	}

	ctx->arguments = malloc(sizeof(char*) * ((ac - i) + 1));
	if (!ctx->arguments)
		free_ctx(ctx, 1);

	j = 0;

	while (i < ac) {
		ctx->arguments[j] = ft_strdup(av[i]);
		if (!ctx->arguments[j])
			free_ctx(ctx, 1);
		i++;
		j++;
	}
	ctx->arguments[j] = NULL;
}

void	ft_ls(t_context *ctx) {
	int	i;

	i = 0;
	while (ctx->arguments && ctx->arguments[i]) {
		DIR	*dir;
		errno = 0;
		dir = opendir(ctx->arguments[i]);
		if (errno) {
			ft_printf("'%s': ", ctx->arguments[i]);
			perror(NULL);
		} else {
			struct dirent	*readed_dir;
			while ((readed_dir = readdir(dir))) {
				if (!ft_strncmp(readed_dir->d_name, ".", ft_strlen(readed_dir->d_name)) ||
						!ft_strncmp(readed_dir->d_name, "..", ft_strlen(readed_dir->d_name))) {
					ft_printf("not reading the info of this dir\n");
				}
				else if (readed_dir->d_type == DT_DIR) {
					printf("%s is a dir\n", readed_dir->d_name);
				}
				else {
					printf("%s is not a dir is type %d\n", readed_dir->d_name, readed_dir->d_type);
				}
			}
			if (errno) {
				perror("Readdir error");
			}
			closedir(dir);
		}
		i++;
	}
}

int main(int ac, char **av) {
	t_context	ctx;

	parse_args(ac, av, &ctx);
	ft_ls(&ctx);

	// DIR*	dir;


	// dir = opendir("./");
	// if (dir) {
	// 	struct dirent	*openDir;

	// 	while ((openDir = readdir(dir)) != NULL) {
	// 		printf("%s %hhu\n", openDir->d_name, openDir->d_type);
			
	// 	}
	// 	return (0);
	// }
	// // ft_printf("strerror: %s\n", strerror(errno));
	// perror("Error opendir");
	// return (1);
}