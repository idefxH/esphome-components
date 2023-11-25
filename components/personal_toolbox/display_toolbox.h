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
    x_y_coordinates top_left;
    x_y_coordinates bottom_right;
    //esphome::display::Display &provided_display;
    //DisplayTile(esphome::display::Display &it) : provided_display(it) {
    DisplayTile(x_y_coordinates tl, x_y_coordinates br) : top_left(tl), bottom_right(br){

    };

    void display_it(esphome::font::Font *f,esphome::display::Display &it ){
        it.printf(bottom_right.x-top_left.x,bottom_right.y-top_left.y,f,TextAlign::TOP_CENTER, "TEST");
    }
    
};
std::vector<DisplayTile*> generate_4_tiles_for_area( x_y_coordinates top_left, x_y_coordinates bottom_right ){
    std::vector<DisplayTile*> output;
    x_y_coordinates buff_1;
    x_y_coordinates buff_2; 
    buff_1.x = top_left.x;
    buff_1.y = top_left.y;
    buff_2.x=top_left.x+(bottom_right.x-top_left.x)/2;
    buff_2.y=top_left.y+(bottom_right.y-top_left.y)/2;
    output.push_back(new DisplayTile(buff_1, buff_2));
    buff_1.x = buff_2.x;
    buff_1.y = top_left.y;
    buff_2.x=bottom_right.x;
    buff_2.y=top_left.y+(bottom_right.y-top_left.y)/2;
    output.push_back(new DisplayTile(buff_1, buff_2));
    buff_1.x = top_left.x;
    buff_1.y = top_left.y+(bottom_right.y-top_left.y)/2;
    buff_2.x=top_left.x+(bottom_right.x-top_left.x)/2;
    buff_2.y=bottom_right.y;
    output.push_back(new DisplayTile(buff_1, buff_2));
    buff_1.x = buff_2.x;
    buff_1.y = top_left.y+(bottom_right.y-top_left.y)/2;
    buff_2.x=bottom_right.x;
    buff_2.y=bottom_right.y;
    output.push_back(new DisplayTile(buff_1, buff_2));

    return output;
}

