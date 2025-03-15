// humidityinputdialog.cpp
#include "humidityinputdialog.h"


/**
 * @brief Получает значение влажности, введённое пользователем.
 * @return Значение влажности типа float.
 */
float HumidityInputDialog::getValue() const
{
    return inputField->text().toFloat();
}
