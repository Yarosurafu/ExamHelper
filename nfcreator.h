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
    void on_pushButton_5_clicked();
    void setQuestion(QString question);

private:
    Ui::NfCreator *ui;
    QString question = "";
};

#endif // NFCREATOR_H
