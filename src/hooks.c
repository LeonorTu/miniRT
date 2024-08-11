#include <miniRT.h>

void	key_hook(mlx_key_data_t keydata, void* param)
{
	(void)param;
	if (keys(keydata))
	{
		printf("\e[3;1HLast step Frame [%.0fms]\e[K\n", rtx()->mlx->delta_time * 1000);
		render();
	}
}

void	loop_hook(void *data)
{
	static int		fps = 1;
	static double	i = 0;
	t_camera		camera;

	(void)data;
	camera = rtx()->camera;
	i += rtx()->mlx->delta_time;
	fps++;
	if (i >= 1)
	{
		printf("\e[1;1Hfps [%d]\e[K\n", fps);
		i = 0;
		fps = 0;
	}
	printf("\e[2;1HLast Frame [%.0fms]\e[K\n",
		rtx()->mlx->delta_time * 1000);
	printf("\e[4;1HFOV [%.2f]\e[K\n",
		camera.fov);
	printf("\e[5;1HCamera position [{%.2f, %.2f, %.2f}]\e[K\n",
		camera.pos.x, camera.pos.y, camera.pos.z);
	printf("\e[6;1HCamera direction [{%.2f, %.2f, %.2f}]\e[K\n",
		camera.dir.x, camera.dir.y, camera.dir.z);
}
