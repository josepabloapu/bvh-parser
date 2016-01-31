#ifndef __SKELETON_CPP
#define __SKELETON_CPP

#define PI 3.14159265358979323846

#include <vector>
#include <iostream>
#include <string.h>

#include "mysql.h"
#include "matrix.h"
#include "node.h"
#include "skeleton.h"

#define SERVER "localhost"
#define USER "user"
#define PASSWORD "password"
#define DATABASE "db"

//REMOVE warning: deprecated conversion from string constant to 'char*'
char Hips				[] = "Hips";
char Spine 				[] = "Spine";			
char Spine1	 			[] = "Spine1";			
char Neck				[] = "Neck";				
char Head				[] = "Head";				
char HeadEnd			[] = "HeadEnd";			
char LeftShoulder 		[] = "LeftShoulder";		
char LeftArm			[] = "LeftArm";			
char LeftForeArm 		[] = "LeftForeArm";		
char LeftHand 			[] = "LeftHand";			
char LeftHandEnd 		[] = "LeftHandEnd";		
char RightShoulder 		[] = "RightShoulder";	
char RightArm 			[] = "RightArm";			
char RightForeArm 		[] = "RightForeArm";		
char RightHand 			[] = "RightHand";		
char RightHandEnd 		[] = "RightHandEnd";		
char LeftUpLeg 			[] = "LeftUpLeg";		
char LeftLeg			[] = "LeftLeg";			
char LeftFoot 			[] = "LeftFoot";			
char LeftToeBase 		[] = "LeftToeBase";		
char LeftToeBaseEnd 	[] = "LeftToeBaseEnd";	
char RightUpLeg 		[] = "RightUpLeg";		
char RightLeg 			[] = "RightLeg";			
char RightFoot 			[] = "RightFoot";		
char RightToeBase 		[] = "RightToeBase";		
char RightToeBaseEnd	[] = "RightToeBaseEnd";	

Skeleton::Skeleton(const char* __Name) 
{
	DEBUG = false;
	this->name = __Name;
	this->frames = 0;
	if (DEBUG == true)
		std::cout << "Constructor of " << this->name << std::endl;
}

Skeleton::~Skeleton()
{
	if (DEBUG == true)
		std::cout << "Destructor of " << this->name << std::endl;
}

const char* Skeleton::GetName()
{
	return this->name;
}

void Skeleton::BuildSkeleton(int joints)
{
	if (joints == 21) 
	{
		joint.push_back(new Node(Hips));				//Joint n.00
		joint.push_back(new Node(Spine));				//Joint n.01
		joint.push_back(new Node(Spine1));				//Joint n.02
		joint.push_back(new Node(Neck));				//Joint n.03
		joint.push_back(new Node(Head));				//Joint n.04
		joint.push_back(new Node(HeadEnd));				//Joint n.05
		joint.push_back(new Node(LeftShoulder));		//Joint n.06
		joint.push_back(new Node(LeftArm));				//Joint n.07
		joint.push_back(new Node(LeftForeArm));			//Joint n.08
		joint.push_back(new Node(LeftHand));			//Joint n.09
		joint.push_back(new Node(LeftHandEnd));			//Joint n.10
		joint.push_back(new Node(RightShoulder));		//Joint n.11
		joint.push_back(new Node(RightArm));			//Joint n.12
		joint.push_back(new Node(RightForeArm));		//Joint n.13
		joint.push_back(new Node(RightHand));			//Joint n.14
		joint.push_back(new Node(RightHandEnd));		//Joint n.15
		joint.push_back(new Node(LeftUpLeg));			//Joint n.16
		joint.push_back(new Node(LeftLeg));				//Joint n.17
		joint.push_back(new Node(LeftFoot));			//Joint n.18
		joint.push_back(new Node(LeftToeBase));			//Joint n.19
		joint.push_back(new Node(LeftToeBaseEnd));		//Joint n.20
		joint.push_back(new Node(RightUpLeg));			//Joint n.21
		joint.push_back(new Node(RightLeg));			//Joint n.22
		joint.push_back(new Node(RightFoot));			//Joint n.23
		joint.push_back(new Node(RightToeBase));		//Joint n.24
		joint.push_back(new Node(RightToeBaseEnd));		//Joint n.25

		joint[0]->LinkChild(joint[1]);
		joint[0]->LinkChild(joint[16]);
		joint[0]->LinkChild(joint[21]);
		joint[1]->LinkChild(joint[2]);
		joint[2]->LinkChild(joint[3]);
		joint[2]->LinkChild(joint[6]);
		joint[2]->LinkChild(joint[11]);
		joint[3]->LinkChild(joint[4]);
		joint[4]->LinkChild(joint[5]);
		joint[6]->LinkChild(joint[7]);
		joint[7]->LinkChild(joint[8]);
		joint[8]->LinkChild(joint[9]);
		joint[9]->LinkChild(joint[10]);
		joint[11]->LinkChild(joint[12]);
		joint[12]->LinkChild(joint[13]);
		joint[13]->LinkChild(joint[14]);
		joint[14]->LinkChild(joint[15]);
		joint[16]->LinkChild(joint[17]);
		joint[17]->LinkChild(joint[18]);
		joint[18]->LinkChild(joint[19]);
		joint[19]->LinkChild(joint[20]);
		joint[21]->LinkChild(joint[22]);
		joint[22]->LinkChild(joint[23]);
		joint[23]->LinkChild(joint[24]);
		joint[24]->LinkChild(joint[25]);
	}
}

