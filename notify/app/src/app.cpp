
#include <sstream>
#include <iostream>

#include <Poco/Util/Application.h>
#include <Poco/Util/Option.h>
#include <Poco/Util/OptionSet.h>
#include <Poco/Util/HelpFormatter.h>
#include <Poco/Util/AbstractConfiguration.h>
#include <Poco/AutoPtr.h>

#include "app.hpp"

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
	bool _jsonConfigLoaded;

public:

	App(): 
		_helpRequested(false),
		_jsonConfigLoaded(false)
	{}

protected:

	void initialize(Application &self)
	{
		loadConfiguration();
		Application::initialize(self);
	}

	void uninitialize()
	{
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
		if(loadJsonConfigFile(value) == 0) {
			_jsonConfigLoaded = true;
		}
	}

	void displayHelp()
	{
		HelpFormatter helpFormatter(options());
		helpFormatter.setCommand(commandName());
		helpFormatter.setUsage("OPTIONS");
		helpFormatter.setHeader("Kafka Notify");
		helpFormatter.format(std::cout);
	}

	int loadJsonConfigFile(const std::string &file)
	{
		return 0;
	}

	int main(const ArgVec &args)
	{
		if(_helpRequested) {
			return Application::EXIT_OK;
		}

		if(!_jsonConfigLoaded) {
			if(loadJsonConfigFile(std::string(APP_DEFAULT_CONFIG_FILE)) != 0) {
				return Application::EXIT_CONFIG;
			}
		}

		std::cout << "Hello World\n";
		return Application::EXIT_OK;

	}


};

POCO_APP_MAIN(App)


