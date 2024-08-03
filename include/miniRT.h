#ifndef MINIRT_H
# define MINIRT_H

# include <libft.h>
# include <math.h> // math
# include <stdio.h> // printf
# include <MLX42/MLX42.h> // mlx
# include <float.h>
# include <colors.h> //colors
# include <struct.h> //colors


# define VV (t_vector){0, 0, 0} //dummy 0 vector for initializationsõ

# define LINE_THICKNESS 0.45

#define NUM_THREADS 24

// # define WIDTH 2560
// # define HEIGHT 1440
# define WIDTH 800
# define HEIGHT 600
# define M_PI 3.14159265358979323846

# define EPSILON 1e-6
# define SCALE_PLANE 0.01

# define WORLD_UP (t_vector){0, 1, 0}
# define WORLD_RIGHT (t_vector){1, 0, 0}
# define WORLD_X (t_vector){1, 0, 0}
# define WORLD_Y (t_vector){0, 1, 0}
# define WORLD_Z (t_vector){0, 0, 1}


# define AXIS_X 1
# define AXIS_Y 2
# define AXIS_Z 3

# define TEST_BG 0x000000FF

# define CHECKERB_COLOR COLOR_BLUE

// test shapes
# define TEST_PLANEF (t_vector){0, 0, 30}, (t_vector){0, 0, -1}, RGBA(WALL_COLOR)
# define TEST_PLANEB (t_vector){0, 0, -165}, (t_vector){0, 0, 1}, RGBA(WALL_COLOR)
# define TEST_PLANEU (t_vector){0, 30, 0}, (t_vector){0, -1, 0}, RGBA(WALL_COLOR)
# define TEST_PLANED (t_vector){0, -30, 0}, (t_vector){0, 1, 0}, RGBA(WALL_COLOR)
# define TEST_PLANER (t_vector){35, 0, 0}, (t_vector){-1, -1, 0}, RGBA(WALL_COLOR)
# define TEST_PLANEL (t_vector){-35, 0, 0}, (t_vector){1, 1, 0}, RGBA(WALL_COLOR)

# define TEST_CYLINDER1 (t_vector){-25, 0, 0}, (t_vector){0, 1, 0}, 4, 8, RGBA(WALL_COLOR)
# define TEST_CYLINDER2 (t_vector){25, 0, 0}, (t_vector){-1, 0, 0}, 60, 1, RGBA(WALL_COLOR)
# define TEST_CYLINDER3 (t_vector){0, 0, -5}, (t_vector){0, 1, 0}, 5, 15, RGBA(WALL_COLOR)

# define TEST_CONE (t_vector){0, 0, 15}, (t_vector){0, 1, 0}, 12, 15, RGBA(COLOR_MAGENTA)

# define TEST_SPHERE2 (t_vector){0, 0, 15}, 81, RGBA(COLOR_PINK)
# define TEST_SPHERE (t_vector){4, 2, 5}, 4, RGBA(COLOR_BLACK)
# define TEST_SPHERE4 (t_vector){-4, 2, 5}, 4, RGBA(COLOR_BLACK)
# define TEST_SPHERE3 (t_vector){0, -2, 5}, 2, RGBA(COLOR_RED)

# define WALL_COLOR COLOR_WARM_WHITE
# define TEXT_COLOR COLOR_METALLIC_GOLD
# define LIGHT_COLOR COLOR_WARM_WHITE

# define SHINE 500

# define REFLECT_DEPTH 1
//test cam
# define TEST_CAM_POS (t_vector){0, 0.8, -35}
# define TEST_CAM_DIR (t_vector){0, -0.2, 1}
# define TEST_FOV 80.0
# define FOV_STEP 10.0
# define MIN_FOV 10.0
# define MAX_FOV 170.0

# define PAN_AMOUNT M_PI / 24
# define MOVE_SPEED 3.0

//test light
# define TEST_LIGHT (t_vector){0, 15, -15}, RGBA(COLOR_PASTEL_BLUE), 1.0
# define TEST_LIGHT2 (t_vector){0, -7, -8}, RGBA(COLOR_PASTEL_ORANGE), 1.0
# define TEST_LIGHT3 (t_vector){10, 10, 0}, RGBA(COLOR_GREEN), 1.0

# define TEST_AMBIENT_COL RGBA(COLOR_WARM_WHITE)
# define TEST_AMBIENT_INT 1

typedef struct s_scene t_scene;
typedef struct s_bvh t_bvh;
typedef struct s_aabb t_aabb;

