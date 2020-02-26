// Calculates mean, median and mode of a whole column.
void centralTendency(vector<dataPull>& pDataStore)
{
	int sum = 0, loopBreak = 1, choice,i = 1;
	float median, mean, sum2 = 0,fmode;
	string columnName, line,mode = "N/A",conf;
	bool finish = false;
  int medianCount = pDataStore.size();

  vector<int> mednumbers(pDataStore.size()); // Vector to hold MEDIAN values.
  vector<float> medfnumbers(pDataStore.size()); // Vector to hold float MEDIAN values.
  vector<string> numbers(pDataStore.size()); // For MODE calculation

	while (!finish)
	{
		cout << "\nMEASURES OF CENTRAL TENDENCY BY COLUMN" << endl;
		cout << "--------------------------------------------------" << endl;

    // If no data is available, show message.
		if (pDataStore.empty())
		{
			cout << "No data available. Please add data to file." << endl;
      cout << "--------------------------------------------------" << endl;
      cin.ignore();
			break;
		}

		cout << "Enter column name: ";
		cin.ignore();
		getline(cin, columnName);
		cout << "--------------------------------------------------" << endl;

		// Assign 1 for dem votes
		if (columnName == "DEM VOTES" || columnName == "Dem Votes" ||
			columnName == "dem votes") choice = 1;

		// Assign 2 for rep votes
		else if (columnName == "REP VOTES" || columnName == "Rep Votes"
			|| columnName == "rep votes") choice = 2;

		// Assign 3 for total votes
		else if (columnName == "TOTAL VOTES" || columnName == "Total Votes"
			|| columnName == "total votes") choice = 3;

		// Assign 4 for dem share
		else if (columnName == "DEM SHARE" || columnName == "Dem Share"
			|| columnName == "dem share") choice = 4;

		else // If column name is invalid, end the function.
		{
			cout << "Column name invalid." << endl;
			break;
		}

    switch(choice)
    { 
      case 1:
        for (int j = 0;j < pDataStore.size();j++)
          {
            numbers[j] = to_string(pDataStore[j].demVotes); // For MODE calculation
            sum += pDataStore[j].demVotes;                  // For MEAN calculation
            mednumbers[j] = pDataStore[j].demVotes;         // For MEDIAN calculation
          }
        break;
      case 2:
        for (int j = 0;j < pDataStore.size();j++)
          {
            numbers[j] = to_string(pDataStore[j].repVotes); // For MODE calculation
            sum += pDataStore[j].repVotes;                  // For MEAN calculation
            mednumbers[j] = pDataStore[j].repVotes;         // For MEDIAN calculation
          }
        break;
      case 3:
        for (int j = 0;j < pDataStore.size();j++)
          {
            numbers[j] = to_string(pDataStore[j].totalVotes); // For MODE calculation
            sum += pDataStore[j].totalVotes;                  // For MEAN calculation
            mednumbers[j] = pDataStore[j].totalVotes;         // For MEDIAN calculation
          }
        break;
      case 4:
        for (int j = 0;j < pDataStore.size();j++)
          {
            numbers[j] = to_string(pDataStore[j].demShare); // For MODE calculation
            sum2 += pDataStore[j].demShare;                 // For MEAN calculation
            medfnumbers[j] = pDataStore[j].demShare;        // For MEDIAN calculation
          }
        break;
    }

    // MEAN Calculation
    switch (choice)
    {
      case 1:
      case 2:
      case 3:
        mean = sum / pDataStore.size();
        break;
      case 4:
        mean = sum2 / pDataStore.size();
        break;
    }

    //MODE calculation
    for (auto &val : numbers)
    {
      if (conf == val) // If the next number is similar, save for mode.
      {
        mode = val;
        break;
      }
      sort(numbers.begin(), numbers.end()); // Sort the vector.
      conf = val; // Assign latest value to conf.
    }
    if (mode != conf) // If no similar numbers were found, mode is N/A.
      mode = "N/A";
    
    else if (choice == 4) // Move mode result for presicion usage in dem share.
      fmode = stof(mode);
    
    // MEDIAN calculation
    switch (choice)
    {
      case 1:
      case 2:
      case 3:
        sort(mednumbers.begin(), mednumbers.end()); // Sort the vector.
        if (pDataStore.size() % 2 != 0) // Check for even case
          // If number is even
          median = mednumbers[medianCount / 2]; 
        else
          // If number is odd
          median = (mednumbers[medianCount / 2] 
                    + mednumbers[(medianCount / 2) - 1]) / 2;
        break;
      case 4:
        sort(medfnumbers.begin(), medfnumbers.end()); // Sort the float vector.
        if (medianCount % 2 != 0) // Check for even case
          // If number is even
          median = medfnumbers[medianCount / 2];
        else
          // If number is odd
          median = (medfnumbers[medianCount / 2] 
                    + medfnumbers[(medianCount / 2) - 1]) / 2;
        break;
    }

		// Display results.
		switch (choice)
		{
      case 1: // Dem Votes
      case 2: // Rep Votes
      case 3: // Total Votes
        cout << "COLUMN" << setw(7) << right << ": " << columnName << endl;
        cout << "MEAN" << setw(9) << right << ": " << setprecision(5)
          << mean << endl;
        cout << "MEDIAN" << setw(7) << right << ": " << setprecision(5)
          << median << endl;
        cout << "MODE" << setw(9) << right << ": " << mode << endl;
        cout << "--------------------------------------------------" << endl;
        finish = true;
        break;
      case 4: // Dem Share
        cout << "COLUMN" << setw(7) << right << ": " << columnName << endl;
        cout << "MEAN" << setw(9) << right << ": " << setprecision(4)
             << mean << endl;
        cout << "MEDIAN" << setw(7) << right << ": " << setprecision(4)
             << median << endl;
        if (mode != conf) // If no mode was found, use "N/A"
          cout << "MODE" << setw(9) << right << ": " << mode << endl;
        else
          cout << "MODE" << setw(9) << setprecision(4) << right << ": " << fmode << endl;
        cout << "--------------------------------------------------" << endl;
        finish = true;
        break;
		}
	}
  pressEnter();
}

