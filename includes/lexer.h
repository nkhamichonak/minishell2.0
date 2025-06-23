/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 11:27:03 by natallia          #+#    #+#             */
/*   Updated: 2025/04/11 12:09:52 by nkhamich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include "libft.h"
# include "tokens.h"

# define LEXER_DEFAULT 0
# define LEXER_ERROR 1
# define LEXER_CRITICAL_ERROR 2

# define METACHAR ";|$<>\'\"()&"

int		generate_tokens(const char *input, t_token **tokens);
int		handle_and(const char **input, t_token **tokens);
int		handle_parentheses(const char **input, t_token **tokens);
int		handle_pipe_or(const char **input, t_token **tokens);
int		handle_quotes(const char **input, t_token **tokens);
int		handle_redirection(const char **input, t_token **tokens);
int		handle_dollar(const char **input, t_token **tokens);
int		handle_semicolon(const char **input, t_token **tokens);
int		handle_spaces(const char **input, t_token **tokens);
int		handle_word(const char **input, t_token **tokens);
bool	bad_operator(t_token *tokens);
bool	incomplete_command_line(t_token *tokens);
bool	valid_parentheses(t_token *tokens);

#endif
