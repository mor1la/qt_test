#include "mainwindow.h"

/**
 * @brief Конструктор класса MainWindow.
 *
 * Инициализирует интерфейс и устанавливает начальные значения температуры и давления.
 * Загружает настройки пользователя из файла.
 *
 * @param parent Родительский элемент, по умолчанию nullptr.
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), climateControl(), userSettings(FILENAME) {
    int tempUnitIndex = 0, pressureUnitIndex = 0, currentTemperature = 0, currentPressure = 0;

    if (!userSettings.loadSettings(tempUnitIndex, pressureUnitIndex, currentTemperature, currentPressure)) {
        currentTemperature = 0;
        currentPressure = 0;
        tempUnitIndex = 0;
        pressureUnitIndex = 0;
    }

    setupUI();
    setupConnections();
    climateControl.setTemperature(currentTemperature);
    climateControl.setPressure(currentPressure);

    unitSelector->setCurrentIndex(tempUnitIndex);
    pressureUnitSelector->setCurrentIndex(pressureUnitIndex);

    updateLabels();
}

/**
 * @brief Деструктор класса MainWindow.
 *
 * Сохраняет текущие настройки пользователя при закрытии окна.
 */
MainWindow::~MainWindow() {
    userSettings.saveSettings(
        unitSelector->currentIndex(),
        pressureUnitSelector->currentIndex(),
        climateControl.getTemperature(),
        climateControl.getPressure()
        );
}

/**
 * @brief Настройка пользовательского интерфейса.
 *
 * Создает и настраивает все элементы интерфейса, включая кнопки, метки и комбинированные поля.
 */
void MainWindow::setupUI() {
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    themeToggleButton = new QPushButton(Strings::switchThemeButton, this);

    mainLayout->addWidget(createTitle(), 0, Qt::AlignCenter);
    mainLayout->addWidget(createStatusGroup());
    mainLayout->addWidget(createControlsGroup());
    mainLayout->addWidget(themeToggleButton, 0, Qt::AlignCenter);

    setCentralWidget(centralWidget);
    resize(800, 600);
}
/**
 * @brief Создание метки с заголовком.
 *
 * Создает и настраивает метку с заголовком приложения.
 *
 * @return Указатель на QLabel, содержащий заголовок.
 */
QLabel* MainWindow::createTitle() {
    QLabel *titleLabel = new QLabel(Strings::climateControlSystemTitle, this);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; text-align: center;");
    return titleLabel;
}

/**
 * @brief Создание группы с состоянием системы.
 *
 * Создает группу, содержащую метки для отображения температуры, влажности и давления.
 *
 * @return Указатель на QGroupBox с состоянием системы.
 */
QGroupBox* MainWindow::createStatusGroup() {
    QGroupBox *statusGroup = new QGroupBox(Strings::systemControlGroup, this);
    QVBoxLayout *statusLayout = new QVBoxLayout(statusGroup);

    tempLabel = new QLabel(this);
    humidityLabel = new QLabel(this);
    pressureLabel = new QLabel(this);

    statusLayout->addWidget(tempLabel);
    statusLayout->addWidget(humidityLabel);
    statusLayout->addWidget(pressureLabel);

    return statusGroup;
}

/**
 * @brief Создание группы с элементами управления.
 *
 * Создает группу элементов управления, включая кнопки и комбинированные поля.
 *
 * @return Указатель на QGroupBox с элементами управления.
 */
QGroupBox* MainWindow::createControlsGroup() {
    QGroupBox *controlsGroup = new QGroupBox(Strings::systemControlGroupTitle, this);
    QGridLayout *controlsLayout = new QGridLayout(controlsGroup);

    toggleButton = new QPushButton(Strings::toggleButtonOn, this);
    controlsLayout->addWidget(toggleButton, 0, 0, 1, 2);

    increaseTempButton = new QPushButton(Strings::increaseTempButton, this);
    decreaseTempButton = new QPushButton(Strings::decreaseTempButton, this);
    increaseHumidityButton = new QPushButton(Strings::increaseHumidityButton, this);
    decreaseHumidityButton = new QPushButton(Strings::decreaseHumidityButton, this);
    increasePressureButton = new QPushButton(Strings::increasePressureButton, this);
    decreasePressureButton = new QPushButton(Strings::decreasePressureButton, this);

    controlsLayout->addWidget(increaseTempButton, 1, 0);
    controlsLayout->addWidget(decreaseTempButton, 1, 1);
    controlsLayout->addWidget(increaseHumidityButton, 2, 0);
    controlsLayout->addWidget(decreaseHumidityButton, 2, 1);
    controlsLayout->addWidget(increasePressureButton, 3, 0);
    controlsLayout->addWidget(decreasePressureButton, 3, 1);

    unitSelector = new QComboBox(this);
    unitSelector->addItems({Strings::celsius, Strings::fahrenheit, Strings::kelvin});
    controlsLayout->addWidget(new QLabel(Strings::tempUnitLabel), 4, 0);
    controlsLayout->addWidget(unitSelector, 4, 1);

    pressureUnitSelector = new QComboBox(this);
    pressureUnitSelector->addItems({"Па", "мм рт. ст."});
    controlsLayout->addWidget(new QLabel(Strings::pressureUnitLabel), 5, 0);
    controlsLayout->addWidget(pressureUnitSelector, 5, 1);

    inputTemperatureButton = new QPushButton(Strings::inputTemperatureButton, this);
    inputHumidityButton = new QPushButton(Strings::inputHumidityButton, this);
    inputPressureButton = new QPushButton(Strings::inputPressureButton, this);

    controlsLayout->addWidget(inputTemperatureButton, 6, 0, 1, 2);
    controlsLayout->addWidget(inputHumidityButton, 7, 0, 1, 2);
    controlsLayout->addWidget(inputPressureButton, 8, 0, 1, 2);

    directionSelector = new QComboBox(this);
    directionSelector->addItems({Strings::upDirection, Strings::downDirection, Strings::leftDirection, Strings::rightDirection});
    controlsLayout->addWidget(new QLabel(Strings::airDirectionLabelString), 9, 0);
    controlsLayout->addWidget(directionSelector, 9, 1);

    return controlsGroup;
}

