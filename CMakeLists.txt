cmake_minimum_required(VERSION 3.5.3)
project(artificial_life)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
find_package(Boost REQUIRED COMPONENTS unit_test_framework)

set(SRC_FILES
        SimulationParameters.hpp
        helper.cpp
        helper.hpp
        AreaMap.cpp
        AreaMap.hpp
        Graphics/MainWindow.cpp
        Graphics/MainWindow.hpp
        Graphics/RendererConstants.hpp
        Subjects/SubjectsCollection.cpp
        Subjects/SubjectsCollection.hpp
        Subjects/SubjectsFactory.hpp
        Subjects/Subject.hpp
        Subjects/Animals/Animal.cpp
        Subjects/Animals/Animal.hpp
        Subjects/Animals/AnimalConstants.hpp
        Subjects/Plants/Plant.cpp
        Subjects/Plants/Plant.hpp
        Subjects/Plants/TypicalPlant.hpp
        Subjects/Plants/SuperPlant.hpp
        Subjects/Animals/Herbivore.cpp
        Subjects/Animals/Herbivore.hpp
        Subjects/Animals/Predator.cpp
        Subjects/Animals/Predator.hpp)

add_executable(artificial_life main.cpp ${SRC_FILES})
target_link_libraries(artificial_life ${SDL2_LIBRARIES})
target_include_directories(artificial_life PUBLIC ${SDL2_INCLUDE_DIRS})

set(TEST_FILES
        Unit_tests/MasterTestSuite.cpp
        Unit_tests/subjectsTests.cpp 
        Unit_tests/factoryTests.cpp 
${SRC_FILES})

add_executable(tests ${TEST_FILES})
target_link_libraries(tests ${SDL2_LIBRARIES})
target_link_libraries(tests Boost::unit_test_framework)
target_include_directories(tests PUBLIC ${SDL2_INCLUDE_DIRS})
target_include_directories(tests PUBLIC ${Boost_INCLUDE_DIRS})
add_test(unit_tests tests)
