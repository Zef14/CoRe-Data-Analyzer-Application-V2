// Displays observation individually by searching its ID.
void displayObservation(vector<dataPull>& pDataStore)
{
	int search,first = 0,last = (pDataStore.size() - 1),middle;
  bool cont = false,found = false,noData = false;
  do
  {
    cout << "\nDISPLAYING AN OBSERVATION" << endl;
    cout << "--------------------------------------------------" << endl;
    // If no data is available, show message.
    if (pDataStore.empty())
    {
      cout << "No data available. Please add data to file." << endl;
      cout << "--------------------------------------------------" << endl;
      noData = true;
      break;
    }
    cout << "Enter observation ID: ";
    cin >> search;
    cont = true;
    if (!cin) // If a non-integer input is detected, display error.
    {
      cout << "Please input a number." << endl;
      cin.clear();
      cin.ignore();
      cont = false;
    }
  } while (!cont); // If input is integer, continue function.

  sort(pDataStore.begin(),pDataStore.end()); // Sort the vector

  while(first <= last && !found) // While search is not the same as ID, keep searching.
  {
    middle = (first+last)/2; // calculate mid point
    // If searched ID is less than 1, show message.
    if (search < 1)
    {
      cout << "--------------------------------------------------" << endl;
      cout << "Invalid ID. Please enter a number higher than 0." << endl;
      cout << "--------------------------------------------------" << endl;
      break;
    }

    if (search == pDataStore[middle].id) // If ID is found, display on screen.
    {
      found = true;
      // Display results.
      cout << "--------------------------------------------------" << endl;
      cout << "ID" << setw(12) << right << ": " << pDataStore[middle].id << endl;
      cout << "STATE" << setw(9) << right << ": " << pDataStore[middle].state << endl;
      cout << "COUNTY" << setw(8) << right << ": " << pDataStore[middle].county << endl;
      cout << "TOTAL VOTES" << setw(3) << right << ": " << pDataStore[middle].totalVotes << endl;
      cout << "DEM VOTES" << setw(5) << right << ": " << pDataStore[middle].demVotes << endl;
      cout << "REP VOTES" << setw(5) << right << ": " << pDataStore[middle].repVotes << endl;
      cout << "DEM SHARE" << setw(5) << right << ": " << pDataStore[middle].demShare << endl;
      cout << "--------------------------------------------------" << endl;
      break;
    } 

    // If search is higher/lower than ID, adjust last/first pointer accordingly
    else if(pDataStore[middle].id > search)
      last = middle -1;

    else
      first = middle + 1;
  }
  // If end of vector is reached and no ID is found, show message.
  if (!found && !noData)
  {
    cout << "--------------------------------------------------" << endl;
    cout << "Could not find an observation with that ID." << endl;
    cout << "--------------------------------------------------" << endl;
  }
  cin.ignore();
	pressEnter();
}

// Displays observations of the same state searched.
void findState(vector<dataPull>& pFindData)
{
	string search;
	bool invCheck = false,noData = false; // Used to validate whether states were found.
	int charCount = 0; // Used to validate STATE letter number.

  cout << "\nDISPLAYING AN OBSERVATION BY STATE" << endl;
  cout << "--------------------------------------------------" << endl;
  do // If there's more than 2 characters and/or any number, reset.
  {
    // If no data is available, show message.
    if (pFindData.empty())
    {
      cout << "No data available. Please add data to file." << endl;
      noData = true;
      break;
    }
    cout << "Enter STATE name: ";
    cin >> search;
    
    // Count the number of characters.
    for (int i = 0; search[i]; i++)
      charCount++;

    // If number of characters exceeds 2, reset counter.
    if (charCount != 2 || any_of(begin(search), end(search), ::isdigit))
    {
      cout << "Please enter only 2 letters for state name." << endl;
      charCount = 0;
    }
      
  }while (any_of(begin(search), end(search), ::isdigit) || charCount != 2);

  if(!noData)
  {
    cout << "\nID   | STATE | COUNTY         |TOTAL VOTES |DEM VOTES |REP VOTES |DEM SHARE\n";
    cout << "----- ------ ----------------- ----------- ---------- ---------- ----------\n";
  }

  // Search every vector element
  for(int i = 0;i < pFindData.size();i++)
  {
    if (search == pFindData[i].state)
    {
      // Print out string on a data sheet format.
      invCheck = true;
      cout << setw(6) << left << pFindData[i].id;
      cout << setw(8) << left << pFindData[i].state;
      cout << setw(22) << left << pFindData[i].county;
      cout << setw(10) << left << pFindData[i].totalVotes;
      cout << setw(11) << left << pFindData[i].demVotes;
      cout << setw(11) << left << pFindData[i].repVotes;
      cout << left << pFindData[i].demShare << endl;
    }
  }
  
  // If end of file is reached and a state is not found, the state does not exist.
  if (!invCheck && !noData)
    cout << "Could not find an observation from that state." << endl;
  cout << "---------------------------------------------------------------------------\n";
  cin.ignore();
	pressEnter();
}

// Finds data by searching for county name.
void findCounty(vector<dataPull>& pFindData)
{
	string search;
  string stringAdd = " County";
	bool invCheck = false,noData = false; // Used to validate whether counties were found.

  cout << "\nDISPLAYING AN OBSERVATION BY COUNTY" << endl;
  cout << "--------------------------------------------------" << endl;
  // If no data is available, show message.
  if (pFindData.empty())
  {
    cout << "No data available. Please add data to file." << endl;
    cin.ignore();
    noData = true;
  }
  if(!noData)
  {
    cout << "Enter COUNTY name: ";
    cin.ignore();
    getline(cin, search); // Adds spaces to string.

    // If substring "County" is not found, add to string.
    if (search.find(stringAdd) == std::string::npos) 
      {
        search = search + " County";
      }

    cout << "\nID   | STATE | COUNTY         |TOTAL VOTES |DEM VOTES |REP VOTES |DEM SHARE\n";
    cout << "----- ------ ----------------- ----------- ---------- ---------- ----------\n";

    // Search every vector element
    for(int i = 0;i < pFindData.size();i++)
    {
      if (search == pFindData[i].county)
      {
        // Print out string on a data sheet format.
        invCheck = true;
        cout << setw(6) << left << pFindData[i].id;
        cout << setw(8) << left << pFindData[i].state;
        cout << setw(22) << left << pFindData[i].county;
        cout << setw(10) << left << pFindData[i].totalVotes;
        cout << setw(11) << left << pFindData[i].demVotes;
        cout << setw(11) << left << pFindData[i].repVotes;
        cout << left << pFindData[i].demShare << endl;
      }
    }
  }
  // If end of vector is reached and a state is not found, the state does not exist.
  if (!invCheck && !noData)
    cout << "Could not find an observation with that county." << endl;
  cout << "---------------------------------------------------------------------------\n";
	pressEnter();
}