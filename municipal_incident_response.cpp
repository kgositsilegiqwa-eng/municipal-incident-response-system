#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

//___________________________________________________
//_____________________Constants_____________________

const int NUM_GAUTENG_LOCATIONS = 10;
const int NUM_RESPONSE_TEAMS = 6;
const int NUM_REPORTED_INCIDENTS = 10;
const unsigned int SEED = 12345;


//_________________________________________________
//_____________________Classes_____________________

class GautengLocations{
public:
    int locationID;
    string locationName;
};

class ResponseTeams{
public:
    int teamID;
    string teamResponseCapabilityCategory;
    int teamCurrentLocationID; //team's location base utilising location ID
    string teamCurrentLocationName;
    string teamCurrentStatus;
};

class Incidents{
public:
    int incidentID;
    int incidentLocationID; //incident location utilising locaiton ID
    string incidentLocation;
    string incidentCategory; //Water/Electricity/Roads/Sanitation/Public Facilities
    string incidentSeverityLevel; //Low/Medium/High
    string incidentStatus; //Open, assigned, resolved
    int assignedTeamID;

};

//_________________________________________________
//_____________________Globals_____________________

//Store location objects in a locations array:
GautengLocations gautengLocationsIndex[NUM_GAUTENG_LOCATIONS];

//store response teams in a response teams array:
ResponseTeams responseTeamsIndex[NUM_RESPONSE_TEAMS];

//store generated incidents in an incidents array:
Incidents incidentsIndex[NUM_REPORTED_INCIDENTS];

//store prioritised incidents in an array sorted based on severity level
Incidents prioritisedIncidentsIndex[NUM_REPORTED_INCIDENTS];

//store travel times between connected locations
int travelTimeMatrix[NUM_GAUTENG_LOCATIONS][NUM_GAUTENG_LOCATIONS];

//Store roads between connected locations
string roadMatrix[NUM_GAUTENG_LOCATIONS][NUM_GAUTENG_LOCATIONS];


//___________________________________________________
//_____________________Functions_____________________

//Assign location names to location's ID to the locations index
void initialiseGautengLocations(){

    gautengLocationsIndex[0].locationID = 1;
    gautengLocationsIndex[0].locationName = "Pretoria";

    gautengLocationsIndex[1].locationID = 2;
    gautengLocationsIndex[1].locationName = "Johannesburg";

    gautengLocationsIndex[2].locationID = 3;
    gautengLocationsIndex[2].locationName = "Westonaria";

    gautengLocationsIndex[3].locationID = 4;
    gautengLocationsIndex[3].locationName = "Germiston";

    gautengLocationsIndex[4].locationID = 5;
    gautengLocationsIndex[4].locationName = "Alberton";

    gautengLocationsIndex[5].locationID = 6;
    gautengLocationsIndex[5].locationName = "Vereeniging";

    gautengLocationsIndex[6].locationID = 7;
    gautengLocationsIndex[6].locationName = "Meyerton";

    gautengLocationsIndex[7].locationID = 8;
    gautengLocationsIndex[7].locationName = "Heidelberg";

    gautengLocationsIndex[8].locationID = 9;
    gautengLocationsIndex[8].locationName = "Soweto";

    gautengLocationsIndex[9].locationID = 10;
    gautengLocationsIndex[9].locationName = "Bronkhorstspruit";

}


