// Saves data from temp file into a new file.
void saveObservation(ofstream& saveFile,vector<dataPull>& pDataStore)
{
	string fileName; // For naming file

	// Ask to name save file.
	cout << "\nSAVING OBSERVATIONS TO FILE" << endl;
	cout << "--------------------------------------------------" << endl;
	cout << "Please name your observation: ";
	cin >> fileName;

	// If written file name is reserved, ask again.
	while (fileName == "swingStatesDF.csv")
	{
		cout << "Cannot use that name. Please input a different name: " << endl;
		cin >> fileName;
	}
	cout << "--------------------------------------------------" << endl;

	saveFile.open(fileName.c_str()); // Open save file and write header line.
  saveFile << "id,state,county,total_votes,dem_votes,rep_votes,dem_share" << endl;
	for(int i = 0;i < pDataStore.size();i++) // While end of vector is not reached
	{
		saveFile << pDataStore[i].id << ",";
    saveFile << pDataStore[i].state << ",";
    saveFile << pDataStore[i].county << ",";
    saveFile << pDataStore[i].totalVotes << ",";
    saveFile << pDataStore[i].demVotes << ",";
    saveFile << pDataStore[i].repVotes << ",";
    saveFile << pDataStore[i].demShare << endl;
	}
  saveFile.close();
	cout << "Save successful." << endl;
  cin.ignore();
	pressEnter();
}

// Loads data from existing file into temp file.
void loadObservation(int& counter,ifstream& loadFile,vector<dataPull>& pDataStore)
{
	int loopBreak = 0;
  dataPull loadData;
  string skipLine,fileName;

	cout << "\nLOADING AN OBSERVATION" << endl;
	cout << "--------------------------------------------------" << endl;
	cout << "Enter observation to load: "; // Ask for filename to load.
  cin.clear();
	cin >> fileName;
	cout << "--------------------------------------------------" << endl;

	loadFile.open(fileName.c_str()); // Opens named file.
  
  if (loadFile.fail()) // If file does not exist, display error.
    cout << "Could not find file with that name." << endl;

  else
  {
    pDataStore.clear();
    getline(loadFile, skipLine); // Skip the first line
    counter = 0; // Reset counter to 0.
    while (!loadFile.eof()) // Count the number of lines in the file.
    {
      getline(loadFile, skipLine);
      counter++;
    }
    counter--; // Ignore last, empty line.
    loadFile.close();
    loadFile.open(fileName.c_str()); // Refresh the file
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
      pDataStore.push_back(loadData);   // Store struct to vector
      loopBreak++;
    }
    cout << "Load successful." << endl;
    loadFile.close();
  }
  cin.ignore();
	pressEnter();
}