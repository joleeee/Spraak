#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <cassert>

using namespace std;

enum BTYPE {BUILTIN=0, CONSTANT=1, VARIABLE=2, DASH=3};
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

const string builtin[9] = {"er", "pluss", "minus", "skriv", "ut", "-", "når", "mindre", "mer"};
int main() // minimized commands (skriv instead of skriv ut), max 3 words per line, variables are max 1 word etc
{
	//istringstream file("a er 10\nb er 20\nb pluss a\nskriv ut a\nskriv ut b\nskriv ut c\n");
	istringstream file("a er 10\nb er 20\nb pluss a\nnår a mindre 20\n- a pluss 1\nskriv ut a\nskriv ut b\n");
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
					if(word == "plus") cerr << "->leste plus, mente du pluss?\n";
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
			//cerr << parsed[i][j].type << '-' << parsed[i][j].value << (j<parsed[i].size()-1?'|':'\n');
	cout << "#include <iostream>\nint main(){\n";
	map<int,bool> used_names;
	int lastj=0;
	for(int i = 0; i < parsed.size(); i++)
	{

		int j=0;
		while(parsed[i][j].type==BUILTIN && builtin[parsed[i][j].value]=="-")
			j++;

		auto indent = [j, &lastj](){
			if(j>lastj)
				cout << "{\n";
			else if(j<lastj)
				cout << "}\n";
			lastj=j;
		};
		indent();

		int size = parsed[i].size()-j;
		if(size < 3) continue;
		byte a = parsed[i][j], b = parsed[i][j+1], c = parsed[i][j+2];
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
			continue;
		}
		else if((a.type == VARIABLE) &&
			(b.type == BUILTIN && (builtin[b.value]=="pluss" || builtin[b.value]=="minus")) &&
			(c.type == VARIABLE || c.type == CONSTANT))
		{
			cout << variable_name[a.value] << (builtin[b.value]=="pluss"?'+':'-')<< '=' << (c.type==VARIABLE?variable_name[c.value]:to_string(c.value)) << ";\n";
			continue;
		}
		else if((a.type == BUILTIN && builtin[a.value]=="skriv")&&
			(b.type == BUILTIN && builtin[b.value]=="ut") &&
			(c.type == VARIABLE))
		{
			cout << "std::cout<<" << '\"'<<variable_name[c.value]<<" er " << "\"<<" << variable_name[c.value] << "<<std::endl;\n";
			continue;
		}
		if(size < 4) continue;
		byte d = parsed[i][j+3];
		if(	(a.type == BUILTIN && builtin[a.value]=="når") &&
			(b.type == VARIABLE) &&
			(c.type == BUILTIN && (builtin[c.value] == "mindre" || builtin[c.value] == "mer")) &&
			(d.type == CONSTANT))
		{
			cout << "while(" << variable_name[b.value] << (builtin[c.value]=="mindre"?"<":">") << d.value << ')' << endl;
			continue;
		}
		continue;

	}
	cout << "}\n";
}
