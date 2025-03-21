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
#include <utility>

class Error final : public std::exception {
public:
    std::string _description;

    explicit Error(std::string description) : _description(std::move(description)) {
    }

public:
    template<typename... Args>
    friend auto error(std::string_view format, Args &&... args) -> Error;
};


template<typename... Args>
auto error(const std::string_view format, Args &&... args) -> Error {
    return Error{std::vformat(format, std::make_format_args(args...))};
}

#endif
