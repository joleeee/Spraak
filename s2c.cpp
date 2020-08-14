#include <iostream>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

enum BTYPE {BUILTIN=0, CONSTANT=1, VARIABLE=2};
struct byte
{
	BTYPE type=BUILTIN;
	int value=-1;
	byte(BTYPE t, int v)
	{
		type=t;
		value=v;
	}
};

string builtin[4] = {"er", "pluss", "skriv", "ut"};
int main() // minimized commands (skriv instead of skriv ut), max 3 words per line, variables are max 1 word etc
{
	istringstream file("a er 10\nb er 20\nb pluss a\nskriv ut a\nskriv ut b\nskriv ut c\n");
	string line;
	int variable_count=1;
	map<string, int> variable_id; // variable_id[a] == 0 because its the first variable (or maybe 1 because int is default 0, right?)
	map<int, string> variable_name; // reverse of the above
	vector<vector<byte>> parsed;
	while(getline(file, line))
	{
		vector<byte> bytes;
		istringstream linestream(line);
		string word;
		while(getline(linestream, word, ' '))
		{
			int i;
			int builtin_size=sizeof(builtin)/sizeof(*builtin);
			for(i = 0; i <= builtin_size; i++)
			{
				if(i==builtin_size) break;
				if(builtin[i]==word)
				{
					//cerr << word << " is built in" << endl;
					bytes.push_back(byte(BUILTIN, i));
					break;
				}
			}
			if(i < builtin_size)
				continue;
			try
			{
				bytes.push_back(byte(CONSTANT, stoi(word)));
				//cerr << "parsed\"" << word << '\"' << endl;
			}
			catch(...)
			{
				if(variable_id.find(word) == variable_id.end())
				{
					variable_id[word]=variable_count;
					variable_name[variable_count]=word;
					bytes.push_back(byte(VARIABLE,variable_count));
					//cerr << word << " er et nytt ord. id=" << variable_count << endl;
					variable_count++;
				}
				else
				{
					//cerr << word << " er er gammelt ord." << endl;
					bytes.push_back(byte(VARIABLE,variable_id[word]));
				}
			}
		}
		parsed.push_back(bytes);
		//cerr << endl;
	}
	//cerr << "PARSED:" << endl;
	//for(int i = 0; i < parsed.size(); i++)
		//for(int j = 0; j < parsed[i].size(); j++)
			//cout << parsed[i][j].type << '-' << parsed[i][j].value << (j<parsed[i].size()-1?'|':'\n');
	map<int,bool> used_names;
	for(int i = 0; i < parsed.size(); i++)
	{
		if(parsed[i].size() != 3)
			cerr << "Linje " << i << " har ikke 3 ord." << endl;
		byte a = parsed[i][0], b = parsed[i][1], c = parsed[i][2];
		if(	(a.type == VARIABLE) &&
			(b.type == BUILTIN && builtin[b.value]=="er") &&
			(c.type == VARIABLE || c.type == CONSTANT))
		{
			if(c.type == VARIABLE && !used_names[c.value])
				cerr << variable_name[c.value] << " har ingen verdi enda!" << endl;
			if(!used_names[a.value])
			{
				cout << "int ";
				used_names[a.value]=true;
			}
			cout << variable_name[a.value] << '=' << (c.type==CONSTANT?to_string(c.value):variable_name[c.value]) << ";\n";
		}
		else if((a.type == VARIABLE) &&
			(b.type == BUILTIN && builtin[b.value]=="pluss") &&
			(c.type == VARIABLE))
		{
			cout << variable_name[a.value] << "+=" << variable_name[c.value] << ";\n";
		}
		else if((a.type == BUILTIN && builtin[a.value]=="skriv")&&
			(b.type == BUILTIN && builtin[b.value]=="ut") &&
			(c.type == VARIABLE))
		{
			cout << "cout<<" << variable_name[c.value] << ";\n";
		}
	}
}
