#include "stdafx.h"
#include "hierholzer_euler_circuit.h"
#include <cstddef>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector> 
#include <unordered_map>
#include <stack>

std::vector<int> printCircuit(std::vector<std::vector<int>> adj)
{
	std::vector<std::vector<int>> adj_matrix = adj;
	std::tr1::unordered_map<int,int> edge_count;

	for (int i = 0; i < adj_matrix.size(); i++)
    {
        edge_count[i] = adj_matrix[i].size();
    }
    
	std::stack<int> curr_path;
	std::vector<int> circuit;

	if (!adj_matrix.size())
        return circuit; 

    curr_path.push(0);
    int curr_v = 0;
    while (!curr_path.empty())
    {
        if (edge_count[curr_v])
        {
            curr_path.push(curr_v);

            int next_v = adj_matrix[curr_v].back();

            edge_count[curr_v]--;
            adj_matrix[curr_v].pop_back();

            curr_v = next_v;
        }
        else
        {
            circuit.push_back(curr_v);

            curr_v = curr_path.top();
            curr_path.pop();
        }
	}

	return circuit;
}

void printCircuit_test()
{
	std::vector<std::vector<int>> adj1, adj2;
	std::vector<int> circuit1, circuit2;

    adj1.resize(3);

    adj1[0].push_back(1);
    adj1[1].push_back(2);
    adj1[2].push_back(0);

    circuit1 = printCircuit(adj1);
}