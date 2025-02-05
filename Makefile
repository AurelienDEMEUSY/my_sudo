##
## EPITECH PROJECT, 2024
## B-CPE-101-LYN-1-1-myprintf-aurelien.demeusy
## File description:
## Makefile
##


CFLAGS   = -g3 -Wall -Wextra -Iinclude
LDFLAGS  = -lcrypt

SRC      = src/main.c \
           src/read_file.c \
           src/switch_to.c \
           src/get_id.c \
           src/flag.c \
           src/flag_e_maj.c \
           src/flag_h.c

OBJ      = $(SRC:.c=.o)
NAME     = my_sudo

TEST_FILES = src/get_id.c src/switch_to.c src/flag_h.c tests/test.c
TEST_EXEC  = unit_tests
TEST_LDFLAGS = -lcriterion --coverage

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)

tests_run: $(TEST_EXEC)
	./$(TEST_EXEC)

$(TEST_EXEC): $(TEST_FILES)
	$(CC) $(CFLAGS) -o $(TEST_EXEC) $(TEST_FILES) $(TEST_LDFLAGS)
	sudo chown root $(TEST_EXEC)
	sudo chmod u+s $(TEST_EXEC)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME) $(TEST_EXEC) *.gcda *.gcno

re: fclean all

.PHONY: all clean fclean re tests_run
