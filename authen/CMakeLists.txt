
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src)
    set(AUTHEN_USE_PREBUILD FALSE PARENT_SCOPE)
    aux_source_directory(src AUTH_SRC)
    add_library(authen SHARED
            ${AUTH_SRC}
    )
    target_compile_definitions(authen PRIVATE EXPORT_AUTHEN)
    if(MSVC)
        target_compile_options(authen PRIVATE /utf-8)
    elseif (Clang)
        target_compile_options(authen PRIVATE -fvisibility=hidden)
    endif ()

    install(
            TARGETS authen
            ARCHIVE DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/lib   # 安装 .lib 文件
            RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/lib   # 安装 .dll 文件
            LIBRARY DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/lib   # AI says 为了兼容性
    )

    target_include_directories(authen PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/inc)

else()
    set(AUTHEN_USE_PREBUILD TRUE PARENT_SCOPE)

    add_library(authen SHARED IMPORTED GLOBAL)
    if (MSVC)
        set_target_properties(authen PROPERTIES
                IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/authen.dll
                IMPORTED_IMPLIB   ${CMAKE_CURRENT_SOURCE_DIR}/lib/authen.lib
        )
    elseif(Clang)
        set_target_properties(authen PROPERTIES
                IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/libauthen.dylib
        )
    else()

    endif ()

    target_include_directories(authen INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}/inc)
endif ()



