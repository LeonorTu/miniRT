#include <miniRT.h>

bool	check_shadow(t_hit *hit, t_light *light)
{
	t_ray	shadow_ray;
	t_hit	temp;
	double	light_distance;
	
	shadow_ray.origin = vector_add(hit->hit_point, vector_scale(hit->normal, 0.001));
	shadow_ray.direction = vector_subtract(
		light->pos,
		shadow_ray.origin);
	light_distance = vector_length(shadow_ray.direction);
	shadow_ray.direction = vector_scale(shadow_ray.direction, 1.0 / light_distance);
	shadow_ray.inv_dir = (t_vector){
		1.0 / shadow_ray.direction.x,
		1.0 / shadow_ray.direction.y,
		1.0 / shadow_ray.direction.z
	};
	temp.distance = light_distance;
	if (rtx()->bvh && intersect_bvh(rtx()->bvh, shadow_ray, &temp) && temp.distance < light_distance)
		return (true);
	temp.distance = light_distance;
	if (check_unbound(&shadow_ray, &temp) && temp.distance < light_distance)
		return (true);
	return (false);
}

t_color	light_one(t_light *light, t_hit *hit)
{
	t_vector	light_dir;
	double		intensity;
	t_color		contribution;

	contribution = light->color;
	light_dir = vector_normalize(
		vector_subtract(light->pos, hit->hit_point));
	intensity = vector_dot(hit->normal, light_dir);
	intensity = fmax(intensity, 0.0);

	contribution = color_scale(contribution, light->bright * intensity);
	return (contribution);
}
t_vector random_in_hemisphere(t_vector normal)
{
	t_vector	random_dir;
	double		dot_product;

	random_dir.x = 2.0 * ((double)rand() / RAND_MAX) - 1.0;
	random_dir.y = 2.0 * ((double)rand() / RAND_MAX) - 1.0;
	random_dir.z = 2.0 * ((double)rand() / RAND_MAX) - 1.0;
	random_dir = vector_normalize(random_dir);
	dot_product = vector_dot(random_dir, normal);
	if (dot_product < 0)
		random_dir = vector_scale(random_dir, -1);

	return (random_dir);
}

t_ray	new_ray(t_hit *hit)
{
	t_ray		new_ray;
	// t_vector	random_dir;
	double		len;

	new_ray.direction = random_in_hemisphere(hit->normal);
	new_ray.origin = vector_add(hit->hit_point, vector_scale(hit->normal, 0.001));
	// new_ray.direction = vector_subtract(
	// 	random_dir,
	// 	new_ray.origin);
	len = vector_length(new_ray.direction);
	new_ray.direction = vector_scale(new_ray.direction, 1.0 / len);
	new_ray.inv_dir = (t_vector){
		1.0 / new_ray.direction.x,
		1.0 / new_ray.direction.y,
		1.0 / new_ray.direction.z
	};
	return (new_ray);
}

t_color	bounce_it(t_hit *hit, int depth)
{
	t_ray	bounce_ray;
	t_color	indirect;

	if (depth <= 0)
		return (color_create(0, 0, 0));
	bounce_ray = new_ray(hit);
	indirect = trace_ray(&bounce_ray, depth - 1);
	//temp
	hit->shape->reflectivity = 0.1;
	indirect = color_scale(indirect, hit->shape->reflectivity);
	return (indirect);
}


t_lighting	calc_lighting(t_hit *hit, int depth)
{
	t_list		*lights;
	t_light		*light;
	t_lighting	lighting;
	t_color		contribution;
	t_color		total;

	lights = rtx()->scene->lights;
	lighting = (t_lighting){{0, 0, 0},{0, 0, 0},{0, 0, 0}};
	contribution = color_create(0, 0, 0);
	total = color_create(0, 0, 0);
	lighting.ambient = rtx()->scene->ambient;
	while (lights)
	{
		light = (t_light *)lights->content;
		if (!check_shadow(hit, light))
		{
			contribution = light_one(light, hit);
			total = color_add(total, contribution);
		}
		lights = lights->next;
	}
	lighting.direct = total;
	lighting.indirect = bounce_it(hit, depth);
	return (lighting);
}
