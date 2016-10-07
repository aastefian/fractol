NAME = fractol

HDRDIR = header
SRCDIR = ./srcs
CUDASRC = cudasrc
CUDAHDR = cudaheader

CSRC =	$(CUDASRC)/cuda_burningship.cu \
		$(CUDASRC)/cuda_ju.cu \
		$(CUDASRC)/cuda_md.cu \

COBJ = cuda_burningship.o \
	   cuda_ju.o \
	   cuda_md.o \

OBJ =	main.o \
		extra.o \
		extra2.o \
		extra3.o \
		image_processing.o \
		cpu_julia.o \
		cpu_burningship.o \
		cpu_mandelbrot.o \
		julia_scaling.o \
		burningship_scaling.o \
		mandelbrot_scaling.o \
		julia_caller.o \
		julia_handlers.o \
		julia_handlers_2.o \
		burningship_caller.o \
		burningship_handlers.o \
		burningship_handlers_2.o \
		mandelbrot_caller.o \
		mandelbrot_handlers.o \
		mandelbrot_handlers_2.o \

SOURCE = $(SRCDIR)/main.c \
		 $(SRCDIR)/extra.c \
		 $(SRCDIR)/extra2.c \
		 $(SRCDIR)/extra3.c \
		 $(SRCDIR)/image_processing.c \
		 $(SRCDIR)/cpu_julia.c \
		 $(SRCDIR)/cpu_burningship.c \
		 $(SRCDIR)/cpu_mandelbrot.c \
		 $(SRCDIR)/julia_scaling.c \
		 $(SRCDIR)/burningship_scaling.c \
		 $(SRCDIR)/mandelbrot_scaling.c \
		 $(SRCDIR)/julia_caller.c \
		 $(SRCDIR)/burningship_caller.c \
		 $(SRCDIR)/mandelbrot_caller.c \
		 $(SRCDIR)/julia_handlers.c \
		 $(SRCDIR)/julia_handlers_2.c \
		 $(SRCDIR)/burningship_handlers.c \
		 $(SRCDIR)/burningship_handlers_2.c \
		 $(SRCDIR)/mandelbrot_handlers.c \
		 $(SRCDIR)/mandelbrot_handlers_2.c \

OFLAGS = -Wall -Werror -Wextra

LIBFTDIR = libft/
LIBFT =  $(LIBFTDIR)libft.a

MLXDIR = mlx-lib
MLXLIB = $(MLXDIR)/libmlx.a

CUDA=/Developer/NVIDIA/CUDA-7.5/
NVCC=/Developer/NVIDIA/CUDA-7.5/bin/nvcc
NVCC_C = -ccbin /usr/bin/clang -m64
NVCC_FRAMEWORK = -Xlinker -framework,OpenGL -Xlinker -framework,AppKit
NVCC_LIB = -Xlinker -rpath -Xlinker /Developer/NVIDIA/CUDA-7.5/lib
NVCC_ARCH = -Xcompiler -arch -Xcompiler x86_64
NVCC_STD = -Xcompiler -stdlib=libstdc++
NVCC_VCODE = -gencode arch=compute_20,code=sm_20 -gencode arch=compute_30,code=sm_30
NVCC_FLAGS = -Xcompiler -Werror -Xcompiler -Wall -Xcompiler -Wextra 

all: $(NAME)


