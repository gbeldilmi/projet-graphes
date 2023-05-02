CXX_FLAGS := 

.PHONY : all
all : ex1 ex2 ex4 ex5
ex% : ex%.cpp
	g++ $(CXX_FLAGS) $< -o $@  && ./$@
