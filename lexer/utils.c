/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:45:42 by nkhamich          #+#    #+#             */
/*   Updated: 2025/04/11 12:10:00 by nkhamich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

bool	bad_operator(t_token *tokens)
{
	t_token	*first;

	if (tokens == NULL)
		return (false);
	first = NULL;
	while (tokens)
	{
		if (tokens->type != SPACE)
		{
			first = tokens;
			break ;
		}
		tokens = tokens->next;
	}
	if (!first)
		return (false);
	if (first->type == AND || first->type == OR
		|| first->type == PIPE || first->type == SEMICOLON)
	{
		mshell_putendl_fd(ERR_TKN, first->value, 2);
		return (true);
	}
	return (false);
}

bool	incomplete_command_line(t_token *tokens)
{
	t_token	*last;
	t_token	*prev;

	if (tokens == NULL)
		return (false);
	last = NULL;
	prev = NULL;
	while (tokens)
	{
		if (tokens->type != SPACE)
		{
			prev = last;
			last = tokens;
		}
		tokens = tokens->next;
	}
	if (!last)
		return (false);
	if ((last->type == AND || last->type == OR || last->type == PIPE)
		&& (prev && prev->type != REDIR_OUT && prev->type != REDIR_IN
			&& prev->type != APPEND && prev->type != HEREDOC))
		return (true);
	return (false);
}