Node* Skeleton::GetJoint(int jointNumber)
{
	return this->joint[jointNumber];
}

int Skeleton::TakeOffsetFromDB(char * tableName)
{
	MYSQL *connect; // Create a pointer to the MySQL instance
    connect=mysql_init(NULL); // Initialise the instance
    /* This If is irrelevant and you don't need to show it. I kept it in for Fault Testing.*/
    if(!connect)    /* If instance didn't initialize say so and exit with fault.*/
    {
        fprintf(stderr,"MySQL Initialization Failed");
        return 1;
    }
    /* Now we will actually connect to the specific database.*/
 	
    connect=mysql_real_connect(connect,SERVER,USER,PASSWORD,DATABASE,0,NULL,0);
    /* Following if statements are unneeded too, but it's worth it to show on your
    first app, so that if your database is empty or the query didn't return anything it
    will at least let you know that the connection to the mysql server was established. */
 
 	if(DEBUG)
 	{
 		if(connect)
 		{
    	    printf("Connection Succeeded\n");
    	}
    	else
    	{
    	    printf("Connection Failed!\n");
    	}
 	}
    

    char command[256] = "SELECT * FROM ";

    MYSQL_RES *res_set; /* Create a pointer to recieve the return value.*/
    MYSQL_ROW row;  /* Assign variable for rows. */
    mysql_query(connect,strcat (command,tableName));
    /* Send a query to the database. */
    
    unsigned int i = 0; /* Create a counter for the rows */
    unsigned int j = 0; /* Create a counter for the skeleton*/
    res_set = mysql_store_result(connect); /* Receive the result and store it in res_set */


    while ((row = mysql_fetch_row(res_set)) != NULL)
    {
    	this->GetJoint(j)->SetOffset(atof(row[i+1]));
    	this->GetJoint(j)->SetOffset(atof(row[i+2]));
    	this->GetJoint(j)->SetOffset(atof(row[i+3]));
    	j++;
    }

    mysql_close(connect);   /* Close and shutdown */
    return 0;
}

