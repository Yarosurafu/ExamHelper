#ifndef NFCREATOR_H
#define NFCREATOR_H

#include <QWidget>

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
    void setQuestion(QString question);

signals:
    void exit();

private:
    Ui::NfCreator *ui;
    QString m_question = "";
    QString m_date = "";
    void writeToJson();
};

#endif // NFCREATOR_H