//Generate response teams
void generateResponseTeams(){

    //Assign unique team IDs
    responseTeamsIndex[0].teamID = 1;
    responseTeamsIndex[1].teamID = 2;
    responseTeamsIndex[2].teamID = 3;
    responseTeamsIndex[3].teamID = 4;
    responseTeamsIndex[4].teamID = 5;
    responseTeamsIndex[5].teamID = 6;

    string responseCapabilityCategories[5] = {"Water", "Electricity", "Roads", "Sanitation", "Public Facilities"};

    string responseTeamStatuses[3] = {"Available", "Assigned", "Unavailable"};

    //for loop that generates random team capabilities and locations, then ensures the first 3 teams are available
    for(int teamIndex = 0; teamIndex < 3; teamIndex++){

        //Randomly assign a starting location ID from 1 to 10
        responseTeamsIndex[teamIndex].teamCurrentLocationID = (rand() % NUM_GAUTENG_LOCATIONS) + 1;

        //Assign location name based on the randomly generated location ID
        responseTeamsIndex[teamIndex].teamCurrentLocationName = gautengLocationsIndex[responseTeamsIndex[teamIndex].teamCurrentLocationID - 1].locationName;

        //Randomly assign a response capability
        responseTeamsIndex[teamIndex].teamResponseCapabilityCategory = responseCapabilityCategories[rand() % 5];

        //assign availability status
        responseTeamsIndex[teamIndex].teamCurrentStatus = "Available";
    }

    //for loop that generates random team capabilities and locations, then assigns random availability status for the remaining 3 teams
    for(int teamIndex = 3; teamIndex < NUM_RESPONSE_TEAMS; teamIndex++){

        //Randomly assign a starting location ID from 1 to 10
        responseTeamsIndex[teamIndex].teamCurrentLocationID = (rand() % NUM_GAUTENG_LOCATIONS) + 1;

         //Assign location name based on the randomly generated location ID
    responseTeamsIndex[teamIndex].teamCurrentLocationName = gautengLocationsIndex[responseTeamsIndex[teamIndex].teamCurrentLocationID - 1].locationName;

        //Randomly assign a response capability
        responseTeamsIndex[teamIndex].teamResponseCapabilityCategory = responseCapabilityCategories[rand() % 5];

        //Assign randomised team status
        responseTeamsIndex[teamIndex].teamCurrentStatus = responseTeamStatuses[rand() % 3];
    }

}


//generate randomised incidents
void generateIncidents(){

    incidentsIndex[0].incidentID = 1;
    incidentsIndex[1].incidentID = 2;
    incidentsIndex[2].incidentID = 3;
    incidentsIndex[3].incidentID = 4;
    incidentsIndex[4].incidentID = 5;
    incidentsIndex[5].incidentID = 6;
    incidentsIndex[6].incidentID = 7;
    incidentsIndex[7].incidentID = 8;
    incidentsIndex[8].incidentID = 9;
    incidentsIndex[9].incidentID = 10;

    string incidentCategories[5] = {"Water", "Electricity", "Roads", "Sanitation", "Public Facilities"};

    string incidentSeverityLevels[3] = {"Low", "Medium", "High"};

    //for loop to assign randomised incident categories and severity levels to incidents
    for(int incidentIndex = 0; incidentIndex < NUM_REPORTED_INCIDENTS; incidentIndex++){

        //Assign a location ID to the incident
        incidentsIndex[incidentIndex].incidentLocationID = (rand() % NUM_GAUTENG_LOCATIONS) + 1;

        //Assign location name to the incident
        incidentsIndex[incidentIndex].incidentLocation = gautengLocationsIndex[incidentsIndex[incidentIndex].incidentLocationID - 1].locationName;

        //assign a cetegory to the incident
        incidentsIndex[incidentIndex].incidentCategory = incidentCategories[rand() % 5];

        //Assign severity level
        incidentsIndex[incidentIndex].incidentSeverityLevel = incidentSeverityLevels[rand() % 3];

        //Assign open status
        incidentsIndex[incidentIndex].incidentStatus = "Open";

        //Assign no response team initially
        incidentsIndex[incidentIndex].assignedTeamID = -1;

    }

}


