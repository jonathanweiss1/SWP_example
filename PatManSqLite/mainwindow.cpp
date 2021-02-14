#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(TableController *controller, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , controller(controller)
{
    setupUi(this);

    //connect signals with slots
    //ADD
    connect(addPushButton, &QPushButton::clicked, this, &MainWindow::addCurrentDataToTable);
    connect(this, SIGNAL(controllerAddData(std::string, std::string, unsigned, float, float)),
            controller, SLOT(addEntry(std::string, std::string, unsigned, float, float)));
    connect(controller, SIGNAL(addEntryToTable(long, std::string, std::string, unsigned int, float, float, float)),
            this, SLOT(addEntry(long, std::string, std::string, unsigned int, float, float, float)));
    //DELETE
    connect(deletePushButton, &QPushButton::clicked, this, &MainWindow::removeButtonPressed);
    connect(this, SIGNAL(controllerDeleteEntry(long)), controller, SLOT(deleteEntry(long)));
    connect(controller, SIGNAL(removeEntryFromTable(long)), this, SLOT(removeEntry(long)));
    //UPDATE
    connect(updatePushButton, &QPushButton::clicked, this, &MainWindow::updateButtonPressed);
    connect(this, SIGNAL(controllerUpdateEntry(long, std::string, std::string, unsigned int, float, float)),
            controller, SLOT(updateEntry(long, std::string, std::string, unsigned int, float, float)));
    connect(controller, SIGNAL(updateEntryInTable(long, std::string, std::string, unsigned int, float, float, float)),
            this, SLOT(updateEntry(long, std::string, std::string, unsigned int, float, float, float)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addEntry(long id, std::string name, std::string givenName, unsigned int age, float size, float weight, float bmi){
    //insert new row at the end of the table
    int newRow = patientsTable->rowCount();
    patientsTable->insertRow(newRow);
    QTableWidgetItem *nameItem = new QTableWidgetItem;
    QTableWidgetItem *givenNameItem = new QTableWidgetItem;
    QTableWidgetItem *ageItem = new QTableWidgetItem;
    QTableWidgetItem *sizeItem = new QTableWidgetItem;
    QTableWidgetItem *weightItem = new QTableWidgetItem;
    QTableWidgetItem *bmiItem = new QTableWidgetItem;

    //the first item (name) stores additional data: The id of the entry that is used to
    //differentiate entries even if all parameters are the same
    nameItem->setData(Qt::UserRole, QVariant::fromValue(id));
    nameItem->setText(QString::fromStdString(name));
    givenNameItem->setText(QString::fromStdString(givenName));
    ageItem->setText(QString::number(age));
    sizeItem->setText(QString::number(size));
    weightItem->setText(QString::number(weight));
    bmiItem->setText(QString::number(bmi));
    //add items to the newly created row
    patientsTable->setItem(newRow, 0, nameItem);
    patientsTable->setItem(newRow, 1, givenNameItem);
    patientsTable->setItem(newRow, 2, ageItem);
    patientsTable->setItem(newRow, 3, sizeItem);
    patientsTable->setItem(newRow, 4, weightItem);
    patientsTable->setItem(newRow, 5, bmiItem);
}

void MainWindow::removeEntry(long id){
    //search the table for the id and remove the first entry that matches
    for(int i = 0;  i < patientsTable->rowCount(); i++){
        int itemid = patientsTable->item(i, 0)->data(Qt::UserRole).toInt();
        if(itemid == id){
            patientsTable->removeRow(i);
        }
    }
}

void MainWindow::updateEntry(long id, std::string name, std::string givenName, unsigned int age, float size, float weight, float bmi){
    //search the table for the id and update the text for all items of the matching entry based on the given parameters
    for(int i = 0;  i < patientsTable->rowCount(); i++){
        int itemid = patientsTable->item(i, 0)->data(Qt::UserRole).toInt();
        if(itemid == id){
            patientsTable->item(i, 0)->setText(QString::fromStdString(name));
            patientsTable->item(i, 1)->setText(QString::fromStdString(givenName));
            patientsTable->item(i, 2)->setText(QString::number(age));
            patientsTable->item(i, 3)->setText(QString::number(size));
            patientsTable->item(i, 4)->setText(QString::number(weight));
            patientsTable->item(i, 5)->setText(QString::number(bmi));
        }
    }
}

void MainWindow::addCurrentDataToTable(){
    emit controllerAddData(
                nameLineEdit->text().toStdString(),
                givenNameLineEdit->text().toStdString(),
                ageSpinBox->value(),
                sizeSpinBox->value(),
                weightSpinBox->value()
                );
    clearInput();
}

void MainWindow::clearInput(){
    nameLineEdit->clear();
    givenNameLineEdit->clear();
    ageSpinBox->clear();
    sizeSpinBox->clear();
    weightSpinBox->clear();
}

int MainWindow::getSelectedRowId(){
    auto selected = patientsTable->selectedItems();
    if(selected.isEmpty())
        return -1;
    else
        return selected.first()->data(Qt::UserRole).toInt();
}

void MainWindow::removeButtonPressed(){
    if(getSelectedRowId() != -1)
        emit controllerDeleteEntry(getSelectedRowId());
}

void MainWindow::updateButtonPressed(){
    if(getSelectedRowId() != -1)
        emit controllerUpdateEntry(
                getSelectedRowId(),
                nameLineEdit->text().toStdString(),
                givenNameLineEdit->text().toStdString(),
                ageSpinBox->value(),
                sizeSpinBox->value(),
                weightSpinBox->value()
         );
}

