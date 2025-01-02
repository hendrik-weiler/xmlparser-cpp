cmake_minimum_required(VERSION 3.30)
project(xmlparser VERSION 0.1.4)

set(CMAKE_CXX_STANDARD 20)

add_library(xmlparser STATIC
        lib/includes/XMLParser.cpp
        lib/includes/XMLParser.h
        lib/Token.cpp
        lib/Token.h
        lib/Type.h
        lib/Lexer.cpp
        lib/Lexer.h
        lib/Parser.cpp
        lib/Parser.h
        lib/Document.cpp
        lib/Document.h
        lib/includes/Node.cpp
        lib/includes/Node.h)