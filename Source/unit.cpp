#include "unit.h"
#include <iostream>

unit::unit(int x, int y, std::string texture) : building(x, y, texture) {
    // Teg = teg;
    health = 200;
    std::cout<<"Unit have been created"<<'\n';
}

unit::~unit() {
    std::cout<<"Unit have been destroyed"<<'\n';
}

void unit::Action(int i) {
    if (i==1) {
        whant_to_move = true;
    } else {
        whant_to_move = false;
    }
}

bool unit::get_Action() const {
    return whant_to_move;
}