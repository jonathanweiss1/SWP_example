#include "patienttablemodel.h"

patientTableModel::patientTableModel()
{
    //establish a database connection. SQLite will create the database if it doesn't exist
    db = new QSqlDatabase(QSqlDatabase::addDatabase(DatabaseDriver));
    db->setDatabaseName("patmandatabase");
    db->setHostName(HOSTNAME);
    db->setPort(3306);
    db->setUserName("PatMan");
    db->setPassword("patman");
    db->open();
}

patientTableModel::~patientTableModel(){
    db->close();
    delete db;
}

long patientTableModel::size(){
    createTableIfNotExists();
    //if there is a sql statement in the constructor, it will get executed immediatly.
    QSqlQuery query("SELECT COUNT(*) FROM patientdata");
    //jump to first row
    query.next();
    return query.value(0).toInt();
}

long patientTableModel::addPatient(std::string name, std::string givenName, unsigned int age, float size, float weight, float bmi){
    createTableIfNotExists();
    QSqlQuery query;
    //prepare a query with placeholders
    query.prepare("INSERT INTO patientdata (name, givenName, age, size, weight, bmi) "
                  "VALUES (:name, :givenName, :age, :size, :weight, :bmi)");
    //add data instead of placeholders
    query.bindValue(":name", QString::fromStdString(name));
    query.bindValue(":givenName", QString::fromStdString(givenName));
    query.bindValue(":age", age);
    query.bindValue(":size", size);
    query.bindValue(":weight", weight);
    query.bindValue(":bmi", bmi);

    if(!query.exec()){
        qWarning() << "ERROR: " << query.lastError().text();
        return -1;
    }
    else
        return query.lastInsertId().toInt();
}

std::vector<std::tuple<long, std::string, std::string, unsigned, float, float, float> > patientTableModel::getPatients(){
    createTableIfNotExists();
    QSqlQuery query("SELECT id, name, givenName, age, size, weight, bmi FROM patientdata");
    std::vector<std::tuple<long, std::string, std::string, unsigned, float, float, float> > patientsVector;
    //create tuples for every row in the database
    while(query.next()){
        patientsVector.push_back(std::make_tuple(
                                     query.value(0).toInt(),
                                     query.value(1).toString().toStdString(),
                                     query.value(2).toString().toStdString(),
                                     query.value(3).toUInt(),
                                     query.value(4).toFloat(),
                                     query.value(5).toFloat(),
                                     query.value(6).toFloat()
                                     ));
    }
    return patientsVector;
}

void patientTableModel::updatePatient(long id, std::string name, std::string givenName, unsigned int age, float size, float weight, float bmi){
    createTableIfNotExists();
    QSqlQuery query;
    query.prepare("UPDATE patientdata "
                  "SET name = :name, givenName = :givenName, age = :age, size = :size, weight = :weight, bmi = :bmi "
                  "WHERE id = :id");
    query.bindValue(":id", QVariant::fromValue(id));
    query.bindValue(":name", QString::fromStdString(name));
    query.bindValue(":givenName", QString::fromStdString(givenName));
    query.bindValue(":age", age);
    query.bindValue(":size", size);
    query.bindValue(":weight", weight);
    query.bindValue(":bmi", bmi);

    if(!query.exec())
        qWarning() << "ERROR: " << query.lastError().text();
}

void patientTableModel::removePatient(long id){
    createTableIfNotExists();
    QSqlQuery query;
    query.prepare("DELETE FROM patientdata WHERE id = :id");
    query.bindValue(":id", QVariant::fromValue(id));

    if(!query.exec())
        qWarning() << "ERROR: " << query.lastError().text();
}

void patientTableModel::createTableIfNotExists(){
    if(db->tables().contains("patientdata"))
        return;

    QSqlQuery query("CREATE TABLE patientdata("
                    "id INTEGER PRIMARY KEY AUTO_INCREMENT NOT NULL, "
                    "name VARCHAR(45) NOT NULL, "
                    "givenName VARCHAR(45) NOT NULL, "
                    "age SMALLINT, "
                    "size FLOAT, "
                    "weight FLOAT, "
                    "bmi FLOAT)");


    if(!query.isActive())
        qWarning() << "ERROR: " << query.lastError().text();
}
