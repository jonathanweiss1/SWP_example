#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "tablecontroller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief The Main GUI of the application
 */
class MainWindow : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT

public:
    /**
     * @brief MainWindow
     * @param controller processes everything that happens in the ui
     * @param parent
     */
    MainWindow(TableController *controller, QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    /**
     * @brief addEntry adds a new entry to the UI's patient table
     * @param id
     * @param name
     * @param givenName
     * @param age
     * @param size
     * @param weight
     * @param bmi
     */
    void addEntry(long id, std::string name, std::string givenName, unsigned age, float size, float weight, float bmi);

    /**
     * @brief removeEntry removes the entry with the specified id from the UI's patient table
     * @param id
     */
    void removeEntry(long id);

    /**
     * @brief updateEntry updates the entry with the specified id in the UI's patient table to ressemble the given parameters
     * @param id
     * @param name
     * @param givenName
     * @param age
     * @param size
     * @param weight
     * @param bmi
     */
    void updateEntry(long id, std::string name, std::string givenName, unsigned int age, float size, float weight, float bmi);

signals:
    /**
     * @brief controllerAddData is raised whenever the controller should add new data to the model
     * @param name
     * @param givenName
     * @param age
     * @param size
     * @param weight
     */
    void controllerAddData(std::string name, std::string givenName, unsigned age, float size, float weight);

    /**
     * @brief controllerDeleteEntry is raised whenever the controller should delete an entry from the model
     * @param id
     */
    void controllerDeleteEntry(long id);

    /**
     * @brief controllerUpdateEntry is raised everytime the controller has to update model data
     * @param id
     * @param name
     * @param givenName
     * @param age
     * @param size
     * @param weight
     */
    void controllerUpdateEntry(long id, std::string name, std::string givenName, unsigned int age, float size, float weight);

private slots:
    /**
     * @brief addCurrentDataToTable adds a new entry to the UI's patient table and raises controllerAddData based on the user's input
     */
    void addCurrentDataToTable();

    /**
     * @brief clearInput clears all input fields
     */
    void clearInput();

    /**
     * @brief removeButtonPressed raises controllerDeleteEntry
     */
    void removeButtonPressed();

    /**
     * @brief updateButtonPressed changes the currently selected patient data and raises controllerUpdateEntry based on the user's input
     */
    void updateButtonPressed();

private:
    /**
     * @brief getSelectedRowId returns the id of the currently selected entry
     * @return
     */
    int getSelectedRowId();

    Ui::MainWindow *ui;
    TableController *controller = nullptr;
};
#endif // MAINWINDOW_H