int Skeleton::TakeChannelsFromDB(char * tableName)
{
	MYSQL *connect; // Create a pointer to the MySQL instance
    connect=mysql_init(NULL); // Initialise the instance
    /* This If is irrelevant and you don't need to show it. I kept it in for Fault Testing.*/
    if(!connect)    /* If instance didn't initialize say so and exit with fault.*/
    {
        fprintf(stderr,"MySQL Initialization Failed");
        return 1;
    }
    /* Now we will actually connect to the specific database.*/
 	
    connect=mysql_real_connect(connect,SERVER,USER,PASSWORD,DATABASE,0,NULL,0);
    /* Following if statements are unneeded too, but it's worth it to show on your
    first app, so that if your database is empty or the query didn't return anything it
    will at least let you know that the connection to the mysql server was established. */
 
 	if(DEBUG)
 	{
    	if(connect)
    	{
    	    printf("Connection Succeeded\n");
    	}
    	else
    	{
    	    printf("Connection Failed!\n");
    	}
	}

    char command[256] = "SELECT * FROM ";

    MYSQL_RES *res_set; /* Create a pointer to recieve the return value.*/
    MYSQL_ROW row;  /* Assign variable for rows. */
    mysql_query(connect,strcat (command,tableName));
    /* Send a query to the database. */

    unsigned int i = 0; /* Create a counter for the rows */
    unsigned int j = 0; /* Create a counter for the skeleton*/
    res_set = mysql_store_result(connect); /* Receive the result and store it in res_set */
    
    while ((row = mysql_fetch_row(res_set)) != NULL)
    {
    	i = 1; /* Create a counter for the rows */
    	j = 0; /* Create a counter for the skeleton*/

    	this->GetJoint(j)->SetChannels(0, atof(row[i]));
    	this->GetJoint(j)->SetChannels(1, atof(row[i+1]));
    	this->GetJoint(j)->SetChannels(2, atof(row[i+2]));

    	i = i+3;
    	for(j=0;j<25;j++)
    	{
    		this->GetJoint(j)->SetChannels(5, atof(row[i])); // Z -> X
    		this->GetJoint(j)->SetChannels(3, atof(row[i+1])); // X -> Y
    		this->GetJoint(j)->SetChannels(4, atof(row[i+2])); // Y -> Z
    		if (j==4 || j==9 || j==14 || j==19)
    			j++;
    		i = i+3;
    	}
   		this->frames++;
    }
    mysql_close(connect);   /* Close and shutdown */
    return 0;
}

int Skeleton::GetFrames()
{
	return this->frames;
}

