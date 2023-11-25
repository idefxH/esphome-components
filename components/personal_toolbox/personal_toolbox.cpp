#pragma once

#include <stdio.h>
#include <string>
#include <vector>
#include <variant>
#include "display/lilygo_t5_47_display.h"
struct x_y_coordinates{
    int x;
    int y;
};

class screen_tile
{
    static esphome::LilygoT547Display it;
    screen_tile(esphome::LilygoT547Display provided_it)
    {
        it=provided_it;
        it->update();
    }
    x_y_coordinates top_left;
    x_y_coordinates top_right;
    x_y_coordinates bnottom_left;
    x_y_coordinates bottom_right;

};


#define FMT_BUF_SIZE (CHAR_BIT * sizeof(uint8_t) + 1)
extern const std::vector<uint8_t>
    payload_segment_length_vector;

const std::vector<uint8_t> payload_segment_length_vector = {5, 6, 4, 1, 4, 1, 4, 1, 4, 1, 4, 1, 4, 1, 4, 1, 4, 1, 1, 1, 1, 1};
struct bus_run
{
    int delay;
    bool rt;
};


struct payload_struct
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

const char *byte_to_binary(uint8_t x)
{
    static char b[sizeof(uint8_t) * 8 + 1] = {0};
    int y;
    long long z;

    for (z = 1LL << (sizeof(uint8_t) * 8 - 1), y = 0; z > 0; z >>= 1, y++)
    {
        b[y] = (((x & z) == z) ? '1' : '0');
    }
    b[y] = 0;

    return b;
}

void
decode_bytes(std::vector<uint8_t> input, std::vector<uint8_t> &output)
{
    uint8_t decoded_byte_cursor = 0;
    uint8_t input_cursor = 0;
    uint8_t decoded_bit_cursor = 0;
    uint8_t reading_mask1 = 0;
    uint8_t reading_mask2 = 0;
    int next_bit_overload;
    uint8_t reading_mask1_left_shift;
    uint8_t reading_mask1_length;
    for (const auto &segment_length : payload_segment_length_vector)
    {
        if (decoded_bit_cursor + segment_length < 8)
        { // On lira tous les bit du segment
            reading_mask1_length = segment_length;
            reading_mask1_left_shift = 8 - (decoded_bit_cursor + segment_length);
        }
        else
        { // on lira tout les bits restants dans le byte
            reading_mask1_length = 8 - (decoded_bit_cursor);
            reading_mask1_left_shift = 0;
        }

        reading_mask1 = ((1 << reading_mask1_length) - 1) << reading_mask1_left_shift;
        output[decoded_byte_cursor] += (reading_mask1 & input[input_cursor]);
        next_bit_overload = segment_length + decoded_bit_cursor - 8;
        output[decoded_byte_cursor] = output[decoded_byte_cursor] << (decoded_bit_cursor);
        if (next_bit_overload >= 0)
        { // il y a chevauchement
            input_cursor++;
            // result[decoded_byte_cursor] = result[decoded_byte_cursor] << (8 - reading_mask1_length);
            reading_mask2 = ((1 << (next_bit_overload)) - 1) << (8 - next_bit_overload);
            uint8_t intermediary_result = (reading_mask2 & input[input_cursor]) >> reading_mask1_length;
            output[decoded_byte_cursor] += intermediary_result;
        }
        output[decoded_byte_cursor] = output[decoded_byte_cursor] >> (8 - segment_length);

        decoded_bit_cursor = ((decoded_bit_cursor + segment_length) % 8);
        decoded_byte_cursor++;
    }
}

void decode_to_struct(std::vector<uint8_t> input, payload_struct &output)
{
    std::vector<uint8_t> buffer;
    for (uint8_t i = 0; i < payload_segment_length_vector.size() + 1; i++)
    {
        buffer.push_back(0);
    }
    decode_bytes(input, buffer);
    output.hours = buffer[0];
    output.minutes = buffer[1];
    output.pully_1->delay = buffer[2];
    output.pully_1->rt = buffer[3];
    return;
}

void encode_bytes(std::vector<uint8_t> input, std::vector<uint8_t> &output)
{
    uint8_t ongoing_byte = 0; // WIP byte
    int curr_input_pos = 0;   // in bytes
    int ongoing_segment_length;
    int curr_target_byte_pos = 0; // position in the target
    int curr_target_bit_pos = 0;  // position in the byte of the target
    int curr_bit_shift = 0;
    int next_bit_shift = 0;
    uint8_t next_byte = 0;

    ongoing_byte = input[curr_input_pos];

    output.push_back(0);

    for (const auto &ongoing_segment_length : payload_segment_length_vector)
    {
        curr_bit_shift = 8 - (curr_target_bit_pos + ongoing_segment_length);
        next_bit_shift = (curr_target_bit_pos + ongoing_segment_length) - 8;
        if (next_bit_shift > 0)
        { // On va devoir déborder sur le prochain octet.
            next_byte = (ongoing_byte & ((1 << next_bit_shift) - 1)) << (8 - next_bit_shift);
            ongoing_byte = ongoing_byte >> next_bit_shift;
            output[curr_target_byte_pos] += ongoing_byte;
            curr_target_byte_pos += 1;
            curr_target_bit_pos = next_bit_shift;
            // output[curr_target_byte_pos] = next_byte;
            output.push_back(next_byte);
        }
        else
        { // on ne dépasse pas
            ongoing_byte = ongoing_byte << curr_bit_shift;
            output[curr_target_byte_pos] = output[curr_target_byte_pos] + ongoing_byte;
            curr_target_bit_pos = curr_target_bit_pos + ongoing_segment_length;

            if (curr_target_bit_pos >= 8)
            {
                curr_target_bit_pos = 0;
                curr_target_byte_pos += 1;
                output.push_back(0);

                // output[curr_target_byte_pos]=0;
            }
        }

        curr_input_pos += 1;
        ongoing_byte = input[curr_input_pos];
    }
    // output.push_back(0);

    // output[curr_target_byte_pos+1] = 0;
    return;
}
