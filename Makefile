NAME = tetris

SRC = main.c \
		alloc.c \
		mino.c \
		game.c \


SRCDIR = srcs
SRCS = $(addprefix $(SRCDIR)/, $(SRC))

OBJDIR = objs
OBJS = $(subst $(SRCDIR), $(OBJDIR), $(SRCS:.c=.o))
DEPS = $(OBJS:.o=.d)

CFLAGS = -MP -MMD -O3 -g3 -fsanitize=address
# CFLAGS += -Wall -Wextra -Werror
RM = rm -rf

INC = -I./includes/

LIBFT = libft/libft.a

ifeq ($(MAKECMDGOALS), debug)
	CFLAGS += -DDEBUG
endif

ifeq ($(MAKECMDGOALS), address)
	CFLAGS += -g3 -fsanitize=address
endif

CHECK		= \033[32m[✔]\033[0m
REMOVE		= \033[31m[✘]\033[0m
GENERATE	= \033[33m[➤]\033[0m
BLUE		= \033[1;34m
YELLOW		= \033[1;33m
RESET		= \033[0m

TOTAL_FILES := $(shell echo $(words $(SRCS)))
CURRENT_FILE = 1

define progress
    @printf "$(GENERATE) $(YELLOW)tetris obj file gen Progress: %3d%% (%d/%d)$(RESET)\r" $$(($(CURRENT_FILE)*100/$(TOTAL_FILES))) $(CURRENT_FILE) $(TOTAL_FILES)
    @$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE)+1))))
    @if [ $(CURRENT_FILE) -gt $(TOTAL_FILES) ]; then \
        printf "$(GENERATE) $(YELLOW)Finish Generating TETRIS Object files !%-50.50s\n$(RESET)"; \
    fi
endef

all : $(NAME)

$(NAME): $(OBJS)
	@ $(CC) $(CFLAGS) -o $@ $^ -lncurses
	@ printf "$(CHECK) $(BLUE)Compiling tetris...%-50.50s\n$(RESET)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@ mkdir -p $(@D)
	@ $(CC) $(CFLAGS) $(INC) -o $@ -c $<
	$(call progress)

clean :
	@ $(RM) $(OBJDIR)
	@ echo "$(REMOVE) $(BLUE)Remove tetris object files. $(RESET)"

fclean :
	@ $(RM) $(OBJDIR) $(NAME)
	@ echo "$(REMOVE) $(BLUE)Remove tetris object files and $(NAME). $(RESET)"

re : fclean all

debug : re

address : re

.PHONY : all clean fclean re debug address

-include $(DEPS)