#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

#include <sstream>

using namespace std;

map<string,int> variables;

pair<string,string> split(string s, string match)
{
	string a="", b="";
	int pos = s.find(match);
	if(pos == string::npos)
		cerr << "ERROR NO MATCH" << endl;
	a = s.substr(0, pos);
	b = s.substr(pos+match.size(), s.size()-pos-match.size());
	//cout << s << "->" << a << "|" << b << endl;
	return make_pair(a, b);
}

void replace(string &line, string target, string result)
{
	if(line.find(target) != string::npos)
	{
		line.replace(line.find(target), target.size(), result);
	}
}

void hvis(string &line)
{
	replace(line, "er", "[ER]");
}

vector<string> get_words(string &line)
{
	vector<string> output;
	string word = "";
	for(int i = 0; i < line.size()+1; i++)
	{
		if(i == line.size() || line[i] == ' ')
		{
			if(word.size() > 0){
				output.push_back(word);
				word="";
			}
		}
		else
		{
			word+=line[i];
		}
	}
	return output;
}


pair<bool,int> get_value(string value)
{
	bool isnumber = true;
	int number=0;
	for(int i = 0; i < value.size(); i++)
	{
		if(value[i] < '0' || value[i] > '9'){
			isnumber = false;
			break;
		}
		else
		{
			char v = value[i]-'0';
			number *= 10;
			number += v;
		}
	}
	return make_pair(isnumber, number);
}

void set_value(string name, string value)
{
	pair<bool,int> _number = get_value(value);
	bool is_number = _number.first;
	int number = _number.second;
	if(is_number) // setting name to a number
	{
		//cout << name << " 1set to " << number << endl;
		variables[name] = number;
	}
	else // setting name to anoter variable
	{
		//cout << name << " 2set to " << variables[value] << endl;
		variables[name] = variables[value];
	}
}

void pluss(string a, string b)
{
	pair<bool,int> _number = get_value(b);
	bool is_number = _number.first;
	int number = _number.second;
	if(is_number)
	{
		variables[a] += number;
	}
	else
	{
		variables[a] += variables[b];
	}
}

int main()
{
	//string program;
	//cin >> program;
	//istringstream f("a er 10\nb er 20\nc er a\nc plus b\nskriv ut a\nskriv ut b\nskriv ut c");
	string line;
	//while(getline(f, line))
	while(getline(cin, line))
	{
		vector<string> words = get_words(line);
		string fline ="";
		for(int i = 0; i < line.size(); i++)
			fline += (line[i]==' '?'_':line[i]);
		//cout << fline << endl;
		if(words.size() < 3)
			continue;
		if(words[0] == "skriv" && words[1] == "ut")
		{
			//string name="";
			//for(int i = 2; i < words.size(); i++)
			//{
				//name+=words[i];
				//if(i<words.size()-1)
					//name+='_';
			//}
			//skriv_ut(name, words);
			pair<string,string> pa = split(fline, "skriv_ut_");
			string name = pa.second;
			cout << '[' << name << " er " << variables[name] << ']' << endl;
		}
		else if(line.find("er") != string::npos)
		{
			//string a="", b="";
			//bool mid = false;
			//for(int i = 0; i < words.size(); i++)
			//{
				//if(words[i] != "er")
				//{
					//if(mid){
						//b+=words[i];
						//b+='_';
					//}
					//else{
						//a+=words[i];
						//a+='_';
					//}
				//}
				//else
					//mid=true;
			//}
			//a = a.substr(0, a.size()-1);
			//b = b.substr(0, b.size()-1);
			pair<string,string> pa = split(fline, "_er_");
			string a = pa.first;
			string b = pa.second;
			//cout << a << " [er] " << b << endl;
			set_value(a, b);
		}
		else if(line.find("plus") != string::npos)
		{
			pair<string,string> pa = split(fline, "_plus_");
			pluss(pa.first, pa.second);
		}
		//cout << "words: ";
		//for(int i = 0; i < words.size(); i++)
			//cout << words[i] << (i<words.size()-1?'|':' ');
		//cout << endl;
		//hvis(line);
		//cout << line << endl;
	}
}
