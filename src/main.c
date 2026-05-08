#include "libft.h"
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
// #include <error.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

enum flags {
	MR,
	L,
	A,
	R,
	T,
	I
};

typedef struct	s_token {
	char			*name;
	int				type;
	struct stat		s;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_arg {
	char			*name;
	int				total;
	t_token			*token;
	struct s_arg	*next;
	struct s_arg	*prev;
}	t_arg;

typedef struct	s_context {
	short	flags_set;
	t_arg	*args;
	t_token	*tokens;
}	t_context;

void	remove_arg_node(t_arg **arg)
{
	t_arg	*save;
	if (arg && *arg)
	{
		if ((*arg)->prev)
			(*arg)->prev->next = (*arg)->next;
		if ((*arg)->next)
			(*arg)->next->prev = (*arg)->prev;
		if ((*arg)->name)
			free((*arg)->name);
		save = *arg;
		if ((*arg)->prev)
			*arg = (*arg)->prev;
		else
			*arg = (*arg)->next;
		free(save);
	}
}

int	ft_strcmp_dirname(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s1[i] && s1[i] == '.')
		i++;
	while (s2[j] && s2[j] == '.')
		j++;
	while (s1[i] && ft_tolower(s1[i]) == ft_tolower(s2[j]))
	{
		i++;
		j++;
	}
	return ((unsigned char)ft_tolower(s1[i]) - (unsigned char)ft_tolower(s2[j]));
}

int	ft_strcmp_filename(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s1[i] && s1[i] == '.')
		i++;
	while (s2[j] && s2[j] == '.')
		j++;
	while (s1[i] && ft_tolower(s1[i]) == ft_tolower(s2[j]))
	{
		i++;
		j++;
	}
	return ((unsigned char)ft_tolower(s1[i]) - (unsigned char)ft_tolower(s2[j]));
}

int	time_cmp(t_token *t1, t_token *t2)
{
	long	diff;

	diff = t1->s.st_mtime - t2->s.st_mtime;
	if (diff != 0)
		return diff;
	diff = t1->s.st_size - t2->s.st_size;
	if (diff != 0)
		return diff;
	return ft_strcmp_filename(t2->name, t1->name);
}

int	ft_sprintf(char *dst, char *src)
{
	dst = ft_strjoin(dst, src);
	if (!dst)
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}

void	swap_adjacent_tokens(t_token **head, t_token *a, t_token *b)
{
	t_token *prev;
	t_token *next;

	if (!a || !b || a->next != b)
		return;
	prev = a->prev;
	next = b->next;
	if (prev)
		prev->next = b;
	else
		*head = b;
	if (next)
		next->prev = a;
	b->prev = prev;
	b->next = a;
	a->prev = b;
	a->next = next;
}

void	swap_adjacent_args(t_arg **head, t_arg *a, t_arg *b)
{
	t_arg *prev;
	t_arg *next;

	if (!a || !b || a->next != b)
		return;
	prev = a->prev;
	next = b->next;
	if (prev)
		prev->next = b;
	else
		*head = b;
	if (next)
		next->prev = a;
	b->prev = prev;
	b->next = a;
	a->prev = b;
	a->next = next;
}

void	bubble_sort_arg(t_arg **head, int reverse)
{
	int		swapped;
	long	diff;
	t_arg	*curr;

	if (!head || !*head)
		return;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		curr = *head;
		while (curr && curr->next)
		{
			diff = ft_strcmp_dirname(curr->name, curr->next->name);
			if ((!reverse && diff > 0) || (reverse && diff < 0))
			{
				swap_adjacent_args(head, curr, curr->next);
				swapped = 1;
				if (curr->prev)
					curr = curr->prev;
			}
			else
				curr = curr->next;
		}
	}
}

void	bubble_sort_token(t_token **head, int flag, int reverse)
{
	int		swapped;
	long	diff;
	t_token	*curr;

	if (!head || !*head)
		return;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		curr = *head;
		while (curr && curr->next)
		{
			if (flag)
				diff = time_cmp(curr->next, curr);
			else
				diff = ft_strcmp_filename(curr->name, curr->next->name);
			if ((!reverse && diff > 0) || (reverse && diff < 0))
			{
				swap_adjacent_tokens(head, curr, curr->next);
				swapped = 1;
				if (curr->prev)
					curr = curr->prev;
			}
			else
				curr = curr->next;
		}
	}
}

