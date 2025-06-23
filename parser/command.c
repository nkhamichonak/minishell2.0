/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:40:48 by nkhamich          #+#    #+#             */
/*   Updated: 2025/04/13 12:18:36 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	add_command_name(t_ast_node *node, t_token **token, t_token *end)
{
	char	*command_name;
	bool	quoted;

	quoted = false;
	command_name = concatenate_tokens(token, end, &quoted);
	if (command_name == NULL)
		return (PARSER_CRITICAL_ERROR);
	node->cmd->cmd_name = command_name;
	node->cmd->args = malloc(2 * sizeof(char *));
	if (node->cmd->args == NULL)
		return (PARSER_CRITICAL_ERROR);
	node->cmd->args[0] = ft_strdup(command_name);
	if (node->cmd->args[0] == NULL)
		return (PARSER_CRITICAL_ERROR);
	node->cmd->args[1] = NULL;
	return (PARSER_DEFAULT);
}

t_ast_node	*process_command(t_token *token, t_token *end, int *status)
{
	t_ast_node	*node;

	node = create_ast_node(NODE_COMMAND);
	if (node == NULL)
		return (*status = PARSER_CRITICAL_ERROR, NULL);
	while (token != end && *status == PARSER_DEFAULT)
	{
		if (token->type == SPACE)
			;
		else if (is_valid_assignment(token) && node->cmd->cmd_name == NULL)
			*status = add_assignment(node, &token, end);
		else if (is_valid_redirection(token, status) && !(*status))
			*status = add_cmd_redir(node, &token, end);
		else if (node->cmd->cmd_name == NULL && !(*status))
			*status = add_command_name(node, &token, end);
		else if (!(*status))
			*status = add_argument(node->cmd, &token, end);
		if (token != end)
			token = token->next;
	}
	return (node);
}
