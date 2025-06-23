/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_group.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:13:19 by pkhvorov          #+#    #+#             */
/*   Updated: 2025/04/11 13:28:05 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_redirection_group(t_executer *exec, t_ast_node *node)
{
	t_redirect	*redirections;
	t_redirect	*save;

	redirections = ft_reverse_redirection(node->group_redirs);
	save = redirections;
	while (redirections)
	{
		if (redirections->redir_type == REDIR_OUT)
			exec->red_status = ft_redirection_out(exec, redirections);
		else if (redirections->redir_type == APPEND)
			exec->red_status = ft_redirection_append(exec, redirections);
		else if (redirections->redir_type == REDIR_IN)
			exec->red_status = ft_redirection_in(exec, redirections);
		else if (redirections->redir_type == HEREDOC && exec->red_status != 130)
			exec->red_status = ft_redirection_heredoc(exec, redirections, save);
		redirections = redirections->next;
	}
	ft_free_redirects(save);
	return (exec->red_status);
}
