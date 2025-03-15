#include "climatecontrol.h"

/**
 * @brief Переключает состояние системы (вкл/выкл).
 */
void ClimateControl::togglePower() {
    isOn = !isOn;
}

/**
 * @brief Возвращает состояние системы.
 * @return true, если система включена.
 */
bool ClimateControl::isSystemOn() const {
    return isOn;
}

/**
 * @brief Увеличивает температуру на 1°C.
 */
void ClimateControl::increaseTemperature() {
    if (isOn) {
        temperature++;
    }
}

/**
 * @brief Уменьшает температуру на 1°C.
 */
void ClimateControl::decreaseTemperature() {
    if (isOn) {
        temperature--;
    }
}

/**
 * @brief Увеличивает влажность на 1%.
 */
void ClimateControl::increaseHumidity() {
    if (isOn && humidity < 100) {
        humidity++;
    }
}

/**
 * @brief Уменьшает влажность на 1%.
 */
void ClimateControl::decreaseHumidity() {
    if (isOn && humidity > 0) {
        humidity--;
    }
}

/**
 * @brief Увеличивает давление на 10.
 */
void ClimateControl::increasePressure() {
    if (isOn) {
        pressure += 10;
    }
}

/**
 * @brief Уменьшает давление на 10.
 */
void ClimateControl::decreasePressure() {
    if (isOn && pressure > 0) {
        pressure -= 10;
    }
}

/**
 * @brief Возвращает строку с температурой.
 * @return Температура в формате "Температура: X°C".
 */
QString ClimateControl::getTemperatureText() const {
    return QString("Температура: %1°C").arg(temperature);
}

/**
 * @brief Возвращает строку с давлением.
 * @return Давление в формате "Давление: X Па".
 */
QString ClimateControl::getPressureText() const {
    return QString("Давление: %1 Па").arg(pressure);
}

/**
 * @brief Возвращает строку с влажностью.
 * @return Влажность в формате "Влажность: X%".
 */
QString ClimateControl::getHumidityText() const {
    return QString("Влажность: %1%").arg(humidity);
}

/**
 * @brief Возвращает текущую температуру.
 * @return Температура.
 */
int ClimateControl::getTemperature() const {
    return temperature;
}

/**
 * @brief Возвращает текущую влажность.
 * @return Влажность.
 */
int ClimateControl::getHumidity() const {
    return humidity;
}

/**
 * @brief Возвращает текущее давление.
 * @return Давление.
 */
int ClimateControl::getPressure() const {
    return pressure;
}

/**
 * @brief Устанавливает температуру.
 * @param temperature Новая температура.
 */
void ClimateControl::setTemperature(float temperature) {
    this->temperature = temperature;
}

/**
 * @brief Устанавливает давление.
 * @param pressure Новое давление.
 */
void ClimateControl::setPressure(float pressure) {
    this->pressure = pressure;
}

/**
 * @brief Устанавливает влажность.
 * @param humidity Новая влажность.
 */
void ClimateControl::setHumidity(float humidity) {
    this->humidity = humidity;
}

/**
 * @brief Рассчитывает влажность на основе температуры и давления.
 * @return Рассчитанная влажность.
 */
float ClimateControl::calculateHumidityBasedOnTemperatureAndPressure() {
    // Примерная формула для расчета влажности (здесь вставить нужную)
    const float baseHumidity = 50.0;
    const float temperatureFactor = 0.2;
    const float pressureFactor = 0.05;

    float calculatedHumidity = baseHumidity + (temperatureFactor * temperature) - (pressureFactor * pressure);

    if (calculatedHumidity < 0) calculatedHumidity = 0;
    if (calculatedHumidity > 100) calculatedHumidity = 100;

    return calculatedHumidity;
}

/**
 * @brief Устанавливает направление воздушного потока.
 * @param direction Направление потока.
 */
void ClimateControl::setAirDirection(const QString &direction) {
    if (direction == "Вверх" || direction == "Вниз" || direction == "Вперед" || direction == "Назад") {
        airDirection = direction;
    }
}

/**
 * @brief Возвращает направление воздушного потока.
 * @return Направление потока.
 */
QString ClimateControl::getAirDirection() const {
    return airDirection;
}
