//
// Created by Hendrik Weiler on 28.12.24.
//

#ifndef TYPE_H
#define TYPE_H



enum Type {
    END_OF_FILE = 0,
    OPEN_TAG = 1,
    CLOSE_TAG = 2,
    IDENTIFIER = 3,
    SLASH = 4,
    EQUAL = 5,
    DOUBLEQUOTE = 6,
    ATTRIBUTE_VALUE = 7,
    INNER_TEXT = 8,
    SLASH_CLOSE_TAG = 9,
    SLASH_OPEN_TAG = 10
};



#endif //TYPE_H