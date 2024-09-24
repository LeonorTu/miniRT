/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:05:12 by aklein            #+#    #+#             */
/*   Updated: 2024/08/30 13:27:41 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

typedef enum e_err_type
{
	E_NOPE,
	E_MLX,
	E_MEM,
	E_PARSER
}	t_err_type;

# define ERR_NO_AMBIENT "No ambient light given\n"
# define ERR_MULTI_AMBIENT "Multiple ambient lights are not allowed!\n"
# define ERR_NO_CAMERA "No camera given\n"
# define ERR_ARG_COUNT "Invalid argument number!\n"
# define ERR_INPUT_FORMAT "Invalid input file!\n"
# define ERR_FILE_OPEN "Open failed!\n"
# define ERR_CAM_SETUP "Invalid camera setup!\n"
# define ERR_FOV_RANGE "Invalid horizontal field of view! Range:[0,180]\n"
# define ERR_LIGHT_SETUP "Invalid light setup!\n"
# define ERR_LIGHT_BRIGHT "Invalid light brightness ratio! Range:[0.0,1.0]\n"
# define ERR_SPHERE_DIAM "Invalid sphere diameter! Range:[0.0, DBL_MAX]\n"
# define ERR_CYL_DIAM "Invalid cylinder diameter! Range:[0.0, DBL_MAX]\n"
# define ERR_CYL_HEIGHT "Invalid cylinder height! Range:[0.0, DBL_MAX]\n"
# define ERR_CONE_DIAM "Invalid cone diameter! Range:[0.0, DBL_MAX]\n"
# define ERR_CONE_HEIGHT "Invalid cone height! Range:[0.0, DBL_MAX]\n"
# define ERR_ZERO_VECTOR "Direction can't be zero vector!\n"
# define ERR_TEXTURE_FORMAT "Invalid texture format! Required: .png file\n"
# define ERR_BUMP_FORMAT "Invalid bump map format! Required: .png file\n"
# define ERR_SHINE "Invalid shine value! Range:[0,INT_MAX]\n"
# define ERR_REFLECT "Invalid reflection value! Range:[0.0,1.0]\n"
# define ERR_DIR_INPUT "Invalid direction input! Ex: 1.0,0.0,0.0\n"
# define ERR_DIR_NOT_NORM "Direction is not normalized!\n"
# define ERR_FLOAT_FORMAT "Invalid float format!\n"
# define ERR_VEC_FORMAT "Invalid vector format!\n"
# define ERR_VEC_VALUE "Invalid vector value!\n"
# define ERR_COLOR_FORMAT "Invalid color format!\n"
# define ERR_AMBIENT_SETUP "Invalid ambient setup!\n"
# define ERR_AMBIENT_RATIO "Invalid ambient lighting ratio! Range:[0.0, 1.0]\n"
# define ERR_MULTI_CAMERA "Multiple cameras are not allowed!\n"
# define ERR_CHK "Invalid checkerboard! chk:1 or chk:0\n"
# define ERR_ELEMENT "Invalid element!\n"

#endif