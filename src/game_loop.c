#include <miniRT.h>

void	pan_camera(double horizontal_angle, double vertical_angle)
{
	t_camera	*camera;

	camera = &(rtx()->scene->camera);
	camera->dir = vector_rotate(camera->dir, WORLD_UP, horizontal_angle);
	camera->dir = vector_rotate(camera->dir, camera->right, -vertical_angle);
	camera->dir = vector_normalize(camera->dir);
	fix_camera();
}

void	adjust_fov(int direction)
{
	double current_fov;

	current_fov = 2 * atan(rtx()->scene->camera.fov) * (180.0 / M_PI);
	if (direction > 0)
		current_fov += FOV_STEP;
	else
		current_fov -= FOV_STEP;
	if (current_fov < MIN_FOV)
		current_fov = MIN_FOV;
	else if (current_fov > MAX_FOV)
		current_fov = MAX_FOV;
	rtx()->scene->camera.fov = tan((current_fov / 2) * (M_PI / 180.0));
}

bool	move_camera(mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_SPACE && (keydata.action == MLX_PRESS))
		translate_vector(&rtx()->scene->camera.pos, UP);
	else if (keydata.key == MLX_KEY_C && (keydata.action == MLX_PRESS))
		translate_vector(&rtx()->scene->camera.pos, DOWN);
	else if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS))
		translate_vector(&rtx()->scene->camera.pos, FORWARD);
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS))
		translate_vector(&rtx()->scene->camera.pos, LEFT);
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS))
		translate_vector(&rtx()->scene->camera.pos, BACK);
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS))
		translate_vector(&rtx()->scene->camera.pos, RIGHT);
	else if (keydata.key == MLX_KEY_UP && (keydata.action == MLX_PRESS))
		pan_camera(0, PAN_AMOUNT);
	else if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS))
		pan_camera(PAN_AMOUNT, 0);
	else if (keydata.key == MLX_KEY_DOWN && (keydata.action == MLX_PRESS))
		pan_camera(0, -PAN_AMOUNT);
	else if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS))
		pan_camera(-PAN_AMOUNT, 0);
	else
		return (false);
	return (true);
}

bool	move_all(mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_O && keydata.action == MLX_RELEASE)
		move_shapes(UP);
	else if (keydata.key == MLX_KEY_L && keydata.action == MLX_RELEASE)
		move_shapes(DOWN);
	else if (keydata.key == MLX_KEY_U && keydata.action == MLX_RELEASE)
		move_shapes(FORWARD);
	else if (keydata.key == MLX_KEY_J && keydata.action == MLX_RELEASE)
		move_shapes(BACK);
	else if (keydata.key == MLX_KEY_H && keydata.action == MLX_RELEASE)
		move_shapes(LEFT);
	else if (keydata.key == MLX_KEY_K && keydata.action == MLX_RELEASE)
		move_shapes(RIGHT);
	else
		return (false);
	return (true);
}

bool	keys(mlx_key_data_t keydata)
{
	if (move_camera(keydata))
		return (true);
	else if (keydata.key == MLX_KEY_PAGE_UP && keydata.action == MLX_RELEASE)
		adjust_fov(-1);
	else if (keydata.key == MLX_KEY_PAGE_DOWN && keydata.action == MLX_RELEASE)
		adjust_fov(1);
	else if (keydata.key == MLX_KEY_B && keydata.action == MLX_RELEASE)
	{
		rtx()->wireframe = !rtx()->wireframe;
		rtx()->wireframe_bvh = make_wireframe(rtx()->bvh);
	}
	else if (keydata.key == MLX_KEY_G && keydata.action == MLX_RELEASE)
		rtx()->debug_normals = !rtx()->debug_normals;
	else if (keydata.key == MLX_KEY_R && keydata.action == MLX_RELEASE)
		random_rotate();
	else if (move_all(keydata))
		return (true);
	else
		return (false);
	return (true);

}

void	key_hook(mlx_key_data_t keydata, void* param)
{
	(void)param;
	if (keys(keydata))
	{
		printf("\e[3;1HLast step Frame [%.0fms]\e[K\n", rtx()->mlx->delta_time * 1000);
		render();
	}
}
