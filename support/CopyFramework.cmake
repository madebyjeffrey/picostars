
function(copy_framework framework_name target)
    set(src "/Library/Frameworks/${framework_name}.framework")
    set(dst "${CMAKE_BINARY_DIR}/${target}.app/Contents/Frameworks/${framework_name}.framework")
    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${dst}
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${src}/Versions/A ${dst}/Versions/A
        COMMAND ${CMAKE_COMMAND} -E rm -R ${dst}/Versions/A/Headers
        COMMAND ${CMAKE_COMMAND} -E create_symlink A ${dst}/Versions/Current
        COMMAND ${CMAKE_COMMAND} -E create_symlink Versions/Current/${framework_name} ${dst}/${framework_name}
        COMMAND ${CMAKE_COMMAND} -E create_symlink Versions/Current/Resources ${dst}/Resources
    )
endfunction()
