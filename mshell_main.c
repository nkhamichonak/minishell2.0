/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 13:34:07 by natallia          #+#    #+#             */
/*   Updated: 2025/04/13 20:21:11 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

int	main(int argc, char **argv, char **envp)
{
	t_mshell		mshell;
	t_mshell_phase	phase;

	((void)argc, (void)argv);
	phase = mshell_start(&mshell, envp);
	while (phase != MINISHELL_EXIT)
	{
		ignore_ctrl_c();
		if (phase == MINISHELL_READLINE)
			phase = mshell_readline(&mshell);
		else if (phase == MINISHELL_READMORE)
			phase = mshell_readmore(&mshell);
		else if (phase == MINISHELL_LEXER)
			phase = mshell_lexer(&mshell);
		else if (phase == MINISHELL_PARSER)
			phase = mshell_parser(&mshell);
		else if (phase == MINISHELL_EXECUTER)
			phase = mshell_execution(&mshell);
		else if (phase == MINISHELL_CLEANUP)
			phase = mshell_cleanup(&mshell);
	}
	ft_putendl_fd("exit", 1);
	return (mshell.vars.exit_status);
}
