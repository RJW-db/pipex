NAME			:=	pipex

MAKEFLAGS		+=	-j
COMPILER		:=	cc

BASE_FLAGS		:=	-std=c99 -Wall -Wextra -Werror

PEDANTIC		:=	-Wpedantic -pedantic-errors -Wundef -Wstrict-prototypes

WARNINGS		:=	-Wshadow -Wconversion -Wsign-conversion			\
					-Wformat=2 -Wuninitialized -Wunreachable-code

CAST_WARNINGS	:=	-Wbad-function-cast
ifeq ($(shell $(COMPILER) --version | grep -c "gcc"),1)
CAST_WARNINGS	+=	-Wcast-function-type
endif

DEPFLAGS		:=	-MMD -MP

OPTIMIZATION	:=	-O2
SECURITY		:=	-fstack-protector-strong
ifeq ($(shell uname -s),Linux)
SECURITY		+=	-D_FORTIFY_SOURCE=2
FSANITIZE		:=	leak
endif

SANITIZERS		:=	-fsanitize=$(FSANITIZE),address,undefined,null,integer-divide-by-zero,signed-integer-overflow,bounds,alignment
DEBUG_FLAGS		:=	-fno-omit-frame-pointer

CFLAGS			:=	$(BASE_FLAGS) $(PEDANTIC) $(WARNINGS) $(CAST_WARNINGS)	\
					$(DEPFLAGS) $(OPTIMIZATION) $(SECURITY)

ifneq ($(filter valgrind,$(MAKECMDGOALS)),)
CFLAGS			+=	-g $(DEBUG_FLAGS)
else ifneq ($(filter debug,$(MAKECMDGOALS)),)
CFLAGS		+=	-g3 $(SANITIZERS) $(DEBUG_FLAGS) -fno-sanitize-recover=all
endif

PRINT_NO_DIR	:=	--no-print-directory
RM				:=	rm -rf

SRC_DIR			:=	src
INC_DIR			:=	include
BUILD_DIR		:=	.build

# Libftx
EXT_DIR			:=	extern_library
LIBFTX_A		:=	libftx.a
LIBFTX_DIR		:=	$(EXT_DIR)/libftx
LIBFTX			:=	$(LIBFTX_DIR)/$(LIBFTX_A)
LIBFTX_INC		:=	$(LIBFTX_DIR)/$(INC_DIR)
LIBFTX_SENTINEL	:=	$(LIBFTX_DIR)/.git

SRC				:=	main.c						\
					pipex.c						\
					pipex_forking_utils.c		\
					pipex_child_processes.c		\
					pipex_heredoc_bonus.c		\
					writing.c

SRC				:=	$(addprefix $(SRC_DIR)/, $(SRC))
OBJ				:=	$(SRC:%.c=$(BUILD_DIR)/%.o)
DEPS			:=	$(OBJ:.o=.d)

DELETE			:=	*.out			**/*.out		.DS_Store	\
					**/.DS_Store	.dSYM/			**/.dSYM/

INCLUDES		:=	-I $(INC_DIR) -I $(LIBFTX_INC)
BUILD			:=	$(COMPILER) $(INCLUDES) $(CFLAGS)

all: $(NAME)

$(NAME): $(OBJ) | $(LIBFTX)
	@$(BUILD) $(OBJ) $(LIBFTX) -o $(NAME)
	@printf "$(CREATED)" $@ $(CUR_DIR)

$(OBJ): | $(LIBFTX)

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(COMPILER) $(CFLAGS) -I $(INC_DIR) -I $(LIBFTX_INC) -c $< -o $@

