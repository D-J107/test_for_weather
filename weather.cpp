
#include "weather.h"

std::string get_day_name(int day) {
    day = day % 7;
    switch (day)
    {
        case 0:  return "Sunday";
        case 1:  return "Monday";
        case 2:  return "Tuesday";
        case 3:  return "Wednesday";
        case 4:  return "Thursday";
        case 5:  return "Friday";
        case 6:  return "Saturday";
        default: return "Sunday";
    }
}

std::string get_month_name(int month) {
    switch (month)
    {
        case 1:  return  "January";
        case 2:  return  "February";
        case 3:  return  "March";
        case 4:  return  "April";
        case 5:  return  "May";
        case 6:  return  "June";
        case 7:  return  "July";
        case 8:  return  "August";
        case 9:  return  "September";
        case 10: return  "October";
        case 11: return  "November";
        case 12: return  "December";
        default: return  "October";
    }
}

std::string get_weather_name(uint8_t val) {
    switch(val) {
        case 0:  return  "Clear sky";
        case 1:  return  "Mainly clear";
        case 2:  return  "Partly cloudy";
        case 3:  return  "Overcast";
        case 45: return  "Fog";
        case 48: return  "Depositing rime fog";
        case 51: return  "Light drizzle";
        case 53: return  "Moderate drizzle";
        case 55: return  "Dense intense drizzle";
        case 56: return  "Freezing drizzle";
        case 57: return  "Freezing drizzle with dense intensity";
        case 61: return  "Rain";
        case 63: return  "Moderate rain";
        case 65: return  "Heavy intensive rain";
        case 71: return  "Snow fall";
        case 73: return  "Moderate snow fall";
        case 75: return  "Heavy intensive snow fall";
        case 77: return  "Snow grains";
        case 80: return  "Slight rain showers";
        case 81: return  "Moderate rain showers";
        case 82: return  "Violent rain showers";
        case 85: return  "Slight snow showers";
        case 86: return  "Heavy snow showers";
        case 95: return  "Thunderstorm";
        case 96: return  "Thunderstorm with slight hail";
        case 99: return  "Thunderstorm with heavy hail";
        default: return  "Clear sky";
    }
}

bool find(const std::vector<uint8_t>& vector, uint8_t key) {
    return std::find(vector.begin(), vector.end(), key) != vector.end();
}

std::string get_string_weather(uint8_t weather_code, int temperature, uint8_t probability) {
    const std::vector<uint8_t> sunny = {0,1};
    const std::vector<uint8_t> cloudy = {2,3};
    const std::vector<uint8_t> foggy = {45,48};
    const std::vector<uint8_t> small_rain = {51,53,55, 61,63, 80};
    const std::vector<uint8_t> strong_rain = {65, 81,82};
    const std::vector<uint8_t> small_snowy = {56,57, 66, 71,73, 77, 86};
    const std::vector<uint8_t> strong_snowy = {67, 75, 86};
    const std::vector<uint8_t> thunder = {95,96,99};
    if (find(sunny,weather_code)) {
        return get_str_sun(weather_code,temperature,probability);
    }

    else if (find(cloudy,weather_code)) {
        return get_str_cloud(weather_code,temperature,probability);
    }

    else if (find(foggy,weather_code)) {
        return get_str_fog(weather_code,temperature,probability);
    }

    else if (find(small_rain,weather_code)) {
        return get_str_small_rain(weather_code,temperature,probability);
    }

    else if (find(strong_rain,weather_code)) {
        return get_str_strong_rain(weather_code,temperature,probability);
    }

    else if (find(small_snowy,weather_code)) {
        return get_str_small_snow(weather_code,temperature,probability);
    }

    else if (find(strong_snowy,weather_code)) {
        return get_str_strong_snow(weather_code,temperature,probability);
    }

    else {
        return get_str_thunder(weather_code,temperature,probability);
    }
}

std::pair<float,float> get_coordinates_from_api_ninja(CSR city_name, CSR api_key) {
    const std::string name = "name";
    const std::string header = "X-Api-Key";
    cpr::Response r = cpr::Get(cpr::Url{"https://api.api-ninjas.com/v1/city"},
                               cpr::Header{{header, api_key}},
                               cpr::Parameters{{name, city_name}});
    if (r.status_code == 400) {
        std::cout << "Error! Cant get coordinates from API Ninja!" << '\n';
        exit(1);
    }
    json data_from_ninja = json::parse(r.text);
    auto component = data_from_ninja[0];
    float value1 = component.at("latitude");
    float value2 = component.at("longitude");
    return std::make_pair(value1,value2);
}

void parse_arguments_from_console(int argc, char** argv) {
    std::ifstream path_to_config;
    if (argc == 1) {
        std::cout << "Error! no config path given!" << '\n';
        exit(1);
    } else if (argc == 2) {
        path_to_config.open(argv[1]);
    } else if (argc > 2) {
        throw std::runtime_error{"Error! only one config file can be passed!\n"};
    }
    json parser = json::parse(path_to_config);
    std::vector<std::string> cities = parser.at("cities");
    int forecast_days = parser.at("settings").at("forecast_days");
    int frequency = parser.at("settings").at("frequency");
    std::string token = parser.at("settings").at("token");
    if (forecast_days <= 0 || frequency <= 0) {
        throw std::runtime_error{"All values in settings must be positive integers!\n"};
    }

    for (CSR current_city : cities) {
        print_weather_forecast_for_city(current_city, forecast_days, token);
    }
}
