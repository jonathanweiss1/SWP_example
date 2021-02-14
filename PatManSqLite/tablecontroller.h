#ifndef TABLECONTROLLER_H
#define TABLECONTROLLER_H

#include <QObject>
#include <patientdatacalculator.h>
#include "patienttablemodel.h"


class TableController : public QObject
{
    Q_OBJECT
public:
    TableController();

    /**
     * @brief initTable raises addEntryToTable for every entry in the model
     */
    void initTable();

signals:
    /**
     * @brief addEntryToTable is raised everytime the view has to add a new entry
     * @param id
     * @param name
     * @param givenName
     * @param age
     * @param size
     * @param weight
     * @param bmi
     */
    void addEntryToTable(long id, std::string name, std::string givenName, unsigned int age, float size, float weight, float bmi);
    /**
     * @brief removeEntryFromTable is raised everytime the view has to delete the entry with the specified id
     * @param id
     */

    void removeEntryFromTable(long id);

    /**
     * @brief updateEntryInTable is raised when the view has to update the entry with the specified id
     * @param id
     * @param name
     * @param givenName
     * @param age
     * @param size
     * @param weight
     * @param bmi
     */
    void updateEntryInTable(long id, std::string name, std::string givenName, unsigned int age, float size, float weight, float bmi);

public slots:
    /**
     * @brief addEntry adds a new entry to the model and raises addEntryToTable
     * @param name
     * @param givenName
     * @param age
     * @param size
     * @param weight
     */
    void addEntry(std::string name, std::string givenName, unsigned int age, float size, float weight);

    /**
     * @brief deleteEntry deletes the entry with the specified id from the model and raises remove entry from table
     * @param id
     */
    void deleteEntry(long id);

    /**
     * @brief updateEntry updates the entry with the specified id in the model and raises updateEntryInTable
     * @param id
     * @param name
     * @param givenName
     * @param age
     * @param size
     * @param weight
     */
    void updateEntry(long id, std::string name, std::string givenName, unsigned int age, float size, float weight);

private:
    patientTableModel model;
};

#endif // TABLECONTROLLER_H
