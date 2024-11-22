
#We create a library for the functions in our program
add_library(edge_distance edge_distance.c
        load_nodes_from_file.h
        load_nodes_from_file.c)
add_library(branch_and_bound branch_and_bound.c
        load_nodes_from_file.h
        load_nodes_from_file.c)

#Make header files in the current folder available for #include
target_include_directories(edge_distance PUBLIC .)
target_include_directories(branch_and_bound PUBLIC .)

#Adding the programs we want to be executable:
add_executable(program program.c
        load_nodes_from_file.h
        load_nodes_from_file.c
        address_generator.c
        address_generator.h
)

#We link our library to the game executable, so the executable can access the functions in the library.
target_link_libraries(program edge_distance)
target_link_libraries(program branch_and_bound)