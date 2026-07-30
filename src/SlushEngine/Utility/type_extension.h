#include <iostream>
#include <string_view>

template <typename T>
constexpr std::string_view get_type_name() {
    #ifdef _MSC_VER
    std::string_view name = __FUNCSIG__;
    #else
    std::string_view name = __PRETTY_FUNCTION__;
    #endif
    
    name = name.substr(name.find_first_of('T') + 3, name.find_first_of(';') - name.find_first_of('T') - 3);
    return name;
}
