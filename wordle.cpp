// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <vector>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
std::set<std::string> helper(
	std::vector<bool> floating_status,
	std::string curr,
	std::string floating);

std::set<std::string> helper2(std::string curr, size_t state);

// Definition of primary wordle function
std::set<std::string> wordle(
  const std::string& in,
  const std::string& floating,
  const std::set<std::string>& dict)
{
	// Add your code here
	std::string curr = in;
	std::vector<bool> floating_status(floating.size(), 0);
	/** we get the first version of list
			which compute combinations of Cr((n-1), k)
			n = in.size()
			k = floating.size()
			other spaces are '-'
	**/ 
	
	std::set<std::string> list = helper(floating_status, curr, floating);
	size_t state = 0;
	std::set<std::string>::iterator it;
	std::set<std::string> res;
	/** we get the second cersion of list which is res
			res contains all of the combinations 
			for each one it have (n-1-k) * 26 permutations
	**/
	
	for(it = list.begin(); it != list.end(); ++it){
		std::set<std::string> s = helper2((*it), state);
		res.insert(s.begin(), s.end());
	}
	
	for(it = res.begin(); it != res.end();){
		if(dict.find(*it) == dict.end()){
			res.erase(it++);
		}
		else ++it;
	}
	return res;
}

// Define any helper functions here
// helper function output the first version of results
std::set<std::string> helper(
	std::vector<bool> floating_status,
	std::string curr,
	std::string floating)
{
	// return case: when the size of curr is equal to size
	bool flag = true;
	for(size_t i = 0; i < floating_status.size(); i++){
		if(floating_status[i] == 0){
			flag = false;
			break;
		}
	}
	if(flag){
		std::set<std::string> res;
		res.insert(curr);
		return res;
	}
	// recursive body
	std::set<std::string> ans;
	for(size_t j = 0; j < curr.size(); j++){
		for(size_t i = 0; i < floating.size(); i++){
			if(floating_status[i] == 0 && curr[j] == '-'){
				std::string new_curr = curr;
				new_curr[j] = floating[i];
				std::vector<bool> new_floating_status = floating_status;
				new_floating_status[i] = 1;
				std::set<std::string> s = helper(new_floating_status, new_curr, floating);
				ans.insert(s.begin(), s.end());
			}
		}
	}
	return ans;
}

// helper2 function compute the second function of results
std::set<std::string> helper2(std::string curr, size_t state)
{
	// Step1: skip occupied spaces
	while(curr[state] != '-' && state < curr.size()){
		state += 1;
	}
	// return case: when already finish checking all spaces of curr
	if(state == curr.size()){
		std::set<std::string> res;
		res.insert(curr);
		return res;
	}
	// recursive body
	std::set<std::string> ans;
	for(int i = 0; i < 26; i++){
		curr[state] = 'a' + i;
		std::set<std::string> s = helper2(curr, state + 1);
		ans.insert(s.begin(), s.end());
		
	}
	return ans;
}