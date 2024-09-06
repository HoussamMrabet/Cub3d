/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays_h.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hamd <mel-hamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:53:05 by mel-hamd          #+#    #+#             */
/*   Updated: 2024/09/06 15:11:50 by mel-hamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"




double	get_angle(double ang)
{
	ang = fmod(ang, 2 * M_PI);
	if (ang < 0)
		ang = ang + (2 * M_PI);
	return (ang);
}

void	cast_ray(t_cub3d *c, double ang)
{
	double	stepx;
	double	stepy;
	int		distance;
	t_corr	intercept;
	int		is_r_down;
	int		is_r_left;
	// t_corr	next;	
	double	tmp;

	if (ang >= 0 && ang <= M_PI)
		is_r_down = 1;
	else
		is_r_down = 0;
	if (ang <= (M_PI / 2) || ang >= (3 * M_PI / 2))
		is_r_left = 0;
	else
		is_r_left = 1;
	intercept.y = floor(c->p.c.y / US) * US;
	distance = 0;
	if (is_r_down)
		intercept.y += US;
	intercept.x = c->p.c.x + ((intercept.y - c->p.c.y) / tan(ang));
	stepy = US;
	if (!is_r_down)
		stepy *= -1;
	stepx = stepy / tan(ang);
	if ((!is_r_left && stepx < 0) || (is_r_left && stepx > 0))
		stepx *= -1;
	
	while (intercept.x >= 0 && (int)(intercept.x / US) < c->map.width && intercept.y >= 0 && (int)(intercept.y / US) < c->map.height)
	{
		if (is_r_down)
			tmp = intercept.y + 1;
		else
			tmp = intercept.y - 1;
		// mlx_put_pixel(c->img, intercept.x, intercept.y - 1, ft_create_color(0, 255, 0, 255));
		// mlx_put_pixel(c->img, intercept.x, intercept.y + 1, ft_create_color(0, 255, 0, 255));
		// mlx_put_pixel(c->img, intercept.x + 1, intercept.y, ft_create_color(0, 255, 0, 255));
		// mlx_put_pixel(c->img, intercept.x - 1, intercept.y, ft_create_color(0, 255, 0, 255));
		if (c->map.map[(int)(tmp / US)][(int)(intercept.x / US)] == '1')
		{
			distance = sqrt((intercept.x - c->p.c.x) * (intercept.x - c->p.c.x) + (intercept.y - c->p.c.y) * (intercept.y - c->p.c.y));
			put_line_v2(c->p.c, distance, ang, c);	
			break;
		}else{
		intercept.x += stepx;
		intercept.y += stepy;
		}
	}
	// printf("is down : %d || is left : %d\n", is_r_down, is_r_left);
	// printf("%d sksk\n", distance);
}
