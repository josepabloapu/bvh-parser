#ifndef __NODE_CPP
#define __NODE_CPP

#include <vector>
#include <iostream>
#include "node.h"

Node::Node(char *__Name) 
{
	DEBUG = false;
	this->name = __Name;
	this->isRoot = true;
	this->isParent = false;
	this->isLeaf = true;
	this->posFlag = false;
	this->childCounter = 0;
	this->parent = NULL;
	if (DEBUG == true)
		std::cout << "Constructor of Node: " << this->name << std::endl;
}

Node::~Node ()
{
	if (DEBUG == true)
		std::cout << "Destructor of Node: " << this->name << std::endl;
}

void Node::Info(int frame)
{
	std::cout << "" << std::endl;
	std::cout << "**************************" << std::endl;
	std::cout << "******** NODE INFO *******" << std::endl;
	std::cout << "" << std::endl;
	std::cout << "******** FRAME "<< frame <<" *******" << std::endl;
	std::cout << "" << std::endl;
	std::cout << "Name: " << this->name << std::endl;
	if (this->parent != NULL)
		std::cout << "*Parent: " << this->parent->name << std::endl;
	for (int counter = 0; counter < children.size(); counter++)
		std::cout << "*Child: " << this->children[counter]->name << std::endl;
	std::cout << "" << std::endl;
	std::cout << "Is it parent: " << this->isParent << std::endl;
	std::cout << "Is it leaf: " << this->isLeaf << std::endl;
	std::cout << "Is it root: " << this->isRoot << std::endl;
	std::cout << "" << std::endl;
	std::cout << "OFFSET VALUES" << std::endl;
	std::cout << offset[0] << " " << offset[1] << " " << offset[2] << std::endl;
	std::cout << "" << std::endl;
	if (isRoot || posFlag)
	{
		std::cout << "CH-POS VALUES" << std::endl;
		std::cout << channels[0][frame] << " " << channels[1][frame] << " " << channels[2][frame] << std::endl;
		std::cout << "" << std::endl;
	}
	if (isLeaf == false)
	{
		std::cout << "CH-ROT VALUES" << std::endl;
		std::cout << channels[3][frame] << " " << channels[4][frame] << " " << channels[5][frame] << std::endl;
		std::cout << "" << std::endl;
		std::cout << "**************************" << std::endl;
	}
}

void Node::LinkChild(Node* child)
{
	this->children.push_back(child);
	this->isParent = true;
	this->isLeaf = false;
	this->children[childCounter]->isRoot = false;
	if (DEBUG == true)
		std::cout << this->name <<" is parent of " << this->children[childCounter]->name << std::endl;
	this->children[childCounter]->LinkParent(this);
	childCounter++;
}

void Node::LinkParent(Node* parent)
{
	this->parent = parent;
	this->isRoot = false;
	if (DEBUG == true)
		std::cout << this->name <<" is child of " << this->parent->name << std::endl;
}

Node* Node::GetParent()
{
	return this->parent;
}

Node* Node::GetChild(int iValue)
{
	return this->children[iValue];
}

char* Node::GetName()
{
	return this->name;
}

bool Node::GetIsRoot()
{
	return this->isRoot;
}

bool Node::GetIsLeaf()
{
	return this->isLeaf;
}

void Node::SetPosFlag(bool bValue)
{
	this->posFlag = bValue;
}

void Node::SetOffset(double dValue)
{
	this->offset.push_back(dValue);
}

double Node::GetOffset(int iValue)
{
	return this->offset[iValue];
}

void Node::SetChannels(int channel, double value)
{
	this->channels[channel].push_back(value);
}

double Node::GetChannels(int channel, int frame)
{
	return this->channels[channel][frame];
}

void Node::SetTRTR(int i,int j ,double value)
{
	this->trtr[i][j] = value;
}

double Node::GetTRTR(int i,int j)
{
	return this->trtr[i][j];
}

#endif	//NODE_CPP
