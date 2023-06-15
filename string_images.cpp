
#include "weather.h"

std::string get_str_sun(uint8_t weather_code, int temperature, uint8_t probability) {
    std::string level_1 = R"(  \   /  )";
    std::string level_2 = R"(   .-.   )";
    std::string level_3 = R"(― (   ) ―)";
    std::string level_4 = R"(   `-’   )";
    std::string level_5 = R"(  /   \  )";
    std::vector<std::string> s = {level_1,level_2,level_3,level_4,level_5};
    return construct_image_string(weather_code,temperature,probability,s);
}

std::string get_str_cloud(uint8_t weather_code, int temperature, uint8_t probability) {
    std::string level_1 = R"(           )";
    std::string level_2 = R"(    .--.   )";
    std::string level_3 = R"( .-(    ). )";
    std::string level_4 = R"((___.__)__))";
    std::string level_5 = R"(           )";
    std::vector<std::string> s = {level_1,level_2,level_3,level_4,level_5};
    return construct_image_string(weather_code,temperature,probability,s);
}

std::string get_str_fog(uint8_t weather_code, int temperature, uint8_t probability) {
    std::string level_1 = R"(    - _ -  )";
    std::string level_2 = R"( _ - _ - _ )";
    std::string level_3 = R"(_ - _ - _ -)";
    std::string level_4 = R"( _ - _ - _ )";
    std::string level_5 = R"(   _ - _   )";
    std::vector<std::string> s = {level_1,level_2,level_3,level_4,level_5};
    return construct_image_string(weather_code,temperature,probability,s);
}

std::string get_str_small_rain(uint8_t weather_code, int temperature, uint8_t probability) {
    std::string level_1 = R"(    .-.   )";
    std::string level_2 = R"(   (   ). )";
    std::string level_3 = R"(  (___(__))";
    std::string level_4 = R"( ‘ ‘ ‘ ‘  )";
    std::string level_5 = R"(‘ ‘ ‘ ‘   )";
    std::vector<std::string> s = {level_1,level_2,level_3,level_4,level_5};
    return construct_image_string(weather_code,temperature,probability,s);
}

std::string get_str_strong_rain(uint8_t weather_code, int temperature, uint8_t probability) {
    std::string level_1 = R"(    .-.   )";
    std::string level_2 = R"(   (   ). )";
    std::string level_3 = R"(  (___(__))";
    std::string level_4 = R"(‚‘‚‘‚‘‚‘  )";
    std::string level_5 = R"(‚’‚’‚’‚’  )";
    std::vector<std::string> s = {level_1,level_2,level_3,level_4,level_5};
    return construct_image_string(weather_code,temperature,probability,s);
}

std::string get_str_small_snow(uint8_t weather_code, int temperature, uint8_t probability) {
    std::string level_1 = R"(   .-.   )";
    std::string level_2 = R"(  (   ). )";
    std::string level_3 = R"( (___(__))";
    std::string level_4 = R"( *  *  * )";
    std::string level_5 = R"(*  *  *  )";
    std::vector<std::string> s = {level_1,level_2,level_3,level_4,level_5};
    return construct_image_string(weather_code,temperature,probability,s);
}

std::string get_str_strong_snow(uint8_t weather_code, int temperature, uint8_t probability) {
    std::string level_1 = R"(   .-.   )";
    std::string level_2 = R"(  (   ). )";
    std::string level_3 = R"( (___(__))";
    std::string level_4 = R"( * * * * )";
    std::string level_5 = R"(* * * *  )";
    std::vector<std::string> s = {level_1,level_2,level_3,level_4,level_5};
    return construct_image_string(weather_code,temperature,probability,s);
}

std::string get_str_thunder(uint8_t weather_code, int temperature, uint8_t probability) {
    std::string level_1 = R"(    .-.   )";
    std::string level_2 = R"(   (   ). )";
    std::string level_3 = R"(  (___(__))";
    std::string level_4 = R"(⚡‘‚’⚡‘‚⚡  )";
    std::string level_5 = R"(‚’⚡’‚⚡‚‘  )";
    std::vector<std::string> s = {level_1,level_2,level_3,level_4,level_5};
    return construct_image_string(weather_code,temperature,probability,s);
}

std::string construct_image_string(uint8_t weather_code, int temperature, uint8_t probability, const std::vector<std::string>& png) {
    const char s = 124;
    const std::string end = {'\n'};
    const std::string wall = std::string{s} + ' ';
    const std::string weather_name_str = get_weather_name(weather_code);
    char sign;
    if (temperature > 0) {
        sign = '+';
    } else {
        sign = '-';
    }
    const std::string temperature_str = sign + std::to_string(temperature) + " °C";
    const std::string probability_str = "drop: " + std::to_string(probability) + '%';
    int delta_1 = 1;
    if (static_cast<int>(weather_name_str.size() > temperature_str.size())) {
        delta_1 = static_cast<int>(weather_name_str.size() - temperature_str.size());
    }

    int delta_2 = 1;
    if (static_cast<int>(weather_name_str.size() > probability_str.size())) {
        delta_2 = static_cast<int>(weather_name_str.size() - probability_str.size());
    }
    const std::string padding_1 = std::string(delta_1, ' ');
    const std::string padding_2 = std::string(delta_2, ' ');
    const std::string padding_3 = std::string(temperature_str.size(), ' ');
    std::string level_1 = wall + png[0] + "  " + weather_name_str + end;
    std::string level_2 = wall + png[1] + "  " + temperature_str + padding_1 + end;
    std::string level_3 = wall + png[2] + "  " + probability_str + padding_2 + end;
    std::string level_4 = wall + png[3] + padding_3 + end;
    std::string level_5 = wall + png[4] + padding_3 + end;
    return ( level_1 + level_2 + level_3 + level_4 + level_5 );
}