//Assign travel times between connected locations
void initialiseTravelTimeMatrix(){

    //initially set all matrix travel times to 0 as a default
    for(int row = 0; row < NUM_GAUTENG_LOCATIONS; row++){
        for(int column = 0; column < NUM_GAUTENG_LOCATIONS; column++){
            travelTimeMatrix[row][column] = 0;
        }
    }

    //Pretoria <-> Johannesburg
    travelTimeMatrix[0][1] = 47;
    travelTimeMatrix[1][0] = 47;

    //Pretoria <-> Bronkhorstspruit
    travelTimeMatrix[0][9] = 45;
    travelTimeMatrix[9][0] = 45;

    //Pretoria <-> Germiston
    travelTimeMatrix[0][3] = 50;
    travelTimeMatrix[3][0] = 50;

    //Johannesburg <-> Germiston
    travelTimeMatrix[1][3] = 16;
    travelTimeMatrix[3][1] = 16;

    //Johannesburg <-> Soweto
    travelTimeMatrix[1][8] = 34;
    travelTimeMatrix[8][1] = 34;

    //Johannesburg <-> Alberton
    travelTimeMatrix[1][4] = 26;
    travelTimeMatrix[4][1] = 26;

    //Johannesburg <-> Vereeniging
    travelTimeMatrix[1][5] = 44;
    travelTimeMatrix[5][1] = 44;

    //Germiston <-> Alberton
    travelTimeMatrix[3][4] = 19;
    travelTimeMatrix[4][3] = 19;

    //Westonaria <-> Soweto
    travelTimeMatrix[2][8] = 29;
    travelTimeMatrix[8][2] = 29;

    //Westonaria <-> Vereeniging
    travelTimeMatrix[2][5] = 51;
    travelTimeMatrix[5][2] = 51;

    //Alberton <-> Vereeniging
    travelTimeMatrix[4][5] = 32;
    travelTimeMatrix[5][4] = 32;

    //Alberton <-> Meyerton
    travelTimeMatrix[4][6] = 26;
    travelTimeMatrix[6][4] = 26;

    //Vereeniging <-> Meyerton
    travelTimeMatrix[5][6] = 15;
    travelTimeMatrix[6][5] = 15;

    //Meyerton <-> Heidelberg
    travelTimeMatrix[6][7] = 33;
    travelTimeMatrix[7][6] = 33;

    //Alberton <-> Heidelberg
    travelTimeMatrix[4][7] = 40;
    travelTimeMatrix[7][4] = 40;

    //Heidelberg <-> Germiston
    travelTimeMatrix[7][3] = 40;
    travelTimeMatrix[3][7] = 40;
}


//Assign roads between connected locations
void initialiseRoadMatrix(){

    //initially set all matrix road names to an empty string as defaults
    for(int row = 0; row < NUM_GAUTENG_LOCATIONS; row++){
        for(int column = 0; column < NUM_GAUTENG_LOCATIONS; column++){
            roadMatrix[row][column] = "";
        }
    }

    //Pretoria <-> Johannesburg
    roadMatrix[0][1] = "N1";
    roadMatrix[1][0] = "N1";

    //Pretoria <-> Bronkhorstspruit
    roadMatrix[0][9] = "N4";
    roadMatrix[9][0] = "N4";

    //Pretoria <-> Germiston
    roadMatrix[0][3] = "N1/N3/M2";
    roadMatrix[3][0] = "N1/N3/M2";

    //Johannesburg <-> Germiston
    roadMatrix[1][3] = "M2";
    roadMatrix[3][1] = "M2";

    //Johannesburg <-> Soweto
    roadMatrix[1][8] = "N1/M70";
    roadMatrix[8][1] = "N1/M70";

    //Johannesburg <-> Alberton
    roadMatrix[1][4] = "M2/N12";
    roadMatrix[4][1] = "M2/N12";

    //Johannesburg <-> Vereeniging
    roadMatrix[1][5] = "R59/R82";
    roadMatrix[5][1] = "R59/R82";

    //Germiston <-> Alberton
    roadMatrix[3][4] = "M2/N3";
    roadMatrix[4][3] = "M2/N3";

    //Westonaria <-> Soweto
    roadMatrix[2][8] = "R28";
    roadMatrix[8][2] = "R28";

    //Westonaria <-> Vereeniging
    roadMatrix[2][5] = "R28/R82";
    roadMatrix[5][2] = "R28/R82";

    //Alberton <-> Vereeniging
    roadMatrix[4][5] = "R59";
    roadMatrix[5][4] = "R59";

    //Alberton <-> Meyerton
    roadMatrix[4][6] = "R59/M61";
    roadMatrix[6][4] = "R59/M61";

    //Vereeniging <-> Meyerton
    roadMatrix[5][6] = "R59/R551";
    roadMatrix[6][5] = "R59/R551";

    //Meyerton <-> Heidelberg
    roadMatrix[6][7] = "R42";
    roadMatrix[7][6] = "R42";

    //Alberton <-> Heidelberg
    roadMatrix[4][7] = "R550/R103";
    roadMatrix[7][4] = "R550/R103";

    //Heidelberg <-> Germiston
    roadMatrix[7][3] = "M35/R103";
    roadMatrix[3][7] = "M35/R103";
}

