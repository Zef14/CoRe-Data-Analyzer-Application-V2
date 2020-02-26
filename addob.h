// Adds observation into the vector.
void addObservation(vector <dataPull>& pDataStore)
{
	dataPull reader; // Holds string values temporarily.
  bool invID = false; // Checks for invalid ID.
  int charCount = 0; // For counting characters in STATE name.
  string stringAdd = " County";

  cout << "\nADDING AN OBSERVATION" << endl;
  cout << "--------------------------------------------------" << endl;
  do
  {
    // Ask for new ID
    cin.clear();
    cin.ignore();
    cout << "Enter ID" << setw(12) << right << ": ";
    cin >> reader.id;
    invID = false;
    // Check whether reader.id contains a letter.
    if (!reader.id)
    {
      cout << "Please input a number." << endl;
      invID = true;
    }
    // Check whether ID exists.
    for(int i = 0;i < pDataStore.size();i++)
    {
      if (reader.id == pDataStore[i].id) // If ID exists, ask again.
      {
        cout << "\nID already exists." << endl;
        invID = true;
        break;
      }
    }
  }while(invID);

  // Ask for state name.
  cout << "Enter STATE" << setw(9) << right << ": ";
  cin >> reader.state;
  // Count the number of characters.
  for (int i = 0; reader.state[i]; i++)
    charCount++;
  // If there's more than 2 characters and/or any number, reset.
  while (any_of(begin(reader.state), end(reader.state), ::isdigit)
         || charCount != 2)
  {
    cout << "Please enter only 2 letters for state name." << endl;
    cout << "Enter STATE" << setw(9) << right << ": ";
    cin >> reader.state;
    // Count the number of characters.
    for (int i = 0; reader.state[i]; i++)
      charCount++;
    // If number of characters exceeds 2, reset counter.
    if (charCount != 2)
      charCount = 0;
  }

  // Ask for county name.
  cout << "Enter COUNTY" << setw(8) << right << ": ";
  cin.ignore();
  getline(cin, reader.county);

  // If string does not contain "County", add substring.
  if (reader.county.find(stringAdd) == std::string::npos) 
      {
        reader.county = reader.county + " County";
      }

  // Ask for total votes.
  cout << "Enter TOTAL VOTES" << setw(3) << right << ": ";
  cin >> reader.totalVotes;
  // Check whether reader.totalvotes contains a letter.
  while (!reader.totalVotes)
  {
    cin.clear();
    cin.ignore();
    cout << "Please enter a number." << endl;
    cout << "Enter TOTAL VOTES" << setw(3) << right << ": ";
    cin >> reader.totalVotes;
  }

  // Ask for democratic votes.
  cout << "Enter DEM VOTES" << setw(5) << right << ": ";
  cin >> reader.demVotes;
  // Check whether reader.demVotes contains a letter.
  while (!reader.demVotes)
  {
    cin.clear();
    cin.ignore();
    cout << "Please enter a number." << endl;
    cout << "Enter DEM VOTES" << setw(5) << right << ": ";
    cin >> reader.demVotes;
    cin.ignore('\n');
  }

  // Ask for republican votes.
  cout << "Enter REP VOTES" << setw(5) << right << ": ";
  cin >> reader.repVotes;
  // Check whether reader.repVotes contains a letter.
  while (!reader.repVotes)
  {
    cin.clear();
    cin.ignore();
    cout << "Please enter a number." << endl;
    cout << "Enter REP VOTES" << setw(12) << right << ": ";
    cin >> reader.repVotes;
  }

  // Ask for democratic share.
  cout << "Enter DEM SHARE" << setw(5) << right << ": ";
  cin >> reader.demShare;
  // Check whether reader.demShare contains a letter.
  while (!reader.demShare)
  {
    cin.clear();
    cin.ignore();
    cout << "Please enter a number." << endl;
    cout << "Enter DEM SHARE" << setw(12) << right << ": ";
    cin >> reader.demShare;
  }
  pDataStore.push_back(reader); // Stores information in vector.
  sort(pDataStore.begin(),pDataStore.end()); // Sort the vector
  cout << "--------------------------------------------------" << endl;
  cout << reader.county << " added successfully." << endl;
  cout << "--------------------------------------------------" << endl;
  cin.ignore();
	pressEnter();
}