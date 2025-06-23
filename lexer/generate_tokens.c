/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:48:49 by nkhamich          #+#    #+#             */
/*   Updated: 2025/04/11 12:13:25 by nkhamich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	handle_other_chars(const char **input, t_token **tokens)
{
	if (**input == '$')
		return (handle_dollar(input, tokens));
	else
		return (handle_semicolon(input, tokens));
}

int	generate_tokens(const char *input, t_token **tokens)
{
	int	status;

	status = LEXER_DEFAULT;
	while (*input && status == LEXER_DEFAULT)
	{
		if (*input == '|')
			status = handle_pipe_or(&input, tokens);
		else if (*input == '&')
			status = handle_and(&input, tokens);
		else if (*input == '(' || *input == ')')
			status = handle_parentheses(&input, tokens);
		else if (*input == '>' || *input == '<')
			status = handle_redirection(&input, tokens);
		else if (*input == '\'' || *input == '\"')
			status = handle_quotes(&input, tokens);
		else if (ft_strchr("$;", *input))
			status = handle_other_chars(&input, tokens);
		else if (ft_isspace(*input))
			status = handle_spaces(&input, tokens);
		else
			status = handle_word(&input, tokens);
	}
	if (!status && (!valid_parentheses(*tokens) || bad_operator(*tokens)))
		status = LEXER_ERROR;
	return (status);
}
