#pragma once

#include <stdio.h>
#include <string>
#include <vector>
#include <variant>

struct x_y_coordinates{
    int x;
    int y;
};

class screen_tile
{
    static lilygo_t5_47::LilygoT547Display *provided_display;
    screen_tile(lilygo_t5_47::LilygoT547Display *it) : provided_display(it) {

    }
    x_y_coordinates top_left;
    x_y_coordinates top_right;
    x_y_coordinates bottom_left;
    x_y_coordinates bottom_right;
    void display_it(){
        provided_display->update();
    }
    
};
lilygo_t5_47::LilygoT547Display* screen_tile::provided_display = nullptr;

