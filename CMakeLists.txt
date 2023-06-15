add_executable(${PROJECT_NAME} main.cpp weather.cpp print_weather.cpp string_images.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE cpr)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json)
target_link_libraries(${PROJECT_NAME} PRIVATE tabulate)