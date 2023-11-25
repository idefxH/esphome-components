#pragma once


#include <stdio.h>
#include "esphome/core/component.h"
#include <string>
#include <vector>
namespace esphome{
namespace personal_toolbox{
    
        class PersonalToolbox : public PollingComponent
        {
        public:
            void setup() override;
            void update() override;
        };
        class screen_tile
        {
            x_y_coordinates top_left;
            x_y_coordinates top_right;
            x_y_coordinates bnottom_left;
            x_y_coordinates bottom_right;
        }
    #define FMT_BUF_SIZE (CHAR_BIT * sizeof(uint8_t) + 1)
            extern const std::vector<uint8_t>
                payload_segment_length_vector;

    const char *byte_to_binary(uint8_t x);

    struct bus_run
    {
        int delay;
        bool rt;
    };
     struct x_y_coordinates
    {
        int x;
        int y;
    };asdsd

     class payload_struct
    {
        int minutes;
        int hours;
        bus_run pully_1[2];
        bus_run pully_2[2];
        bus_run sainf_1[2];
        bus_run sainf_2[2];
        bus_run metro_1[2];
        bus_run metro_2[2];
        bus_run paudex_1[2];
        bus_run paudex_2[2];
        bool rain_1h;
        bool rain_2h;
        bool rain_4h;
        bool rain_12h;
    };

    void decode_bytes(std::vector<uint8_t> input, std::vector<uint8_t> &output);
    void decode_to_struct(std::vector<uint8_t> input, payload_struct &output);
    void encode_bytes(std::vector<uint8_t> input, std::vector<uint8_t> &output);
    } // namespace esphome
} //namespace personal_toolbox