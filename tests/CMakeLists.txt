find_package( Boost REQUIRED COMPONENTS program_options regex log log_setup unit_test_framework)


add_executable(emu_tests 
    "Main.cpp"   
    "OpcodeTests.cpp"                 
    )
target_link_libraries(emu_tests PUBLIC gbc_emulator_lib Boost::unit_test_framework Boost::log Boost::log_setup) 