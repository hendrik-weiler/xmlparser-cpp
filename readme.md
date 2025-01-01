# XMLPARSER c++

## Description

This is a simple XML parser written in C++ as static library.
Its possible that the parser is not complete and may not work for all XML files.
It was a excercise to learn more about shared libraries but static seems to be recommended.

### Features
- Tags
- Attributes
- CDATA
- Comments
- Declaration
- Manipulate and convert back to a xml string

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

int main() {
    // Load the dynamic library
    auto* myClassInstance = new xmlparser::XMLParser();

    myClassInstance->parse(R"(
<?xml version="1.0" encoding="UTF-8"?>
<html xmlns="http://www.w3.org/1999/xhtml"
      xmlns:h="http://xmlns.jcp.org/jsf/html"
      xmlns:ui="http://xmlns.jcp.org/jsf/facelets"
      xmlns:f="http://xmlns.jcp.org/jsf/core">
<f:view>
    <h:outputLabel value="Hello, world"/>
</f:view>
</html>

)");

    std::vector<xmlparser::Node*> myClassInstanceElements = myClassInstance->getElementsByName("html");

    for (xmlparser::Node* node : myClassInstanceElements) {
        //std::cout << "Node: " << node->name << std::endl;

        node->attributes["id"] = "test";
        auto* child = new xmlparser::Node();
        child->name = "child";
        node->children.push_back(child);
        std::cout << node->toXML() << std::endl;
    }

    //std::cout << myClassInstance->toXML() << std::endl;

    std::string version = myClassInstance->getDeclarationAttribute("xml", "version");
    std::string encoding = myClassInstance->getDeclarationAttribute("xml", "encoding");

    std::cout << "Version: " << version << std::endl;
    std::cout << "Encoding: " << encoding << std::endl;

    myClassInstance->destroy();

    return 0;
}
```