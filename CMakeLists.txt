cmake_minimum_required(VERSION 3.10)
project(SFMLProject)
set(CMAKE_CXX_STANDARD 17)

# Find the SFML package
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Specify your source files explicitly
add_executable(${PROJECT_NAME}
    main.cpp
    Bullet.cpp
    Enemy.cpp
    Game.cpp
    Player.cpp
    # Add other files here if needed
)

# Link SFML libraries
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)

# Ensure the executable is placed in a known output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Copy assets (Textures and Fonts directories) to the output directory after build
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/Textures" "${CMAKE_BINARY_DIR}/bin/Textures"
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/Fonts" "${CMAKE_BINARY_DIR}/bin/Fonts"
)

# Cross-platform SFML library path configuration
if (APPLE)
    set(SFML_ROOT "/opt/homebrew")  # Adjust if your SFML path is different
    target_include_directories(${PROJECT_NAME} PRIVATE "${SFML_ROOT}/include")
    target_link_directories(${PROJECT_NAME} PRIVATE "${SFML_ROOT}/lib")
elseif (UNIX AND NOT APPLE)
    target_include_directories(${PROJECT_NAME} PRIVATE "/usr/include/SFML")
    target_link_directories(${PROJECT_NAME} PRIVATE "/usr/lib")
elseif (WIN32)
    set(SFML_ROOT "C:/SFML")  # Adjust if SFML is in a different path on Windows
    target_include_directories(${PROJECT_NAME} PRIVATE "${SFML_ROOT}/include")
    target_link_directories(${PROJECT_NAME} PRIVATE "${SFML_ROOT}/lib")
    set(SFML_STATIC_LIBRARIES FALSE)
    add_definitions(-DSFML_STATIC)
endif()

# Copy SFML DLLs on Windows if using dynamic linking
if (WIN32 AND NOT SFML_STATIC_LIBRARIES)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${SFML_ROOT}/bin" $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()