// Creates a histogram based on democratic share percentages for each county.
void histogram(vector<dataPull>& pDataStore)
{
  // For percentage calculation.
	float percent[] = { 100,90,80,70,60,50,40,30,20,10,0 };
	float numbers[10] = {0}; // Call numbers array for classification.
  float min = 0,max = 10.99;
	float share; // For comparing and classifying data.

	cout << "\nDEMOCRATIC SHARE HISTOGRAM" << endl;
	cout << "------------------------------------------------------------------------\n";

	for(int i = 0;i <= pDataStore.size();i++)  // Classify each value depending on range.
	{
		share = pDataStore[i].demShare; // Assign vector element value to share
    for(int j = 0; j <= 9; j++)
    {
      if (share >= min && share <= max)
        numbers[j]++;
      while(min == 0)
        min++;
      min += 10.0; // Increment min/max values by 10
      max += 10.0;
    }
    // Reset min/max value for next classification
    max = 10.99;
    min = 0;
	}
	for (auto& val : numbers) // Calculate percentage of each value amount in the array.
    val = (val / pDataStore.size()) * 100;

	// If no data is available, show message.
	if (pDataStore.empty())
	{
    cout << "No data available. Please add data to file." << endl;
		cout << "------------------------------------------------------------------------\n";
	}
	else // If there is data in vector, perform function.
	{
		for (auto& vert : percent) // Evaluate each of the 10 values in the array.
		{
			cout << setw(3) << vert << "% ";
			for (auto hor : numbers)
			{
				// If value is greater than or equal to percent, add stars.
				if (hor >= vert && hor != 0)
					cout << "*****\t";
				else
					cout << "     \t";
			}
			cout << endl;
		}
		cout << "__________________________________________________________________________________"
			<< endl;
		cout << "\t 0-10\t11-20\t21-30\t31-40\t41-50\t51-60\t61-70\t71-80\t81-90\t91-100"
			<< endl;
	}
  cin.ignore();
	pressEnter();
}

// Press enter prompt.
void pressEnter()
{
	cin.clear();
	string c;
	cout << "\n<Press enter to continue>";
	getline(cin, c);
}