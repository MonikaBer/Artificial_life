#OBJS specifies which files to compile as part of the project
OBJS = main.cpp Graphics/MainWindow.cpp Subjects/Plants/Plant.cpp Subjects/Animals/Animal.cpp Subjects/Animals/Herbivore.cpp Subjects/Animals/Predator.cpp 
TEST_OBJS = Unit_tests/subjectsTests.cpp Subjects/Animals/Animal.cpp Subjects/Animals/Herbivore.cpp Subjects/Animals/Predator.cpp Subjects/Plants/Plant.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = 

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2
TEST_LINKER_FLAGS = -lboost_unit_test_framework

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = a.out
TEST_NAME = test.out

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
test : 
	$(CC) $(TEST_OBJS) $(TEST_LINKER_FLAGS) -o $(TEST_NAME)

clean:
	rm $(OBJ_NAME) $(TEST_NAME)