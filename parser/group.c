/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:47:55 by nkhamich          #+#    #+#             */
/*   Updated: 2025/04/09 15:56:10 by nkhamich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static bool	has_unexpected_token(t_token *token, int status)
{
	if (!status && token && token->type != SPACE && token->type != PAREN_OPEN)
	{
		mshell_putendl_fd(ERR_TKN, token->value, 2);
		return (true);
	}
	return (false);
}

static int	process_redirection(t_token **token, t_token *end,
	t_ast_node *node, int last_paren)
{
	int	status;

	status = PARSER_DEFAULT;
	if (!last_paren)
	{
		mshell_putendl_fd(ERR_TKN, "(", 2);
		status = PARSER_ERROR;
		return (status);
	}
	status = add_grp_redir(node, token, end);
	return (status);
}

static void	update_balance(t_token *token, int *balance, int *last_paren)
{
	if (token->type == PAREN_OPEN)
		(*balance)++;
	else if (token->type == PAREN_CLOSE)
	{
		(*balance)--;
		if (*balance == 0)
			*last_paren = 1;
	}
}

static bool	check_for_strays(t_token *token, t_token *end, t_ast_node *node)
{
	int	balance;
	int	last_paren;
	int	status;

	balance = 0;
	last_paren = 0;
	status = PARSER_DEFAULT;
	while (token != end)
	{
		if (balance == 0 || last_paren == 1)
		{
			if (is_valid_redirection(token, &status))
			{
				status = process_redirection(&token, end, node, last_paren);
				if (status != PARSER_DEFAULT || token == end)
					break ;
			}
			if (has_unexpected_token(token, status))
				return (PARSER_ERROR);
		}
		update_balance(token, &balance, &last_paren);
		token = token->next;
	}
	return (status);
}

t_ast_node	*process_group(t_token *start, t_token *end, int *status)
{
	t_token		*group_start;
	t_token		*group_end;
	t_ast_node	*node;

	node = create_ast_node(NODE_GROUP);
	if (node == NULL)
	{
		*status = PARSER_CRITICAL_ERROR;
		return (NULL);
	}
	*status = check_for_strays(start, end, node);
	if (*status != PARSER_DEFAULT)
	{
		free_ast_node(&node);
		return (NULL);
	}
	group_start = skip_open_paren(start, end);
	group_end = get_close_paren(start, end);
	node->subtree = build_ast(group_start, group_end, status);
	return (node);
}
