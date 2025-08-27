

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src)
    aux_source_directory(src AUTH_SRC)
    add_library(authen SHARED
            ${AUTH_SRC}
    )
else()
    add_library(authen SHARED IMPORTED GLOBAL)
    if (WIN32)
        set_target_properties(authen PROPERTIES
                IMPORTED_LOCATION "lib/libauthen.dll"
                IMPORTED_IMPLIB   "lib/authen.lib"
        )
    elseif(APPLE)
        set_target_properties(authen PROPERTIES
                IMPORTED_LOCATION "lib/libauthen.dylib"
        )
    endif()
endif ()

target_include_directories(authen PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc)
