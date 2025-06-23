/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:13:19 by pkhvorov          #+#    #+#             */
/*   Updated: 2025/04/11 12:24:25 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_redirection_out(t_executer *exec, t_redirect *redirects)
{
	int	fd_out;

	fd_out = open(redirects->filename, \
		O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
		return (handle_redirection_error(redirects->filename));
	close(exec->out_fd);
	exec->out_fd = fd_out;
	return (0);
}

int	ft_redirection_append(t_executer *exec, t_redirect *redirects)
{
	int	fd_out;

	fd_out = open(redirects->filename, \
		O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_out == -1)
		return (handle_redirection_error(redirects->filename));
	close(exec->out_fd);
	exec->out_fd = fd_out;
	return (0);
}

int	ft_redirection_in(t_executer *exec, t_redirect *redirects)
{
	int	fd_in;

	fd_in = open(redirects->filename, O_RDONLY);
	if (fd_in == -1)
		return (handle_redirection_error(redirects->filename));
	close(exec->in_fd);
	exec->in_fd = fd_in;
	return (0);
}

t_redirect	*ft_reverse_redirection(t_redirect *redirects)
{
	t_redirect	*redir;
	t_redirect	*temp;

	redir = NULL;
	while (redirects)
	{
		temp = malloc(sizeof(t_redirect));
		if (temp == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		*temp = *redirects;
		temp->next = redir;
		redir = temp;
		redirects = redirects->next;
	}
	return (redir);
}

int	ft_redirection(t_executer *exec, t_ast_node *node)
{
	t_redirect	*redirections;
	t_redirect	*save;

	redirections = ft_reverse_redirection(node->cmd->redirects);
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
