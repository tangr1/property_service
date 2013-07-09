/***************************************************************************
 * 
 * Copyright (c) 2013 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
/**
 * @file server.cpp
 * @author Tang Rui(tangrui01@baidu.com)
 * @date 2013/07/9 17:00:00
 * @version $Revision$ 
 * @brief 
 *  
 **/

#include <iostream>   
#include "server.h"

using namespace pservice;

int Server::test()
{
	std::cout << "Hello world!" << std::endl;

	return 0;
}

int main(int argc, char **argv)
{
	Server server;
	server.test();

	return 0;
}

/* vim: set ts=4 sw=4 sts=4 tw=100 noet: */
