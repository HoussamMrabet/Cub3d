/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_rays_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmrabet <hmrabet@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:44:11 by mel-hamd          #+#    #+#             */
/*   Updated: 2024/10/30 12:17:04 by hmrabet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_ray	which_ray(double ang, t_cub3d *c)
{
	int		ang_dir[2];
	t_ray	r1;
	t_ray	r2;

	get_angl_direction(&ang_dir[0], &ang_dir[1], get_angle(ang));
	r1 = cast_ray_h(c, get_angle(ang), ang_dir[0], ang_dir[1]);
	r1.type = 'h';
	r1.ang = get_angle(ang);
	r1.distance *= cos(get_angle(c->p.rot_ang) - ang);
	r2 = cast_ray_v(get_angle(ang), ang_dir[0], ang_dir[1], c);
	r2.type = 'v';
	r2.ang = get_angle(ang);
	r2.distance *= cos(get_angle(c->p.rot_ang) - ang);
	if (r1.is_w_hited && r2.is_w_hited)
	{
		if (r1.distance < r2.distance)
			return (r1);
		return (r2);
	}
	if (r1.is_w_hited)
		return (r1);
	return (r2);
}

int	ft_texture_color(unsigned int c)
{
	int	r;
	int	g;
	int	b;
	int	a;

	a = c % 256;
	c /= 256;
	b = c % 256;
	c /= 256;
	g = c % 256;
	c /= 256;
	r = c;
	return (ft_create_color(a, b, g, r));
}

void	draw_wall(t_cub3d *cub, t_corr *c)
{
	int		r_down;
	int		r_left;

	cub->wall.start = (H_SIZE / 2 - cub->wall.o_wall_h / 2);
	if (cub->wall.start < 0)
		cub->wall.start = 0;
	cub->wall.end = (H_SIZE / 2 + cub->wall.o_wall_h / 2);
	if (cub->wall.end >= H_SIZE)
		cub->wall.end = H_SIZE;
	get_angl_direction(&r_down, &r_left, cub->ray.ang);
	if (r_left && cub->ray.type == 'v')
		cub->wall.png = cub->wall_e;
	else if (!r_left && cub->ray.type == 'v')
		cub->wall.png = cub->wall_w;
	else if (r_down && cub->ray.type == 'h')
		cub->wall.png = cub->wall_n;
	else if (!r_down && cub->ray.type == 'h')
		cub->wall.png = cub->wall_s;
	draw_textures(cub, c->x);
}

void	draw_ceiling(t_cub3d *cub)
{
    int			x;
	int			y;
    int			ceiling_index;
    uint32_t	ceiling_color;
	int			offset_x;
	int			offset_y;
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;
	uint8_t		a;
	
	y = -1;
    while (++y < H_SIZE / 2)
    {
		x = -1;
        while (++x < W_SIZE)
        {
            offset_x = (x * cub->sky->width) / W_SIZE;
            offset_y = (y * cub->sky->height) / (H_SIZE / 2);
            ceiling_index = (offset_y * cub->sky->width + offset_x) * cub->sky->bytes_per_pixel;
            r = cub->sky->pixels[ceiling_index];
            g = cub->sky->pixels[ceiling_index + 1];
            b = cub->sky->pixels[ceiling_index + 2];
            a = cub->sky->pixels[ceiling_index + 3];
            ceiling_color = (r << 24 | g << 16 | b << 8 | a);
            mlx_put_pixel(cub->img, x, y, ceiling_color);
        }
    }
}

// void	draw_floor(t_cub3d *cub)
// {
//     int			x;
// 	int			y;
//     int			floor_index;
//     uint32_t	floor_color;
// 	int			offset_x;
// 	int			offset_y;
// 	uint8_t		r;
// 	uint8_t		g;
// 	uint8_t		b;
// 	uint8_t		a;

// 	y = (H_SIZE / 2) - 1;
//     while (++y < H_SIZE)
//     {
// 		x = -1;
//         while (++x < W_SIZE)
//         {
//             offset_x = (x * cub->floor->width) / W_SIZE;
//             offset_y = ((y - H_SIZE / 2) * cub->floor->height) / (H_SIZE / 2);
//             floor_index = (offset_y * cub->floor->width + offset_x) * cub->floor->bytes_per_pixel;
//             r = cub->floor->pixels[floor_index];
//             g = cub->floor->pixels[floor_index + 1];
//             b = cub->floor->pixels[floor_index + 2];
//             a = cub->floor->pixels[floor_index + 3];
//             floor_color = (r << 24 | g << 16 | b << 8 | a);
//             mlx_put_pixel(cub->img, x, y, floor_color);
//         }
//     }
// }


void	print_rays(t_cub3d *cub)
{
	double	stp_ray;
	double	str_ang;
	t_corr	c;

	1 && (stp_ray = FOV / W_SIZE, c.y = 0, c.x = 0);
	str_ang = cub->p.rot_ang - (FOV / 2);
	draw_ceiling(cub);
	// draw_floor(cub);
	while (c.x < W_SIZE)
	{
		cub->ray = which_ray(str_ang, cub);
		(1) && (cub->wall.wall_h = (US * H_SIZE) / cub->ray.distance);
		cub->wall.o_wall_h = cub->wall.wall_h;
		(!cub->ray.distance || cub->wall.wall_h > H_SIZE)
			&& (cub->wall.wall_h = H_SIZE);
		// 1 && (c.y = 0, c.color = ft_create_color(cub->map.c_rgb[0] * 0.2,
		// 		cub->map.c_rgb[1] * 0.2, cub->map.c_rgb[2] * 0.2, 200));
		// put_line_v2(c, floor(H_SIZE / 2 - cub->wall.wall_h / 2), M_PI / 2, cub);
		c.y = floor(H_SIZE / 2 + cub->wall.wall_h / 2);
		c.color = ft_create_color(cub->map.f_rgb[0] * 0.2,
				cub->map.f_rgb[1] * 0.2, cub->map.f_rgb[2] * 0.2, 160);
		if (H_SIZE / 2 + cub->wall.wall_h / 2 < H_SIZE)
			put_line_v2(c, floor(H_SIZE / 2 + cub->wall.wall_h / 2),
				M_PI / 2, cub);
		draw_wall(cub, &c);
		1 && (c.x++, str_ang += stp_ray);
	}
}