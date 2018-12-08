/*******************************************************************
*
*  DESCRIPTION: Common header file
*
*  AUTHOR: Ali Salaheddin
*  Note: Imported from old E-CD++ project (Daniella)
*******************************************************************/


#ifndef __COMMON_H
#define __COMMON_H


#define START_PROC		10
#define STOP_PROC		11

#define BRIGHT			0
#define DARK			1
#define ALL_DARK		2

#define PATTERN			3
#define NO_PATTER		4

#define ON_TRACK		5
#define OFF_TRACK		6

#define ZERO_TIME		0


namespace COMMON_H {

	enum OutputVal{
		O_STOP,
		O_GO_FWD,
		O_GO_REV
	};

}


#endif