//locations and connecting roads display
void displayLocationsAndRoads(){

    cout << endl;
    cout << "Locations and routes" << endl;
    cout << endl;

    //loop through every location in the locations array
    for(int row = 0; row < NUM_GAUTENG_LOCATIONS; row++){

        //display current location ID and name
        cout << "Location ID: " << gautengLocationsIndex[row].locationID << endl;
        cout << "Location Name: " << gautengLocationsIndex[row].locationName << endl;
        cout << "Direct Routes: " << endl;

        //check travel time matrix for roads connected to current location
        for(int column = 0; column < NUM_GAUTENG_LOCATIONS; column++){

            if(travelTimeMatrix[row][column] > 0){
                cout << " -> " << gautengLocationsIndex[column].locationName << " | Road: " << roadMatrix[row][column] << " | Travel time: " << travelTimeMatrix[row][column] << " minutes |" << endl;

            }
        }

        cout << endl;

    }

}

//display response teams
void displayResponseTeams(){

    cout << "Response Teams" << endl;
    cout << endl;

    //Loop through every response team in the response teams array
    for(int teamIndex = 0; teamIndex < NUM_RESPONSE_TEAMS; teamIndex++){

        cout << "Response Team ID: " << responseTeamsIndex[teamIndex].teamID << endl;
        cout << "Response Team Capability: " << responseTeamsIndex[teamIndex].teamResponseCapabilityCategory << endl;
        cout << "Response Team Current Location: " << responseTeamsIndex[teamIndex].teamCurrentLocationName << endl;
        cout << "Response Team Current Status: " << responseTeamsIndex[teamIndex].teamCurrentStatus << endl;
        cout << endl;
    }


}

void findCapableResponseTeams(int incidentIndex){

    cout << "Capable Response Teams:" << endl;
    cout << endl;

    bool capableTeamFound = false;

    //Loop through every response team
    for(int teamIndex = 0; teamIndex < NUM_RESPONSE_TEAMS; teamIndex++){

        //check team availability
        if(responseTeamsIndex[teamIndex].teamCurrentStatus == "Available"){

            if(responseTeamsIndex[teamIndex].teamResponseCapabilityCategory == incidentsIndex[incidentIndex].incidentCategory){

                cout << "Response Team ID: " << responseTeamsIndex[teamIndex].teamID << endl;

                cout << "Response Team Capability: " << responseTeamsIndex[teamIndex].teamResponseCapabilityCategory << endl;

                cout << "Response Team Current Location: " << responseTeamsIndex[teamIndex].teamCurrentLocationName << endl;

                cout << endl;

                capableTeamFound = true;
            }

        }

    }

    if(!capableTeamFound){
        cout << "No available response teams found for this incident." << endl;
    }

}

