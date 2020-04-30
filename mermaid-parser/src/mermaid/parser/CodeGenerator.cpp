#include "mermaid/parser/CodeGenerator.h"

#include "mermaid/parser/Error.h"
#include "mermaid/parser/Parser.h"

#include <boost/algorithm/string.hpp>
#include <iostream>
#include <sstream>

mermaid::parser::CodeGenerator::CodeGenerator()
{
}

std::string mermaid::parser::CodeGenerator::generateHeader(const std::string& filename)
{
    auto parser = parse(filename);
    return doGenerateHeader(parser);
}

mermaid::parser::Parser mermaid::parser::CodeGenerator::parse(const std::string& filename)
{
    mermaid::parser::Parser parser;

    try {
        parser.parse(filename);
    } catch (mermaid::parser::Error& error) {
        std::cout << "Parser Error: " << error.getLocation().getFile() << ':' << error.getLocation().getLine() << ":"
                  << error.getLocation().getColumn() << " " << error.getMessage() << std::endl;
    }

    return parser;
}

std::string mermaid::parser::CodeGenerator::generateImplementation(const std::string& filename)
{
    auto parser = parse(filename);
    return doGenerateImplementation(parser);
}

std::string mermaid::parser::CodeGenerator::doGenerateHeader(mermaid::parser::Parser& parser)
{
    std::stringstream ss;

    bool hasNs = parser.getNamespace() != "";

    std::string guard = parser.getClass();
    boost::algorithm::to_upper(guard);

    if (hasNs) {
        std::string nsGuard = parser.getNamespace();
        boost::algorithm::to_upper(nsGuard);
        boost::algorithm::replace_all(nsGuard, "::", "_");
        guard = nsGuard + "_" + guard;
    }

    guard = "MERMAID_GEN_" + guard + "_H";

    ss << "#ifndef " << guard << "\n";
    ss << "#define " << guard << "\n\n";

    ss << "#include <mermaid/components/Widget.h>"
       << "\n";

    if (parser.usesString()) {
        ss << "#include <string>\n";
    }

    if (parser.usesVector()) {
        ss << "#include <vector>\n";
    }

    ss   << "\n";

    if (hasNs) {
        ss << "namespace " << parser.getNamespace() << " {\n\n";
    }

    ss << "class " << parser.getClass() << ": public Widget\n";
    ss << "{"
       << "\n";

    ss << "  public:"
       << "\n";
    ss << "    " << parser.getClass() << "();\n";

    ss << "\n  private:"
       << "\n";
    for (auto& d : parser.getDataVariables()) {
        ss << "    int " << d.name << ";\n";
    }

    ss << "}; // class " << parser.getClass() << "\n";

    if (hasNs) {
        ss << "\n} // namespace " << parser.getNamespace() << "\n";
    }
    ss << "#endif";

    return ss.str();
}

std::string mermaid::parser::CodeGenerator::doGenerateImplementation(mermaid::parser::Parser& parser)
{
    std::stringstream ss;

    return ss.str();
}
