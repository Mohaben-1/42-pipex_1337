NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror


SRC = pipex.c ft_split.c ft_strjoin.c utils.c handle_fds.c cmd_handle.c
OBJ = $(SRC:.c=.o)

SRC_BNS = pipex_bonus.c ft_split_bonus.c ft_strjoin_bonus.c utils_bonus.c handle_fds_bonus.c cmd_handle_bonus.c get_next_line_bonus.c
OBJ_BNS = $(SRC_BNS:.c=.o)


$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

all: $(NAME)

bonus: $(OBJ_BNS)
	$(CC) $(CFLAGS) $(OBJ_BNS) -o $(NAME)
	@touch bonus

%_bonus.o: %_bonus.c pipex_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c pipex.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJ_BNS) bonus

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean
