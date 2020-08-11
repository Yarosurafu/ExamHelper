#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "parsingdb.h"
#include "nfcreator.h"
#include "database.h"
#include "tests.h"
#include "statistics.h"
#include "notification.h"

#include <QFileDialog>
#include <QDir>
#include <QFileInfoList>
#include <vector>
#include <QJsonObject>
#include <QMessageBox>
#include <QMdiSubWindow>
#include <QDebug>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    std::vector<QString> subjectsNames = db_m.getSubjectsNames();
    ui->matterComboBox->addItem("Искать во всех темах");
    for(size_t i = 0; i < subjectsNames.size(); ++i){
        ui->matterComboBox->addItem(subjectsNames[i]);
        ui->mattersList->addItem(subjectsNames[i]);
    }
    QPixmap image(":/icons/images/Basya-def.png");
    ui->image->setPixmap(image);
    QPixmap basyaNotif(":/icons/images/Basya-notif.png");
    ui->basya->setPixmap(basyaNotif);
    ui->notifButt->setText("Количество уведомлений: " + QString::number(notif.getNotifQuant()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_parseButt_clicked()
{
    QString dirName = ui->directoryLine->text();
    ui->directoryLine->clear();
    QDir directory(dirName);
    QFileInfoList files = directory.entryInfoList();
    for(int i = 0; i < files.size(); ++i){
        QString path = files[i].absoluteFilePath();
        if(path.contains(".html")){
            //QMessageBox::critical(this, "Debug", QString::number(i));
            ParsingDB::parse(path);
        }
    }
    QMessageBox::information(this, "Анализ веб-страниц", "Анализ завершен");
}

void MainWindow::on_pickFileButt_clicked()
{
    QString dirName = QFileDialog::getExistingDirectory(this, "Pick up directory with HTML", "C:/", QFileDialog::ShowDirsOnly
                                                                                                    | QFileDialog::DontResolveSymlinks);
    ui->directoryLine->setText(dirName);
}

void MainWindow::on_searchButton_clicked()
{
    QString key = ui->userQuestion->text();
    QString matter = ui->matterComboBox->currentText();
    searchedQuestions_m = db_m.searchQuestion(matter, key);
    currentQuestionInd = 0;
    setSearchedQuestion();
}

void MainWindow::on_nextButton_clicked()
{
    if(!searchedQuestions_m.size())
        return;
    if(searchedQuestions_m.size() - currentQuestionInd == 1)
        currentQuestionInd = 0;
    else
        ++currentQuestionInd;
    setSearchedQuestion();
}

void MainWindow::on_prevButton_clicked()
{
    if(!searchedQuestions_m.size())
        return;
    if(currentQuestionInd == 0)
        currentQuestionInd = searchedQuestions_m.size() - 1;
    else
        --currentQuestionInd;
    setSearchedQuestion();
}

void MainWindow::setSearchedQuestion(){
    QJsonObject currentQuestion = searchedQuestions_m[currentQuestionInd].toObject();
    ui->fullQuestion->setText(currentQuestion["question"].toString());
    ui->answer->setText(currentQuestion["answer"].toString());
    if(currentQuestion["question"].toString() == ""){
        QMessageBox::warning(this, "Поиск вопросов", "Вопросов не было найдено");
        ui->page->setText("-");
        return;
    }
    QString page = QString::number(currentQuestionInd + 1) + "/"
            + QString::number(searchedQuestions_m.size());
    ui->page->setText(page);
}

void MainWindow::on_startTest_clicked()
{
    ui->mdiArea->closeAllSubWindows();
    if(ui->mattersList->currentItem() == nullptr){
        QMessageBox::critical(this, "Ошибка", "Тему теста не выбрано");
        return;
    }
    QString selectedMatter = ui->mattersList->currentItem()->text();
    NfCreator *notif = new NfCreator(this);
    Statistics *statWindow = new Statistics(this);
    Tests *testWindow = new Tests(db_m.getTestVariant(selectedMatter), statWindow, this);

    setSubWindow(notif, "Создать уведомление", ui->mdiArea);
    setSubWindow(statWindow, "Результаты", ui->mdiArea);
    setSubWindow(testWindow, "Тест", ui->mdiArea);
    connect(notif, &NfCreator::exit, ui->mdiArea, &QMdiArea::activatePreviousSubWindow);
    connect(testWindow, &Tests::testEnd, ui->mdiArea, &QMdiArea::activatePreviousSubWindow);
    connect(testWindow, &Tests::notification, ui->mdiArea, &QMdiArea::activateNextSubWindow);
    connect(testWindow, &Tests::notification, notif, &NfCreator::setQuestion);
    connect(testWindow, &Tests::answer, this, &MainWindow::setBasya);
    connect(statWindow, &Statistics::closeAll, ui->mdiArea, &QMdiArea::closeAllSubWindows);
    connect(statWindow, &Statistics::repeat, ui->mdiArea, &QMdiArea::closeAllSubWindows);
    connect(statWindow, &Statistics::repeat, this, &MainWindow::on_startTest_clicked);
}

void MainWindow::setBasya(int emotion){
    switch(emotion){
        case (int)Tests::Results::CORRECT_RESULT:
            ui->image->setPixmap(QPixmap(":/icons/images/Basya-pass.png"));
        break;
        case (int)Tests::Results::WRONG_RESULT:
            ui->image->setPixmap(QPixmap(":/icons/images/Basya-wrong.png"));
        break;
        case (int)Tests::Results::CHANGE_RESULT:
            ui->image->setPixmap(QPixmap(":/icons/images/Basya-wait.png"));
        break;
        case (int)Tests::Results::PERFECT_RESULT:
            ui->image->setPixmap(QPixmap(":/icons/images/Basya-30end.png"));
        break;
        case (int)Tests::Results::PASSED_RESULT:
            ui->image->setPixmap(QPixmap(":/icons/images/Basya-20end.png"));
        break;
        case (int)Tests::Results::FAILED_RESULT:
            ui->image->setPixmap(QPixmap(":/icons/images/Basya-wrong.png"));
        break;
    }
}

void MainWindow::setSubWindow(QWidget *widget, QString title, QMdiArea* area){
    auto window = area->addSubWindow(widget);
    window->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
    window->setWindowTitle(title);
    window->showMaximized();
}

void MainWindow::on_startDownload_clicked()
{
    QString address = ui->address->text() + "/1";
    ui->address->clear();
    int  quantity = ui->quantity->text().toInt();
    ui->quantity->clear();
    for(int i = 1; i <= quantity; ++i){
        while(address.at(address.size() - 1) != '/')
            address.chop(1);
        address += QString::number(i);
        QString command = "wget -P \"" + QApplication::applicationDirPath() + "/pages\" "
                + address + " --no-check-certificate -E";
        QByteArray ba = command.toLatin1();
        const char *c_str = ba.data();
        system(c_str);
        delete c_str;
    }
}

void MainWindow::on_refreshNotif_clicked()
{
    notif.update();
    ui->notifButt->setText("Количество уведомлений: " + QString::number(notif.getNotifQuant()));
}

void MainWindow::on_startNotif_clicked()
{
    ui->notifArea->closeAllSubWindows();
    NfCreator *notifCreator = new NfCreator(this);
    Statistics *statWindow = new Statistics(this);
    QJsonArray variant = notif.getQuestions();
    if(variant.isEmpty())
        return;
    Tests *testWindow = new Tests(variant, statWindow, this);
    setSubWindow(notifCreator, "Создать уведомление", ui->notifArea);
    setSubWindow(statWindow, "Результаты", ui->notifArea);
    setSubWindow(testWindow, "Тест", ui->notifArea);
    connect(notifCreator, &NfCreator::exit, ui->notifArea, &QMdiArea::activatePreviousSubWindow);
    connect(testWindow, &Tests::testEnd, ui->notifArea, &QMdiArea::activatePreviousSubWindow);
    connect(testWindow, &Tests::notification, ui->notifArea, &QMdiArea::activateNextSubWindow);
    connect(testWindow, &Tests::notification, notifCreator, &NfCreator::setQuestion);
    connect(statWindow, &Statistics::closeAll, ui->notifArea, &QMdiArea::closeAllSubWindows);
    connect(statWindow, &Statistics::repeat, ui->notifArea, &QMdiArea::closeAllSubWindows);
    notif.deleteCurrentQuestionsFromFile();
    on_refreshNotif_clicked();
}
