#include "controlbuttons.h"

/**
 * @brief Конструктор. Инициализирует UI и соединяет сигналы с слотами.
 * @param parent Родительский виджет.
 */
ControlButtons::ControlButtons(QWidget *parent) : QWidget(parent)
{
    setupUI();
    setupConnections();
}

/**
 * @brief Настройка UI: создание и размещение кнопок.
 */
void ControlButtons::setupUI()
{
    increaseTempButton = new QPushButton("+ Температура", this);
    decreaseTempButton = new QPushButton("- Температура", this);
    increaseHumidityButton = new QPushButton("+ Влажность", this);
    decreaseHumidityButton = new QPushButton("- Влажность", this);
    increasePressureButton = new QPushButton("+ Давление", this);
    decreasePressureButton = new QPushButton("- Давление", this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(increaseTempButton);
    layout->addWidget(decreaseTempButton);
    layout->addWidget(increaseHumidityButton);
    layout->addWidget(decreaseHumidityButton);
    layout->addWidget(increasePressureButton);
    layout->addWidget(decreasePressureButton);
}

/**
 * @brief Настройка соединений кнопок с соответствующими слотами.
 */
void ControlButtons::setupConnections()
{
    connect(increaseTempButton, &QPushButton::clicked, this, &ControlButtons::increaseTemperature);
    connect(decreaseTempButton, &QPushButton::clicked, this, &ControlButtons::decreaseTemperature);
    connect(increaseHumidityButton, &QPushButton::clicked, this, &ControlButtons::increaseHumidity);
    connect(decreaseHumidityButton, &QPushButton::clicked, this, &ControlButtons::decreaseHumidity);
    connect(increasePressureButton, &QPushButton::clicked, this, &ControlButtons::increasePressure);
    connect(decreasePressureButton, &QPushButton::clicked, this, &ControlButtons::decreasePressure);
}
