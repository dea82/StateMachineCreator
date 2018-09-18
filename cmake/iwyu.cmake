function(iwyu_check BUILD_IWYU)
    if (BUILD_IWYU)
        set(iwyu_EXECUTABLE_NAME include-what-you-use)
        find_program(iwyu_EXECUTABLE ${iwyu_EXECUTABLE_NAME})
        if (iwyu_EXECUTABLE)
            message(STATUS "Successfully found IWYU.")
            get_filename_component(iwyu_EXECUTABLE_PATH ${iwyu_EXECUTABLE} DIRECTORY)
            set(iwyu_map_files_PATH ${iwyu_EXECUTABLE_PATH}/../share/include-what-you-use)
            #TODO: This shall be input to function => make this a function
            set(iwyu_MAP_FILES
                    qt5_4.imp
                    )
            #TODO: Print all map files used
            set(map_files_option "")
            foreach (MAP_FILE ${iwyu_MAP_FILES})
                set(map_files_option ${map_files_option} --mapping_file=${iwyu_map_files_PATH}/${MAP_FILE})
            endforeach ()
            set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE ${iwyu_EXECUTABLE} -Xiwyu ${map_files_option} PARENT_SCOPE)
        else ()
            message(STATUS "Unable to find the ${iwyu_EXECUTABLE_NAME} executable")
        endif ()
    endif ()
endfunction()