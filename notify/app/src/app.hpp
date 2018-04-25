#pragma once

#define APP_DEFAULT_CONFIG_FILE "/etc/kafka-notify.json"

#include <string>
#include <sstream>
#include <iostream>

#include <Poco/Util/OptionSet.h>
#include <Poco/Util/Application.h>

#include "config/configfactory.hpp"

using Poco::Util::Application;
using Poco::Util::OptionSet;

class App: public Application
{
private:
	bool _helpRequested;
	bool _daemonize;
	Config::ShPtr _pConfig;
public:
	App(); 
protected:
	void initialize(Application &self);
	void uninitialize();
	void reinitialize(Application &self);
	void defineOptions(OptionSet &options);
	void handleHelp(const std::string &name, const std::string &value);
	void handleConfig(const std::string &name, const std::string &value);
	void handleDaemonize(const std::string &name, const std::string &value);
	void displayHelp();
	int loadConfigFile(const std::string &filename);
	int main(const ArgVec &args);
};

