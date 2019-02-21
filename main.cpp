#include <iostream>
#include <ctime>
#include <vector>

using namespace std;


class Duty {


    string day;
    int hour;
    int duration;
    int physician_id;

public:

    //Parameterized Constructor
    Duty(string dutyDay, int dutyHour, int dutyDuration, int dutyPhysician_id) {

        day = dutyDay; //Day of duty, should be either "Mo", "Tu", "We", "Th", "Fr"
        hour = dutyHour; // Starting time of duty (0 to 23)
        duration = dutyDuration; // How long duty lasts
        physician_id = dutyPhysician_id;
    }

    string getDay() {

        if (day == "Mo" || day == "Tu" || day == "We" || day == "Th" || day == "Fri") {
                        return day;

        }
        else {
            return "Error: Invalid day.";
        }


    }

    int getHour() {

    return hour;

    }

    int getDuration() {

        return duration;

    }


    int getPhysician_id() {

        return physician_id;

        }

};

class AbsenceRequest {


    string absenceDay;
    int absenceHour;
    int absenceDuration;
    int absentPhysician_id;

public:

    //Parameterized Constructor
    AbsenceRequest(string requestDay, int requestHour, int requestDuration, int requestPhysician_id) {

        absenceDay = requestDay;
        absenceHour = requestHour;
        absenceDuration = requestDuration;
        absentPhysician_id = requestPhysician_id;
    }

    string getAbsentDay() {

        if (absenceDay == "Mo" || absenceDay == "Tu" || absenceDay == "We" || absenceDay == "Th" || absenceDay == "Fri") {
                        return absenceDay;

        }
        else {
            return "Error: Invalid Day.";
        }


    }

    int getAbsentHour() {

    return absenceHour;

    }

    int getAbsentDuration() {

        return absenceDuration;

    }


    int getAbsentPhysician_id() {

        return absentPhysician_id;

        }



};

//Problem 1 Part A
int validAbsenceRequest(AbsenceRequest request) {

        if ((request.getAbsentHour() + request.getAbsentDuration()) > 23)
        {
            return 1; //Error
        }
        else
        {
            return 0; //Success
        }
    }

bool isInRange(int low, int high, int numberInQuestion)
{
    return (numberInQuestion > low && numberInQuestion < high);
}

//Problem 1 Part B

vector<Duty> conflictingDuties(vector<Duty> doctorDuties, vector<AbsenceRequest> requests)
{
    vector<Duty> dutiesInConflict;
    //Loops through list of duties

    for (int a = 0; a<doctorDuties.size(); a++)
    {


        int dutyId = doctorDuties.at(a).getPhysician_id();
        string dutyWeekDay = doctorDuties.at(a).getDay();

        for (int b = 0; b< requests.size(); b++)
        {
            int requestId = requests.at(b).getAbsentPhysician_id();
            string requestWeekDay = requests.at(b).getAbsentDay();

            //Compares the Id and weekday of a duty and absenceRequest to determine of there is a need
            // to check for conflicts

            bool potentialDutyConflict = ((dutyId == requestId) && (dutyWeekDay == requestWeekDay));

            if (potentialDutyConflict == true)
            {
                int dutyBegins = doctorDuties.at(a).getHour();
                int dutyDuration = doctorDuties.at(a).getDuration();
                int dutyEnds = dutyBegins + dutyDuration;

                int absenceBegins = requests.at(b).getAbsentHour();
                int absentDuration = requests.at(b).getAbsentDuration();
                int absenceEnds = absenceBegins + absentDuration;

                //Sees of any part of the absence request is in the range of the duty.
                // If both are true, then the duty is added to the list of conflicts.

                bool absenceBeginsInRange = isInRange(dutyBegins, dutyEnds, absenceBegins);
                bool absenceEndsInRange = isInRange(dutyBegins, dutyEnds, absenceEnds);

                if (absenceBeginsInRange == true || absenceEndsInRange == true)
                {
                    //Adds the duty that has a conficting absent request
                    dutiesInConflict.push_back(doctorDuties.at(a));
                }

            }
        }
    }

    return dutiesInConflict;
}

int main()
{


    Duty d1("Mo", 8, 4, 1);
    Duty d2("Mo", 9, 5, 2);
    Duty d3("Mo", 10, 3, 3);
    Duty d4("Mo", 12, 2, 4);
    Duty d5("Mo", 13, 4, 5);
    Duty d6("Mo", 9, 2, 6);
    Duty d7("Mo", 7, 4, 7);
    Duty d8("Mo", 15, 1, 8);

    //"List of duties"
    vector<Duty> duties;
    duties.push_back(d1);
    duties.push_back(d2);
    duties.push_back(d3);
    duties.push_back(d4);
    duties.push_back(d5);
    duties.push_back(d6);
    duties.push_back(d7);
    duties.push_back(d8);


    AbsenceRequest r1("Mo", 1, 7, 1);
    AbsenceRequest r2("Mo", 10, 2, 2);
    AbsenceRequest r3("Th", 13, 2, 3);

    //"List of absence requests"
    vector<AbsenceRequest> absences;
    absences.push_back(r1);
    absences.push_back(r2);
    absences.push_back(r3);



    //Execution of Problem 1, part A
    int x = validAbsenceRequest(r1);
    AbsenceRequest badRequest("Mo", 16, 12, 1);
    int y = validAbsenceRequest(badRequest);

    cout << "Successful Absence Request: " << x << endl;
    cout << "Bad Absence Request: " << y << endl;


    //Execution of Problem 1, part B.
    vector<Duty> theConflicts = conflictingDuties(duties, absences);

    cout << "\nThe following duties have conflicting absence requests: \n" << endl;

    for (int t = 0; t<theConflicts.size(); t++)
    {

        Duty individualDuty = theConflicts.at(t);
        cout << "Day: "<< individualDuty.getDay() << "\nHour: "
         << individualDuty.getHour()

            << "\nDuration: " << individualDuty.getDuration()
            << "\nPhysicanID: " << individualDuty.getPhysician_id() << "\n" << endl;

    }


    return 0;
}

