/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:03:54 by pkhvorov          #+#    #+#             */
/*   Updated: 2025/04/10 11:48:37 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	free_ptr(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	free_double_array(char **array)
{
	int	i;

	i = 0;
	if (array != NULL)
	{
		while (array[i] != NULL)
		{
			if (array[i] != NULL)
			{
				free_ptr(array[i]);
				array[i] = NULL;
			}
			i++;
		}
		free(array);
		array = NULL;
	}
}

int	handle_redirection_error(char *file)
{
	if (errno == ENOENT)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putendl_fd(": no such file or directory", 2);
	}
	else if (errno == EACCES)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putendl_fd(": permission denied", 2);
	}
	else if (errno == EISDIR)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putendl_fd(": Is a directory", 2);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putendl_fd(": something goes wrong", 2);
	}
	return (1);
}

int	handle_cd_error(char *dir)
{
	if (errno == ENOENT)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(dir, 2);
		ft_putendl_fd(": no such file or directory", 2);
	}
	else if (errno == EACCES)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(dir, 2);
		ft_putendl_fd(": permission denied", 2);
	}
	else if (errno == ENOTDIR)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(dir, 2);
		ft_putendl_fd(": not a directory", 2);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(dir, 2);
		ft_putendl_fd(": something goes wrong", 2);
	}
	return (1);
}

int	check_limit(int sign, unsigned long long number, int count)
{
	if ((sign == 1 && number > LLONG_MAX) \
		|| (sign == -1 && number > -(unsigned long long)LLONG_MIN)
		|| count > 19)
		return (1);
	return (0);
}
