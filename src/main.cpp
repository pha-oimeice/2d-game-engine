#include "Engine.hpp"
#include "cttmp/type_list.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    using test_t = cttmp::internal::TypeList<int, double, float, int, int>;
    std::cout << cttmp::Arity<test_t> << "\n";

    auto& engine = engine::get_engine();
    std::cout << "Acta est febula, plaudite.\n";
    return 0;
}
