#ifndef PARSINGPROGRESS_H
#define PARSINGPROGRESS_H

#include <QDialog>

namespace Ui {
class ParsingProgress;
}

class ParsingProgress : public QDialog
{
    Q_OBJECT

public:
    explicit ParsingProgress(QWidget *parent = nullptr);
    ~ParsingProgress();

private:
    Ui::ParsingProgress *ui;
};

#endif // PARSINGPROGRESS_H
