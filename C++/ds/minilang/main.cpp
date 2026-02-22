#include "Lexer.h"
#include "Parser.h"
#include "Bytecode.h"
#include "CodeGen.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

int main(int argc,char** argv){
    if(argc<2){ std::cerr<<"Usage: minicomp <file.minilang>\n"; return 1; }

    std::ifstream fin(argv[1]);
    if(!fin){ std::cerr<<"Cannot open "<<argv[1]<<"\n"; return 1; }
    std::stringstream buffer; buffer << fin.rdbuf();
    std::string source = buffer.str();

    Lexer lexer(source);
    auto tokens = lexer.tokenize();

    Parser parser(tokens);
    auto stmts = parser.parse();

    BytecodeGen bcgen;
    bcgen.generate(stmts);

    std::string cppCode = generateCppFromBytecode(bcgen.code);
    std::string tmpFile = "tmp_program.cpp";
    std::ofstream fout(tmpFile); fout << cppCode;

    std::string exeName = argv[1];
    if(exeName.find(".minilang")!=std::string::npos)
        exeName = exeName.substr(0,exeName.find(".minilang"));

    std::string cmd = "g++ -O2 -o " + exeName + " " + tmpFile;
    int ret = std::system(cmd.c_str());
    if(ret!=0){ std::cerr<<"Compilation failed\n"; return 1; }
    std::cout<<"Compiled "<<argv[1]<<" → "<<exeName<<"\n";
}
