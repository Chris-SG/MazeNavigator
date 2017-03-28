#include "../include/Navigator.h"
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

	chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
	Navigator* lNavigator;

	try
	{
		MapParser lMap(argv[1]);
		lMap.ReadFile(lNavigator);
		DepthFirstSearch* lDFS = new DepthFirstSearch();
		lNavigator->Navigate(lDFS);
	}
	catch (exception& e)
	{
		cout << "An exception occurred: " << e.what() << endl;

		return 2;
	}
	chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
	cout << chrono::duration_cast<chrono::milliseconds>(end - start).count() << endl;

	delete lNavigator;

	return 0;
}