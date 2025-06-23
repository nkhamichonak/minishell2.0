/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natallia <natallia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:57:59 by pkhvorov          #+#    #+#             */
/*   Updated: 2025/04/09 20:06:44 by natallia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static long long	parse_digits_with_check(const char *str, int sign, int i)
{
	unsigned long long	number;
	int					count;

	number = 0;
	count = 0;
	while (str[i] != '\0' && str[i] >= 48 && str[i] <= 57)
	{
		number = number * 10 + (str[i] - '0');
		count++;
		if (check_limit(sign, number, count))
		{
			errno = ERANGE;
			return (errno);
		}
		i++;
	}
	return (sign * number);
}

static long long	ft_atoll_with_check(const char *str)
{
	int					i;
	int					sign;

	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
	{
		i++;
	}
	if (str[i] != '\0' && (str[i] == 43 || str[i] == 45))
	{
		if (str[i] == 45)
			sign = -1;
		i++;
	}
	return (parse_digits_with_check(str, sign, i));
}

static int	get_exit_code(char *str)
{
	int				i;
	long long int	num;

	i = 0;
	while (ft_isspace(str[i]) != 0)
		i++;
	if (str[i] == '\0')
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0)
		{
			errno = ERANGE;
			return (errno);
		}
		i++;
	}
	num = ft_atoll_with_check(str);
	return (num % 256);
}

static int	handle_exit_error(t_executer *exec, char **args)
{
	if (check_int(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		exec->isexit = 1;
		return (2);
	}
	else
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (EXIT_FAILURE);
	}
}

int	ft_builtin_exit(t_executer *exec, char **args)
{
	int	exit_code;

	if (args == NULL || args[1] == NULL)
	{
		exec->isexit = 1;
		return (exec->vars->exit_status);
	}
	else if (args[1][0] == '\0' || args[2] != NULL)
		return (handle_exit_error(exec, args));
	exit_code = get_exit_code(args[1]);
	if (errno == ERANGE)
	{
		errno = 0;
		exec->isexit = 1;
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		return (2);
	}
	exec->isexit = 1;
	return (exit_code);
}
