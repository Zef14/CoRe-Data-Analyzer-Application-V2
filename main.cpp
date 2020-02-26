// CoRe Data Analyzer final project for basic programming.
// This analyzer allows for managing observations in a simulated Data Frame.
// Author: Kelvin Torres
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <vector>
using namespace std;

struct dataPull // Global structure variable for data extraction.
{
	int id;         // Unique ID
	string state;   // State
	string county;  // County
	int totalVotes; // Total votes
	int demVotes;   // Democratic votes
	int repVotes;   // Republican votes
	float demShare; // Democratic share

  // Overload struct with '<' operator for sorting purposes.
  bool operator < (const dataPull & order) const
    {
      return (id < order.id);
    }
};

// Prototypes go here.
void displayData(vector<dataPull>& pLoadData);
void displayObservation(vector<dataPull>&);
void addObservation(vector<dataPull>&);
void deleteObservation(vector<dataPull>&);
void findCounty(vector<dataPull>&);
void findState(vector<dataPull>&);
void loadObservation(int&,ifstream&,vector<dataPull>&);
void saveObservation(ofstream&,vector<dataPull>&);
void histogram(vector<dataPull>&);
void centralTendency(vector<dataPull>&);
void pressEnter();

// Function files go here.
#include "displaydata.h"  // Option 1
#include "obfinder.h"     // Options 2,5,6
#include "addob.h"        // Option 3
#include "delob.h"        // Option 4
#include "savloadob.h"    // Options 7,8
#include "calculateob.h"  // Options 9,10

// Perform startup commands and show main menu.
int main()
{
  dataPull loadData;
	int choice;
	int counter = 0,loopBreak = 0;
	char sample; // For loading sample file at the beginning of the program.
	string skipLine;
	ifstream loadFile;
  ofstream saveFile;
	bool done = false, loadPrompt = false, fileRefresh = false;
  vector <dataPull> dataStore; // Vector that holds all the values in a file
  dataStore.begin();

	cout << "Do you wish to load a sample file?(Y/N): ";
	cin >> sample;

	if (sample == 'y' || sample == 'Y')
	{
		// Load sample file. Only happens once after starting the program.
		loadFile.open("swingStatesDF.csv");
    getline(loadFile, skipLine); // Skip the first line
		while (!loadFile.eof()) // Count the number of lines in the file.
		{
			getline(loadFile, skipLine);
      counter++;
		}
    loadFile.close();
    loadFile.open("swingStatesDF.csv"); // Refresh the file
    getline(loadFile, skipLine); // Skip the first line

    while (loopBreak != counter) // Store all data on vector
    {
      getline(loadFile, skipLine, ','); // Pull ID from file
      loadData.id = stoi(skipLine);
      getline(loadFile, skipLine, ','); // Pull STATE from file
      loadData.state = skipLine;
      getline(loadFile, skipLine, ','); // Pull COUNTY from file
      loadData.county = skipLine;
      getline(loadFile, skipLine, ','); // Pull TOTAL VOTES from file
      loadData.totalVotes = stoi(skipLine);
      getline(loadFile, skipLine, ','); // Pull DEM VOTES from file
      loadData.demVotes = stoi(skipLine);
      getline(loadFile, skipLine, ','); // Pull REP VOTES from file
      loadData.repVotes = stoi(skipLine);
      getline(loadFile, skipLine);      // Pull DEM SHARE from file
      loadData.demShare = stof(skipLine);
      dataStore.push_back(loadData);    // Store struct to vector
      loopBreak++;
    }
    loadFile.close();
		cout << "Sample file loaded." << endl;
	}
  
	// Main menu
	while (!done)
	{
    cout << "\n\nCoRe Data Analyzer APPLICATION" << endl;
    cout << "------------------------------" << endl;
    cout << "1.  Display Data Frame" << endl;
    cout << "2.  Display an observation" << endl;
    cout << "3.  Add an observation" << endl;
    cout << "4.  Delete an observation" << endl;
    cout << "5.  Find observation by state" << endl;
    cout << "6.  Find observation by county" << endl;
    cout << "7.  Save observation to file" << endl;
    cout << "8.  Load observation from file" << endl;
    cout << "9.  Create Histogram" << endl;
    cout << "10. Calculate Measures of Central Tendency" << endl;
    cout << "11. Exit application" << endl;
    cout << "-------------------------------" << endl;
    cout << "Enter option number: ";
    cin >> choice;

    switch (choice)
    {
      case 1: // Displays the loaded data frame.
        displayData(dataStore);
        break;
      case 2: // Displays observation by performing a binary search for data ID.
        displayObservation(dataStore);
        break;
      case 3: // Adds an observation to current loaded file.
        addObservation(dataStore);
        break;
      case 4: // Removes an observation by searching its ID.
        deleteObservation(dataStore);
        break;
      case 5: // Displays observation by searching state name.
        findState(dataStore);
        break;
      case 6: // Displays observation by searching county name.
        findCounty(dataStore);
        break;
      case 7: // Saves observation to a new file.
        saveObservation(saveFile, dataStore);
        break;
      case 8: // Asks for file name and loads into temp file.
        loadObservation(counter, loadFile, dataStore);
        break;
      case 9: // Creates histogram based on democratic share.
        histogram(dataStore);
        break;
      case 10: // Calculates mean, median and mode of a chosen column.
        centralTendency(dataStore);
        break;
      case 11: // Terminates the program.
        cout << "PROGRAM TERMINATED" << endl;
        done = true;
        break;
      default: // If option is invalid, ask again.
        cout << "\nInvalid option." << endl;
        if (!cin) // If a non-integer input is detected, display error.
        {
          cout << "Please input a number." << endl;
          cin.clear();
          cin.ignore();
        }
        loadFile.close();
        break;
    }
	}
	return 0;
}