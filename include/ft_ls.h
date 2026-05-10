/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 21:04:03 by mazakov           #+#    #+#             */
/*   Updated: 2026/05/10 21:11:42 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include <dirent.h>
# include <errno.h>
# include <stdio.h>
# include <sys/stat.h>
# include <string.h>
# include <stdlib.h>
# include <dirent.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>

enum e_flags
{
	MR,
	L,
	A,
	R,
	T,
	I
};

typedef struct s_token
{
	char			*name;
	int				type;
	struct stat		s;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_arg
{
	char			*name;
	int				total;
	t_token			*token;
	struct s_arg	*next;
	struct s_arg	*prev;
}	t_arg;

typedef struct s_context
{
	short	flags_set;
	t_arg	*args;
	t_token	*tokens;
}	t_context;

/*
** =========================
** args.c
** =========================
*/

void	parse_args(int ac, char **av, t_context *ctx);
void	set_flags(char **av, t_context *ctx, int i);
void	set_bit(short *flags, int i);
int		is_flag_set(short flag, int i);
void	no_args_given(t_context *ctx);

/*
** =========================
** arg_list.c
** =========================
*/

int		new_arg(t_arg **curr);
int		add_arg_node(t_arg *curr, char *name);
void	remove_arg_node(t_arg **arg);
t_arg	*get_first_arg(t_arg *curr);
void	swap_adjacent_args(t_arg **head, t_arg *a, t_arg *b);

/*
** =========================
** token_list.c
** =========================
*/

int		new_token(t_token **curr);
t_token	*get_first_token(t_token *curr);
void	swap_adjacent_tokens(t_token **head,
			t_token *a,
			t_token *b);
void	sort_tokens(t_token **t, short flag);
int		time_cmp(t_token *t1, t_token *t2);

/*
** =========================
** sorting.c
** =========================
*/

void	bubble_sort_arg(t_arg **head, int reverse);
void	bubble_sort_token(t_token **head,
			int flag,
			int reverse);
int		ft_strcmp_ignore_dot(const char *s1, const char *s2);

/*
** =========================
** path.c
** =========================
*/

char	*create_path(char *dir, char *file);
int		ft_sprintf(char *dst, char *src);

/*
** =========================
** context.c
** =========================
*/

void	rewind_ctx(t_context *ctx);
void	free_tokens(t_token *tokens);
void	free_args(t_arg *args);
void	free_ctx(t_context *ctx, int ret, char *error);

/*
** =========================
** directory.c
** =========================
*/

void	dir_parsing(t_context *ctx);
void	fill_dirs_data(t_context *ctx, DIR *dir);

/*
** =========================
** print_utils.c
** =========================
*/

void	condition_print(int condition, char *true_str, char *false_str);
void	print_type(int mode);
void	print_permissions(int permissions);
void	print_time_format(long t);

/*
** =========================
** print_long_format.c
** =========================
*/

void	print_l_flag(struct stat s);

/*
** =========================
** display.c
** =========================
*/

void	token_print(t_token *tokens, short flags_set, t_arg *args);
void	ls_print(t_context *ctx);

/*
** =========================
** ls.c
** =========================
*/

void	handle_file_as_arg(t_context *ctx, struct stat s);
void	ft_ls(t_context *ctx);

#endif