int dijkstraShortestRoute(int startingLocationID, int destinationLocationID, bool displayRoute){

    int startingLocationIndex = startingLocationID - 1;
    int destinationLocationIndex = destinationLocationID - 1;

    int shortestDistances[NUM_GAUTENG_LOCATIONS];
    bool visitedLocations[NUM_GAUTENG_LOCATIONS];
    int previousLocation[NUM_GAUTENG_LOCATIONS];

    //Initialise Dijkstra arrays
    for(int locationIndex = 0; locationIndex < NUM_GAUTENG_LOCATIONS; locationIndex++){

    shortestDistances[locationIndex] = 10000;
    visitedLocations[locationIndex] = false;
    previousLocation[locationIndex] = -1;

    }

    //Set starting location's shortest distance to 0
    shortestDistances[startingLocationIndex] = 0;

    //loop through each location to check for shortest distances to the current location
    for(int iteration = 0; iteration < NUM_GAUTENG_LOCATIONS; iteration++){

        int currentLocationIndex = -1;//-1 for no location selected
        int shortestDistance = 10000;

        //Check each location to find the unvisited location with the shortest distance
        for(int locationIndex = 0; locationIndex < NUM_GAUTENG_LOCATIONS; locationIndex++){

            //identify unvisited location with shortest distance and set as shortest distance current location if true
            if(!visitedLocations[locationIndex] && shortestDistances[locationIndex] < shortestDistance){

                currentLocationIndex = locationIndex;
                shortestDistance = shortestDistances[locationIndex];
            }

        }

        //check if there are no more reachable, unvisited locations and stops loop if true
        if(currentLocationIndex == -1){
        break;
        }

        //Mark current location as visited
        visitedLocations[currentLocationIndex] = true;

        //Check all locations connected to the current location
        for(int neighbourIndex = 0; neighbourIndex < NUM_GAUTENG_LOCATIONS; neighbourIndex++){

            if(travelTimeMatrix[currentLocationIndex][neighbourIndex] > 0){

                //calc total distance travelled to this point
                int newDistance = shortestDistances[currentLocationIndex] + travelTimeMatrix[currentLocationIndex][neighbourIndex];

                //checks true if new route is shorter than current route
                if(newDistance < shortestDistances[neighbourIndex]){

                    //Update the shortest distance to the neighbouring location
                    shortestDistances[neighbourIndex] = newDistance;

                    //Store the current location as the previous location on the shortest route
                    previousLocation[neighbourIndex] = currentLocationIndex;

                }

            }

        }

    }

    //display shortest route if true:
    if(displayRoute){

        //Display the shortest travel time to the destination
        cout << endl;
        cout << "Shortest Travel Time: " << shortestDistances[destinationLocationIndex] << " minutes" << endl;

        //Store the locations that form the shortest route
        int shortestRoute[NUM_GAUTENG_LOCATIONS];
        int routeLength = 0;


        //Trace the shortest route backwards from the destination
        int currentRouteLocation = destinationLocationIndex;

        while(currentRouteLocation != -1){

            shortestRoute[routeLength] = currentRouteLocation;
            routeLength++;
            currentRouteLocation = previousLocation[currentRouteLocation];

        }

        //Display the shortest route from the starting location to the destination
        cout << "Shortest Route: ";

        for(int routeIndex = routeLength - 1; routeIndex >= 0; routeIndex--){

            cout << gautengLocationsIndex[shortestRoute[routeIndex]].locationName;

            if(routeIndex > 0){
            cout << " -> ";
            }

        }

        cout << endl;
    }

    return shortestDistances[destinationLocationIndex]; //Give the calculated shortest travel time back to whatever function called dijkstraShortestRoute
}


int capableResponseTeamSelection(int incidentIndex){

    int selectedTeamIndex = -100;
    int shortestTravelTime = 10000;


    //loop through every response team
    for(int teamIndex = 0; teamIndex < NUM_RESPONSE_TEAMS; teamIndex++){

        //availability confirmation
        if(responseTeamsIndex[teamIndex].teamCurrentStatus == "Available"){

            //capability confirmation
            if(responseTeamsIndex[teamIndex].teamResponseCapabilityCategory == incidentsIndex[incidentIndex].incidentCategory){

                //Calculate the shortest travel time between the team's location and the incident location
                int travelTime = dijkstraShortestRoute(responseTeamsIndex[teamIndex].teamCurrentLocationID, incidentsIndex[incidentIndex].incidentLocationID, false);

                //Check whether current iteration's team's travel time is shorter than the current shortest travel time
                if(travelTime < shortestTravelTime){

                    //Store team as the currently selected team
                    selectedTeamIndex = teamIndex;

                    //Store team's travel time as the current shortest travel time
                    shortestTravelTime = travelTime;

                }

            }

        }


    }

    //if a suitable response team was found
    if(selectedTeamIndex != -100){

        cout << "Selected Response Team:" << endl;
        cout << endl;
        cout << "Response Team ID: " << responseTeamsIndex[selectedTeamIndex].teamID << endl;
        cout << "Response Team Capability: " << responseTeamsIndex[selectedTeamIndex].teamResponseCapabilityCategory << endl;
        cout << "Response Team Current Location: " << responseTeamsIndex[selectedTeamIndex].teamCurrentLocationName << endl;
        cout << "Travel Time to Incident: " << shortestTravelTime << " minutes" << endl;

    }

    else{
    cout << "No available response team found at the moment." << endl;
    }

    return selectedTeamIndex;

}


