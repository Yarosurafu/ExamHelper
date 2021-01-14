#ifndef CONFIG_H
#define CONFIG_H
#include <vector>
#include <QString>
#include <QJsonArray>


class Config
{
public:
    Config();
    enum class Buttons{
        FIRST_BUTTON,
        SECOND_BUTTON,
        THIRD_BUTTON,
        MAX_BUTTONS
    };

    std::vector<QString> getButtons();
    void saveOptions(std::vector<QString> buttons);
private:
    QJsonArray options;
    void parseOptions();
    QJsonObject getOption(QString option);
};

#endif // CONFIG_H
