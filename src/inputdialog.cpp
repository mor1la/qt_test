#include "inputdialog.h"

/**
 * @brief Конструктор диалогового окна для ввода числа с ограничениями.
 * @param parent Родительский виджет.
 * @param title Заголовок окна.
 * @param label Текст с подсказкой.
 * @param minValue Минимально допустимое значение.
 * @param maxValue Максимально допустимое значение.
 */
InputDialog::InputDialog(QWidget *parent, const QString &title, const QString &label,
                         float minValue, float maxValue)
    : QDialog(parent), minValue(minValue), maxValue(maxValue)
{
    setWindowTitle(title);
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *prompt = new QLabel(label, this);
    inputField = new QLineEdit(this);
    QPushButton *okButton = new QPushButton("OK", this);
    QPushButton *cancelButton = new QPushButton("Отмена", this);

    QDoubleValidator *validator = new QDoubleValidator(minValue, maxValue, 2, this);
    validator->setNotation(QDoubleValidator::StandardNotation);
    inputField->setValidator(validator);

    layout->addWidget(prompt);
    layout->addWidget(inputField);
    layout->addWidget(okButton);
    layout->addWidget(cancelButton);

    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

/**
 * @brief Получает введённое значение с учётом ограничений.
 * @return Введённое значение, ограниченное диапазоном от minValue до maxValue.
 */
float InputDialog::getValue() const
{
    float value = inputField->text().toFloat();
    return qBound(minValue, value, maxValue); // Ограничение значений
}
