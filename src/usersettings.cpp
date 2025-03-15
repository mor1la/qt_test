#include "usersettings.h"

/**
 * @brief Сохраняет настройки пользователя в XML файл.
 *
 * Эта функция сохраняет в файл текущие настройки приложения, такие как единицы измерения температуры и давления,
 * а также текущие значения температуры и давления. Настройки сохраняются в формате XML.
 *
 * @param temperatureUnitIndex Индекс выбранной единицы измерения температуры.
 * @param pressureUnitIndex Индекс выбранной единицы измерения давления.
 * @param currentTemperature Текущая температура.
 * @param currentPressure Текущее давление.
 *
 * @note Если файл не удается открыть для записи, будет показано предупреждение.
 */
void UserSettings::saveSettings(int temperatureUnitIndex, int pressureUnitIndex, int currentTemperature, int currentPressure){
    QFile file(settingsFileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(nullptr, "Ошибка", "Не удалось сохранить настройки.");
        return;
    }

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("Settings");

    // Запись единиц измерения
    xmlWriter.writeTextElement("TemperatureUnit", QString::number(temperatureUnitIndex));
    xmlWriter.writeTextElement("PressureUnit", QString::number(pressureUnitIndex));

    // Запись текущих значений
    xmlWriter.writeTextElement("CurrentTemperature", QString::number(currentTemperature));
    xmlWriter.writeTextElement("CurrentPressure",QString::number(currentPressure));

    xmlWriter.writeEndElement(); // Закрываем <Settings>
    xmlWriter.writeEndDocument();

    file.close();
}

/**
 * @brief Загружает настройки пользователя из XML файла.
 *
 * Эта функция загружает сохраненные настройки из XML файла, включая единицы измерения температуры и давления,
 * а также текущие значения температуры и давления.
 * Если файл не существует или содержит ошибку, возвращается false.
 *
 * @param temperatureUnitIndex Переменная, в которую будет записан индекс единицы измерения температуры.
 * @param pressureUnitIndex Переменная, в которую будет записан индекс единицы измерения давления.
 * @param currentTemperature Переменная, в которую будет записано текущее значение температуры.
 * @param currentPressure Переменная, в которую будет записано текущее значение давления.
 *
 * @return Возвращает true, если настройки успешно загружены, и false, если возникла ошибка при разборе XML.
 */
bool UserSettings::loadSettings(int &temperatureUnitIndex, int &pressureUnitIndex, int &currentTemperature, int &currentPressure) {
    QFile file(settingsFileName);
    if (!file.open(QIODevice::ReadOnly)) {
        return false; // Файл не найден или не может быть открыт
    }

    QXmlStreamReader xmlReader(&file);
    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        QXmlStreamReader::TokenType token = xmlReader.readNext();
        if (token == QXmlStreamReader::StartElement) {
            if (xmlReader.name() == "TemperatureUnit") {
                temperatureUnitIndex = xmlReader.readElementText().toInt();
            } else if (xmlReader.name() == "PressureUnit") {
                pressureUnitIndex = xmlReader.readElementText().toInt();
            } else if (xmlReader.name() == "CurrentTemperature") {
                currentTemperature = xmlReader.readElementText().toInt();
            } else if (xmlReader.name() == "CurrentPressure") {
                currentPressure = xmlReader.readElementText().toInt();
            }
        }
    }

    file.close();
    return !xmlReader.hasError(); // Проверка на ошибки при разборе XML
}

