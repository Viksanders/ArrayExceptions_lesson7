#pragma once

class bad_range : public std::exception
{
public:
    const char* what() const noexcept override
    {
        return "Error: out of range!\n";
    }
    virtual ~bad_range() noexcept {}
};

class bad_length : public std::exception
{
public:
    const char* what() const noexcept override
    {
        return "Error: array length can't be less of equal 0 or larger than 10000!\n";
    }
    virtual ~bad_length() noexcept {}
};
