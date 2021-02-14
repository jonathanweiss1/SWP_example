#ifndef PATIENTTABLEMODEL_H
#define PATIENTTABLEMODEL_H

#include <vector>
#include <string>
#include <tuple>
#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QDebug>

class patientTableModel
{
public:
    patientTableModel();
    ~patientTableModel();
    /**
     * @brief size Returns the number of rows in the database
     * @return
     */
    long size();

    /**
     * @brief addPatient adds a new entry to the patients table
     * @param name
     * @param givenName
     * @param age
     * @param size
     * @param weight
     * @param bmi
     * @return
     */
    long addPatient(std::string name, std::string givenName, unsigned age, float size, float weight, float bmi);

    /**
     * @brief getPatients returns a vector with all patients in the database
     * @return
     */
    std::vector<std::tuple<long, std::string, std::string, unsigned, float, float, float> > getPatients();

    /**
     * @brief updatePatient updates the entry with the specified id in the database
     * @param id
     * @param name
     * @param givenName
     * @param age
     * @param size
     * @param weight
     * @param bmi
     */
    void updatePatient(long id, std::string name, std::string givenName, unsigned age, float size, float weight, float bmi);

    /**
     * @brief removePatient deletes the entry with the specified id from the database
     * @param id
     */
    void removePatient(long id);
private:

    /**
     * @brief createTableIfNotExists checks if the database table exists and creates a new one if it does not
     */
    void createTableIfNotExists();

    const QString DatabaseDriver = "QSQLITE";
    QSqlDatabase *db = nullptr;
};

#endif // PATIENTTABLEMODEL_H