t_token	*get_first_token(t_token *curr)
{
	if (curr) {
		while (curr->prev) {
			curr = curr->prev;
		}
	}
	return curr;
}

t_arg	*get_first_arg(t_arg *curr)
{
	if (curr) {
		while (curr->prev) {
			curr = curr->prev;
		}
	}
	return curr;
}

void	rewind_ctx(t_context *ctx) {
	if (ctx)
	{
		ctx->tokens = get_first_token(ctx->tokens);
		ctx->args = get_first_arg(ctx->args);
		while (ctx->args)
		{
			ctx->args->token = get_first_token(ctx->args->token);
			if (!ctx->args->next)
				break;
			ctx->args = ctx->args->next;
		}
		ctx->args = get_first_arg(ctx->args);
	}
}

int	new_token(t_token** curr)
{
	t_token	*new;

	new = ft_calloc(sizeof(t_token), 1);
	if (!new)
		return EXIT_FAILURE;
	if (*curr) {
		new->prev = *curr;
		(*curr)->next = new;
	}
	*curr = new;
	return EXIT_SUCCESS;
}

int	new_arg(t_arg **curr)
{
	t_arg	*new;

	new = ft_calloc(sizeof(t_arg), 1);
	if (!new)
		return EXIT_FAILURE;
	if (*curr) {
		new->prev = *curr;
		(*curr)->next = new;
	}
	*curr = new;
	return EXIT_SUCCESS;
}

int	add_arg_node(t_arg *curr, char *name)
{
	t_arg	*new;

	if (!name)
		return EXIT_FAILURE;
	new = ft_calloc(sizeof(t_arg), 1);
	if (!new)
	{
		free(name);
		return EXIT_FAILURE;
	}
	new->name = name;
	if (curr)
	{
		if (curr->next)
			curr->next->prev = new;
		new->prev = curr;
		new->next = curr->next;
		curr->next = new;
	}
	return EXIT_SUCCESS;
}

void	free_ctx(t_context* ctx, int ret, char *error)
{
	void	*save;

	if (error)
		ft_printf_fd(2, "Error: %s\n", error);
	if (ctx && ctx->args)
	{
		rewind_ctx(ctx);
		while (ctx->tokens)
		{
			if (ctx->tokens->name)
				free(ctx->tokens->name);
			save = ctx->tokens;
			ctx->tokens = ctx->tokens->next;
			free(save);
		}
		while (ctx->args)
		{
			if (ctx->args->name)
				free(ctx->args->name);
			while (ctx->args->token) {
				if (ctx->args->token->name)
					free(ctx->args->token->name);
				save =  ctx->args->token;
				ctx->args->token = ctx->args->token->next;
				free(save);
			}
			save = ctx->args;
			ctx->args = ctx->args->next;
			free(save);
		}
	}
	exit(ret);
}

int	is_flag_set(short flag, int i)
{
	return (flag & (1 << i));
}

void	set_bit(short *flags, int i)
{
	*flags = *flags | (1 << i);
}

void	set_flags(char **av, t_context *ctx, int i)
{
	int	j;

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
		else if (av[i][j] == 'i')
			set_bit(&ctx->flags_set, I);
	}
}

void	no_args_given(t_context *ctx)
{
	if (new_arg(&ctx->args))
		free_ctx(ctx, 1, "malloc failed");
	ctx->args->name = ft_strdup(".");
	if (!ctx->args->name) {
		free_ctx(ctx, 1, "ft_strudp failed");
	}
}

void	parse_args(int ac, char **av, t_context *ctx)
{
	int		i;

	i = 1;
	while (i < ac) {
		if (av[i][0] == '-')
			set_flags(av, ctx, i);
		else
		{
			if (new_arg(&ctx->args))
				free_ctx(ctx, 1, "malloc failed");
			ctx->args->name = ft_strdup(av[i]);
			if (!ctx->args->name)
				free_ctx(ctx, 1, "ft_strdup failed");
		}
		i++;
	}
	if (!ctx->args)
		no_args_given(ctx);
	ctx->args = get_first_arg(ctx->args);
}