/**
 * @brief Настройка всех соединений сигналов и слотов.
 *
 * Соединяет сигналы от кнопок и других элементов интерфейса с соответствующими слотами.
 */
void MainWindow::setupConnections() {
    connect(themeToggleButton, &QPushButton::clicked, &themeSwitcher, &ThemeSwitcher::toggleTheme);
    connect(toggleButton, &QPushButton::clicked, this, &MainWindow::toggleSystem);
    connect(increaseTempButton, &QPushButton::clicked, this, &MainWindow::increaseTemperature);
    connect(decreaseTempButton, &QPushButton::clicked, this, &MainWindow::decreaseTemperature);
    connect(increaseHumidityButton, &QPushButton::clicked, this, &MainWindow::increaseHumidity);
    connect(decreaseHumidityButton, &QPushButton::clicked, this, &MainWindow::decreaseHumidity);
    connect(increasePressureButton, &QPushButton::clicked, this, &MainWindow::increasePressure);
    connect(decreasePressureButton, &QPushButton::clicked, this, &MainWindow::decreasePressure);
    connect(unitSelector, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::updateLabels);
    connect(pressureUnitSelector, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::updateLabels);
    connect(inputTemperatureButton, &QPushButton::clicked, this, &MainWindow::openTemperatureInputDialog);
    connect(inputPressureButton, &QPushButton::clicked, this, &MainWindow::openPressureInputDialog);
    connect(inputHumidityButton, &QPushButton::clicked, this, &MainWindow::openHumidityInputDialog);
    connect(directionSelector, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::changeAirDirection);
}

/**
  * @brief Переключение состояния системы (включение/выключение).
  *
  * Переключает состояние системы и обновляет текст на кнопке.
  */
void MainWindow::toggleSystem() {
    climateControl.togglePower();
    toggleButton->setText(climateControl.isSystemOn() ? Strings::turnOffAirConditioner : Strings::turnOnAirConditioner);
}

/**
 * @brief Увеличение температуры.
 *
 * Увеличивает температуру и обновляет метки на экране.
 */
void MainWindow::increaseTemperature() {
    climateControl.increaseTemperature();
    updateLabels();
}

/**
  * @brief Уменьшение температуры.
  *
  * Уменьшает температуру и обновляет метки на экране.
  */
void MainWindow::decreaseTemperature() {
    climateControl.decreaseTemperature();
    updateLabels();
}

/**
 * @brief Увеличение влажности.
 *
 * Увеличивает влажность, при этом не допускается, чтобы она выходила за пределы от 0 до 100%.
 * Если влажность превышает 100%, выводится предупреждение.
 */
void MainWindow::increaseHumidity() {
    climateControl.increaseHumidity();
    if (climateControl.getHumidity() > 100) {
        QMessageBox::warning(this, Strings::warningHumidityOver100, Strings::warningHumidityOver100);
        climateControl.setHumidity(100);
    }
    updateLabels();
}

/**
 * @brief Уменьшение влажности.
 *
 * Уменьшает влажность, при этом не допускается, чтобы она выходила за пределы от 0 до 100%.
 */
void MainWindow::decreaseHumidity() {
    climateControl.decreaseHumidity();
    if (climateControl.getHumidity() < 0) {
        climateControl.setHumidity(0);
    }
    updateLabels();
}

/**
 * @brief Увеличение давления.
 *
 * Увеличивает давление и обновляет метки на экране.
 */
void MainWindow::increasePressure() {
    climateControl.increasePressure();
    updateLabels();
}

