#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

class CsvTable
{
public:
	size_t rowsLength;
	size_t collsLength;

	string getCell(string row, string coll)
	{
		vector<string> tmpRows;
		vector<string>* tmpColls = &(this -> table.at(0) -> values);
		for (auto &elem : table)
			tmpRows.push_back(elem -> getItem(0));

		size_t r = distance(tmpRows.begin(), find(tmpRows.begin(), tmpRows.end(), row));
		size_t c = distance(tmpColls -> begin(), find(tmpColls -> begin(), tmpColls -> end(), coll));

		return getCell(r, c);
	}

	string getCell(size_t row, size_t coll)
	{
		return this -> table.at(row) -> getItem(coll);
	}

	CsvTable(string str)
	{
		stringstream stream;
                stream << str;
                string s;
                while(getline(stream, s, '\n'))
		{
			Row* r = new Row(s);
			this -> table.push_back(r);
		} 
		this -> rowsLength = table.size();
		this -> collsLength = table.at(0) -> length;
	}

private:
	class Row
	{
	public:
		size_t length;

		string getItem(size_t order)
		{
			return this -> values.at(order);
		}

	        Row(string str)
        	{
	                stringstream stream;
                	stream << str;
        	        string cell;
	                while(getline(stream, cell, ','))
                	        values.push_back(cell);
			this -> length = values.size();
        	}
		vector<string> values;
	};

	vector<Row*> table;
};

bool isNumber (string s)
{
	if (find_if ( s.begin(), s.end(), [](unsigned char c) { return !isdigit(c); } ) == s.end() ) return true;
	return false;
}

int calculate(string num1, char op, string num2)
{
	int x = stoi(num1);
	int y = stoi(num2);

	switch (op)
	{
		case '+':
			return x + y;
		case '-':
			return x - y;
		case '*':
			return x * y;
		case '/':
			return x / y;
	}
}

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		cout << "Need .csv file name" << std::endl;
		return 1;
	}

	ifstream fname(argv[1]);
	string str { 
		istreambuf_iterator<char>(fname), istreambuf_iterator<char>() 
	};

	CsvTable* t = new CsvTable(str);

	for(size_t i = 0; i < t -> rowsLength; ++i)
	{
		for(size_t j = 0; j < t -> collsLength; ++j)
		{
			string s = t -> getCell(i, j);
			if ((i == 0) || (j == 0) || (isNumber(s)))
			{
				cout << s;
			}
			else
			{
				stringstream stream;
				stream << s;
				string tmp;

				char op = *find_if(s.begin(), s.end(), [](char c) {string symbols = "+-*/"; if (symbols.find(c) != string::npos) return 1; return 0; });

				getline(stream, tmp, op);
				string coll1 = string(tmp.begin() + 1, find_if( tmp.begin(), tmp.end(), [](char c) { return isdigit(c); } ));
				string row1 = string(find_if(tmp.begin(), tmp.end(), [](char c) { return isdigit(c); } ), tmp.end());

				getline(stream, tmp, op);
				string coll2 = string(tmp.begin(), find_if( tmp.begin(), tmp.end(), [](char c) { return isdigit(c); } ));
                                string row2 = string(find_if(tmp.begin(), tmp.end(), [](char c) { return isdigit(c); } ), tmp.end());	

				cout << calculate(t -> getCell(row1, coll1), op, t -> getCell(row2, coll2));
			}
			if (j != (t -> collsLength) - 1) cout << ",";
			else cout << endl;
		}
	}	

	return 0;
}
