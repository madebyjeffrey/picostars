//
//  error.h
//  picostars
//
//  Created by Jeffrey Drake on 2025-03-13.
//

#ifndef ERROR_H
#define ERROR_H

#include <string>
#include <string_view>
#include <format>


class Error {
private:
    std::string _description;
    
    Error(std::string description) : _description(description) {
    }
public:
    template<typename... Args>
    friend auto make_error(std::string_view format, Args&&... args) -> Error;
};


template<typename... Args>
auto make_error(std::string_view format, Args&&... args) -> Error {
    return std::vformat(format, std::make_format_args(args...));
}

#endif
