/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:32:44 by nkhamich          #+#    #+#             */
/*   Updated: 2025/04/14 12:30:14 by nkhamich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"

void	expand_exit_var(t_token *token, int exit_status, int *status)
{
	free(token->value);
	token->value = ft_itoa(exit_status);
	if (token->value == NULL)
	{
		*status = ENVP_CRITICAL_ERROR;
		return ;
	}
	token->type = WORD;
}

void	expand_var(t_token **head, t_token *token, char **g_vars, int *status)
{
	char	*expanded_value;
	t_token	*prev;

	if (!*head || !token || !g_vars)
		return ;
	expanded_value = get_env_value(g_vars, token->value + 1);
	if (expanded_value[0] == '\0')
	{
		prev = get_previous_token(*head, token);
		remove_token(head, token, prev);
	}
	else
	{
		free(token->value);
		token->value = ft_strdup(expanded_value);
		if (token->value == NULL)
		{
			*status = ENVP_CRITICAL_ERROR;
			return ;
		}
		token->type = WORD;
	}
}

bool	is_heredoc_delimiter(t_token *tokens, t_token *temp)
{
	t_token	*prev;

	prev = NULL;
	while (tokens && tokens != temp)
	{
		if (tokens->type != SPACE)
			prev = tokens;
		tokens = tokens->next;
	}
	if (prev && prev->type == HEREDOC)
		return (true);
	return (false);
}

void	parse_variables(t_token **tokens, t_vars vars, int *status)
{
	t_token	*temp;
	t_token	**head;

	head = tokens;
	temp = *tokens;
	while (temp && *status == ENVP_DEFAULT)
	{
		if (temp->type == VARIABLE && !is_heredoc_delimiter(*tokens, temp))
		{
			if (*(temp->value + 1) == '?')
				expand_exit_var(temp, vars.exit_status, status);
			else
			{
				expand_var(head, temp, vars.global_vars, status);
				temp = *tokens;
				continue ;
			}
		}
		else if (temp->type == STR_DOUBLE_Q && ft_strchr(temp->value, '$')
			&& !is_heredoc_delimiter(*tokens, temp))
			expand_quoted_str(temp, vars, status);
		if (temp)
			temp = temp->next;
	}
}
