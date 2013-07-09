/***************************************************************************
 * 
 * Copyright (c) 2013 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 
 
/**
 * @file client.h
 * @author Tang Rui(tangrui01@baidu.com)
 * @date 2013/07/9 17:00:00
 * @version $Revision$ 
 * @brief 
 *  
 **/


#ifndef  __CLIENT_H_
#define  __CLIENT_H_

namespace pservice
{

class Client
{
public:
	Client(){}
	virtual ~Client(){}
	int test();

private:
};

} //namespace pservice

#endif //__CLIENT_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 noet: */
