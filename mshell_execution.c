/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:02:50 by pkhvorov          #+#    #+#             */
/*   Updated: 2025/04/09 14:41:57 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mshell_phase	mshell_execution(t_mshell *mshell)
{
	mshell->vars.exit_status = g_signal;
	mshell->vars.exit_status = ft_execution(&mshell->exec, mshell->ast);
	ignore_ctrl_c();
	free_ast(&mshell->ast);
	if (mshell->exec.isexit)
		return (MINISHELL_CLEANUP);
	return (MINISHELL_READLINE);
}
