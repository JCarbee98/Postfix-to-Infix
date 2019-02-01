//Joshua Carbee		
//Task is to implement a binary expression tree and use the tree to convert postfix expressions into infix expressions 
#include <iostream>
#include <string>
#include <stack>
#include <vector>


class conv {

	public:
	conv();
	conv(const std::string& postfix);
	conv(const conv&);
	~conv();

	bool buildFromPostfix(const std::string& postfix);
	const conv & operator=(const conv &);
	void printInfixExpression();
	void printPostfixExpression() const;
	size_t size() const;
	size_t leaf_nodes() const; 
	bool empty() const;


	private:

	struct BinaryNode
	{
		std::string element;
		BinaryNode *left;
		BinaryNode *right;
		
		BinaryNode(const std::string Element = "", BinaryNode *lt = nullptr, BinaryNode *rt= nullptr)
		{
			element = Element;
			left = lt;
			right = rt;
		}

		BinaryNode(std::string && Element, BinaryNode *lt, BinaryNode *rt)
		{
			element = std::move(Element);
			left = std::move(lt);	
			right = std::move(rt);
		}
	};

	BinaryNode *root = new BinaryNode();
	int theSize = 0;	


	void printInfixExpression(BinaryNode *n);
	void makeEmpty(BinaryNode* &t);
	BinaryNode * clone(BinaryNode *t);
	void printPostfixExpression(BinaryNode * n) const;
	size_t size(BinaryNode *t) const;
	size_t leaf_nodes(BinaryNode *t) const;

};