$(LIBFTX_SENTINEL):
	git submodule update --init $(LIBFTX_DIR)
	git -C $(LIBFTX_DIR) checkout $(shell git config -f .gitmodules submodule.$(LIBFTX_DIR).branch || echo main)
	git submodule update --remote --merge $(LIBFTX_DIR)
	cd $(LIBFTX_DIR) && git submodule update --init $(SRC_DIR)/printf $(SRC_DIR)/get_next_line
	cd $(LIBFTX_DIR)/$(SRC_DIR)/printf &&																					\
		git checkout $$(git config -f $(abspath $(LIBFTX_DIR))/.gitmodules submodule.src/printf.branch || echo main)
	cd $(LIBFTX_DIR)/src/get_next_line &&																					\
		git checkout $$(git config -f $(abspath $(LIBFTX_DIR))/.gitmodules submodule.src/get_next_line.branch || echo main)

$(LIBFTX): | $(LIBFTX_SENTINEL)
	@$(MAKE) $(PRINT_NO_DIR) -C $(LIBFTX_DIR) SUBMODULES_CMD= all printf gnl $(filter debug valgrind,$(MAKECMDGOALS))

clean:
	@$(RM) $(BUILD_DIR) $(DELETE)
	@printf "$(REMOVED)" $(BUILD_DIR) $(CUR_DIR)$(BUILD_DIR)

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) $(PRINT_NO_DIR) -C $(LIBFTX_DIR) fclean
	@printf "$(REMOVED)" $(NAME) $(CUR_DIR)

re:
	$(MAKE) $(PRINT_NO_DIR) fclean
	$(MAKE) $(PRINT_NO_DIR) all

pip:
	./pipex "./test/test1.txt" "ls -la" "cat -e" "./test/test2.txt"
	cat ./test/test2.txt

pip2:
	./pipex "./test/test1.txt" "cat" "grep -a3 3" "grep -a2 3" "./test/test2.txt"
	cat ./test/test2.txt

pip3:
	cat ./test/test2.txt
	./pipex "./test/test1.txt" "sleep 5" "sleep 5" "sleep 5" "sleep 5" "sleep 5" "./test/test2.txt"

pip4:
	./pipex "./test/test1.txt" /bin/ls "cat -e" "sort" "./test/test2.txt"
	cat ./test/test2.txt

pip5:
	./pipex "./test/test1.txt" "./test/program" "cat -e" sort "./test/test2.txt"
	cat ./test/test2.txt

pip6:
	./pipex "./test/test1.txt" "./test/program" sort "./test/test2.txt"
	cat ./test/test2.txt

pip7:
	./pipex "./test/test1.txt" 'sed "s/And/But/"' 'grep But' "./test/test2.txt"
	cat ./test/test2.txt

pip8:
	./pipex "./test/test1.txt" './test/program space' 'wc' "./test/test2.txt"
	cat ./test/test2.txt

pipb:
	./pipex here_doc LIMITER "sort" "wc -l" ./test/test2.txt
	cat ./test/test2.txt

pipb2:
	./pipex here_doc LIMITER "sort" ./test/test2.txt
	cat ./test/test2.txt

pipb3:
	./pipex here_doc LIMITER "sort" "cat -e" ./test/test2.txt
	cat ./test/test2.txt

pipb4:
	./pipex here_doc e "sort" "cat -e" ./test/test2.txt
	cat ./test/test2.txt

debug: all

valgrind: all

print-%:
	$(info $($*))

-include $(DEPS)

.PHONY:	all clean fclean re						\
		pip pip2 pip3 pip4 pip5 pip6 pip7 pip8	\
		pipb pipb2 pipb3 pipb4					\
		debug valgrind print-%

# Terminal markup
BOLD			:=	\033[1m
GREEN			:=	\033[32m
MAGENTA			:=	\033[35m
CYAN			:=	\033[36m
RESET			:=	\033[0m

R_MARK_UP		:=	$(MAGENTA)$(BOLD)
CA_MARK_UP		:=	$(GREEN)$(BOLD)

# Current directory and formatted status messages
CUR_DIR			:=	$(dir $(abspath $(firstword $(MAKEFILE_LIST))))
REMOVED			:=	$(R_MARK_UP)REMOVED $(CYAN)%s$(MAGENTA) (%s) $(RESET)\n
CREATED			:=	$(CA_MARK_UP)CREATED $(CYAN)%s$(GREEN) (%s) $(RESET)\n
