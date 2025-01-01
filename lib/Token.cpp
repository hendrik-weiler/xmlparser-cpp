//
// Created by Hendrik Weiler on 28.12.24.
//

#include "Token.h"

#include <iostream>

void xmlparser::Token::toString() {

    std::cout << "Token: " << type << ", Value: " << value << std::endl;

}
