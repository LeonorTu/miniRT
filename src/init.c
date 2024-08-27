/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:17:28 by jtu               #+#    #+#             */
/*   Updated: 2024/08/27 18:17:29 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

static void	start_mlx(int width, int height)
{
	rtx()->width = width;
	rtx()->height = height;
	if (!rtx()->mlx)
	{
		rtx()->mlx = mlx_init(width, height, "miniRT", 1);
		if (!rtx()->mlx)
			error(E_MLX, NULL);
	}
	if (rtx()->img)
		mlx_delete_image(rtx()->mlx, rtx()->img);
	rtx()->img = mlx_new_image(rtx()->mlx, width, height);
	if (!rtx()->img)
		error(E_MLX, NULL);
}

void	rebuild_bvh(void)
{
	if (rtx()->bvh)
		free_bvh(&rtx()->bvh);
	if (!rtx()->shapes)
		return ;
	rtx()->bvh = bvh(rtx()->shapes);
	if (!rtx()->bvh)
		error(E_MEM, NULL);
}

void	build_images(t_list *shapes)
{
	t_shape	*shape;

	while (shapes)
	{
		shape = (t_shape *)shapes->content;
		if (shape->tex_path)
		{
			shape->texture = png_to_image(rtx()->mlx, shape->tex_path, false);
			free(shape->tex_path);
			shape->tex_path = NULL;
		}
		if (shape->tex_path)
		{
			shape->bump = png_to_image(rtx()->mlx, shape->bmp_path, false);
			free(shape->bmp_path);
			shape->bmp_path = NULL;
		}
		if (shape->chk)
			shape->checkerboard = make_checkerboard(shape->color);
		shapes = shapes->next;
	}
}

void	setup_scene(void)
{
	build_images(rtx()->unbound);
	build_images(rtx()->shapes);
	rebuild_bvh();
}

static mlx_image_t *safe_mlx_put_string(mlx_t *mlx, char *str)
{
	mlx_image_t	*img;

	img = mlx_put_string(mlx, str, 0, 0);
	if (!img)
		error(E_MLX, NULL);
	img->enabled = false;
	return (img);
}

void	init_ui(void)
{
	rtx()->ui[SPHERE] = safe_mlx_put_string(rtx()->mlx, "SPHERE");
	rtx()->ui[CYLINDER] = safe_mlx_put_string(rtx()->mlx, "CYLINDER");
	rtx()->ui[CONE] = safe_mlx_put_string(rtx()->mlx, "CONE");
	rtx()->ui[PLANE] = safe_mlx_put_string(rtx()->mlx, "PLANE");
	rtx()->ui[LIGHT] = safe_mlx_put_string(rtx()->mlx, "LIGHT");
	change_target();
}

void	init_rtx(void)
{
	start_mlx(WIDTH, HEIGHT);
	rtx()->seed = (unsigned int)(mlx_get_time() * 1000000);
	if (mlx_image_to_window(rtx()->mlx, rtx()->img, 0, 0) == -1)
		error(E_MLX, NULL);
	init_ui();
}
