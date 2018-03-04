/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 12:52:55 by                   #+#    #+#             */
/*   Updated: 2018/03/03 19:55:17 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "cl_wrap.h"

int	main(void)
{
	void		*mlx;
	void		*window;
	void		*image;
	int			*data;
	int			dummy;
	t_cl_info	info;

	rt_cl_init(&info);
	rt_cl_compile(&info, "hello.cl");
	cl_mem buf = rt_cl_malloc_write(&info, 400 * 400 * sizeof(int));
	t_kernel kernel = rt_cl_create_kernel(&info, "hello");
	mlx = mlx_init();
	window = mlx_new_window(mlx, 400, 400, "IT WORKED?!");
	image = mlx_new_image(mlx, 400, 400);
	data = (int *)mlx_get_data_addr(image, &dummy, &dummy, &dummy);
	rt_cl_push_arg(&kernel, buf, sizeof(cl_mem));
	rt_cl_push_task(&kernel, 400 * 400);
	rt_cl_device_to_host(&info, buf, data, 400 * 400 * sizeof(int));
	rt_cl_join(&info);
	rt_cl_free(&info);
	rt_cl_free_kernel(&kernel);
	mlx_put_image_to_window(mlx, window, image, 0, 0);
	mlx_loop(mlx);
}
