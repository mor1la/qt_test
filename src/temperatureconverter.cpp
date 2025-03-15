#include "temperatureconverter.h"

/**
 * @brief Преобразует температуру из Цельсия в указанную единицу измерения.
 * @param tempCelsius Температура в градусах Цельсия.
 * @param unit Единица измерения, в которую нужно преобразовать температуру:
 *        - Celsius: Цельсий (°C),
 *        - Fahrenheit: Фаренгейт (°F),
 *        - Kelvin: Кельвин (K).
 * @return Преобразованная температура в указанной единице измерения.
 */
float TemperatureConverter::convert(float tempCelsius, int unit) const {
    switch (unit) {
    case Celsius: return tempCelsius;
    case Fahrenheit: return tempCelsius * 9.0 / 5.0 + 32;
    case Kelvin: return tempCelsius + 273.15;
    default: return tempCelsius;
    }
}

/**
 * @brief Возвращает строковое представление единицы измерения температуры.
 * @param unit Единица измерения:
 *        - Celsius: Цельсий (°C),
 *        - Fahrenheit: Фаренгейт (°F),
 *        - Kelvin: Кельвин (K).
 * @return Строка с символом единицы измерения.
 */
std::string TemperatureConverter::unitToString(int unit) const {
    switch (unit) {
    case Celsius: return "°C";
    case Fahrenheit: return "°F";
    case Kelvin: return "K";
    default: return "";
    }
}
