#include <miniRT.h>
#include <wireframe.h>

static void	set_corners(t_aabb box, t_vector *corners)
{
	corners[0] = (t_vector){box.min.x, box.min.y, box.min.z};
	corners[1] = (t_vector){box.max.x, box.min.y, box.min.z};
	corners[2] = (t_vector){box.min.x, box.max.y, box.min.z};
	corners[3] = (t_vector){box.max.x, box.max.y, box.min.z};
	corners[4] = (t_vector){box.min.x, box.min.y, box.max.z};
	corners[5] = (t_vector){box.max.x, box.min.y, box.max.z};
	corners[6] = (t_vector){box.min.x, box.max.y, box.max.z};
	corners[7] = (t_vector){box.max.x, box.max.y, box.max.z};
}

static void	add_aabb_line(t_list **lines, t_vector start, t_vector end, t_rgba color)
{
	t_shape	*line;

	line = ft_calloc(1, sizeof(t_shape));
	if (!line)
		return ;
	line->type = WIREFRAME;
	line->pos = start;
	line->color = color;
	line->dir = vector_subtract(end, start);
	line->diameter = AABB_LINE_THICKNESS * 2;
	line->radius = AABB_LINE_THICKNESS;
	ft_lstadd_back(lines, ft_lstnew(line));
}

/*
Front Face = first 4
Back Face = middle 4
connecting edges = last 4
*/
static void	add_lines(t_list **lines, t_vector *corners, t_rgba color)
{
	add_aabb_line(lines, corners[0], corners[1], color);
	add_aabb_line(lines, corners[1], corners[3], color);
	add_aabb_line(lines, corners[3], corners[2], color);
	add_aabb_line(lines, corners[2], corners[0], color);
	add_aabb_line(lines, corners[4], corners[5], color);
	add_aabb_line(lines, corners[5], corners[7], color);
	add_aabb_line(lines, corners[7], corners[6], color);
	add_aabb_line(lines, corners[6], corners[4], color);
	add_aabb_line(lines, corners[0], corners[4], color);
	add_aabb_line(lines, corners[1], corners[5], color);
	add_aabb_line(lines, corners[2], corners[6], color);
	add_aabb_line(lines, corners[3], corners[7], color);
}
static void	add_connecting_edges(t_list **lines, t_vector *corners,
				t_rgba color)
{
	add_aabb_line(lines, corners[0], corners[4], color);
	add_aabb_line(lines, corners[1], corners[5], color);
	add_aabb_line(lines, corners[2], corners[6], color);
	add_aabb_line(lines, corners[3], corners[7], color);
}

/**
 * Recursively generates AABB lines for BVH visualization.
 *
 * Creates color-coded lines representing the AABB of each BVH node.
 * Lines are added to the provided list for later rendering.
 *
 * @param node Current BVH node
 * @param depth Depth in BVH tree (for color coding)
 * @param lines List to store generated lines
 */
void	generate_aabb_lines(t_bvh *node, int depth, t_list **lines)
{
	t_rgba		color;
	t_vector	corners[8];

	if (!node)
		return ;
	color = depth_colors[depth % MAX_DEPTH];
	set_corners(node->box, corners);
	add_lines(lines, corners, color);
	add_connecting_edges(lines, corners, color);
	generate_aabb_lines(node->left, depth + 1, lines);
	generate_aabb_lines(node->right, depth + 1, lines);
}