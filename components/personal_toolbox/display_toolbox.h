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
    lilygo_t5_47::LilygoT547Display provided_display;
    x_y_coordinates top_left;
    x_y_coordinates top_right;
    x_y_coordinates bottom_left;
    x_y_coordinates bottom_right;
    void display_it(){
        provided_display->update();
    }
    
};
