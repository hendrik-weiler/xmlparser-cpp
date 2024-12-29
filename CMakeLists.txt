cmake_minimum_required(VERSION 3.30)
project(xmlparser)

set(CMAKE_CXX_STANDARD 20)

add_library(xmlparser SHARED library.cpp
        XMLParser.cpp
        XMLParser.h
        lib/Token.cpp
        lib/Token.h
        lib/Type.h
        lib/Lexer.cpp
        lib/Lexer.h
        lib/Parser.cpp
        lib/Parser.h
        lib/Document.cpp
        lib/Document.h
        lib/Node.cpp
        lib/Node.h
        includes/XMLParserLoader.h)
