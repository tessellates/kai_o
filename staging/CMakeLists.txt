add_executable(${EXECUTABLE_NAME} main.cpp)
target_link_libraries(${EXECUTABLE_NAME} PUBLIC ${PROJECT_NAME})

# install(
#     TARGETS ${EXECUTABLE_NAME}
#     ARCHIVE
#         DESTINATION run
#     LIBRARY
#         DESTINATION run
#     RUNTIME
#         DESTINATION run
#     INCLUDES 
#         DESTINATION run
# )
