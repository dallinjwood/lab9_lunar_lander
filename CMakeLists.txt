add_executable(lab9m1.elf main.c game_control.c lander.c maps.c)
target_link_libraries(lab9m1.elf ${330_LIBS} intervalTimer interrupts buttons_switches )
set_target_properties(lab9m1.elf PROPERTIES LINKER_LANGUAGE CXX)