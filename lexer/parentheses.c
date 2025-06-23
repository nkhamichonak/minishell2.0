/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parentheses.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:29:04 by natallia          #+#    #+#             */
/*   Updated: 2025/04/01 12:43:22 by nkhamich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static bool	parentheses_msg(char paren)
{
	if (paren == ')')
		ft_putendl_fd("minishell: syntax error near"
			" unexpected token ')'", 2);
	else
		ft_putendl_fd("minishell: syntax error near"
			" unexpected token '('", 2);
	return (false);
}

bool	valid_parentheses(t_token *tokens)
{
	int		balance;

	balance = 0;
	while (tokens != NULL)
	{
		if (tokens->type == PAREN_OPEN)
			balance++;
		else if (tokens->type == PAREN_CLOSE)
		{
			balance--;
			if (balance < 0)
				return (parentheses_msg(')'));
		}
		tokens = tokens->next;
	}
	if (balance != 0)
		return (parentheses_msg('('));
	else
		return (true);
}

int	handle_parentheses(const char **input, t_token **tokens)
{
	t_token		*new_token;

	if (**input == '(')
		new_token = create_token(PAREN_OPEN, "(");
	else
		new_token = create_token(PAREN_CLOSE, ")");
	if (new_token == NULL)
		return (LEXER_CRITICAL_ERROR);
	append_token(tokens, new_token);
	(*input)++;
	return (LEXER_DEFAULT);
}
