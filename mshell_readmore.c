/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell_readmore.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 20:17:35 by natallia          #+#    #+#             */
/*   Updated: 2025/04/14 13:09:33 by nkhamich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_handler_readmore(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	ft_putendl_fd("", STDOUT_FILENO);
	close(STDIN_FILENO);
}

static void	ignore_ctrl_c_readmore(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_handler_readmore;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

static void	cleanup_readmore_ctrl_d(t_mshell *mshell)
{
	ft_putendl_fd(ERR_EOF, 2);
	mshell->vars.exit_status = 2;
	free_tokens(&mshell->tokens);
}

static bool	cleanup_readmore_ctrl_c(t_mshell *mshell, int saved_stdin)
{
	if (dup2(saved_stdin, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2 failed");
		return (false);
	}
	mshell->vars.exit_status = 130;
	g_signal = 0;
	free_tokens(&mshell->tokens);
	return (true);
}

t_mshell_phase	mshell_readmore(t_mshell *mshell)
{
	char	*prompt;
	int		saved_stdin;

	prompt = "> ";
	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdin == -1)
		return (perror("minishell: dup failed"), MINISHELL_CLEANUP);
	ignore_ctrl_c_readmore();
	rl_on_new_line();
	mshell->input = readline(prompt);
	if (mshell->input == NULL && g_signal == SIGINT)
	{
		if (!cleanup_readmore_ctrl_c(mshell, saved_stdin))
			return (close(saved_stdin), MINISHELL_CLEANUP);
		return (close(saved_stdin), MINISHELL_READLINE);
	}
	if (mshell->input == NULL)
	{
		cleanup_readmore_ctrl_d(mshell);
		return (close(saved_stdin), MINISHELL_CLEANUP);
	}
	if (mshell->input[0])
		add_history(mshell->input);
	return (close(saved_stdin), MINISHELL_LEXER);
}
