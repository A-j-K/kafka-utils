
#include "app.hpp"
#include <Poco/Util/Option.h>
#include <Poco/Util/HelpFormatter.h>
#include <Poco/Util/AbstractConfiguration.h>
#include <Poco/AutoPtr.h>

using Poco::Util::Option;
using Poco::Util::HelpFormatter;
using Poco::Util::AbstractConfiguration;
using Poco::Util::OptionCallback;
using Poco::AutoPtr;

App::App(): 
	_daemonize(false),
	_helpRequested(false),
	_pConfig(0)
{}

int 
App::main(const ArgVec &args)
{
	if(_helpRequested) {
		return Application::EXIT_OK;
	}
	if(_pConfig == nullptr) {
		if(loadConfigFile(std::string(APP_DEFAULT_CONFIG_FILE)) != 0) {
			return Application::EXIT_CONFIG;
		}
	}

	std::cout << "Hello World\n";
	return Application::EXIT_OK;
}

void
App::initialize(Application &self)
{
	loadConfiguration();
	Application::initialize(self);
}

void
App::uninitialize()
{
	Application::uninitialize();
}

void 
App::reinitialize(Application &self)
{
	Application::reinitialize(self);
}

void 
App::defineOptions(OptionSet &options)
{
	Application::defineOptions(options);
	options.addOption(
		Option("help", "h", "Display help")
			.required(false)
			.repeatable(false)
			.callback(OptionCallback<App>(this, &App::handleHelp))
	);
	options.addOption(
		Option("daemonize", "d", "Daemonize program")
			.required(false)
			.repeatable(false)
			.callback(OptionCallback<App>(this, &App::handleDaemonize))
	);
	options.addOption(
		Option("conf-file", "f", "Load configuration data from file")
			.required(false)
			.repeatable(true)
			.argument("json-file")
			.callback(OptionCallback<App>(this, &App::handleConfig))
	);
}

void 
App::handleHelp(const std::string &name, const std::string &value)
{
	_helpRequested = true;
	displayHelp();
	stopOptionsProcessing();
}

void 
App::handleConfig(const std::string &name, const std::string &value)
{
	loadConfigFile(value);
}

void 
App::handleDaemonize(const std::string &name, const std::string &value)
{
	_daemonize = true;
}

void 
App::displayHelp()
{
	HelpFormatter helpFormatter(options());
	helpFormatter.setCommand(commandName());
	helpFormatter.setUsage("OPTIONS");
	helpFormatter.format(std::cout);
}

int 
App::loadConfigFile(const std::string &filename)
{
	_pConfig = ConfigFactory::getConfigByFile(filename);
	return 0;
}