$(NAME): $(LIBFT) $(MLXLIB) $(OBJ) $(COBJ)
	@echo "--Linking everything-----"
	@nvcc $(NVCC_C) $(NVCC_ARCH) $(NVCC_STD) $(NVCC_FRAMEWORK) $(NVCC_LIB) -o $(NAME) $(OBJ) $(LIBFT) $(MLXLIB) $(COBJ)
	@echo    "----------------------------------------------------------------------------------------------------------------------------------------------------------"
	@echo    "|                                                                                                      ''''''                                            |"
	@echo    "| FFFFFFFFFFFFFFFFFFFFFF                                                                tttt           '::::'     OOOOOOOOO     LLLLLLLLLLL              |"
	@echo    "| F::::::::::::::::::::F                                                             ttt:::t           '::::'   OO:::::::::OO   L:::::::::L              |"
	@echo    "| F::::::::::::::::::::F                                                             t:::::t           ':::'' OO:::::::::::::OO L:::::::::L              |"
	@echo    "| FF::::::FFFFFFFFF::::F                                                             t:::::t          ':::'  O:::::::OOO:::::::OLL:::::::LL              |"
	@echo    "|   F:::::F       FFFFFFrrrrr   rrrrrrrrr   aaaaaaaaaaaaa      ccccccccccccccccttttttt:::::ttttttt    ''''   O::::::O   O::::::O  L:::::L                |"
	@echo    "|   F:::::F             r::::rrr:::::::::r  a::::::::::::a   cc:::::::::::::::ct:::::::::::::::::t           O:::::O     O:::::O  L:::::L                |"
	@echo    "|   F::::::FFFFFFFFFF   r:::::::::::::::::r aaaaaaaaa:::::a c:::::::::::::::::ct:::::::::::::::::t           O:::::O     O:::::O  L:::::L                |"
	@echo    "|   F:::::::::::::::F   rr::::::rrrrr::::::r         a::::ac:::::::cccccc:::::ctttttt:::::::tttttt           O:::::O     O:::::O  L:::::L                |"
	@echo    "|   F:::::::::::::::F    r:::::r     r:::::r  aaaaaaa:::::ac::::::c     ccccccc      t:::::t                 O:::::O     O:::::O  L:::::L                |"
	@echo    "|   F::::::FFFFFFFFFF    r:::::r     rrrrrrraa::::::::::::ac:::::c                   t:::::t                 O:::::O     O:::::O  L:::::L                |"
	@echo    "|   F:::::F              r:::::r           a::::aaaa::::::ac:::::c                   t:::::t                 O:::::O     O:::::O  L:::::L                |"
	@echo    "|   F:::::F              r:::::r          a::::a    a:::::ac::::::c     ccccccc      t:::::t    tttttt       O::::::O   O::::::O  L:::::L         LLLLLL |"
	@echo    "| FF:::::::FF            r:::::r          a::::a    a:::::ac:::::::cccccc:::::c      t::::::tttt:::::t       O:::::::OOO:::::::OLL:::::::LLLLLLLLL:::::L |"
	@echo    "| F::::::::FF            r:::::r          a:::::aaaa::::::a c:::::::::::::::::c      tt::::::::::::::t        OO:::::::::::::OO L::::::::::::::::::::::L |"
	@echo    "| F::::::::FF            r:::::r           a::::::::::aa:::a cc:::::::::::::::c        tt:::::::::::tt          OO:::::::::OO   L::::::::::::::::::::::L |"
	@echo    "| FFFFFFFFFFF            rrrrrrr            aaaaaaaaaa  aaaa   cccccccccccccccc          ttttttttttt              OOOOOOOOO     LLLLLLLLLLLLLLLLLLLLLLLL |"
	@echo    "----------------------------------------------------------------------------------------------------------------------------------------------------------"
	@echo    "| Usage : ./fractol [param]                                                                                                                              |"
	@echo    "| Availble fractals(parameters) are:                                                                                                                     |"
	@echo    "|   -Julia (ju)                                                                                                                                          |"
	@echo    "|   -Mandelbrot (md)                                                                                                                                     |"
	@echo    "|   -Burning Ship (bs)                                                                                                                                   |"
	@echo    "----------------------------------------------------------------------------------------------------------------------------------------------------------"

$(LIBFT):
	@echo "--Compiling libft--------"
	@make re -C $(LIBFTDIR)

$(COBJ):
	@echo "--Compiling CUDA sources-"
	@nvcc $(NVCC_C) $(NVCC_ARCH) $(NVCC_STD) $(NVCC_VCODE) $(NVCC_FLAGS) -I $(CUDA)/include -I header -I $(CUDAHDR) -c $(CSRC)

$(MLXLIB):
	@echo "--Compiling mlx-lib------"
	@make -C $(MLXDIR)

$(OBJ):
	@gcc -iquote $(LIBFTDIR) -I $(MLXDIR) -iquote $(CUDAHDR) -c $(SOURCE)

clean:
	@echo "--Cleanning leftovers----"
	@rm -f $(OBJ) $(COBJ)

fclean: clean
	@echo "--Cleanning executable---"
	@rm -f $(NAME)

re: fclean all
