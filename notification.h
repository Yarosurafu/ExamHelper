#ifndef NOTIFICATION_H
#define NOTIFICATION_H
#include <QJsonArray>
#include <vector>
#include <QWidget>


class Notification
{
public:
    Notification();
    QJsonArray getQuestions();
    /**
     * @brief deleteCurrentQuestionsFromFile
     *
     * Method for saving UPDATED notification-database with
     * deleted records of irrelevant questions.
     */
    void deleteCurrentQuestionsFromFile();
    void update();
    int getNotifQuant();

private:
    //Database of all notifications
    QJsonArray database;
    /*Vector, that contains indices of questions,
     * that will be displayed for user at the moment of
     * "NotificationHelper" execution.
    */
    std::vector<int> questions;
    /**
     * @brief parseJson
     *
     * Method, that parses JSON-file, called
     * "notifications.json", at the start of app's execution
     */
    void parseJson();
    /**
     * @brief formCurrentQuestions
     *
     * Method for forming an array of indices of relevant questions.
     * Relevant questions - questions, date and time of which are
     * less or equals than current date and time. Relevant questions
     * will be displayed for user.
     */
    void formCurrentQuestions();
};

#endif // NOTIFICATION_H
