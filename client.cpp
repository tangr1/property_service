/***************************************************************************
 * 
 * Copyright (c) 2013 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
/**
 * @file client.cpp
 * @author Tang Rui(tangrui01@baidu.com)
 * @date 2013/07/9 17:00:00
 * @version $Revision$ 
 * @brief 
 *  
 **/

#include <iostream>   
#include "client.h"

using namespace pservice;

int Client::test()
{
	std::cout << "Hello world!" << std::endl;

	return 0;
}

int main(int argc, char **argv)
{
	Client client;
	client.test();

	return 0;
}

/* vim: set ts=4 sw=4 sts=4 tw=100 noet: */
