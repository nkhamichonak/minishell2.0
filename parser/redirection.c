/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:51:41 by natallia          #+#    #+#             */
/*   Updated: 2025/04/13 12:13:37 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	is_valid_redirection(t_token *token, int *status)
{
	if (token->type == REDIR_IN || token->type == REDIR_OUT
		|| token->type == HEREDOC || token->type == APPEND)
	{
		if (token->next && token->next->type == SPACE)
			token = token->next;
		if (token-> next && (token->next->type == WORD
				|| token->next->type == STR_SINGLE_Q
				|| token->next->type == STR_DOUBLE_Q
				|| token->next->type == VARIABLE))
			return (true);
		else
		{
			*status = PARSER_ERROR;
			if (token->next)
				mshell_putendl_fd(ERR_TKN, token->next->value, 2);
			else
				mshell_putendl_fd(ERR_TKN, "newline", 2);
			return (false);
		}
	}
	return (false);
}

int	add_grp_redir(t_ast_node *node, t_token **token, t_token *end)
{
	t_redirect	*new_redir;
	t_token		*temp;

	new_redir = malloc(sizeof(t_redirect));
	if (new_redir == NULL)
		return (PARSER_CRITICAL_ERROR);
	new_redir->redir_type = (*token)->type;
	new_redir->quoted = false;
	if ((*token)->next->type == SPACE)
		(*token) = (*token)->next;
	temp = (*token)->next;
	new_redir->filename = concatenate_tokens(&temp, end, &new_redir->quoted);
	if (new_redir->filename == NULL)
		return (free(new_redir), PARSER_CRITICAL_ERROR);
	new_redir->next = node->group_redirs;
	node->group_redirs = new_redir;
	*token = temp;
	return (PARSER_DEFAULT);
}

int	add_cmd_redir(t_ast_node *node, t_token **token, t_token *end)
{
	t_redirect	*new_redir;
	t_token		*temp;

	new_redir = malloc(sizeof(t_redirect));
	if (new_redir == NULL)
		return (PARSER_CRITICAL_ERROR);
	new_redir->redir_type = (*token)->type;
	new_redir->quoted = false;
	if ((*token)->next->type == SPACE)
		*token = (*token)->next;
	temp = (*token)->next;
	new_redir->filename = concatenate_tokens(&temp, end, &new_redir->quoted);
	if (new_redir->filename == NULL)
		return (free(new_redir), PARSER_CRITICAL_ERROR);
	new_redir->next = node->cmd->redirects;
	node->cmd->redirects = new_redir;
	*token = temp;
	return (PARSER_DEFAULT);
}
