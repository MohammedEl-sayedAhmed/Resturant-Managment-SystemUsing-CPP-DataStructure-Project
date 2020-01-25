#pragma once

enum PROG_MODE	//mode of the program interface
{
	MODE_INTR,	//interactive mode
	MODE_STEP,	//Step-by-step mode
	MODE_SLNT,	//Silent mode
	MODE_DEMO,	//Demo mode (for introductory phase only, should be removed in phases 1&2)
	MODE_CNT	//number of possible modes
};

enum ORD_TYPE	//types of orders
{
	TYPE_NRM,	//normal order
	TYPE_VEG,	//vegan
	TYPE_VIP,	//VIP
	TYPE_CNT	//Number of types

};

enum ORD_STATUS	//order status
{
	WAIT,	//waiting to be served
	SRV,	//In-service but not delivered (not finished) yet
	DONE,	//Delivered (finished) to its destination
	ORD_STATUS_CNT
};
