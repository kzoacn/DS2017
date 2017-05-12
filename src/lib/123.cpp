#include"vector.hpp"
#include<iostream>
using std::string;
using sjtu::vector;
int main()
{
	vector<string>vec1,vec2;
	
	string a="21321123123123123123123123";
	vec1.push_back(a);
	vec1.push_back(string());
	vec2=vec1;
	std::cout<<vec2[0]<<std::endl;
	
	return 0;
 } 
