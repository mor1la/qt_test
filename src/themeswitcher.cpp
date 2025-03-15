#include "themeswitcher.h"

/**
 * @brief Конструктор класса ThemeSwitcher.
 *
 * Инициализирует состояние темы как светлая (darkMode = false).
 * @param parent Родительский объект для QObject.
 */
ThemeSwitcher::ThemeSwitcher(QObject *parent) : QObject(parent), darkMode(false) {}

/**
 * @brief Переключает тему между темной и светлой.
 *
 * Этот метод изменяет состояние переменной darkMode и вызывает
 * соответствующие методы для применения нужной темы.
 */
void ThemeSwitcher::toggleTheme() {
    darkMode = !darkMode;
    if (darkMode) {
        applyDarkTheme();
    } else {
        applyLightTheme();
    }
}

/**
 * @brief Применяет темную тему для приложения.
 *
 * Этот метод изменяет стили приложения, чтобы использовать темную тему.
 * Меняются цвета фона, текста, кнопок и других элементов интерфейса.
 */
void ThemeSwitcher::applyDarkTheme() {
    qApp->setStyleSheet(""
                        "QWidget { background-color: #121212; color: #ffffff; }"
                        "QPushButton { background-color: #333333; color: #ffffff; border: 1px solid #555555; padding: 5px; }"
                        "QPushButton:hover { background-color: #444444; }"  // добавляем эффект при наведении
                        "QPushButton:pressed { background-color: #555555; }"  // добавляем эффект при нажатии
                        "QLabel { color: #ffffff; margin: 2px; }"
                        "QGroupBox { border: 1px solid #555555; color: #ffffff; padding: 10px; margin-top: 1px; }"
                        "");
}

/**
 * @brief Применяет светлую тему.
 *
 * Этот метод сбрасывает стиль, применяя дефолтный стиль приложения, который является светлым.
 */
void ThemeSwitcher::applyLightTheme() {
    qApp->setStyleSheet("");
}
