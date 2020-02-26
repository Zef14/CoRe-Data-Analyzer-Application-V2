// Loads the data from the file and displays up to 100 of them.
void displayData(vector<dataPull>& pLoadData)
{
	int choice;
  // Option for observation display limit.
  cout << "Select number of observations to show:" << endl;
  cout << "1. 50\n2. 100\n3. 150\n4. Show all" << endl;
  cin >> choice;
  switch (choice)
  {
    case 1: // Display first 50 results.
      choice = 50;
      break;
    case 2: // Display first 100 results.
      choice = 100;
      break;
    case 3: // Display first 150 results.
      choice = 150;
      break;
    case 4: // Display all observations.
      choice = pLoadData.size();
      break;
  }

  cout << "\nID   | STATE | COUNTY         |TOTAL VOTES |DEM VOTES |REP VOTES |DEM SHARE\n";
  cout << "----- ------ ----------------- ----------- ---------- ---------- ----------\n";

  // If no data is available, show message.
  if (pLoadData.empty())
    cout << "No data available. Please add data to file." << endl;
  else
  {
    for(int i = 0;i < choice;i++) // Iterate based on choice
    {
      if(i == pLoadData.size()) // If vector reached its end, end the loop.
        break;
      
      cout << setw(6) << left << pLoadData[i].id;
      cout << setw(8) << left << pLoadData[i].state;
      cout << setw(22) << left << pLoadData[i].county;
      cout << setw(10) << left << pLoadData[i].totalVotes;
      cout << setw(11) << left << pLoadData[i].demVotes;
      cout << setw(11) << left << pLoadData[i].repVotes;
      cout << left << pLoadData[i].demShare << endl;
    }
  }
  cout << "---------------------------------------------------------------------------\n";
  cin.ignore();
	pressEnter();
}