/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:26:17 by aklein            #+#    #+#             */
/*   Updated: 2024/09/24 01:08:35 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <libft.h>
# include <MLX42/MLX42.h>
# include <structs.h>
# include <error.h>
# include <colors.h>

# define NUM_THREADS 24
# define SSAA 1
# define RESIZE_TIME 0.5

# define WIDTH 800
# define HEIGHT 600
# define M_PI 3.14159265358979323846

# define EPSILON 1e-6
# define DBL_MAX __DBL_MAX__
# define DBL_DIG __DBL_DIG__

# define SCALE_PLANE 0.01
# define SCALE_STEP 0.1

# define AXIS_X 1
# define AXIS_Y 2
# define AXIS_Z 3

# define BACKGROUND_COLOR COLOR_BLACK

# define SHINE_MOD 50

# define BUMP_STR 2.0

# define REFLECT_DEPTH 1

# define GAMMA 2.2

# define ROTATION_ANGLE 30

# define FOV_STEP 10.0
# define MIN_FOV 10.0
# define MAX_FOV 170.0

# define PAN_AMOUNT 7
# define MOVE_SPEED 1.0

# define SHINE_PLANE 60
# define SHINE_SPHERE 1000
# define SHINE_CYLINDER 500
# define SHINE_CONE 500

// parsing
double		ft_atof(char *str);
void		parse_input(char *argv[]);
t_vector	check_dir(t_vector dir);
t_color		parse_color(char *color_str);
t_vector	parse_vector(char *vector_str, bool dir);
void		parse_bonus(char **element, t_shape	*shape);
void		parse_element(char **element, int check[2]);
void		check_range_int(int value, int min, int max, char *err_msg);
void		check_range_double(double value, double min,
				double max, char *err_msg);
void		check_ac(int check[2]);
t_vector	check_dir(t_vector dir);
int			check_float(char *str);
int			check_int(char *str);
int			check_vector(char *str);
int			check_color(char *str);

//lalloc
t_list		**allocs(void);
void		clear_lal(void);
void		ft_free(void **ptr);
void		free_content(void *content);
void		add_to_lal(void *ptr);
void		free_one_lal(void *ptr);

// init
void		parse_ambient(char **element);
void		parse_camera(char **element);
void		parse_light(char **element);
void		parse_sphere(char	**element);
void		parse_plane(char	**element);
void		parse_cylinder(char **element);
void		parse_cone(char **element);
void		parse_checkerboard(char *element, t_shape *shape);
void		parse_texture(char *element, t_shape *shape);
void		parse_bump_map(char *element, t_shape *shape);
void		parse_shine(char *element, t_shape *shape);
void		parse_reflectivity(char *element, t_shape *shape);
void		scale_shape(t_shape *shape, double mult);

//basic vector equation
t_vector	vector_add(t_vector a, t_vector b);
t_vector	vector_subtract(t_vector a, t_vector b);
t_vector	vector_scale(t_vector a, double scalar);
double		vector_dot(t_vector a, t_vector b);
t_vector	vector_cross(t_vector a, t_vector b);
double		vector_length(t_vector a);
t_vector	vector_normalize(t_vector a);
double		vector_length_squared(t_vector a);
t_vector	vector_min(t_vector a, t_vector b);
t_vector	vector_max(t_vector a, t_vector b);

//clamp
int			clampi(int value, int min, int max);
double		clampd(double value, double min, double max);

//util
void		ft_swap(double *a, double *b);
t_hit		new_hit(void);
int			array_len(char **array);
char		**split_line(char *line);
char		**ft_safe_split(char const *s, char *set);
char		**ft_split_new(char const *s, char *set);
char		*ft_safe_strtrim(char const *s1, char const *set);
int			ft_char_count(const char *s, int c);

//error
void		error(t_err_type err, const char *msg);

//init rtx
t_rtx		*rtx(void);
void		init_rtx(void);
void		fix_camera(void);
void		setup_scene(void);
mlx_image_t	*make_checkerboard(t_color color);
t_bvh		*bvh(t_list *shapes);
//bvh
t_aabb		compute_box(t_shape **shapes, int num_shapes);
int			partition_shapes(t_shape **shapes, int num_shapes, int axis);
t_shape		**shapes_to_arr(t_list *shapes, int num_shapes);
void		rebuild_bvh(void);
void		free_bvh(t_bvh **bvh);

//render
void		render(void);
void		render_scene(void);
void		render_multi_threaded(void);
t_ray		create_ray(t_vector origin, t_vector direction);
t_ray		generate_ray(double x, double y);
t_color		trace_ray(t_ray *ray, int depth);
//intersect
bool		check_unbound(t_ray *ray, t_hit *hit);
bool		intersect_bvh(t_bvh *node, t_ray *ray, t_hit *hit);
bool		intersect(t_shape *shape, t_ray *ray, double *t);
void		get_valid_t(double t[2], t_quad_coeffs *coeffs, double *d);
bool		intersect_sphere(t_ray *ray, t_shape *sphere, double *t);
int			intersect_plane(t_ray *ray, t_shape *plane, double *t);
int			intersect_cylinder(t_ray *ray, t_shape *cylinder, double *t);
int			intersect_cone(t_ray *ray, t_shape *cone, double *t);
void		fix_hit_normal(t_hit *hit);
//lights
double		get_diffuse(t_hit *hit, t_vector *light_dir);
t_lighting	calc_lighting(t_hit *hit);
//material
t_color		add_material(t_hit *hit);
//reflection
t_color		get_reflections(t_hit *hit, int depth);
//colors
t_color		get_pixel_color(t_ray *ray, t_hit *hit, int depth);
int			color_to_int(t_color c);
t_color		color_from_int(int r, int g, int b);
t_color		color_from_hex(unsigned int hex);
t_color		color_clamp(t_color c);
t_color		color_scale(t_color c, double scale);
t_color		color_multiply(t_color c1, t_color c2);
t_color		color_subtract(t_color c1, t_color c2);
t_color		color_add(t_color c1, t_color c2);
t_color		color_create(double r, double g, double b);
t_color		color_blend(t_color c1, t_color c2, double factor);

//MLX
void		resize_hook(int32_t width, int32_t height, void *data);
void		loop_hook(void *data);
void		key_hook(mlx_key_data_t keydata, void *param);
bool		keys(mlx_key_data_t keydata);
bool		change_target(void);
void		move_objects(t_direction dir);
mlx_image_t	*mlx_image_gray(mlx_t *mlx, mlx_image_t *image);
mlx_image_t	*png_to_image(mlx_t *mlx, char *path, bool to_grayscale);

//rotate and translate
t_vector	vector_rotate(t_vector v, t_vector axis, double angle);
bool		rotate_objects(t_direction dir);
void		translate_vector(t_vector *object, t_direction dir);
void		move_shapes(t_direction dir);
bool		scale(t_direction dir);

//axis-aligned bounding boxes
bool		intersect_aabb(t_ray ray, t_aabb box, double max_t);
t_aabb		box_sphere(t_shape *sphere);
t_aabb		box_cylinder(t_shape *cylinder);
t_aabb		box_line(t_shape *line);
t_aabb		box_cone(t_shape *cone);

//uv
void		get_uv(t_hit *hit);
t_color		uv_get_color(mlx_image_t *image, double u, double v);
void		uv_repeat_wrap(double *u, double *v, int repeat);
void		create_local_system(t_shape *shape);
//wireframe
t_bvh		*make_wireframe(t_bvh *shapes_bvh);
bool		intersect_aabb_line(t_ray *ray, t_shape *line, double *t);

#endif