char	*create_path(char *dir, char *file)
{
	char	*path;
	int		i;
	int		j;

	path = malloc(sizeof(char) * (ft_strlen(dir) + ft_strlen(file) + 2));
	if (!path)
		return NULL;
	i = -1;
	while (dir && dir[++i])
		path[i] = dir[i];
	if (i > 0 && path[i - 1] != '/')
	{
		path[i] = '/';
		i++;
	}
	j = -1;
	while (file && file[++j])
		path[i + j] = file[j];
	path[i + j] = '\0';
	return path;
}

void	fill_dirs_data(t_context *ctx, DIR *dir)
{
	struct dirent	*entry;
	char			*path;

	while ((entry = readdir(dir)))
	{
		errno = 0;
		if (is_flag_set(ctx->flags_set, A) || (!is_flag_set(ctx->flags_set, A) && entry->d_name[0] != '.'))
		{
			if (new_token(&ctx->args->token)) {
				closedir(dir);
				free_ctx(ctx, 1, "malloc failed");
			}
			ctx->args->token->type = entry->d_type;
			ctx->args->token->name = ft_strdup(entry->d_name);
			if (!ctx->args->token->name)
			{
				closedir(dir);
				free_ctx(ctx, 1, "malloc failed");
			}
			path = create_path(ctx->args->name, ctx->args->token->name);
			if (!path)
				free_ctx(ctx, 1, "malloc failed");
			lstat(path, &ctx->args->token->s);
			free(path);
			if (errno)
			{
				ft_printf_fd(2, "ft_ls: cannot access '%s': ", ctx->args->token->name);
				perror(NULL);
			}
			if (is_flag_set(ctx->flags_set, MR) && (ctx->args->token->s.st_mode & __S_IFMT) == __S_IFDIR)
				if (add_arg_node(ctx->args, create_path(ctx->args->name, entry->d_name)))
					free_ctx(ctx, 1, "malloc failed");
			ctx->args->total += ctx->args->token->s.st_blocks;
		}
	}
	closedir(dir);
	if (errno)
		perror("Readdir");
}

void	sort_tokens(t_token **t, short flag)
{
	*t = get_first_token(*t);
	bubble_sort_token(t, is_flag_set(flag, T), is_flag_set(flag, R));
}

void	print_type(int mode)
{
	int	value;

	value = mode & __S_IFMT;
	if (__S_IFBLK == value)
		ft_printf_fd(1, "b");
	else if (__S_IFCHR == value)
		ft_printf_fd(1, "c");
	else if (__S_IFDIR == value)
		ft_printf_fd(1, "d");
	else if (__S_IFIFO == value)
		ft_printf_fd(1, "p");
	else if (__S_IFLNK == value)
		ft_printf_fd(1, "l");
	else if (__S_IFREG == value)
		ft_printf_fd(1, "-");
	else if (__S_IFSOCK == value)
		ft_printf_fd(1, "s");
	else
		ft_printf_fd(1, "?"); 
}

void	condition_print(int condition, char *true, char *false)
{
	if (condition)
		ft_printf_fd(1, "%s", true);
	else
		ft_printf_fd(1, "%s", false);
}

void	print_permissions(int permissions)
{
	condition_print(permissions & S_IRUSR, "r", "-");
	condition_print(permissions & S_IWUSR, "w", "-");
	condition_print(permissions & S_IXUSR, "x", "-");
	condition_print(permissions & S_IRGRP, "r", "-");
	condition_print(permissions & S_IWGRP, "w", "-");
	condition_print(permissions & S_IXGRP, "x", "-");
	condition_print(permissions & S_IROTH, "r", "-");
	condition_print(permissions & S_IWOTH, "w", "-");
	condition_print(permissions & S_IXOTH, "x", "-");
	ft_printf_fd(1, " ");
}

void	print_time_format(long t)
{
	char	*c_time;
	time_t	time;
	int		count;
	int		i;

	time = t;
	count = 0;
	i = 3;
	c_time = ctime(&time);
	if (!c_time)
	{
		ft_printf_fd(1, "time_error ");
		return;
	}
	while (c_time[++i])
	{
		if (c_time[i] == ':')
			count++;
		if (c_time[i] == ':' && count > 1)
		{
			ft_printf_fd(1, " ");
			return ;
		}
		ft_printf_fd(1, "%c", c_time[i]);
	}
}

