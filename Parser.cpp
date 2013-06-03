#include <iostream>
#include <string>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <fstream>

using std::string;
using std::cout;
using std::cin;
using std::vector;

double parse(string);
bool parenCheck(string, int);
string replaceString(string, char, string);

int main(){

    string filename;
    string expr;
    int n;
    double sum;
    string num;

    cout << "Please input the name of the data file:" << std::endl;
    cin >> filename;

    std::ifstream myfile(filename.c_str());

    if(myfile.is_open()){

    	while(myfile.good())
    	{
    		sum = 0;

    		myfile >> expr;
    		myfile >> n;

    		for(int i = 0; i < n; i++){
    			myfile >> num;
    			sum += parse(replaceString(expr, 'x', num));
    		}

    	    cout << "Average value for expression " << expr << ": " << sum/n << std::endl;
    	}

    }



    return 0;
}



string replaceString(string expr, char a, string b){

	for(int i = 0; i < expr.size(); i++){
		if(expr[i] == a){
			expr.erase(i, 1);
			expr.insert(i, b);
		}
	}

	return expr;
}


double parse(string s){


    //if the input does not contain operators then return the numerical value
    if(s.find("+") == string::npos && s.find("-") == string::npos
       && s.find("*") == string::npos && s.find("/") == string::npos
       && s.find("sqrt") == string::npos && s.find("sin") == string::npos
       && s.find("cos") == string::npos && s.find("tan") == string::npos){

        return atof(s.c_str());
    }
    //if - is used a sign operator
    else if(s.find("-") == 0){
    	return - parse(s.substr(1));
    }
    else if(s.find("+") == 0){
    	return parse(s.substr(1));
    }
    else {
    	int pos;

    	//distinguishes between sign operator and subtraction operator
    	pos = s.find("-");
    	if(pos != string::npos && parenCheck(s, pos) && pos != 0 && pos != s.size()-1 && s[pos-1] != '+'
    			&& s[pos-1] != '-' && s[pos-1] != '*' && s[pos-1] != '/'){
    		return parse(s.substr(0, pos)) - parse(s.substr(pos+1));
    	}

    	//distinguishes between sign operator and addition
    	pos = s.find("+");
    	if(pos != string::npos && pos != 0 && pos != s.size()-1 && parenCheck(s, pos)
    		&& s[pos-1] != '+' && s[pos-1] != '-' && s[pos-1] != '*' && s[pos-1] != '/'){
    		return parse(s.substr(0, pos)) + parse(s.substr(pos+1));
    	}

    	pos = s.find("*");
    	if(pos != string::npos && pos != 0 && pos != s.size()-1 && parenCheck(s, pos))
    		return parse(s.substr(0, pos)) * parse(s.substr(pos+1));

    	pos = s.find("/");
    	if(pos != string::npos && pos != 0 && pos != s.size()-1 && parenCheck(s, pos))
    		return parse(s.substr(0, pos)) / parse(s.substr(pos+1));

    	pos = s.find("sqrt");
    	if(pos != string::npos && pos == 0){
    		return sqrt(parse(s.substr(pos+5, s.size()-6)));
    	}

    	pos = s.find("sin");
    	if(pos != string::npos && pos == 0){
    		return sin(parse(s.substr(pos+4, s.size()-5)));
    	}

    	pos = s.find("cos");
    	if(pos != string::npos && pos == 0){
    	    return cos(parse(s.substr(pos+4, s.size()-5)));
    	}

    	pos = s.find("tan");
    	if(pos != string::npos && pos == 0){
    	    return tan(parse(s.substr(pos+4, s.size()-5)));
    	}
    }

    cout << "Invalid syntax: " << s << std::endl;
    return 0;
}

bool parenCheck(string s, int pos){

	int paren = 0;

	for(int i = 0; i < pos; i++){
		if(s[i] == '(')
			paren++;
		else if(s[i] == ')')
			paren--;
	}

	if(paren == 0)
		return true;
	else
		return false;
}
