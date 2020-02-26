// Deletes an observation by searching its ID.
void deleteObservation(vector<dataPull>& pLoadData)
{
	dataPull writer;
	int writeChk = 0, searchid;
	bool success = false, confirm = false;
	char choice;

	// Asks for line ID so that getline deletes its matching line.
	cout << "\nDELETING AN OBSERVATION" << endl;
	cout << "--------------------------------------------------" << endl;
	do
	{
		cout << "Enter observation ID: ";
		cin >> searchid;
    
    // If a non-integer input is detected, display error.
		if (!searchid) 
		{
			cout << "Please input a number." << endl;
			cin.clear();
			cin.ignore();
		}
	} while (!searchid);

	// Search for ID on vector
	for (int i = 0;i < pLoadData.size();i++)
	{
		// If ID is the same as the searched ID, ask user if they want to delete. 
		if (searchid == pLoadData[i].id)
		{
			cout << "\nID   | STATE | COUNTY         |TOTAL VOTES |DEM VOTES |REP VOTES |DEM SHARE\n";
			cout << "----- ------ ----------------- ----------- ---------- ---------- ----------\n";
			cout << setw(6) << left << pLoadData[i].id;
			cout << setw(8) << left << pLoadData[i].state;
			cout << setw(22) << left << pLoadData[i].county;
			cout << setw(10) << left << pLoadData[i].totalVotes;
			cout << setw(11) << left << pLoadData[i].demVotes;
			cout << setw(11) << left << pLoadData[i].repVotes;
			cout << left << pLoadData[i].demShare << endl;
			cout << "------------------------------------------------------------------------\n";
			success = true; // Confirms ID is found.

			// Asks if user wants to delete ID.
			cout << "Are you sure you want to delete this observation?(Y/N): ";
			cin >> choice;
			if (choice == 'Y' || choice == 'y')
			{
        pLoadData.erase(pLoadData.begin() + i);
				cout << "Observation deleted successfully." << endl;
			}
			else // If user cancels, write back the whole file as it was.
			{
				cout << "Action cancelled." << endl;
			}
    } 
	}
	// If ID is not found, end the function.
	if (success != true)
		cout << "Could not find observation with that ID." << endl;
  cin.ignore();
	pressEnter();
}