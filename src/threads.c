#include <miniRT.h>
#include <pthread.h>

#define NUM_THREADS 12
#define SSAA 1

typedef struct s_thread_data
{
	int		start_x;
	int		end_x;
	int		start_y;
	int		end_y;
}	t_thread_data;

// t_color	super_sample(int x, int y)
// {
// 	int					i;
// 	double				offset[2];
// 	t_color				pixel_color;
// 	t_ray				ray;
// 	unsigned int		seed;

// 	seed =  rtx()->seed ^ (unsigned int)pthread_self() ^
// 		(unsigned int)(mlx_get_time() * 100000);
// 	pixel_color = color_create(0, 0, 0);
// 	i = 0;
// 	while (i++ < SSAA)
// 	{
// 		offset[0] = (double)rand_r(&seed) / RAND_MAX;
// 		offset[1] = (double)rand_r(&seed) / RAND_MAX;
// 		ray = generate_ray(x + offset[0], y + offset[1]);
// 		pixel_color = color_add(pixel_color, trace_ray(&ray));
// 	}
// 	return (pixel_color);
// }

static inline t_ray	sub_ray(int x, int y, int j, int i, int	grid_size)
{
	double				off_x;
	double				off_y;
	unsigned int		seed;
	static unsigned int	hits = 0;

	seed =  rtx()->seed ^ (unsigned int)pthread_self() ^
		(unsigned int)(mlx_get_time() * 100000) ^ ++hits;
	off_x = ((double)j + (double)rand_r(&seed) / RAND_MAX) / grid_size;
	off_y = ((double)i + (double)rand_r(&seed) / RAND_MAX) / grid_size;
	return (generate_ray(x + off_x, y + off_y));
}

t_color	super_sample(int x, int y)
{
	int		i;
	int		j;
	t_color	pixel_color;
	t_ray	ray;
	int		grid_size;

	grid_size = rtx()->grid_size;
	pixel_color = color_create(0, 0, 0);
	j = 0;
	while (j < grid_size)
	{
		i = 0;
		while (i < grid_size)
		{
			ray = sub_ray(x, y, j, i, grid_size);
			pixel_color = color_add(pixel_color, trace_ray(&ray, BOUNCE));
			i++;
		}
		j++;
	}
	return (pixel_color);
}

void	*sample_region(void *arg)
{
	t_thread_data	*data;
	int				x;
	int				y;
	t_color			pixel_color;

	data = (t_thread_data *)arg;
	y = data->start_y;
	while (y < data->end_y)
	{
		x = data->start_x;
		while (x < data->end_x)
		{
			pixel_color = super_sample(x, y);
			pixel_color = color_scale(pixel_color, 1.0 / SSAA);
			mlx_put_pixel(rtx()->img, x, y, color_to_int(pixel_color));
			x++;
		}
		y++;
	}
	return (NULL);
}

void	render_multi_threaded(void)
{
	pthread_t		threads[NUM_THREADS];
	t_thread_data	data[NUM_THREADS];
	int				i;

	rtx()->grid_size = sqrt(SSAA);
	rtx()->ssaa = SSAA;
	i = 0;
	while (i < NUM_THREADS)
	{
		data[i].start_x = 0;
		data[i].end_x = WIDTH;
		data[i].start_y = i * (HEIGHT / NUM_THREADS);
		data[i].end_y = (i + 1) * (HEIGHT / NUM_THREADS);
		pthread_create(&threads[i], NULL, sample_region, &data[i]);
		i++;
	}
	i = 0;
	while (i < NUM_THREADS)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}
