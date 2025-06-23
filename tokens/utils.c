/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhamich <nkhamich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:44:20 by nkhamich          #+#    #+#             */
/*   Updated: 2025/04/09 12:44:42 by nkhamich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

void	mshell_putendl_fd(char *str, char *detail, int fd)
{
	if (!str || !detail)
		return ;
	write (fd, str, ft_strlen(str));
	write (fd, "'", 1);
	write (fd, detail, ft_strlen(detail));
	write (fd, "'", 1);
	write (fd, "\n", 1);
}
