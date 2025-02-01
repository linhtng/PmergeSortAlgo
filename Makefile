CFLAGS = c++ -Wall -Wextra -Werror -g3 -std=c++17 -I include

NAME = PmergeMe

SRC_DIR = src/
SRC = main.cpp \
      PmergeMe.cpp

SRCS = $(addprefix $(SRC_DIR), $(SRC))

OBJ_PATH = ./objects/
OBJ		= $(SRC:.cpp=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))

all: $(NAME)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

$(OBJ_PATH)%.o: $(SRC_DIR)%.cpp
	$(CFLAGS) -c $< -o $@

$(NAME): $(OBJ_PATH) $(OBJS)
	$(CFLAGS) $(OBJS) -o $@

test:
	@mkdir -p test_output
	@$(CFLAGS) tests/tests.cpp $(OBJ_PATH)PmergeMe.o -o test_pmerge
	@./test_pmerge > test_output/detailed_output.txt 2>&1
	@grep -A 10 "=== Test Summary ===" test_output/detailed_output.txt
	@echo "Detailed test results saved in test_output/detailed_output.txt"

clean:
	rm -rf $(OBJ_PATH) test_output
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all
