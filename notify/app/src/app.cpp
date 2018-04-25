
#include <sstream>
#include <iostream>

#include <Poco/Util/Application.h>
#include <Poco/Util/Option.h>
#include <Poco/Util/OptionSet.h>
#include <Poco/Util/HelpFormatter.h>
#include <Poco/Util/AbstractConfiguration.h>
#include <Poco/AutoPtr.h>

#include "app.hpp"
#include "config/jsonconfig.hpp"

using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::HelpFormatter;
using Poco::Util::AbstractConfiguration;
using Poco::Util::OptionCallback;
using Poco::AutoPtr;

class App: public Application
{
private:
	bool _helpRequested;
	Config *_pConfig;

public:

	App(): 
		_helpRequested(false),
		_pConfig(0)
	{}

protected:

	void initialize(Application &self)
	{
		loadConfiguration();
		Application::initialize(self);
	}

	void uninitialize()
	{
		if(_pConfig) delete _pConfig;
		Application::uninitialize();
	}

	void reinitialize(Application &self)
	{
		Application::reinitialize(self);
	}

	void defineOptions(OptionSet &options)
	{
		Application::defineOptions(options);
		options.addOption(
			Option("help", "h", "Display help")
				.required(false)
				.repeatable(false)
				.callback(OptionCallback<App>(this, &App::handleHelp))
		);
		options.addOption(
			Option("conf-file", "f", "Load configuration data from file")
				.required(false)
				.repeatable(true)
				.argument("yaml-file")
				.callback(OptionCallback<App>(this, &App::handleConfig))
		);
	}

	void handleHelp(const std::string &name, const std::string &value)
	{
		_helpRequested = true;
		displayHelp();
		stopOptionsProcessing();
	}

	void handleConfig(const std::string &name, const std::string &value)
	{
		loadConfigFile(value);
	}

	void displayHelp()
	{
		HelpFormatter helpFormatter(options());
		helpFormatter.setCommand(commandName());
		helpFormatter.setUsage("OPTIONS");
		helpFormatter.setHeader("Kafka Notify");
		helpFormatter.format(std::cout);
	}

	int loadConfigFile(const std::string &file)
	{
		JsonConfig *p = new JsonConfig();
		if(p) {
			p->loadFromFile(file);
			_pConfig = p;
			return 0;
		}
		return -1;
	}

	int main(const ArgVec &args)
	{
		if(_helpRequested) {
			return Application::EXIT_OK;
		}

		if(!_pConfig) {
			if(loadConfigFile(std::string(APP_DEFAULT_CONFIG_FILE)) != 0) {
				return Application::EXIT_CONFIG;
			}
		}

		std::cout << "Hello World\n";
		return Application::EXIT_OK;

	}


};

POCO_APP_MAIN(App)


