
#include "weather.h"

void show_data_in_console(float first_coord, float second_coord, int forecast_days) {
    std::string latitude_value = std::to_string(first_coord);
    std::string longitude_value = std::to_string(second_coord);
    std::string forecast_value = std::to_string(forecast_days);
    const std::string basic_parameters = "temperature_2m,precipitation_probability,weathercode";
    const std::string base_url = "https://api.open-meteo.com/v1/forecast";
    cpr::Response r = cpr::Get(cpr::Url{base_url},
                               cpr::Parameters{{"latitude", latitude_value},
                                               {"longitude", longitude_value},
                                               {"hourly", basic_parameters},
                                               {"forecast_days", forecast_value}});
    if (r.status_code != 200) {
        std::cout << "Error! Cannot get Weather Variable!" << '\n';
        exit(1);
    }
    json data = json::parse(r.text);
    const int morning_time = 5;
    const int midday_time = 11;
    const int evening_time = 17;
    const int night_time = 23;
    const int day_periodic = 24;
    const int day_times[4] = {morning_time, midday_time, evening_time, night_time};
    const int month_start = 5; // in json it has this format: "2023-04-09T00::00"
    const int month_end = 6;
    const int day_start = 8;
    const int day_end = 9;

    tabulate::Table table;
    table.format().multi_byte_characters(true);
    table.format().hide_border_left().hide_border_right();
    std::vector<std::string> daily_weather;

    for (int i = 0; i < forecast_days; i++) {
        std::string date = data["hourly"]["time"][day_periodic * i];
        int month_number = 10 * (date[month_start] - '0') + (date[month_end] - '0');
        int day_number = 10 * (date[day_start] - '0') + (date[day_end] - '0');
        std::string final_date = get_day_name(day_number) + ' ' + std::to_string(day_number) + ' ' + get_month_name(month_number);
        table.add_row({"", final_date, "", ""});
        table[i * 4].format().font_align(tabulate::FontAlign::center).width(40);
        table.add_row({"Morning", "Noon", "Evening", "Night"});
        table[i * 4 + 1].format().font_align(tabulate::FontAlign::center);

        for (int day_time : day_times) {
            int temperature = data["hourly"]["temperature_2m"][day_time + day_periodic * i];
            uint8_t probability = data["hourly"]["precipitation_probability"][day_time + day_periodic * i];
            uint8_t weathercode = data["hourly"]["weathercode"][day_time + day_periodic * i];
            std::string abomination = get_string_weather(weathercode,temperature,probability);
            daily_weather.push_back(abomination);
        }
        table.add_row({daily_weather[0], daily_weather[1], daily_weather[2], daily_weather[3]});
        table[i * 4 + 2].format().font_align(tabulate::FontAlign::left);
        daily_weather.clear();
        if (i == forecast_days - 1) continue;
        table.add_row({""});
    }
    std::cout << table << std::endl;
}


void print_weather_forecast_for_city(CSR name, int forecast_days, CSR token) {
    std::cout << '\n' << "Weather report: " << name << '\n' << '\n';
    auto coordinates = get_coordinates_from_api_ninja(name, token);
    show_data_in_console(coordinates.first,coordinates.second,forecast_days);
    std::cout << '\n' << '\n' << '\n';
}