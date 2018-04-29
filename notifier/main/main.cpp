
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <string>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <exception>

#include "configfactory.hpp"

#include "callback.hpp"

#define OPTSTR "df:"

static bool 
should_daemonize(int argc, char **argv) 
{
	int opt;
	while((opt = getopt(argc, argv, OPTSTR)) != -1) {
		switch(opt) {
		case 'd':
			return true;
		}
	}
	return false;
}

int
main(int argc, char *argv[])
{
	AbsConfig::ShPtr pConfig;
	Callback::ShPtr pCallback;

	if(should_daemonize(argc, argv)) {
		int pid = fork();
		if(pid) {
			printf("Daemon mode engaged.\n");
			return 0;
		}
	}

	try {
		pConfig = ConfigFactory::getConfigByFile(std::string("/etc/notifier.json"));
		pCallback = Callback::ShPtr(new Callback(pConfig));	
	}
	catch(std::exception e) {
		std::cout << e.what();
		return -1;
	}
	
	printf("Hello World\n");
	return 0;
}