/**
 * @brief Уменьшение давления.
 *
 * Уменьшает давление и обновляет метки на экране.
 */
void MainWindow::decreasePressure() {
    climateControl.decreasePressure();
    updateLabels();
}

/**
 * @brief Изменение направления воздуха.
 *
 * Изменяет направление потока воздуха в зависимости от выбора пользователя.
 */
void MainWindow::changeAirDirection() {
    int directionIndex = directionSelector->currentIndex();
    QString direction = directionSelector->itemText(directionIndex);
    climateControl.setAirDirection(direction);
    QMessageBox::information(this, Strings::airDirectionLabelString, Strings::directionChosenMessage + direction);
}

/**
 * @brief Открытие диалога для ввода температуры.
 *
 * Открывает диалоговое окно для ввода температуры, и если значение подтверждено, обновляет температуру в системе.
 */
void MainWindow::openTemperatureInputDialog() {
    TemperatureInputDialog inputDialog(this);
    if (inputDialog.exec() == QDialog::Accepted) {
        climateControl.setTemperature(inputDialog.getValue());
        updateLabels();
    }
}

/**
 * @brief Открытие диалога для ввода давления.
 *
 * Открывает диалоговое окно для ввода давления, и если значение подтверждено, обновляет давление в системе.
 */
void MainWindow::openPressureInputDialog() {
    PressureInputDialog inputDialog(this);
    if (inputDialog.exec() == QDialog::Accepted) {
        climateControl.setPressure(inputDialog.getValue());
        updateLabels();
    }
}

/**
 * @brief Открытие диалога для ввода влажности.
 *
 * Открывает диалоговое окно для ввода влажности. Если влажность выходит за пределы допустимых значений, показываются предупреждения.
 */
void MainWindow::openHumidityInputDialog() {
    HumidityInputDialog inputDialog(this);
    if (inputDialog.exec() == QDialog::Accepted) {
        float humidity = inputDialog.getValue();

        if (humidity > 100) {
            QMessageBox::warning(this, Strings::warningHumidityOver100, Strings::warningHumidityOver100);
        } else if (humidity < 0) {
            QMessageBox::warning(this, Strings::warningHumidityUnder0, Strings::warningHumidityUnder0);
        } else {
            climateControl.setHumidity(humidity);
            updateLabels();
        }
    }
}

/**
 * @brief Обновление меток на экране.
 *
 * Пересчитывает и обновляет значения температуры и давления в зависимости от выбранных единиц измерения.
 */
void MainWindow::updateLabels() {
    IConverter* tempConverter = new TemperatureConverter();
    int tempUnit = unitSelector->currentIndex();
    float convertedTemp = tempConverter->convert(climateControl.getTemperature(), tempUnit);

    // Получаем строку с единицей измерения для температуры
    QString tempUnitString = QString::fromStdString(tempConverter->unitToString(tempUnit));

    // Форматируем строку с температурой и единицей измерения
    tempLabel->setText(QString("Температура: %1 %2")
                           .arg(convertedTemp)
                           .arg(tempUnitString));

    humidityLabel->setText(climateControl.getHumidityText());

    IConverter* pressureConverter = new PressureConverter();
    int pressureUnit = pressureUnitSelector->currentIndex();
    float pressure = climateControl.getPressure();
    float convertedPressure = pressureConverter->convert(pressure, pressureUnit);


    QString pressureUnitString = QString::fromStdString(pressureConverter->unitToString(pressureUnit));


    QString pressureText = QString("Давление: %1 %2")
                               .arg(convertedPressure)
                               .arg(pressureUnitString);

    pressureLabel->setText(pressureText);

    delete tempConverter;
    delete pressureConverter;
}

/**
 * @brief Открывает диалоговое окно для ввода текста пользователем.
 *
 * Эта функция открывает стандартное диалоговое окно, которое позволяет пользователю ввести строку текста.
 * После того как пользователь введет данные и подтвердит выбор, текст будет выведен в информационном сообщении.
 * Если пользователь отменяет ввод, показывается соответствующее информационное сообщение.
 * В случае ошибки или если пользователь ввел пустое значение, показывается предупреждающее сообщение.
 *
 * @note Использует стандартные компоненты Qt: QInputDialog и QMessageBox.
 */
void MainWindow::openInputDialog() {
    bool ok;
    QString text = QInputDialog::getText(this, Strings::inputDataTitle,
                                         Strings::inputDataMessage, QLineEdit::Normal,
                                         QString(), &ok);

    if (ok && !text.isEmpty()) {
        QMessageBox::information(this, Strings::inputDataTitle, Strings::enteredDataMessage + text);
    } else if (!ok) {
        QMessageBox::information(this, Strings::inputDataTitle, Strings::cancelMessage);
    } else {
        QMessageBox::warning(this, Strings::inputDataTitle, Strings::errorMessage);
    }
}
