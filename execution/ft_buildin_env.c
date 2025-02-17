/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buildin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:55:08 by pkhvorov          #+#    #+#             */
/*   Updated: 2025/02/13 14:56:00 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int ft_buildin_env(t_executer *exec) //(char **env, char **args)
{
	int	i;
	
	// if (args != NULL && args[1] != NULL)
	// 	return (error_message());
	i = 0;
	if (exec->env == NULL)
		return (EXIT_FAILURE);
	while (exec->env[i] != NULL)
	{
		ft_putendl_fd(exec->env[i], STDOUT_FILENO);
		i++;		
	}
	return (EXIT_SUCCESS);
}