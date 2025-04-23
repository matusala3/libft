/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:23:18 by magebreh          #+#    #+#             */
/*   Updated: 2025/04/22 12:25:55 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// it doesnt have to return 1 if s is printable character can return any value 
int	ft_isprint(int s)
{
	int	rtn;

	rtn = 0;
	if (s > 31 && s < 127)
		rtn = 16384;
	return (rtn);
}
