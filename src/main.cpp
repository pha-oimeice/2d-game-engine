#include "Engine.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    auto& engine = engine::get_engine();
    std::cout << "Acta est febula, plaudite.\n";
    return 0;
}
