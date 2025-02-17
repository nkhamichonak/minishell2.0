/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buildin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:57:59 by pkhvorov          #+#    #+#             */
/*   Updated: 2025/02/13 15:29:03 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	check_limit(int sign, unsigned long long number)
{
	if ((sign == 1 && number > LLONG_MAX) \
		|| (sign == -1 && number > -(unsigned long long)LLONG_MIN))
		return (1);
	return (0);
}

long long	ft_atoll_with_check(const char *str)
{
	unsigned long long	number;
	int			i;
	int			sign;

	number = 0;
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
	while (str[i] != '\0' && str[i] >= 48 && str[i] <= 57)
	{
		number = number * 10;
		number = number + str[i] - 48;
		if (check_limit(sign, number) == 1)
			return (1); // Place for error handle
		i++;
	}
	return (sign * number);
}

int get_exit_code(char *str)
{
	int	i;
	long long int	num; //-9223372036854775808 : 9223372036854775807
// bash: line 1: exit: 9223372036854775808: numeric argument required

	i = 0;
	while (ft_isspace(str[i]) != 0)
		i++;
	if (str[i] == '\0')
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0) //bash: line 1: exit: 922t: numeric argument required
			return (0);
		i++;
	}
	num = ft_atoll_with_check(str);
	return (num % 256);
}

int ft_buildin_exit(char **args)
{
	int exit_code;
	
	if(args[2] != NULL)
		return (0); //worng number of args
	else if (args == NULL || args[1] == NULL)
		exit_code = 0; //= global exit code
	else
	{
		exit_code = get_exit_code(args[1]);
	}
	exit(exit_code);
	return(2);
}