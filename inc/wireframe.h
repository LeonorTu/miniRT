/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wireframe.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:05:32 by aklein            #+#    #+#             */
/*   Updated: 2024/08/28 20:04:14 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WIREFRAME_H
# define WIREFRAME_H

# include <miniRT.h>

# define AABB_LINE_THICKNESS 0.1

typedef struct s_coeff
{
	double	a;
	double	b;
	double	c;
	double	d;
	double	e;
	double	inv_denom;
}	t_coeff;

t_color	wireframe_color(int depth);
void	generate_aabb_lines(t_bvh *node, int depth, t_list **lines);
void	make_aabb_line(t_list **lines, t_vector start, t_vector end, int depth);

#endif