//Joshua Carbee
//Task is to implement a binary expression tree and use the tree to convert postfix expressions into infix expressions 

#include <iostream>
#include <string>
#include "conv.h"
using namespace std;


conv::conv()
{
	root->left = nullptr;
	root->right = nullptr;
}


conv::conv(const string& postfix)
{
	
	vector<string> conv;
	BinaryNode* test = new BinaryNode();
	stack<BinaryNode*> s;
	int count = 0;
	string temp = "";
	for(int i =0; i < postfix.size(); i++)
	{
		if(postfix[i] == ' ')
		{
			conv.push_back(temp);
			temp = "";
		}
		else
		{
			temp = temp + postfix[i];
		}

	}
	conv.push_back(temp);
	
	//ERROR CHECKING
	int numOperators = 0;
	int numOperands = 0;
	
	for(int i =0; i < conv.size(); i++)
	{
		if(conv[i] == "+" || conv[i] == "-" || conv[i] == "/" || conv[i] == "*")
		numOperators++;
		else
		numOperands++;
	}
		
	
		if(numOperands-numOperators != 1)
		{
				cout << "Wrong postfix expression\n";
				exit(1);
		}
		
	
	int counter = conv.size();
	theSize = conv.size();
	for(int i =0; i < counter; i++)
	{
		if(conv[i] != "+" && conv[i] != "-" && conv[i] != "/" && conv[i] != "*")
		{
			BinaryNode *temp = new BinaryNode();
			temp->element = conv[i];
			s.push(temp);
		}
		else
		{
			BinaryNode *temp = new BinaryNode();
			temp->element = conv[i];
			temp->right = s.top();
			s.pop();
			temp->left = s.top();
			s.pop();
			s.push(temp);
		}
	
	}	

	root->element = s.top()->element;
	root->left = s.top()->left;
	root->right = s.top()->right;	

}

conv::conv(const conv& c)
{
	root = clone(c.root);
	theSize = c.theSize;
}

conv::~conv()
{
	makeEmpty(root);
}


bool conv::buildFromPostfix(const string& postfix)
{
	conv Test(postfix);
	*this = Test;
	return true;
}

const conv & conv::operator=(const conv& c)
{
	root = clone(c.root);
	theSize = c.theSize;
	return *this;	
}

void conv::printInfixExpression() 
{
	printInfixExpression(root);	
}

void conv::printPostfixExpression() const
{
	printPostfixExpression(root);
}

size_t conv::size() const 
{
	size_t temp = size(root);
	return temp;
}

size_t conv::leaf_nodes() const 
{
	size_t temp = leaf_nodes(root);
	return temp;
}

bool conv::empty() const
{
	if(root != nullptr)
	return false;
	else
	return true;
}

//PRIVATE HELPER FUNCTIONS

int getPrec(string temp)
{
	if(temp == "+" || temp == "-")
	return 1;
	else if(temp == "/" || temp == "*")
	return 2;
	else	
	return 3;
}


void conv::printInfixExpression(BinaryNode *n)
{
	int rightcheck = 0;
	if(n == nullptr)
	return;
	if(n->left != nullptr)
	{		
		if(getPrec(n->element) >= getPrec(n->left->element) && (getPrec(n->element) != 3 || getPrec(n->left->element) != 3))
		{
			counter++;
			cout << "(";
		}
	}
	printInfixExpression(n->left);
	cout << n->element << " ";
	
	if(n->right != nullptr)
	{
		if(getPrec(n->element) >= getPrec(n->right->element) && (getPrec(n->element) != 3 || getPrec(n->right->element) != 3))
		{
		cout << "(";
		counter++;
		}
		rightcheck = 1;
	}
	printInfixExpression(n->right);
	if(rightcheck == 1 && counter != 0)
	{
		cout << ")";
		counter--;
		rightcheck = 0;
	}
}

void conv::makeEmpty(BinaryNode* &t)
{

	if(t != nullptr)
	{
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}
	t = nullptr; 
	theSize = 0;
}

conv::BinaryNode * conv::clone(BinaryNode *t)
{

	if(t == nullptr)
	return nullptr;
	else
	return new BinaryNode{t->element, clone(t->left), clone(t->right)};
	
}

void conv::printPostfixExpression(BinaryNode *n) const
{	
	if(n == nullptr)
	return;

	printPostfixExpression(n->left);
	printPostfixExpression(n->right);
		
	cout << n->element << " ";
}

size_t conv::size(BinaryNode *t) const
{
	return theSize;
}

size_t conv::leaf_nodes(BinaryNode *t) const
{
	if(t == nullptr)
	return 0;
	if(t->left == nullptr && t->right == nullptr)
	return 1;
	else
	{
		return leaf_nodes(t->left) + leaf_nodes(t->right);
	}
}
