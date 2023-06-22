set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(ui)

set(calc_SourceFiles ${calc_SourceFiles}
    "${DIR}/main.cpp"
    "${DIR}/lexer.cpp"
    "${DIR}/parser.cpp"

    PARENT_SCOPE
)