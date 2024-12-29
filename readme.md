# XMLPARSER c++

## Description

This is a simple XML parser written in C++ as shared library for loading on demand.
Its possible that the parser is not complete and may not work for all XML files.
It was a excercise to learn more about shared library usage.

### Features
- Tags
- Attributes
- CDATA
- Comments
- Declaration

## Usage

In CMakeLists.txt add the includes
```cmake
include_directories(/Users/hendrikweiler/CLionProjects/xmlparser/includes)
```

In your code include the header files
```c++
#include "XMLParser.h"
#include "XMLParserLoader.h"
```

Example code
```c++
#include <iostream>
#include "XMLParser.h"
#include "XMLParserLoader.h"

int main() {
    // Load the dynamic library
    XMLParserLoader loader("/Volumes/Expansion/xmlparser-cpp/cmake-build-debug/libxmlparser.dylib");
    XMLParser* myClassInstance = loader.create();

    myClassInstance->parse(R"(
<?xml version="1.0" encoding="UTF-8"?>
<html lang="en">
<head>
    <!-- Meta Tags -->
    <meta charset="UTF-8"/>
    <meta name="viewport" content="width=device-width, initial-scale=1.0"/>
    <link rel="icon" href="favicon.ico" type="image/x-icon"/> <!-- test -->
    <title>Titles</title>
</head>
<body>
    <dialog id="pi"><img src="progress-indicator.gif" /></dialog>
    <div id="layouts"></div>
    <div id="templates"></div>
    <div id="dialogs"></div>
    <div><![CDATA[<div id="dialogs"></div>]]></div>
</body>
</html>

)");

    std::vector<Node*> myClassInstanceElements = myClassInstance->getElementsByName("html");
    for (Node* node : myClassInstanceElements) {
        //std::cout << "Node: " << node->name << std::endl;
        node->toString();
    }

    std::string version = myClassInstance->getDeclarationAttribute("xml", "version");
    std::string encoding = myClassInstance->getDeclarationAttribute("xml", "encoding");

    std::cout << "Version: " << version << std::endl;
    std::cout << "Encoding: " << encoding << std::endl;

    loader.destroy(myClassInstance);

    return 0;
}
```