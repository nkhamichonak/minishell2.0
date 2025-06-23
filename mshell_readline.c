/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell_readline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 12:19:47 by natallia          #+#    #+#             */
/*   Updated: 2025/04/14 13:09:58 by nkhamich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mshell_phase	mshell_readline(t_mshell *mshell)
{
	char	*prompt;

	prompt = "minishell> ";
	ignore_ctrl_c();
	rl_on_new_line();
	mshell->input = readline(prompt);
	if (g_signal == SIGINT)
	{
		mshell->vars.exit_status = 130;
		g_signal = 0;
	}
	if (mshell->input == NULL)
		return (MINISHELL_CLEANUP);
	if (mshell->input[0])
		add_history(mshell->input);
	return (MINISHELL_LEXER);
}
