#pragma once

#include <stdio.h>
#include <string>
#include <vector>
#include <variant>

struct x_y_coordinates{
    int x;
    int y;
};

 class DisplayTile
{
    public:
    esphome::display::Display *provided_display;
    DisplayTile(esphome::display::Display *it) : provided_display(it) {

    }
    x_y_coordinates top_left;
    x_y_coordinates top_right;
    x_y_coordinates bottom_left;
    x_y_coordinates bottom_right;
    void display_it(esphome::font::Font *f){
        it.printf(200,100,f, "TEST");
    }
    
};

