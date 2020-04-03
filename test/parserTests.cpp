#include <iostream>
#include <string>
#include <fstream> 

using namespace std;

int compare(string fname)
{
	ifstream testFile( (fname + "_correct.csv").c_str());
	ifstream resultFile("res.csv");

	string test{ istreambuf_iterator<char>(testFile), istreambuf_iterator<char>() };
	string result{ istreambuf_iterator<char>(resultFile), istreambuf_iterator<char>() };

	return test.compare(result);
}

void test(string fname)
{
	system( ("./parser " + fname + ".csv > res.csv").c_str() );
	if (compare(fname) == 0)
		cout << "    --- PASSED " << fname << endl;
	else
		cout << "    --- FAILED " << fname << endl;
}

int main()
{
	// Test from example
	cout << "=== RUNNING Test1 (from example)" << endl;
	test("test/test1");	

	// Test with division and multiplication
	cout << "=== RUNNING Test2 (with division and multiplication)" << endl;
	test("test/test2");

	// Test with empty cells
        cout << "=== RUNNING Test3 (with empty cells)" << endl;
        test("test/test3");

	return 0;
}
