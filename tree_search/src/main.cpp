#include <iostream>

#include "../include/MapParser.h"
#include "../include/DepthFirstSearch.h"
#include "../include/Timer.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cout << "Must include file to parse!" << endl;
		return 1;
	}

	Navigator* lNavigator = nullptr;

	try
	{
		MapParser lMap(argv[1]);
		lMap.ReadFile(lNavigator);

		lNavigator->GetMap()->PrintMap();
		DepthFirstSearch* lDFS = new DepthFirstSearch();
		lNavigator->Navigate(lDFS);
	}
	catch (exception& e)
	{
		cout << "An exception occurred: " << e.what() << endl;

		return 2;
	}

	delete lNavigator;

	return 0;
}