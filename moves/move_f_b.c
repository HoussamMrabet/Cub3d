/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_f_b.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hamd <mel-hamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:41:12 by mel-hamd          #+#    #+#             */
/*   Updated: 2024/09/02 19:06:01 by mel-hamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_f_b(t_cub3d *c)
{
	double	ang;
	double	tmp;
	double	tmp2;
	double	r;

	r = c->p.rad / 2;
	ang = c->p.rot_ang;
	tmp = c->p.c.x + c->p.ms * cos(ang) * c->p.wd;
	tmp2 = c->p.c.y + c->p.ms * sin(ang) * c->p.wd;
	if (c->map.map[(int)((tmp2) / US)][(int)((tmp + r) / US)] == '1')
		return ;
	else if (c->map.map[(int)((tmp2) / US)][(int)((tmp - r) / US)] == '1')
		return ;
	else if (c->map.map[(int)((tmp2 + r) / US)][(int)((tmp) / US)] == '1')
		return ;
	else if (c->map.map[(int)((tmp2 - r) / US)][(int)((tmp) / US)] == '1')
		return ;
	c->p.c.y = tmp2;
	c->p.c.x = tmp;
}

