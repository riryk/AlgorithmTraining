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
	std::vector<std::vector<int>> adj1, adj2, adj3;
	std::vector<int> circuit1, circuit2, circuit3;

    adj1.resize(3);

    adj1[0].push_back(1);
    adj1[1].push_back(2);
    adj1[2].push_back(0);

    circuit1 = printCircuit(adj1);

    adj2.resize(7);

    adj2[0].push_back(1);
    adj2[0].push_back(6);
    adj2[1].push_back(2);
    adj2[2].push_back(0);
    adj2[2].push_back(3);
    adj2[3].push_back(4);
    adj2[4].push_back(2);
    adj2[4].push_back(5);
    adj2[5].push_back(0);
    adj2[6].push_back(4);

	circuit2 = printCircuit(adj2);

    adj3.resize(5);
    adj3[0].push_back(1);
    adj3[1].push_back(3);
    adj3[1].push_back(2);
    adj3[2].push_back(0);
    adj3[3].push_back(4);
    adj3[4].push_back(1);

    circuit3 = printCircuit(adj3);
}