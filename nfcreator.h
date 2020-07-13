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

private:
    Ui::NfCreator *ui;
};

#endif // NFCREATOR_H
