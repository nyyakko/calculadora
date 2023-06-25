set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(Ui)

set(calc_SourceFiles ${calc_SourceFiles}
    "${DIR}/Main.cpp"
    "${DIR}/Calc.cpp"
    "${DIR}/Lexer.cpp"

    PARENT_SCOPE
)