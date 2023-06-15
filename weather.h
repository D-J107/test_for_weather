
#ifndef LABWORK_10_D_J107_WEATHER_RESPONCE_H
#define LABWORK_10_D_J107_WEATHER_RESPONCE_H

#include "cpr/cpr.h"
#include "nlohmann/json.hpp"
#include "tabulate/table.hpp"
using json = nlohmann::json;
typedef const std::string& CSR;

std::string get_day_name(int day);

std::string get_month_name(int month);

std::string get_weather_name(uint8_t val);

std::string construct_image_string(uint8_t weathercode, int temperature, uint8_t probability, const std::vector<std::string>& png);

std::string get_str_sun(uint8_t weathercode, int temperature, uint8_t probability);

std::string get_str_cloud(uint8_t weathercode, int temperature, uint8_t probability);

std::string get_str_fog(uint8_t weathercode, int temperature, uint8_t probability);

std::string get_str_small_rain(uint8_t weathercode, int temperature, uint8_t probability);

std::string get_str_strong_rain(uint8_t weathercode, int temperature, uint8_t probability);

std::string get_str_small_snow(uint8_t weathercode, int temperature, uint8_t probability);

std::string get_str_strong_snow(uint8_t weathercode, int temperature, uint8_t probability);

std::string get_str_thunder(uint8_t weathercode, int temperature, uint8_t probability);

bool find(const std::vector<uint8_t>& vector, uint8_t key);

std::string get_string_weather(uint8_t weathercode, int temperature, uint8_t probability);

std::pair<float,float> get_coordinates_from_api_ninja(CSR city_name, CSR api_key);

void show_data_in_console(float first_coord, float second_coord, int forecast_days);

void print_weather_forecast_for_city(CSR name, int forecast_days, CSR token);

void parse_arguments_from_console(int argc, char** argv);


#endif //LABWORK_10_D_J107_WEATHER_RESPONCE_H