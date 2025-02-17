/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buildin_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:40:12 by pkhvorov          #+#    #+#             */
/*   Updated: 2025/02/11 15:40:45 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int ft_buildin_pwd() //(char **args)
{
	char	*buffer;
	char	*cwd;

	// if (args != NULL && args[1] != NULL)
	// 	return (error_message());
	buffer = NULL;
	// if (struct->pwd != NULL)
	// {
	// 	ft_putendl_fd(struct->pwd, STDOUT_FILENO);
	// 	return(EXIT_SUCCESS);
	// }
	cwd = getcwd(buffer, PATH_MAX);
	if (cwd != NULL)
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		return(EXIT_SUCCESS);
	}
	// error_message();
	return(EXIT_FAILURE);
}