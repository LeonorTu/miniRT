#include <miniRT.h>

t_rtx	*rtx(void)
{
	static t_rtx	rtx;

	return (&rtx);
}

t_shape	*make_sphere(t_vector pos, double diameter, t_rgba color)
{
	t_shape	*sphere;

	sphere = ft_calloc(1, sizeof(t_shape));
	sphere->type = SPHERE;
	sphere->pos = pos;
	sphere->diameter = diameter;
	sphere->radius = sphere->diameter / 2;
	sphere->color = color;

	return (sphere);
}

t_shape	*make_plane(t_vector pos, t_vector dir, t_rgba color)
{
	t_shape	*plane;

	plane = ft_calloc(1, sizeof(t_shape));
	plane->type = PLANE;
	plane->pos = pos;
	plane->dir = dir;
	plane->color = color;

	return (plane);
}

t_shape	*make_cylinder(t_vector pos, t_vector dir, double diameter, double height, t_rgba color)
{
	t_shape	*cylinder;

	cylinder = ft_calloc(1, sizeof(t_shape));
	cylinder->type = CYLINDER;
	cylinder->pos = pos;
	cylinder->dir = dir;
	cylinder->diameter = diameter;
	cylinder->height = height;
	cylinder->color = color;

	return (cylinder);
}

