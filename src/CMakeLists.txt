cmake_minimum_required(VERSION 3.5)
project(test_task_qt VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ищем необходимые компоненты для Qt5 (Core и Widgets)
find_package(QT NAMES Qt5 COMPONENTS Widgets Core REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Widgets Core)

# Список исходных файлов
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    climatecontrol.cpp
    climatecontrol.h
    controlbuttons.cpp
    controlbuttons.h
    humidityinputdialog.cpp
    humidityinputdialog.h
    temperatureinputdialog.cpp
    temperatureinputdialog.h
    iconverter.cpp
    iconverter.h
    inputdialog.cpp
    inputdialog.h
    pressureconverter.cpp
    pressureconverter.h
    pressureinputdialog.cpp
    pressureinputdialog.h
    settings.xml
    constString.h
    temperatureconverter.cpp
    temperatureconverter.h
    themeswitcher.cpp
    themeswitcher.h
    usersettings.cpp
    usersettings.h
)

# Создание исполняемого файла
add_executable(test_task_qt ${PROJECT_SOURCES})

# Линковка с необходимыми библиотеками Qt5
target_link_libraries(test_task_qt PRIVATE Qt5::Widgets Qt5::Core)

# Устанавливаем свойства для целевого исполняемого файла
set_target_properties(test_task_qt PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
