#ifndef CUDA_JU_H
# define CUDA_JU_H
#include "../includes/fractol.h"
# ifdef __cplusplus
	extern "C"
#endif
	void	cuda_call_julia(unsigned int *a_h, unsigned int constw, unsigned int consth, float middlex, float middley, float scale, t_com c, unsigned int max, unsigned int reset);
	int		sign(float x);
#endif
