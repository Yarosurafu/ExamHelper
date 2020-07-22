#ifndef NFCREATOR_H
#define NFCREATOR_H

#include <QWidget>
#include <QJsonObject>

namespace Ui {
class NfCreator;
}

class NfCreator : public QWidget
{
    Q_OBJECT

public:
    explicit NfCreator(QWidget *parent = nullptr);
    ~NfCreator();

private slots:
    void on_cancelBut_clicked();

    void on_createNotifBut_clicked();

public slots:
    void setQuestion(QJsonObject question);

signals:
    void exit();

private:
    Ui::NfCreator *ui;
    QJsonObject m_question;
    QString m_date = "";
    void writeToJson();
};

#endif // NFCREATOR_H