void	print_l_flag(struct stat s)
{
	struct passwd	*passwd;
	struct group	*group;

	print_type(s.st_mode);
	print_permissions(s.st_mode);
	ft_printf_fd(1, "%d ", s.st_nlink);
	passwd = getpwuid(s.st_uid);
	if (!passwd)
		ft_printf_fd(1, "%d ", s.st_uid);
	else
		ft_printf_fd(1, "%s ", passwd->pw_name);
	group = getgrgid(s.st_gid);
	if (!group)
		ft_printf_fd(1, "%d ", s.st_gid);
	else
		ft_printf_fd(1, "%s ", group->gr_name);
	ft_printf_fd(1, "%d ", s.st_size);
	print_time_format(s.st_mtime);
}

void	ls_print(t_context *ctx)
{
	bubble_sort_arg(&ctx->args, is_flag_set(ctx->flags_set, R));
	sort_tokens(&ctx->tokens, ctx->flags_set);
	while (ctx->tokens)
	{
		if (is_flag_set(ctx->flags_set, I))
			ft_printf_fd(1, "%d ", ctx->tokens->s.st_ino);
		if (is_flag_set(ctx->flags_set, L))
			print_l_flag(ctx->tokens->s);
		ft_printf_fd(1, "%s", ctx->tokens->name);
		if (!ctx->tokens->next)
		{
			ft_printf_fd(1, "\n");
			if (ctx->args && ctx->args->token)
				ft_printf_fd(1, "\n");
			break;
		}
		else if (is_flag_set(ctx->flags_set, L))
			ft_printf_fd(1, "\n");
		else
			ft_printf_fd(1, "  ");
		ctx->tokens = ctx->tokens->next;
	}
	while (ctx->args)
	{
		if (ctx->args->token)
		{
			sort_tokens(&ctx->args->token, ctx->flags_set);
			if (ctx->args->next || ctx->args->prev)
				ft_printf_fd(1, "%s:\n", ctx->args->name);
			if (is_flag_set(ctx->flags_set, L))
				ft_printf_fd(1, "total %d\n", ctx->args->total / 2);
			while (ctx->args->token)
			{
				if (is_flag_set(ctx->flags_set, I))
					ft_printf_fd(1, "%d ", ctx->args->token->s.st_ino);
				if (is_flag_set(ctx->flags_set, L))
					print_l_flag(ctx->args->token->s);
				ft_printf_fd(1, "%s", ctx->args->token->name);
				if (!ctx->args->token->next)
				{
					ft_printf_fd(1, "\n");
					break;
				}
				else if (is_flag_set(ctx->flags_set, L))
					ft_printf_fd(1, "\n");
				else
					ft_printf_fd(1, "  ");
				ctx->args->token = ctx->args->token->next;
			}
		}
		if (!ctx->args->next)
			break;
		if (ctx->args->token)
			ft_printf_fd(1, "\n", ctx->args->name);
		ctx->args = ctx->args->next;
	}
}

void	dir_parsing(t_context *ctx)
{
	DIR	*dir;

	errno = 0;
	dir = opendir(ctx->args->name);
	if (errno) {
		ft_printf_fd(2, "ft_ls: cannot access '%s': ", ctx->args->name);
		perror(NULL);
		return ;
	}
	fill_dirs_data(ctx, dir);
	return ;
}

void	ft_ls(t_context *ctx)
{
	struct stat	s;

	while (ctx->args)
	{
		errno = 0;
		lstat(ctx->args->name, &s);
		if (errno)
		{
			ft_printf_fd(2, "ft_ls: cannot access '%s': ", ctx->args->name);
			perror(NULL);
		}
		else {
			if ((s.st_mode & __S_IFMT) == __S_IFDIR)
				dir_parsing(ctx);
			else
			{
				if (new_token(&ctx->tokens))
					free_ctx(ctx, 1, "malloc failed");
				ctx->tokens->name = ctx->args->name;
				ctx->tokens->s = s;
				ctx->args->name = NULL;
				remove_arg_node(&ctx->args);
				continue;
			}
		}
		if (!ctx->args || !ctx->args->next)
			break;
		ctx->args = ctx->args->next;
	}
	ctx->args = get_first_arg(ctx->args);
	ls_print(ctx);
}

int main(int ac, char **av)
{
	t_context	ctx;

	ctx.args = NULL;
	ctx.tokens = NULL;
	ctx.flags_set = 0;
	parse_args(ac, av, &ctx);
	ft_ls(&ctx);
	free_ctx(&ctx, 0, NULL);
}