//display incidents in order of occurrence
void displayIncidents(){

    cout << "Reported Incidents:" << endl;
    cout << endl;

    //Loop through each incident in the incidents array
    for(int incidentIndex = 0; incidentIndex < NUM_REPORTED_INCIDENTS; incidentIndex++){

        cout << "Incident ID: " << incidentsIndex[incidentIndex].incidentID << endl;
        cout << "Location ID: " << incidentsIndex[incidentIndex].incidentLocationID << endl;
        cout << "Location: " << incidentsIndex[incidentIndex].incidentLocation << endl;
        cout << "Category: " << incidentsIndex[incidentIndex].incidentCategory << endl;
        cout << "Severity level: " << incidentsIndex[incidentIndex].incidentSeverityLevel << endl;
        cout << "Status: " << incidentsIndex[incidentIndex].incidentStatus << endl;
        cout << endl;

    }

}

//copy the incidents array into a separate array and assign priority levels
void prioritySetIncidents(){

    //Copy incidents into the prioritised incidents array
    for(int incidentIndex = 0; incidentIndex < NUM_REPORTED_INCIDENTS; incidentIndex++){

        prioritisedIncidentsIndex[incidentIndex] = incidentsIndex[incidentIndex];

    }

    //Sort the copied incidents based on severity priority
    for(int incidentIndex = 0; incidentIndex < NUM_REPORTED_INCIDENTS; incidentIndex++){

        int severityPriorityNumber = 0;

        //Assign priority levels for open incidents
        if(prioritisedIncidentsIndex[incidentIndex].incidentStatus == "Open"){

            if(prioritisedIncidentsIndex[incidentIndex].incidentSeverityLevel == "Low"){
                severityPriorityNumber = 1;
            }

             else if(prioritisedIncidentsIndex[incidentIndex].incidentSeverityLevel == "Medium"){
                severityPriorityNumber = 2;
            }

            else if(prioritisedIncidentsIndex[incidentIndex].incidentSeverityLevel == "High"){
                severityPriorityNumber = 3;
            }

        }

        int highestPriorityIndex = incidentIndex;
        int highestSeverityPriorityNumber = severityPriorityNumber;

        //compare severity priority numbers of current incident with subsequent incidents
        for(int compareIndex = incidentIndex + 1; compareIndex < NUM_REPORTED_INCIDENTS; compareIndex++){

            int compareSeverityPriorityNumber = 0; //variable to store the priority number of the incident being compared

            //Assign priority level for the incident being compared
            if(prioritisedIncidentsIndex[compareIndex].incidentStatus == "Open"){

                if(prioritisedIncidentsIndex[compareIndex].incidentSeverityLevel == "Low"){
                    compareSeverityPriorityNumber = 1;
                }

                else if(prioritisedIncidentsIndex[compareIndex].incidentSeverityLevel == "Medium"){
                    compareSeverityPriorityNumber = 2;
                }

                else if(prioritisedIncidentsIndex[compareIndex].incidentSeverityLevel == "High"){
                    compareSeverityPriorityNumber = 3;
                }

                //Check if the compared incident has a higher priority
                if(compareSeverityPriorityNumber > highestSeverityPriorityNumber){

                highestPriorityIndex = compareIndex;
                highestSeverityPriorityNumber = compareSeverityPriorityNumber;

                }


            }


        }

        //check whether a higher-priority incident was found
        if(highestPriorityIndex != incidentIndex){

            //Temporarily store current incident
            Incidents temporaryIncident = prioritisedIncidentsIndex[incidentIndex];

            //Move higher priority incident to current position
            prioritisedIncidentsIndex[incidentIndex] = prioritisedIncidentsIndex[highestPriorityIndex];

            //Move original current incident into previous position of the higher-priority incident
            prioritisedIncidentsIndex[highestPriorityIndex] = temporaryIncident;

        }

    }

}

