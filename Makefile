NAME =		pipex

CFLAGS =	-Wall -Wextra -Werror -fsanitize=address
RM =		rm -f
MKDIR_P =	mkdir -p

MISC =		*.out \
			.DS_Store \
			*.dSYM/

SRC =		pipex.c \
			pipex_forking_utils.c \
			pipex_child_processes.c \
			pipex_heredoc_bonus.c

LIBFT =		ft_strlen.c \
			ft_memmove.c \
			ft_memcpy.c \
			ft_strlcpy.c \
			ft_strlcat.c \
			ft_isalpha.c \
			ft_isdigit.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_memset.c \
			ft_bzero.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strncmp.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_strnstr.c \
			ft_atoi.c \
			ft_calloc.c \
			ft_strdup.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_split.c \
			ft_itoa.c \
			ft_strmapi.c \
			ft_striteri.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstmap.c \
			get_next_line.c \
			ft_cpy.c \
			ft_free_str.c

PRINTF =	ft_printf.c \
			ft_printf_count.c \
			ft_printf_utils.c \
			ft_bonus_flags.c \
			ft_bonus_sort_spec.c \
			ft_bonus_char.c \
			ft_bonus_str.c \
			ft_bonus_str_count.c \
			ft_bonus_int.c \
			ft_bonus_unsigned.c

OBJ_DIR =	objects

PIP_DIR =	src
PIP_OBJ = 	$(patsubst $(PIP_DIR)/%.c, $(OBJ_DIR)/%.o, $(addprefix $(PIP_DIR)/, $(SRC)))

LIB_DIR =	libft
LIBOBJ = 	$(patsubst $(LIB_DIR)/%.c, $(OBJ_DIR)/%.o, $(addprefix $(LIB_DIR)/, $(LIBFT)))
PR_DIR = 	ft_printf
PROBJ = 	$(patsubst $(PR_DIR)/%.c, $(OBJ_DIR)/%.o, $(addprefix $(PR_DIR)/, $(PRINTF)))
OBJ = 		$(PIP_OBJ) $(LIBOBJ) $(PROBJ)

all:	objects_mkdir $(NAME)

$(OBJ_DIR)/%.o: $(PIP_DIR)/%.c
	cc $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(LIB_DIR)/%.c
	cc $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(PR_DIR)/%.c
	cc $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@cc $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	@$(RM) -r $(OBJ_DIR) $(MISC)

fclean:	clean
	@$(RM) $(NAME)

re:		fclean all

objects_mkdir:
	@$(MKDIR_P) objects

pip:
	./pipex "./misc/test1.txt" "ls -la" "cat -e" "./misc/test2.txt"
	cat ./misc/test2.txt

pip2:
	./pipex "./misc/test1.txt" "cat" "grep -a3 3" "grep -a2 3" "./misc/test2.txt"
	cat ./misc/test2.txt

pip3:
	# ./pipex "./misc/test1.txt" "sleep 5" "sleep 5" "sleep 5" "sleep 5" sleep 5 "./misc/test2.txt"
	cat ./misc/test2.txt
	./pipex "./misc/test1.txt" "sleep 5" "sleep 5" "sleep 5" "sleep 5" "sleep 5" "./misc/test2.txt"

pip4:
	./pipex "./misc/test1.txt" /bin/ls "cat -e" "sort" "./misc/test2.txt"
	cat ./misc/test2.txt

pip5:
	./pipex "./misc/test1.txt" "./misc/program" "cat -e" sort "./misc/test2.txt"
	cat ./misc/test2.txt

pip6:
	./pipex "./misc/test1.txt" "./misc/program" sort "./misc/test2.txt"
	cat ./misc/test2.txt

pip7:
	./pipex "./misc/test1.txt"  'sed    "s/And/But/"' 'grep But' "./misc/test2.txt"
	cat ./misc/test2.txt

pip8:
	./pipex "./misc/test1.txt"  './misc/program space' 'wc' "./misc/test2.txt"
	cat ./misc/test2.txt

pipb:
	./pipex here_doc LIMITER "sort" "wc -l" ./misc/test2.txt
	cat ./misc/test2.txt

pipb2:
	./pipex here_doc LIMITER "sort" ./misc/test2.txt
	cat ./misc/test2.txt

pipb3:
	./pipex here_doc LIMITER "sort" "cat -e" ./misc/test2.txt
	cat ./misc/test2.txt

pipb4:
	./pipex here_doc e "sort" "cat -e" ./misc/test2.txt
	cat ./misc/test2.txt

.PHONY:	all clean fclean re objects_mkdir
