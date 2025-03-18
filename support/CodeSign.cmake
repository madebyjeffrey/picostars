
function(code_sign identity target appName entitlements)
    add_custom_command(TARGET ${target} POST_BUILD
            COMMAND codesign  -o runtime -o library --timestamp --verify --verbose --sign "${identity}" --entitlements ${entitlements} ${CMAKE_BINARY_DIR}/${appName}.app
    )

endfunction()

function(code_sign_framework identity target appName framework_name)
    add_custom_command(TARGET ${target} POST_BUILD
            COMMAND codesign -o runtime -f --timestamp --verify --verbose --sign "${identity}" ${CMAKE_BINARY_DIR}/${appName}.app/Contents/Frameworks/${framework_name}.framework
    )

endfunction()
