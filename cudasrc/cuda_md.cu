#include <cuda.h>
#include "../includes/fractol.h"
#include "../libft/libft.h"
#include <stdio.h>
# define gpuErrchk(ans) { gpuAssert((ans), __FILE__, __LINE__); }
__global__ void md_2(unsigned int *a, unsigned int constw, unsigned int consth, float middlex, float middley, float scale, unsigned int max)
{
  int row = blockIdx.y * blockDim.y + threadIdx.y;
  int col = blockIdx.x * blockDim.x + threadIdx.x;
  int index = row * constw + col;
  if(col >= constw || row >= consth) return;
	float cr = ((col - ((float)(DEF_WIN_WIDTH - 2) / 2)) / scale) - middlex;
	float ci = ((row - ((float)(DEF_WIN_HEIGHT - 2) / 2)) / scale) + middley;
    float zn_1r = 0;
    float zn_1i = 0;
    float zn_r = 0;
    float zn_i = 0;
   unsigned int iteration = 0;
  while (iteration < max)
  {
    zn_r = (zn_1r * zn_1r) - (zn_1i * zn_1i) + cr;
	zn_i = 2 * (zn_1r * zn_1i) + ci;
	zn_1r = zn_r;
	zn_1i = zn_i;
	if ((zn_r * zn_r + zn_i * zn_i) > 4)
		break;
	iteration++;
  }
  a[index] = iteration;
}

inline void gpuAssert(cudaError_t code, const char *file, int line, bool abort=true)
{
	if (code != cudaSuccess) 
	{
		(void)file;
		(void)line;
		if (abort) exit(code);
	}
}

extern "C" void cuda_call_md(unsigned int *a_h, unsigned int constw, unsigned int consth, float middlex, float middley, float scale, unsigned int max, unsigned int reset)
{
  static unsigned int *a_d = NULL;
  static size_t size = 0;
  static dim3 block_size(16, 16);
  static dim3 grid_size(DEF_WIN_WIDTH / block_size.x + (DEF_WIN_WIDTH - DEF_WIN_WIDTH / block_size.x), DEF_WIN_HEIGHT / block_size.y + (DEF_WIN_HEIGHT - DEF_WIN_HEIGHT / block_size.y));  
  if (!reset)
  {
    if (size == 0)
    {
      size = constw * consth * sizeof(unsigned int);
      gpuErrchk(cudaMalloc((void **) &a_d, size));
    }
   md_2 <<< grid_size, block_size, 0 >>> (a_d, constw, consth, middlex, middley, scale, max);
   gpuErrchk(cudaMemcpy(a_h, a_d, size, cudaMemcpyDeviceToHost));
  }
  else
  {
    cudaFree(a_d);
  }
}
