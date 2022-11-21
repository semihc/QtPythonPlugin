#include "QtPythonPI.hh"


QString QtPythonPI::echo(const QString &message)
{
    return message;
}

// https://stackoverflow.com/questions/23068700/embedding-python3-in-qt-5
#pragma push_macro("slots")
#undef slots
#include <pybind11/embed.h>
#pragma pop_macro("slots")
#include <iostream>

namespace py = pybind11;
using namespace py::literals;

int main2() {
    py::scoped_interpreter guard{};

    auto locals = py::dict("name"_a="World", "number"_a=42);
    py::exec(R"(
        message = "Hello, {name}! The answer is {number}".format(**locals())
    )", py::globals(), locals);

    auto message = locals["message"].cast<std::string>();
    std::cout << message;

  return 0;
}
