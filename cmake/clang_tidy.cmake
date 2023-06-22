function(add_clang_tidy target)
    find_program(CLANG-TIDY_PATH clang-tidy REQUIRED)

    set_target_properties(${target}
        PROPERTIES CXX_CLANG_TIDY
        "${CLANG-TIDY_PATH};--warnings-as-errors=*"    
    )
endfunction()