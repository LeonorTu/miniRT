/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:17:35 by jtu               #+#    #+#             */
/*   Updated: 2024/09/24 01:12:46 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

static void	pan_camera(double h_angle, double v_angle)
{
	t_camera	*camera;

	h_angle = h_angle * M_PI / 180;
	v_angle = v_angle * M_PI / 180;
	camera = &(rtx()->camera);
	camera->dir = vector_rotate(camera->dir, (t_vector){0, 1, 0}, h_angle);
	camera->dir = vector_rotate(camera->dir, camera->right, -v_angle);
	camera->right = vector_rotate(camera->right, (t_vector){0, 1, 0}, h_angle);
	camera->right = vector_rotate(camera->right, camera->right, -v_angle);
	camera->up = vector_rotate(camera->up, (t_vector){0, 1, 0}, h_angle);
	camera->up = vector_rotate(camera->up, camera->right, -v_angle);
}

static void	adjust_fov(int direction)
{
	double	current_fov;

	current_fov = 2 * atan(rtx()->camera.fov) * (180.0 / M_PI);
	if (direction > 0)
		current_fov += FOV_STEP;
	else
		current_fov -= FOV_STEP;
	if (current_fov < MIN_FOV)
		current_fov = MIN_FOV;
	else if (current_fov > MAX_FOV)
		current_fov = MAX_FOV;
	rtx()->camera.fov = tan((current_fov * 0.5) * (M_PI / 180.0));
}

static bool	move_camera(mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_SPACE)
		translate_vector(&rtx()->camera.pos, UP);
	else if (keydata.key == MLX_KEY_C)
		translate_vector(&rtx()->camera.pos, DOWN);
	else if (keydata.key == MLX_KEY_W)
		translate_vector(&rtx()->camera.pos, FORWARD);
	else if (keydata.key == MLX_KEY_A)
		translate_vector(&rtx()->camera.pos, LEFT);
	else if (keydata.key == MLX_KEY_S)
		translate_vector(&rtx()->camera.pos, BACK);
	else if (keydata.key == MLX_KEY_D)
		translate_vector(&rtx()->camera.pos, RIGHT);
	else if (keydata.key == MLX_KEY_UP)
		pan_camera(0, PAN_AMOUNT);
	else if (keydata.key == MLX_KEY_RIGHT)
		pan_camera(PAN_AMOUNT, 0);
	else if (keydata.key == MLX_KEY_DOWN)
		pan_camera(0, -PAN_AMOUNT);
	else if (keydata.key == MLX_KEY_LEFT)
		pan_camera(-PAN_AMOUNT, 0);
	else
		return (false);
	return (true);
}

static bool	adjust_shapes(mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_O)
		move_objects(UP);
	else if (keydata.key == MLX_KEY_L)
		move_objects(DOWN);
	else if (keydata.key == MLX_KEY_U)
		move_objects(FORWARD);
	else if (keydata.key == MLX_KEY_J)
		move_objects(BACK);
	else if (keydata.key == MLX_KEY_H)
		move_objects(LEFT);
	else if (keydata.key == MLX_KEY_K)
		move_objects(RIGHT);
	else if (keydata.key == MLX_KEY_R)
		return (rotate_objects(FORWARD));
	else if (keydata.key == MLX_KEY_T)
		return (rotate_objects(BACK));
	else if (keydata.key == MLX_KEY_PERIOD)
		return (scale(UP));
	else if (keydata.key == MLX_KEY_COMMA)
		return (scale(DOWN));
	else
		return (false);
	return (true);
}

bool	keys(mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_ESCAPE)
		error(E_NOPE, NULL);
	if (move_camera(keydata))
		return (true);
	if (keydata.key == MLX_KEY_TAB && keydata.action == MLX_RELEASE)
		return (change_target());
	else if (keydata.key == MLX_KEY_PAGE_UP && keydata.action == MLX_RELEASE)
		adjust_fov(-1);
	else if (keydata.key == MLX_KEY_PAGE_DOWN && keydata.action == MLX_RELEASE)
		adjust_fov(1);
	else if (keydata.key == MLX_KEY_B && keydata.action == MLX_RELEASE)
	{
		rtx()->wireframe = !rtx()->wireframe;
		rtx()->wireframe_bvh = make_wireframe(rtx()->bvh);
		if (!rtx()->wireframe_bvh)
			error(E_MEM, NULL);
	}
	else if (adjust_shapes(keydata))
		return (true);
	else
		return (false);
	return (true);
}