void Skeleton::ParseData(int frame)
{
	for(int joint=0;joint<=25;joint++)
	{
		if(DEBUG)
		{
			std::cout << "************************************************************" << std::endl;
			std::cout << "************************************************************" << std::endl;
			std::cout << this->GetJoint(joint)->GetName() << std::endl;
			std::cout << "************************************************************" << std::endl;
			std::cout << "************************************************************" << std::endl;
		}

		QSMatrix<double> identity(4, 4, 0);
		QSMatrix<double> stmat(4, 4, 0);
		QSMatrix<double> dtmat(4, 4, 0);
		QSMatrix<double> drmat(4, 4, 0);
		QSMatrix<double> local2world(4, 4, 0);
		QSMatrix<double> trtr(4, 4, 0);
		QSMatrix<double> parent_trtrmat(4, 4, 0);
	
		if(this->GetJoint(joint)->GetIsRoot()==false)
		{
			parent_trtrmat(0,0) = this->GetJoint(joint)->GetParent()->GetTRTR(0,0);
			parent_trtrmat(0,1) = this->GetJoint(joint)->GetParent()->GetTRTR(0,1);
			parent_trtrmat(0,2) = this->GetJoint(joint)->GetParent()->GetTRTR(0,2);
			parent_trtrmat(0,3) = this->GetJoint(joint)->GetParent()->GetTRTR(0,3);
			parent_trtrmat(1,0) = this->GetJoint(joint)->GetParent()->GetTRTR(1,0);
			parent_trtrmat(1,1) = this->GetJoint(joint)->GetParent()->GetTRTR(1,1);
			parent_trtrmat(1,2) = this->GetJoint(joint)->GetParent()->GetTRTR(1,2);
			parent_trtrmat(1,3) = this->GetJoint(joint)->GetParent()->GetTRTR(1,3);
			parent_trtrmat(2,0) = this->GetJoint(joint)->GetParent()->GetTRTR(2,0);
			parent_trtrmat(2,1) = this->GetJoint(joint)->GetParent()->GetTRTR(2,1);
			parent_trtrmat(2,2) = this->GetJoint(joint)->GetParent()->GetTRTR(2,2);
			parent_trtrmat(2,3) = this->GetJoint(joint)->GetParent()->GetTRTR(2,3);
			parent_trtrmat(3,0) = this->GetJoint(joint)->GetParent()->GetTRTR(3,0);
			parent_trtrmat(3,1) = this->GetJoint(joint)->GetParent()->GetTRTR(3,1);
			parent_trtrmat(3,2) = this->GetJoint(joint)->GetParent()->GetTRTR(3,2);
			parent_trtrmat(3,3) = this->GetJoint(joint)->GetParent()->GetTRTR(3,3);
		}
	
		identity(0,0) = 1;
		identity(1,1) = 1;
		identity(2,2) = 1;
		identity(3,3) = 1;
	
	  	stmat = identity;
	  	stmat(0,3) = this->GetJoint(joint)->GetOffset(0);
		stmat(1,3) = this->GetJoint(joint)->GetOffset(1);
		stmat(2,3) = this->GetJoint(joint)->GetOffset(2);
	
		if(DEBUG)
		{
			std::cout << "" << std::endl;
			std::cout << "**************************************************STRANMAT" << std::endl;
			std::cout << "Joint: " << this->GetJoint(joint)->GetName() << std::endl;
			std::cout << "Frame: " << frame+1 << std::endl;
			std::cout << "" << std::endl;
		
			for (int i=0; i<stmat.get_rows(); i++)
			{
		    	for (int j=0; j<stmat.get_cols(); j++)
		    	{
		      		std::cout << stmat(i,j) << ", ";
		    	}
		    	std::cout << std::endl;
		  	}
		}
	
	  	if(this->GetJoint(joint)->GetIsRoot()==true)
	  	{
			dtmat = identity;
			dtmat(0,3) = this->GetJoint(joint)->GetChannels(0,frame);
			dtmat(1,3) = this->GetJoint(joint)->GetChannels(1,frame);
			dtmat(2,3) = this->GetJoint(joint)->GetChannels(2,frame);
		
			if(DEBUG)
			{
				std::cout << "" << std::endl;
				std::cout << "**************************************************DTRANMAT" << std::endl;
				std::cout << "Joint: " << this->GetJoint(joint)->GetName() << std::endl;
				std::cout << "Frame: " << frame+1 << std::endl;
				std::cout << "" << std::endl;
				
				for (int i=0; i<dtmat.get_rows(); i++) 
				{
				   	for (int j=0; j<dtmat.get_cols(); j++) 
				   	{
				   	  	std::cout << dtmat(i,j) << ", ";
				   	}
				   	std::cout << std::endl;
			  	}
		  	}
		}
	
		if(this->GetJoint(joint)->GetIsLeaf()==false)
		{
			drmat = identity;
			QSMatrix<double> drmatx = identity;
			double x = this->GetJoint(joint)->GetChannels(3,frame) * PI / 180.0;
		
			drmatx(1,1) = cos(x);
			drmatx(1,2) = -sin(x);
			drmatx(2,1) = sin(x);
			drmatx(2,2) = cos(x);
		
			QSMatrix<double> drmaty = identity;
			double y = this->GetJoint(joint)->GetChannels(4,frame) * PI / 180.0;
		
			drmaty(0,0) = cos(y);
			drmaty(0,2) = sin(y);
			drmaty(2,0) = -sin(y);
			drmaty(2,2) = cos(y);
		
		  QSMatrix<double> drmatz = identity;
			double z = this->GetJoint(joint)->GetChannels(5,frame) * PI / 180.0;
		
		  drmatz(0,0) = cos(z);
			drmatz(0,1) = -sin(z);
			drmatz(1,0) = sin(z);
			drmatz(1,1) = cos(z);
		
			drmat=drmat*drmatz;
			drmat=drmat*drmatx;
			drmat=drmat*drmaty;
		
			if(DEBUG)
			{
			  std::cout << "" << std::endl;
				std::cout << "**************************************************DROTMAT" << std::endl;
				std::cout << "Joint: " << this->GetJoint(joint)->GetName() << std::endl;
				std::cout << "Frame: " << frame+1 << std::endl;
				std::cout << "" << std::endl;
			
				for (int i=0; i<drmat.get_rows(); i++) 
				{
					for (int j=0; j<drmat.get_cols(); j++) 
					{
					  	std::cout << drmat(i,j) << ", ";
					}
					std::cout << std::endl;
				}
			}
		}

		if(this->GetJoint(joint)->GetIsLeaf()==true)
		{
			drmat = identity;
			if(DEBUG){
			  std::cout << "" << std::endl;
				std::cout << "**************************************************DROTMAT" << std::endl;
				std::cout << "Joint: " << this->GetJoint(joint)->GetName() << std::endl;
				std::cout << "Frame: " << frame+1 << std::endl;
				std::cout << "" << std::endl;
			
				for (int i=0; i<drmat.get_rows(); i++) 
				{
					for (int j=0; j<drmat.get_cols(); j++) 
					{
					  	std::cout << drmat(i,j) << ", ";
					}
					std::cout << std::endl;
				}
			}
		}
	
	  	if(this->GetJoint(joint)->GetIsRoot()==true)
	  	{
	  		local2world = stmat*dtmat;
	  		if(DEBUG)
	  		{
		  		std::cout << "" << std::endl;
					std::cout << "**************************************************LOCAL2WORLD" << std::endl;
					std::cout << "Joint: " << this->GetJoint(joint)->GetName() << std::endl;
					std::cout << "Frame: " << frame+1 << std::endl;
					std::cout << "" << std::endl;
			
					for (int i=0; i<local2world.get_rows(); i++) 
					{
						for (int j=0; j<local2world.get_cols(); j++) 
						{
						  	std::cout << local2world(i,j) << ", ";
						}
						std::cout << std::endl;
					}
				}
	  	}
	
	  	if(this->GetJoint(joint)->GetIsRoot() == false)
	  	{
	  		local2world = parent_trtrmat*stmat;
			if(DEBUG)
			{
		  	std::cout << "" << std::endl;
				std::cout << "**************************************************LOCAL2WORLD" << std::endl;
				std::cout << "Joint: " << this->GetJoint(joint)->GetName() << std::endl;
				std::cout << "Frame: " << frame+1 << std::endl;
				std::cout << "" << std::endl;
			
				for (int i=0; i<<local2world.get_rows(); i++) 
				{
					for (int j=0; j<<local2world.get_cols(); j++) 
					{
					  	std::cout << local2world(i,j) << ", ";
					}
					std::cout << std::endl;
				}
			}
	  	}
		
		if(this->GetJoint(joint)->GetIsRoot() == false)
		{
			this->GetJoint(joint)->SetChannels(0,local2world(0,3));
	  		this->GetJoint(joint)->SetChannels(1,local2world(1,3));
	  		this->GetJoint(joint)->SetChannels(2,local2world(2,3));
	  		this->GetJoint(joint)->SetPosFlag(true);
		}
	  	
	  	trtr = identity;
	  	trtr = local2world*drmat;
	
	  	for (int i=0; i<trtr.get_rows(); i++) 
	  	{
			for (int j=0; j<trtr.get_cols(); j++) 
			{
			  	this->GetJoint(joint)->SetTRTR(i,j,trtr(i,j));
			}
		}
	
		if(DEBUG)
		{
		  std::cout << "" << std::endl;
			std::cout << "**************************************************TRTRMAT" << std::endl;
			std::cout << "Joint: " << this->GetJoint(joint)->GetName() << std::endl;
			std::cout << "Frame: " << frame+1 << std::endl;
			std::cout << "" << std::endl;
		
			for (int i=0; i<<trtr.get_rows(); i++) 
			{
				for (int j=0; j<<trtr.get_cols(); j++)
				{
				  	std::cout << trtr(i,j) << ", ";
				}
				std::cout << std::endl;
			}
		}

	} // End for
	
}

#endif	// SKELETON_CPP
