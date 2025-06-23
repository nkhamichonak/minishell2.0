/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:18:08 by nkhamich          #+#    #+#             */
/*   Updated: 2025/04/13 12:12:45 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# include "libft.h"
# include <dirent.h>

# define ERR_TKN "minishell: syntax error near unexpected token "

typedef enum e_token_type
{
	SEMICOLON,
	PAREN_OPEN,
	PAREN_CLOSE,
	AND,
	OR,
	PIPE,
	WORD,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	VARIABLE,
	STR_DOUBLE_Q,
	STR_SINGLE_Q,
	SPACE
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

t_token	*get_last_token(t_token *token_lst);
t_token	*get_previous_token(t_token *head, t_token *target);
t_token	*create_token(t_token_type type, const char *value);
char	*concatenate_tokens(t_token **token, t_token *end, bool *quoted);
void	append_token(t_token **token_lst, t_token *new);
void	remove_token(t_token **head, t_token *target, t_token *prev);
void	insert_sublist(t_token **head, t_token *temp, t_token *sublst);
void	print_tokens(t_token *tokens);
void	free_tokens(t_token **tokens);
void	free_one_token(t_token **token);
void	mshell_putendl_fd(char *str, char *detail, int fd);

#endif
