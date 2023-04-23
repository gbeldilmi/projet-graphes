CXX_FLAGS := -v -Wall -Werror -Wextra -O3

.PHONY : all, ex1, ex2
all : ex1 ex2
% : %.cpp
	g++ $(CXX_FLAGS) $< -o $@ 
	./$@
