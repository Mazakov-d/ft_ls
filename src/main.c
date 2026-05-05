#include "libft.h"
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
// #include <error.h>
#include <sys/stat.h>
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

typedef struct	s_token {
	char			*name;
	int				type;
}	t_token;

typedef struct	s_context {
	char	**arguments;
	short	flags_set;
	t_token	**tokens;
}	t_context;

void	free_ctx(t_context* ctx, int ret, char *error)
{
	int	i;
	int	j;

	if (error)
		ft_printf("Error: %s\n", error);
	if (ctx && ctx->tokens)
	{
		i = -1;
		while (ctx->tokens && ctx->tokens[++i])
		{
			j = -1;
			while (ctx->tokens[i][++j].name)
				free(ctx->tokens[i][j].name);
			free(ctx->tokens[i]);
		}
		free(ctx->tokens);
	}
	if (ctx && ctx->arguments) {
		i = -1;
		while (ctx->arguments[++i])
			free(ctx->arguments[i]);
		free(ctx->arguments);
	}
	exit(ret);
}

void	realloc_struct_token(t_token **token, size_t new_size, size_t curr_size) {
	 t_token *new_token;
	size_t i;

	i = 0;
	new_token = ft_calloc(sizeof(t_token), new_size);
	if (!new_token) {
		if (*token)
			free(*token);
		*token = NULL;
		return;
	}
	while (i < curr_size && (*token)[i].name)
	{
		new_token[i].name = (*token)[i].name;
		new_token[i].type = (*token)[i].type;
		i++;
	}
	new_token[i].name = NULL;
	free(*token);
	*token = new_token;
	return;
}

int	is_flag_set(short flag, int i)
{
	return (flag & (1 << i));
}

void	set_bit(short *flags, int i)
{
	*flags = *flags | (1 << i);
}

int	set_flags(int ac, char **av, t_context *ctx)
{
	int	i;
	int	j;

	i = 0;
	ctx->flags_set = 0;
	while (++i < ac) {
		if (av[i][0] == '-') {
			j = 0;
			while (av[i][++j]) {
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
			}
		} else {
			break;
		}
	}
	return i;
}

void	no_args_given(t_context *ctx)
{
	ctx->arguments = ft_calloc(sizeof(char*), 2);
	ctx->tokens = ft_calloc(sizeof(t_token*), 2);
	if (!ctx->arguments || !ctx->tokens)
		free_ctx(ctx, 1, "malloc failed");
	ctx->arguments[0] = ft_strdup("./");
	if (!ctx->arguments[0]) {
		free_ctx(ctx, 1, "ft_strudp failed");
	}
}

void	parse_args(int ac, char **av, t_context *ctx)
{
	int	i;
	int	j;

	i = set_flags(ac, av, ctx);
	j = 0;
	if (ac == 1 || i == ac) {
		no_args_given(ctx);
		return ;
	}
	ctx->arguments = ft_calloc(sizeof(char*), (ac - i + 1));
	ctx->tokens = ft_calloc(sizeof(t_token*), (ac - i + 1));
	if (!ctx->arguments || !ctx->tokens)
		free_ctx(ctx, 1, "malloc failed");
	while (i < ac) {
		ctx->arguments[j] = ft_strdup(av[i]);
		if (!ctx->arguments[j])
			free_ctx(ctx, 1, "ft_strdup failed");
		i++;
		j++;
	}
}

void	fill_tokens_data(t_context *ctx, DIR *dir, int i)
{
	struct dirent *entry;
	int j = 0;

	ctx->tokens[i] = NULL;

	while ((entry = readdir(dir)))
	{
		realloc_struct_token(&ctx->tokens[i], j + 1, j);
		ctx->tokens[i][j].name = ft_strdup(entry->d_name);
		ctx->tokens[i][j].type = entry->d_type;
		j++;
	}
	realloc_struct_token(&ctx->tokens[i], j + 1, j);
	ctx->tokens[i][j].name = NULL;
	closedir(dir);
	if (errno)
		perror("Readdir");
}

void	dir_parsing(t_context *ctx, char *dir_name, int i)
{
	DIR				*dir;
	// int				count_tokens;

	errno = 0;
	dir = opendir(dir_name);
	if (errno) {
		ctx->tokens[i] = ft_calloc(sizeof(t_token), 1);
		if (!ctx->tokens[i])
			free_ctx(ctx, 1, "malloc failed");
		ft_printf("ft_ls: cannot access '%s': ", dir_name);
		perror(NULL);
		return ;
	}
	fill_tokens_data(ctx, dir, i);
	return ;
}

void	ft_ls(t_context *ctx)
{
	int	i;

	i = 0;
	while (ctx->arguments && ctx->arguments[i]) {
		dir_parsing(ctx, ctx->arguments[i], i);
		i++;
	}
}

int main(int ac, char **av) {
	t_context	ctx;

	parse_args(ac, av, &ctx);
	ft_ls(&ctx);
	ft_printf("------Arguments---------\n");
	int i = 0;
	while(ctx.arguments[i]) {
		ft_printf("%s\n", ctx.arguments[i]);
		i++;
	}
	i = 0;
	ft_printf("-------DIR------\n");
	while (ctx.tokens[i]) {
		int j = 0;
		while (ctx.tokens[i][j].name) {
			if (ctx.tokens[i][j].name)
				ft_printf("%s\n", ctx.tokens[i][j].name);
			j++;
		}
		i++;
	}
	free_ctx(&ctx, 0, NULL);
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