# In this List file, we declare some variables and a function
# so we can copy the Resources folder common to all tests
# into the test binary directory.

# This is the full path to the resources
set(RES_DIR ${CMAKE_CURRENT_LIST_DIR}/Resources)

# 
# Adds a custom command to the given target, that copies the given file list
#
function(copy_resources DEPENDENCY_TARGET)
    
    set(DESTINATION_DIR $<TARGET_FILE_DIR:${DEPENDENCY_TARGET}>/Resources)

    add_custom_command(TARGET ${DEPENDENCY_TARGET}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${DESTINATION_DIR}
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${RES_DIR} ${DESTINATION_DIR}
        COMMENT "Copying resources: ${RES_DIR} to ${DESTINATION_DIR}"
    )

endfunction()

#
# This function links and includes all the engine necessary files to all tests
#
function(setup_test TESTNAME)

    # Include the directories of the engine
    target_include_directories(${TESTNAME}
        PUBLIC ../../src
    )

    # Link to the engine target
    target_link_libraries(${TESTNAME} simple-cpp-engine)

    # Specify that that our test target is dependant of the engine target
    add_dependencies(${TESTNAME} simple-cpp-engine)

    # specify that we want to copy the resources folder into this binary folder
    copy_resources(${TESTNAME} $<TARGET_FILE_DIR:${TESTNAME}>)

endfunction()


add_subdirectory(InputTest)
add_subdirectory(Spritebatch)
add_subdirectory(GameClass)
add_subdirectory(BitmapFont)
add_subdirectory(FrameBufferTest)
