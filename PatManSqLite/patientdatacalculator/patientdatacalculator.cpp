#include "patientdatacalculator.h"

PatientDataCalculator::PatientDataCalculator()
{

}

float PatientDataCalculator::calculateBmi(float size, float weight){
    return weight/(size*size);  //bmi = weight/sqrt(size)
}
