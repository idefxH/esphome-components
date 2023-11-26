#pragma once

#include <stdio.h>
#include <string>
#include <vector>
#include <variant>
#include <encode-decode.h>

struct x_y_coordinates{
    int x;
    int y;
};

 class DisplayTile
{

    public:
    x_y_coordinates top_left;
    x_y_coordinates bottom_right;
    std::string title;
    std::string content;
    std::string icon;


    //esphome::display::Display &provided_display;
    //DisplayTile(esphome::display::Display &it) : provided_display(it) {
    //DisplayTile(x_y_coordinates tl, x_y_coordinates br,  std::string t,  std::string c,  std::string i) : top_left(tl), bottom_right(br),title(t),content(c),icon(i){
    DisplayTile(x_y_coordinates tl, x_y_coordinates br) : top_left(tl), bottom_right(br){

    };

    void display_it(esphome::font::Font *f,esphome::font::Font *f_icon,esphome::display::Display &it ){
        it.printf(top_left.x+((bottom_right.x-top_left.x)/2),top_left.y,f_icon,TextAlign::TOP_CENTER, icon.c_str());
        ESP_LOGD("main","Title: %s", title.c_str());
        it.printf(top_left.x+((bottom_right.x-top_left.x)/2),top_left.y+((bottom_right.y-top_left.y)/2),f,TextAlign::TOP_CENTER, title.c_str());
        it.printf(top_left.x+((bottom_right.x-top_left.x)/2),top_left.y+((bottom_right.y-top_left.y)/2),f,TextAlign::BOTTOM_CENTER, content.c_str());

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

    for(int i =0; i<4; i++){
        output[i]->title=payload_data.buses[i].name;
        output[i]->icon=payload_data.buses[i].icon;

    }
    return output;
}

