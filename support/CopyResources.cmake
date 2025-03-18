
function(copy_resources resources_src resource_name target app_name)
    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${resources_src}/${resource_name}
        ${CMAKE_BINARY_DIR}/${app_name}.app/Contents/Resources/${resource_name})
endfunction()

function(copy_asset resources_src resource_name target app_name)
    add_custom_command(TARGET ${target} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${resources_src}/${resource_name}
            ${CMAKE_BINARY_DIR}/${app_name}.app/Contents/Resources/Assets/${resource_name})
endfunction()