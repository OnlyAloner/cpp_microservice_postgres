include(FetchContent)

cmake_minimum_required(VERSION 3.16)

set(project_name my-project) ## rename your project here

project(${project_name})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(${project_name}-lib
        src/AppComponent.hpp
        src/storage/postgres/Postgres.cpp
        src/storage/postgres/Postgres.hpp
        src/storage/postgres/crud/Crud.hpp
        src/storage/postgres/crud/Crud.cpp
)
FetchContent_Declare(
        libpqxx
        GIT_REPOSITORY https://github.com/jtv/libpqxx.git
        GIT_TAG a6b1d60e74c1427c8ac2324b85cd4a0dc2068332
)
set(PQXX_LIBRARIES pqxx_static)

FetchContent_MakeAvailable(libpqxx)

FetchContent_Declare(
        libcds
        GIT_REPOSITORY https://github.com/khizmax/libcds
        GIT_TAG master
)
set(CDS_LIBRARIES cds)

FetchContent_MakeAvailable(libcds)


find_package(Crow)
find_package(Boost "1.81.0" COMPONENTS filesystem system thread program_options regex)
find_package(dmitigr_libs)

target_link_libraries(${project_name}-lib
        PUBLIC ${PQXX_LIBRARIES}
        PUBLIC Boost::thread
        # PUBLIC Boost::tuple
        PUBLIC Crow::Crow
        PUBLIC ${CDS_LIBRARIES}
        PUBLIC dmitigr_pgfe
)

target_include_directories(${project_name}-lib PUBLIC src)

## add executables

add_executable(${project_name}-exe
        src/App.cpp
)

target_link_libraries(${project_name}-exe ${project_name}-lib)
add_dependencies(${project_name}-exe ${project_name}-lib)