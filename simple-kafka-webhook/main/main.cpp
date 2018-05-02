
#include <iostream>

#include "kafka.hpp"
#include "curler.hpp"
#include "config/config_factory.hpp"

int
main(int argc, char *argv[])
{
	int rval = 0;
	Kafka::ShPtr spKafka;
	Curler::ShPtr spCurler;
	AbstractConfig::ShPtr spConfig;

	Curler::startup();
	try {
		spConfig = ConfigFactory::getConfigByFile(std::string("/etc/notifier.json"));
		spCurler = Curler::ShPtr(new Curler(spConfig));
		//spKafka  = Kafka::ShPtr(new Kafka(spConfig, spCurler));
		//spKafka->run();
	}
	catch(std::exception e) {
		std::cout << e.what();
		rval = -1;
	}
	Curler::shutdown();
	return rval;
}