int	clamp(int value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

int	get_rgba(t_rgba color, double intensity)
{
	t_rgba	result;

	result.r = clamp((int)(color.r * intensity), 0, 255);
	result.g = clamp((int)(color.g * intensity), 0, 255);
	result.b = clamp((int)(color.b * intensity), 0, 255);
	result.a = clamp(color.a, 0, 255);
	return (result.r << 24 | result.g << 16 | result.b << 8 | result.a);
}

int	get_pixel_color(t_ray ray, t_intersection intersection)
{
	t_vector	hit_point;
	t_vector	normal;
	double		intensity;
	double		ambient;
	
	hit_point = vector_add(
		ray.origin,
		vector_scale(ray.direction, intersection.distance));
	normal = vector_normalize(vector_subtract(hit_point, intersection.shape.pos));
	ambient = rtx()->scene->amb.amb_light;
	intensity = fmax(vector_dot(normal, rtx()->scene->light.dir), ambient);
	return (get_rgba(intersection.shape->color, intensity));
}

/*
calculate right and up vectors based on current camera dir and WORLD_UP
WORLD_UP x CAMERA_FORWARD = CAM_RIGHT
CAMERA_FORWARD x CAM_RIGHT = CAM_UP
*/
t_vector	add_panning(t_vector vector)
{
	t_vector	direction;
	t_vector	right;
	t_vector	up;

	right = vector_cross(WORLD_UP, rtx()->scene->camera.dir);
	up = vector_cross(rtx()->scene->camera.dir, right);
	direction = vector_add(
		vector_scale(right, vector.x),
		vector_scale(up, vector.y));
	direction = vector_add(
		direction,
		vector_scale(rtx()->scene->camera.dir, vector.z));
	rtx()->scene->camera.right = right;
	rtx()->scene->camera.up = up;
	return (direction);
}

t_ray	generate_ray(int x, int y)
{
	t_ray		ray;
	t_vector	vector;
	double		fov;
	t_scene		*scene;

	scene = rtx()->scene;
	ray.origin = rtx()->scene->camera.pos;
	fov = scene->camera.fov;
	vector.x = (2 * ((x + 0.5) / WIDTH) - 1) * fov * WIDTH / HEIGHT;
	vector.y = (1 - 2 * ((y + 0.5) / HEIGHT)) * fov;
	vector.z = 1;
	ray.direction = add_panning(vector);
	ray.direction = vector_normalize(ray.direction);
	ray.inv_dir = (t_vector){
		1.0 / ray.direction.x,
		1.0 / ray.direction.y,
		1.0 / ray.direction.z
	};
	return (ray);
}

bool	intersect(t_shape *shape, t_ray ray, double *t)
{
	bool	hit;

	hit = false;
	if (shape->type == SPHERE)
		hit = intersect_sphere(ray, shape, t);
	else if (shape->type == PLANE)
	{
		intersect_plane(ray, shape, t);
	}
	else if (shape.type == CYLINDER)
	{
		intersect_cylinder(ray, shape, t);
	}
	if (*t < 0)
		return (false);
	return (hit && *t > 0);
}

t_intersection	intersect_shape(t_ray ray, t_list *shapes)
{
	t_intersection	result;
	double			t;
	t_shape			*shape;

	t = INFINITY;
	result = (t_intersection){INFINITY, NULL, 0};
	while (shapes)
	{
		shape = (t_shape *)shapes->content;
		if (intersect(shape, ray, &t))
		{
			if (t < result.distance)
			{
				result.distance = t;
				result.shape = shape;
				result.hit = true;
			}
		}
		shapes = shapes->next;
	}
	return (result);
}

int trace_ray (t_ray ray)
{
	t_intersection	t;

	t = (t_intersection){INFINITY, NULL, false};
	t.hit = intersect_bvh(rtx()->bvh, ray, &t);
	// t = intersect_shape(ray, rtx()->shapes);
	if (!t.hit)
		return (TEST_BG);
	return (get_pixel_color(ray, t));
}

void	render_scene(void)
{
	t_ray	ray;
	int		color;
	int		x;
	int		y;

	y = 0;
	while(y < HEIGHT)
	{
		x = 0;
		while(x < WIDTH)
		{
			ray = generate_ray(x, y);
			color = trace_ray(ray);
			mlx_put_pixel(rtx()->img, x, y, color);
			x++;
		}
		y++;
	}
}

void	get_shapes(void)
{
	ft_lstadd_back(&rtx()->shapes, ft_lstnew(make_sphere(TEST_SPHERE)));
	ft_lstadd_back(&rtx()->shapes, ft_lstnew(make_sphere(TEST_SPHERE2)));
	ft_lstadd_back(&rtx()->shapes, ft_lstnew(make_sphere(TEST_SPHERE3)));
	ft_lstadd_back(&rtx()->shapes, ft_lstnew(make_sphere(TEST_SPHERE4)));
	bvh(rtx()->shapes);
}

void	start_mlx(void)
{
	rtx()->mlx = mlx_init(WIDTH, HEIGHT, "miniRT", 1);
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	
	rtx()->img = mlx_new_image(rtx()->mlx, WIDTH, HEIGHT);
	if (!rtx()->img)
		exit(1);
	rtx()->width = WIDTH;
	rtx()->height = HEIGHT;
	mlx_image_to_window(rtx()->mlx, rtx()->img, 0, 0);
}

void	setup_cache(void)
{
	int	i;

	rtx()->cache.index = 0;
	i = 0;
	while (i < CACHE_SIZE)
	{
		rtx()->cache.shape[i] = NULL;
		i++;
	}
}

void	setup_scene(void)
{
	rtx()->scene = ft_calloc(1, sizeof(t_scene));
	rtx()->scene->amb.amb_light = TEST_AMBIENT;
	rtx()->scene->camera.pos = TEST_CAM_POS;
	rtx()->scene->camera.dir = vector_normalize(TEST_CAM_DIR);
	rtx()->scene->camera.right = TEST_CAM_DIR;
	rtx()->scene->camera.up = TEST_CAM_DIR;
	rtx()->scene->camera.fov = tan((TEST_FOV / 2) * (M_PI / 180.0));
	rtx()->scene->light.pos	= TEST_LIGHT_POS;
	rtx()->scene->light.dir	= vector_normalize(TEST_LIGHT_DIR);
	get_shapes();
	setup_cache();
}

void	loop_hook(void *data)
{
	(void)data;
	static int		fps = 1;
	static double	i = 0;
	t_camera		camera;

	camera = rtx()->scene->camera;
	i += rtx()->mlx->delta_time;
	fps++;
	if (i >= 1)
	{
		printf("\e[1;1Hfps [%d]\e[K\n", fps);
		i = 0;
		fps = 0;
	}
	printf("\e[2;1HLast Frame [%.0fms]\e[K\n", rtx()->mlx->delta_time * 1000);

	printf("\e[4;1HFOV [%.2f]\e[K\n", camera.fov);
	printf("\e[5;1HCamera position [{%.2f, %.2f, %.2f}]\e[K\n", camera.pos.x, camera.pos.y, camera.pos.z);
	printf("\e[6;1HCamera direction [{%.2f, %.2f, %.2f}]\e[K\n", camera.dir.x, camera.dir.y, camera.dir.z);
}

int	main(void)
{
	start_mlx();
	setup_scene();
	render_scene();
	mlx_key_hook(rtx()->mlx, key_hook, NULL);
	mlx_loop_hook(rtx()->mlx, loop_hook, NULL);
	mlx_loop(rtx()->mlx);
	mlx_terminate(rtx()->mlx);
	return (0);
}

