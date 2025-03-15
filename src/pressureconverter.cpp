#include "pressureconverter.h"

/**
 * @brief Конвертирует давление из паскалей в указанную единицу.
 * @param pressurePascals Давление в паскалях.
 * @param unit Единица измерения (Pascals или MmHg).
 * @return Давление в указанной единице измерения.
 */
float PressureConverter::convert(float pressurePascals, int unit) const {
    switch (unit) {
    case Pascals: return pressurePascals;
    case MmHg: return pressurePascals / 133.322;
    default: return pressurePascals;
    }
}

/**
 * @brief Преобразует единицу измерения в строку.
 * @param unit Единица измерения (Pascals или MmHg).
 * @return Строковое представление единицы измерения.
 */
std::string PressureConverter::unitToString(int unit) const {
    switch (unit) {
    case Pascals: return "Па";
    case MmHg: return "мм рт. ст.";
    default: return "";
    }
}