void updateIncident(){

    int incidentID;

    cout << endl;
    cout << "Enter Incident ID to update: ";
    cin >> incidentID;

    //Loop through every incident to find matching incident ID
    for(int incidentIndex = 0; incidentIndex < NUM_REPORTED_INCIDENTS; incidentIndex++){

        if(incidentsIndex[incidentIndex].incidentID == incidentID){

            cout << endl;
            cout << "Incident ID: " << incidentsIndex[incidentIndex].incidentID << endl;
            cout << "Incident Location: " << incidentsIndex[incidentIndex].incidentLocation << endl;
            cout << "Incident Category: " << incidentsIndex[incidentIndex].incidentCategory << endl;
            cout << "Incident Severity-Level: " << incidentsIndex[incidentIndex].incidentSeverityLevel << endl;
            cout << "Incident Current Status: " << incidentsIndex[incidentIndex].incidentStatus << endl;

            int updateChoice;

            cout << endl;
            cout << "1. Assign Incident" << endl;
            cout << "2. Resolve Incident" << endl;
            cout << "Enter choice: ";
            cin >> updateChoice;

            if(updateChoice == 1){

                //Check whether the incident is still open before assigning a team
                if(incidentsIndex[incidentIndex].incidentStatus == "Open"){

                    //Find the most suitable available response team
                    int selectedTeamIndex = capableResponseTeamSelection(incidentIndex);

                    //Confirm whether a suitable response team was found
                    if(selectedTeamIndex != -100){

                        //Assign the selected response team to the incident
                        incidentsIndex[incidentIndex].incidentStatus = "Assigned";

                        incidentsIndex[incidentIndex].assignedTeamID = responseTeamsIndex[selectedTeamIndex].teamID;

                        //Make the selected response team unavailable
                        responseTeamsIndex[selectedTeamIndex].teamCurrentStatus = "Unavailable";

                        cout << "Team assigned to " << incidentsIndex[incidentIndex].incidentCategory << " incident in " << incidentsIndex[incidentIndex].incidentLocation << "." << endl;

                    }
                }

                else if(incidentsIndex[incidentIndex].incidentStatus == "Resolved"){
                    cout << "Incident has already been resolved." << endl;
                }

                else{
                cout << "Incident is already assigned." << endl;
                }

            }

            else if(updateChoice == 2){

                //Check whether a response team has been assigned to the incident
                if(incidentsIndex[incidentIndex].assignedTeamID != -1){

                    //Change incident status to resolved
                    incidentsIndex[incidentIndex].incidentStatus = "Resolved";

                    //Find the response team assigned to the incident
                    for(int teamIndex = 0; teamIndex < NUM_RESPONSE_TEAMS; teamIndex++){

                        if(responseTeamsIndex[teamIndex].teamID == incidentsIndex[incidentIndex].assignedTeamID){

                            //Make the response team available again
                            responseTeamsIndex[teamIndex].teamCurrentStatus = "Available";

                            break;
                        }

                    }

                    cout << "Team resolved " << incidentsIndex[incidentIndex].incidentCategory << " incident in " << incidentsIndex[incidentIndex].incidentLocation << "." << endl;

                }

                else{
                    cout << "This incident has no response team assigned to it." << endl;
                }

            }

            else{
            cout << "Invalid choice." << endl;
            }

            return;
        }

    }

    cout << "Incident ID not found." << endl;


}

