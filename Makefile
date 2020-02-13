# ft_ssl Makefile

CC := gcc
LD := ld

CFLAGS := -g -Wall -Werror -Wextra -c \
		-I./include -I./libft/include 

LDFLAGS := -lc -L./libft -lft \
			-e _main -arch x86_64 -macosx_version_min 10.13

INCDIR := include
SRCDIR := src
OBJDIR := build

SRCS := $(addprefix $(SRCDIR)/, \
		main.c \
		ft_getopt.c ft_argparse.c \
		ft_fdread.c \
		ft_envnew.c \
		ft_md5.c ft_sha256.c)

OBJS := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

NAME := ft_ssl

all : $(NAME)

$(NAME) : $(OBJS)
	@if [[ ! -e ./libft/libft.a ]]; then make -C ./libft; fi
	$(LD) $(LDFLAGS) $^ -o $@

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@if [[ ! -e $(OBJDIR) ]]; then mkdir $(OBJDIR); fi
	@$(CC) $(CFLAGS) $< -o $@

.PNOHY : all clean fclean re

clean :
	@if [[ -e $(OBJDIR) ]]; then rm -rf $(OBJDIR); fi
#	@make clean -C ./libft

fclean : clean
	@rm -f $(NAME)
#	@make fclean -C ./libft

re : fclean all