/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays_v_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hamd <mel-hamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:41:49 by mel-hamd          #+#    #+#             */
/*   Updated: 2024/11/11 14:10:54 by mel-hamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static inline t_bool	condition(t_cub3d *c, t_corr i, double tmp)
{
	return (floor(tmp / US) < c->map.width
		&& (int)floor(i.y / US) < c->map.height
		&& (int)floor(i.y / US) >= 0 && floor(tmp / US) >= 0
		&& (c->map.map[(int)floor(i.y / US)][(int)floor(tmp / US)] == '1'
		|| ((c->map.map[(int)floor(i.y / US)][(int)floor(tmp / US)] == 'D' && (int)floor(fmod(i.y , US)) >= ft_get_door(c, (int)floor(tmp / US ), (int)floor(i.y / US))->progress))));
																				//  (int)floor(fmod(i.x , US)) >= ft_get_door(c, (int)floor(i.x / US ), (int)floor(tmp / US))->progress))))
}

t_ray	cast_ray_v(double ang, int is_down, int is_left, t_cub3d *c)
{
	double	step[2];
	t_ray	ray;
	t_corr	intercept;
	double	tmp;

	intercept.x = floor(c->p.c.x / US) * US;
	if (!is_left)
		intercept.x += US;
	intercept.y = c->p.c.y + ((intercept.x - c->p.c.x) * tan(ang));
	setup_steps_v(step, is_down, is_left, ang);
	while (cast_condition(intercept, c))
	{
		if (is_left)
			tmp = intercept.x - 1;
		else
			tmp = intercept.x + 1;
		if (condition(c, intercept, tmp))
		{
			ray.distance = calc_distance(intercept, c->p.c);
			ray.is_door = c->map.map[(int)floor(intercept.y / US)][(int)floor(tmp / US)] == 'D';
			return (ray.is_w_hited = 1, ray.hit_wall = intercept, ray);
		}
		intercept.x += step[0];
		intercept.y += step[1];
	}
	return (ray.is_w_hited = 0, ray);
}