//display prioritised incidents
void displayPrioritisedIncidents(){

    int priorityNumber = 1;

    cout << "Prioritised Incidents" << endl;
    cout << endl;

    //Loop through each incident in the prioritised incidents array
    for(int incidentIndex = 0; incidentIndex < NUM_REPORTED_INCIDENTS; incidentIndex++){

        if(prioritisedIncidentsIndex[incidentIndex].incidentStatus == "Open"){

            cout << "Priority Number :" << priorityNumber << endl;
            cout << "Incident ID: " << prioritisedIncidentsIndex[incidentIndex].incidentID << endl;
            cout << "Location ID: " << prioritisedIncidentsIndex[incidentIndex].incidentLocationID << endl;
            cout << "Location: " << prioritisedIncidentsIndex[incidentIndex].incidentLocation << endl;
            cout << "Category: " << prioritisedIncidentsIndex[incidentIndex].incidentCategory << endl;
            cout << "Severity level: " << prioritisedIncidentsIndex[incidentIndex].incidentSeverityLevel << endl;
            cout << "Status: " << prioritisedIncidentsIndex[incidentIndex].incidentStatus << endl;

            cout << endl;

            priorityNumber++;

        }

    }

}




//_______________________________________________________
//_____________________Main Function_____________________

int main()
{
    //seed call
    srand(SEED);

    //calling functions to initialise locations, travel times and roads
    initialiseGautengLocations();
    initialiseTravelTimeMatrix();
    initialiseRoadMatrix();

    //caling functions to geneate randomised data
    generateResponseTeams();
    generateIncidents();


    int menuChoice;

    do{
        cout << endl;
        cout << "__________________________________________________________________" << endl;
        cout << "________________MUNICIPAL INCIDENT RESPONSE SYSTEM________________" << endl;
        cout << endl;

        cout << "1. Display Locations and Roads" << endl;
        cout << "2. Display Incidents" << endl;
        cout << "3. Prioritise Open Incidents" << endl;
        cout << "4. Display Response Teams" << endl;
        cout << "5. Find Capable Response Teams available for dispatch to an Incident" << endl;
        cout << "6. Find Route" << endl;
        cout << "7. Update Incident" << endl;
        cout << "0. Exit" << endl;
        cout << "__________________________________________________________________" << endl;


        cout << endl;
        cout << "Enter choice: ";
        cin >> menuChoice;

        if(menuChoice == 1){
            displayLocationsAndRoads();
        }

        else if(menuChoice == 2){
            displayIncidents();
        }

        else if(menuChoice == 3){
            prioritySetIncidents();
            displayPrioritisedIncidents();
        }

        else if(menuChoice == 4){
            displayResponseTeams();
        }

        else if(menuChoice == 5){
            int incidentID;
            bool incidentFound = false;

            cout << "Enter Incident ID to investigate: ";
            cin >> incidentID;

            for(int incidentIndex = 0; incidentIndex < NUM_REPORTED_INCIDENTS; incidentIndex++){

                if(incidentsIndex[incidentIndex].incidentID == incidentID){
                    findCapableResponseTeams(incidentIndex);

                    incidentFound = true;

                    break;
                }
            }
            if(!incidentFound){
                cout << "Incident ID not found." << endl;
            }
        }

        else if(menuChoice == 6){

            int startingLocationID;
            int destinationLocationID;

            cout << "Enter Starting Location ID: ";
            cin >> startingLocationID;

            cout << "Enter Destination Location ID: ";
            cin >> destinationLocationID;

            //Check whether both location IDs are valid
            if(startingLocationID >= 1 && startingLocationID <= NUM_GAUTENG_LOCATIONS && destinationLocationID >= 1 && destinationLocationID <= NUM_GAUTENG_LOCATIONS){

                dijkstraShortestRoute(startingLocationID, destinationLocationID, true);
            }

            else{
                cout << "Invalid location ID. Please enter a location ID between 1-10." << endl;
            }
        }

        else if(menuChoice == 7){
            updateIncident();
        }

        else if(menuChoice != 0){
            cout << "Invalid Entry, please select an option between 1-7, or 0 to exit. " << endl;
        }


    }while(menuChoice != 0);

    return 0;
}
