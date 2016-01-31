#ifndef __SKELETON_H
#define __SKELETON_H

#include <vector>
#include "node.h"

//! A Skeleton class.
/*!
	When you merge an amount of Node instances
	it formes a skeleton instance.
*/
class Skeleton
{
	private:
		const char* name;	/*!< It names a Skeleton */
		int frames;			/*!< Stores the number of frames that has each Skeleton */

		std::vector<Node*> joint;		/*!< Vector of pointers of type Node for a 21 joints Skeleton
										-# Node(Hips));				[Joint n.0]
										-# Node(Spine));			[Joint n.1]
										-# Node(Spine1));			[Joint n.2]
										-# Node(Neck));				[Joint n.3]
										-# Node(Head));				[Joint n.4]
										-# Node(HeadEnd));			[Joint n.5]
										-# Node(LeftShoulder));		[Joint n.6]
										-# Node(LeftArm));			[Joint n.7]
										-# Node(LeftForeArm));		[Joint n.8]
										-# Node(LeftHand));			[Joint n.9]
										-# Node(LeftHandEnd));		[Joint n.10]
										-# Node(RightShoulder));	[Joint n.11]
										-# Node(RightArm));			[Joint n.12]
										-# Node(RightForeArm));		[Joint n.13]
										-# Node(RightHand));		[Joint n.14]
										-# Node(RightHandEnd));		[Joint n.15]
										-# Node(LeftUpLeg));		[Joint n.16]
										-# Node(LeftLeg));			[Joint n.17]
										-# Node(LeftFoot));			[Joint n.18]
										-# Node(LeftToeBase));		[Joint n.19]
										-# Node(LeftToeBaseEnd));	[Joint n.20]
										-# Node(RightUpLeg));		[Joint n.21]
										-# Node(RightLeg));			[Joint n.22]
										-# Node(RightFoot));		[Joint n.23]
										-# Node(RightToeBase));		[Joint n.24]
										-# Node(RightToeBaseEnd));	[Joint n.25]*/
	public:

		//! A constructor.
		/*!
			To identify several skeletons, it's important that each skeleton has its name. 
			In addition this constructor initialize the Skeleton attributes.
			\param name a char pointer to store the node alias.
		*/	
		Skeleton(const char* name);

		//! A destructor.
		/*!
		*/
		~Skeleton();

		//! Gets the skeleton's alias.
			/*!
			\return A pointer of type char.
			\sa Skeleton()
		*/
		const char* GetName();

		//! Build the skeleton instance.
			/*!
			Sets isRoot attribute of the child node to false. At every run
			the number of children is incremented by one.
			\param joint An integer argument. Right now only the skeleton
			of 21 joints is working. The are also of 17 joints but this
			is not implemented yet.
			\sa Node(), Node::LinkChild(), Node::LinkParent()
		*/
		void BuildSkeleton(int joints);

		//! Gets the skeleton's specific joint.
			/*!
			Gets the pointer of type Node frome the joint vector.
			\param jointNumber An integer argument.
			\return A pointer of type Node.
			\sa Node()
		*/
		Node* GetJoint(int jointNumber);

		//! Takes the offset data from a database.
			/*!
			It connects to mysql database. You have to configure the
			database before using this function.
			\param tableName A pointer of type char. Selects which table you want
			to use from the database
			SERVER "localhost" (if it is hosted at your computer, default value)
			USER "MocapRTRuser" (default value)
			PASSWORD "MocapRTRpassword" (default value)
			DATABASE "MocapRTRdb" (default value)
			\param char A pointer of type char
			\return An integer argument, it is used for debugging
		*/
		int TakeOffsetFromDB(char* tableName);

		//! Takes the channels data from a database.
			/*!
			It connects to mysql database. You have to configure the
			database before using this function.
			\param tableName A pointer of type char. Selects which table you want
			to use from the database
			SERVER "localhost" (if it is hosted at your computer, default value)
			USER "MocapRTRuser" (default value)
			PASSWORD "MocapRTRpassword" (default value)
			DATABASE "MocapRTRdb" (default value)
			\param char A pointer of type char
			\return An integer argument, it is used for debugging
		*/
		int TakeChannelsFromDB(char* tableName);

		//! Gets the number of skeleton's frames.
			/*!
			\return A pointer an integer argument.
			\sa Skeleton()
		*/
		int GetFrames();

		//! Gets all the positions of every joint.
			/*!
			When you don't have the position of every node, but have the
			rotation values (euler ones) for each axis, you must apply this function 
			to determine the position of every joint (a Node instace) 
			at the selected frame.
			As you can see it only determines one frame, so it usually inside a loop
			to track all the frames. Due to it only manages one frame at a time it
			can be parallelized (it's not implemented yet).
			\param frame An integer argument.
		*/
		void ParseData(int frame);

		//! The DEBUG attribute of the class Skeleton.
		/*!
			It is used to print some messages. Useful for debugging.
		*/
		bool DEBUG;
};

#endif	// SKELETON_H
