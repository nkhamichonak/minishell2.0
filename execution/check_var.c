/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:19:12 by pkhvorov          #+#    #+#             */
/*   Updated: 2025/04/11 13:43:23 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	check_int(char *var)
{
	int	i;

	i = 0;
	if (!var || !ft_isdigit(var[0]))
		return (1);
	while (var[i] != '\0')
	{
		if (!ft_isdigit(var[i]))
			return (1);
		i++;
	}
	return (0);
}

int	check_var(char *var)
{
	int	i;

	if (!var || (!ft_isalpha(var[0]) && var[0] != '_'))
		return (1);
	i = 1;
	while (var[i] != '\0' && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (1);
		i++;
	}
	return (0);
}
