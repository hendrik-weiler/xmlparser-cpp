#ifndef MYCLASS_H
#define MYCLASS_H

#include <iostream>
#include "../../library.h"
#include "Node.h"
#include "../Parser.h"

namespace xmlparser {
    class EXPORT XMLParser {
    private:
        Parser* parser = nullptr;
    public:
        virtual ~XMLParser() = default;
        virtual void parse(std::string text);
        virtual void destroy();
        virtual std::string toXML();
        virtual std::vector<xmlparser::Node*> getElementsByName(std::string tag);
        virtual std::string getDeclarationAttribute(std::string declaration, std::string attribute);
    };
}

#endif //MYCLASS_H
