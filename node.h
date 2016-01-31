#ifndef __NODE_H
#define __NODE_H

#include <vector>

//! A Node class.
/*!
	A general node class usually used in graphs. 
	It can be linked each other as a parent or child node.
	It is oriented to motion captor technology. So it has channels,
	that is used to store values for (x,y,z) position and
	(x,y,z) euler rotation.
*/
class Node 
{
	private:
		char* name;				/*!< It names a Node */
		bool isRoot;				/*!< Is this Node root? */
		bool isParent;				/*!< Does this Node has child? */
		bool isLeaf;				/*!< Does this Node has not any child? */
		bool posFlag;				/*!< Indicates if the vector channels (from 0 to 2), that are the position channels, has data or not. */
		int childCounter;			/*!< Indicates the number of children that has this Node. */
		Node* parent;				/*!< Pointer to the parent's Node*/
		std::vector<Node*> children;		/*!< Vector of pointer to the children's Node */
		std::vector<double> offset;		/*!< Vector of double arguments to store the offset data */
		std::vector<double> channels[6];	/*!< Vector of double arguments to store the channaels data */
		double trtr[4][4];			/*!< Matrix that helps to determine a Node position from rotation values */
	
	public:

		//! A constructor.
		/*!
			To identify several nodes, it's important that each node has its name. 
			In addition this constructor initialize the Node attributes.
			\param name a char pointer to store the node alias.
		*/		
		Node(char *name);
		
		//! A destructor.
		/*!
		*/
		~Node();
		
		//! Displays all the infomation of a single node at the selected frame.
			/*!
			\param frame An integer argument.
			\sa Node() ,LinkChild(), LinkParent(), SetOffset(), SetChannels()
		*/
		void Info(int frame);
		
		//! Links a node to its child.
			/*!
			\param child An argument of type Node.
			\sa Info()
		*/
		void LinkChild(Node* child);

		//! Links a node to its parent.
			/*!
			Sets isRoot attribute of the child node to false. At every run
			the number of children is incremented by one.
			\param parent An argument of type Node.
			\sa Info()
		*/
		void LinkParent(Node* parent);

		//! Get its parent node.
			/*!
			Sets isLeaf attribute of the parent node to false ;
			\return A pointer of type Node.
		*/
		Node* GetParent();

		//! Gets its child node.
			/*!
			\param child An integer argument. When you link a child node to
			its parent, this child node is stored in a vector variable 
			(children attribute) of the parent node. 
			You must be careful and become aware if the integer is
			pointing the correct child node.
			\return A pointer of type Node.
			\sa LinkChild(), LinkParent()
		*/
		Node* GetChild(int child);

		//! Gets the node's alias.
			/*!
			\return A pointer of type char.
			\sa Node()
		*/
		char* GetName();

		//! Gets the boolean value of isRoot.
			/*!
			\return A boolean argument.
			\sa Node(), LinkParent()
		*/
		bool GetIsRoot();

		//! Gets the boolean value of isLeaf.
			/*!
			\return A boolean argument.
			\sa Node(), LinkChild()
		*/
		bool GetIsLeaf();

		//! Sets the boolean value of posFlag.
			/*!
			At initialization the channels are empty. Later or you  fill
			the rotation channels and then (after parsing data) you fill
			the position channels. After that posFlag is set to true.
			\sa Node(), ParseData()
		*/
		void SetPosFlag(bool);

		//! Sets the offset value.
			/*!
			This function is ussually called three times to store x,y,z offset, in
			this order. These values are constant for each node.
			\param value A double parament. This value is stored in the offset vector.
		*/
		void SetOffset(double value);

		//! Get a specific offset's value.
			/*! 
			\param channel an integer argument. 0=[X], 1=[Y], 2=[Z].
			\return A double argument. The offset value of the determined channel.
		*/
		double GetOffset(int channel);

		//! Sets the channel's value for each frame.
			/*!
			At the channel argument, 0-2 are axis-positions and 3-5 are euler-rotations.
			\param channel An integer argument. 0=[X], 1=[Y], 2=[Z], 3=[X], 4=[Y], 5=[Z].
			\param value A double argument. This value may be centimeters or degrees, 
			depending of the channel.
		*/
		void SetChannels(int channel, double value);

		//! Gets a specific channel's value.
			/*!
			At the channel argument, 0-2 are axis-positions and 3-5 are euler-rotations. 
			\param channel An integer argument. 0=[X], 1=[Y], 2=[Z], 3=[X], 4=[Y], 5=[Z].
			\param frame an integer argument. Represents the frame of interest.
			\return A double argument. 
			The value of the determined channel at the frame of interest. 
			This value may be length or degrees, depending of the channel.
		*/
		double GetChannels(int channel,int frame);

		//! Fills the TRTR matrix.
			/*!
			A matrix that helps to determine node's position.
			Usually is used inside a loop, to fill out the whole 4x4 matrix
			\param i An integer An integer argument. Selects the row.
			\param j An integer An integer argument. Selects the column.
			\param value A double argument. 
		*/
		void SetTRTR(int i,int j,double value);

		//! Gets the TRTR matrix.
			/*!
			A matrix that helps to determine node's position.
			Usually is used inside a loop, to get the whole 4x4 matrix
			\param i An integer An integer argument. Selects the row.
			\param j An integer An integer argument. Selects the column.
			\return value A double argument. 
		*/
		double GetTRTR(int i,int j);

		//! The DEBUG attribute of the class Node.
		/*!
			It is used to print some messages. Useful for debugging.
		*/
		bool DEBUG;
};

#endif 	//NODE_H
