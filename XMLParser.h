#ifndef MYCLASS_H
#define MYCLASS_H

#include <iostream>
#include "library.h"
#include "lib/Node.h"
#include "lib/Parser.h"

class EXPORT XMLParser {
private:
    Parser* parser = nullptr;
public:
    virtual ~XMLParser() = default;
    virtual void parse(std::string text);
    virtual void destroy();
    virtual std::vector<Node*> getElementsByName(std::string tag);
    virtual std::string getDeclarationAttribute(std::string declaration, std::string attribute);
};

#endif //MYCLASS_H
