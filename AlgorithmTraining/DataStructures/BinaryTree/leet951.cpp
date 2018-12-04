#include "stdafx.h"
#include "Leet951.h"
#include <vector>  
#include <errno.h>
#include <math.h>  

bool leet951_flip_equivalent(TreeNode* root1, TreeNode* root2)
{
	if (root1 == NULL && root2 == NULL)
       return 1;

	if (root1->val == root2->val 
		&& (leet951_flip_equivalent(root1->left, root2->left) && leet951_flip_equivalent(root1->right, root2->right)
		|| leet951_flip_equivalent(root1->left, root2->right) && leet951_flip_equivalent(root1->right, root2->left)))
		return 1;

	return 0;
}

void leet951_test()
{
	bool result;
	TreeNode* root1 = (TreeNode*)malloc(sizeof(TreeNode));
	root1->val = 1;
	TreeNode* node1_2 = (TreeNode*)malloc(sizeof(TreeNode));
	node1_2->val = 2;
	TreeNode* node1_3 = (TreeNode*)malloc(sizeof(TreeNode));
	node1_3->val = 3;
	TreeNode* node1_4 = (TreeNode*)malloc(sizeof(TreeNode));
	node1_4->val = 4;
	TreeNode* node1_5 = (TreeNode*)malloc(sizeof(TreeNode));
	node1_5->val = 5;
	TreeNode* node1_6 = (TreeNode*)malloc(sizeof(TreeNode));
	node1_6->val = 6;
    TreeNode* node1_7 = (TreeNode*)malloc(sizeof(TreeNode));
	node1_7->val = 7;
	TreeNode* node1_8 = (TreeNode*)malloc(sizeof(TreeNode));
	node1_8->val = 8;

	node1_5->left = node1_7;
	node1_5->right = node1_8;
    node1_3->left = node1_6;
	node1_2->left = node1_4;
	node1_2->right = node1_5;

	root1->left = node1_2;
	root1->right = node1_3;

	TreeNode* root2 = (TreeNode*)malloc(sizeof(TreeNode));
	root2->val = 1;
	TreeNode* node2_2 = (TreeNode*)malloc(sizeof(TreeNode));
	node2_2->val = 2;
	TreeNode* node2_3 = (TreeNode*)malloc(sizeof(TreeNode));
	node2_3->val = 3;
	TreeNode* node2_4 = (TreeNode*)malloc(sizeof(TreeNode));
	node2_4->val = 4;
	TreeNode* node2_5 = (TreeNode*)malloc(sizeof(TreeNode));
	node2_5->val = 5;
	TreeNode* node2_6 = (TreeNode*)malloc(sizeof(TreeNode));
	node2_6->val = 6;
    TreeNode* node2_7 = (TreeNode*)malloc(sizeof(TreeNode));
	node2_7->val = 7;
	TreeNode* node2_8 = (TreeNode*)malloc(sizeof(TreeNode));
	node2_8->val = 8;

	node2_5->left = node2_8;
	node2_5->right = node2_7;
	node2_3->right = node2_6;
	node2_2->left = node2_4;
	node2_2->right = node2_5;

	root2->left = node2_3;
	root2->right = node2_2;

	result = leet951_flip_equivalent(root1, root2);
}

