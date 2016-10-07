#ifndef CUDA_BS_H
# define CUDA_BS_H
# ifdef __cplusplus
	extern "C"
#endif
	void cuda_call_bs(unsigned int* a_h, unsigned int constw, unsigned int consth, float middlex, float middley, float scale, unsigned int max, unsigned int reset);
#endif
