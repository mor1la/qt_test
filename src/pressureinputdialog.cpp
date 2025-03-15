// pressureinputdialog.cpp
#include "pressureinputdialog.h"

/**
 * @brief Получает значение, введенное пользователем в поле ввода.
 * @return Введенное пользователем значение, преобразованное в тип float.
 */
float PressureInputDialog::getValue() const
{
    return inputField->text().toFloat();
}
