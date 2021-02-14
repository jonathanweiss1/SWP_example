#include "patientdatacalculator.h"
#include <cmath>

PatientDataCalculator::PatientDataCalculator()
{

}

float PatientDataCalculator::calculateBmi(float size, float weight){
    if(size < 0)
        size *= -1;
    //the equivalent for weight is missing on purpose to make the test fail. Uncomment the following to make it pass:
    //if(weight < 0)
        //weight *= -1;

    //round to two decimals
    return roundf((weight/(size*size)) * 100) / 100;  //bmi = weight/sqrt(size)
}
