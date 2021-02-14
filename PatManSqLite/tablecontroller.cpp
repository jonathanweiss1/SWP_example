#include "tablecontroller.h"

TableController::TableController()
{

}

void TableController::addEntry(std::string name, std::string givenName, unsigned int age, float size, float weight){
    float bmi = PatientDataCalculator::calculateBmi(size, weight);
    long id = model.addPatient(name, givenName, age, size, weight, bmi);
    emit addEntryToTable(id, name, givenName, age, size, weight, bmi);
}

void TableController::deleteEntry(long id){
    model.removePatient(id);
    emit removeEntryFromTable(id);
}

void TableController::updateEntry(long id, std::string name, std::string givenName, unsigned int age, float size, float weight){
    float bmi = PatientDataCalculator::calculateBmi(size, weight);
    model.updatePatient(id, name, givenName, age, size, weight, bmi);
    emit updateEntryInTable(id, name, givenName, age, size, weight, bmi);
}

void TableController::initTable(){
    std::vector<std::tuple<long, std::string, std::string, unsigned, float, float, float> > patientVector = model.getPatients();
    for(unsigned long long i = 0; i < patientVector.size(); i++){
        emit addEntryToTable(
                    std::get<0>(patientVector[i]),  //id
                    std::get<1>(patientVector[i]),  //name
                    std::get<2>(patientVector[i]),  //givenName
                    std::get<3>(patientVector[i]),  //age
                    std::get<4>(patientVector[i]),  //size
                    std::get<5>(patientVector[i]),  //weight
                    std::get<6>(patientVector[i])   //bmi
                    );
    }
}