// parsing
t_vector	check_dir(t_vector dir);

//basic vector equation
t_vector		vector_add(t_vector a, t_vector b);
t_vector		vector_subtract(t_vector a, t_vector b);
t_vector		vector_scale(t_vector a, double scalar);
double			vector_dot(t_vector a, t_vector b);
t_vector		vector_cross(t_vector a, t_vector b);
double			vector_length(t_vector a);
t_vector		vector_normalize(t_vector a);
double			vector_length_squared(t_vector a);
t_vector		vector_min(t_vector a, t_vector b);
t_vector		vector_max(t_vector a, t_vector b);

//clamp
int				clampi(int value, int min, int max);
double			clampd(double value, double min, double max);

//init
t_rtx			*rtx(void);
void			init_rtx(void);
void			fix_camera(void);
void			get_lights(void);
void			get_shapes(void);
t_bvh			*bvh(t_list *shapes);
//bvh
t_aabb			compute_box(t_shape **shapes, int num_shapes);
int				partition_shapes(t_shape **shapes, int num_shapes, int axis);
t_shape			**shapes_to_arr(t_list *shapes, int num_shapes);
void			free_bvh(t_bvh *bvh);

//render
void			render(void);
void			render_scene(void);
void			render_multi_threaded(void);
t_ray			create_ray(t_vector origin, t_vector direction);
t_ray			generate_ray(int x, int y);
t_color			trace_ray (t_ray *ray, int depth);
//intersect
bool			check_unbound(t_ray *ray, t_hit *hit);
bool			intersect_bvh(t_bvh *node, t_ray ray, t_hit *hit);
bool			intersect(t_shape *shape, t_ray ray, double *t);
bool			intersect_sphere(t_ray ray, t_shape *sphere, double* t);
int				intersect_plane(t_ray ray, t_shape plane, double *t);
int				intersect_cylinder(t_ray ray, t_shape cylinder, double *t);
int				intersect_cone(t_ray ray, t_shape *cone, double *t);
void			fix_hit_normal(t_hit *hit);
//lights
double			get_diffuse(t_hit *hit, t_vector *light_dir);
t_lighting		calc_lighting(t_hit *hit);
//colors
t_color			get_pixel_color(t_ray *ray, t_hit *hit, int depth);
int				color_to_int(t_color c);
t_color			color_from_int(int r, int g, int b);
t_color			color_from_hex(unsigned int hex);
t_color			color_clamp(t_color c);
t_color			color_scale(t_color c, double scale);
t_color			color_multiply(t_color c1, t_color c2);
t_color			color_subtract(t_color c1, t_color c2);
t_color			color_add(t_color c1, t_color c2);
t_color			color_create(double r, double g, double b);
t_color			color_blend(t_color c1, t_color c2, double factor);

//MLX
void			loop_hook(void *data);
void			key_hook(mlx_key_data_t keydata, void* param);
bool			keys(mlx_key_data_t keydata);

//rotate and translate
t_vector		vector_rotate(t_vector v, t_vector axis, double angle);
void			random_rotate(void);
void			translate_vector(t_vector *object, t_direction dir);
void			move_shapes(t_direction dir);

//shapes
t_shape			*make_sphere(t_vector pos, double diameter, t_color color);
t_shape			*make_cone(t_vector pos, t_vector dir, double diameter, double height, t_color color);
t_shape			*make_plane(t_vector pos, t_vector dir, t_color color);
t_shape			*make_cylinder(t_vector pos, t_vector dir, double diameter, double height, t_color color);

//axis-aligned bounding boxes
bool		intersect_aabb(t_ray ray, t_aabb box, double max_t);
t_aabb		box_sphere(t_shape *sphere);
t_aabb		box_cylinder(t_shape *cylinder);
t_aabb		box_line(t_shape *line);
t_aabb		box_cone(t_shape *cone);

//uv
void		sphere_uv(t_vector point, double *u, double *v, int repeat);
void		plane_uv(t_hit *hit, double *u, double *v, int repeat);
void		cylindrical_uv(t_hit *hit, double *u, double *v, int repeat);
void		cone_uv(t_hit *hit, double *u, double *v, int repeat);

//wireframe
t_bvh		*make_wireframe(t_bvh *shapes_bvh);
void		make_aabb_line(t_list **lines, t_vector start, t_vector end, t_color color, t_shape_type type);
bool		intersect_aabb_line(t_ray ray, t_shape *line, double *t);
void		generate_aabb_lines(t_bvh *node, int depth, t_list **lines);

void		error(void);
#endif
