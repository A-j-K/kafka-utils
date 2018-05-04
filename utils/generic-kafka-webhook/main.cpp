
#include <iostream>

#include "curler.hpp"
#include "kafka_conf.hpp"
#include "config/config_factory.hpp"

int
main(int argc, char *argv[])
{
	int rval = 0;
	Curler::ShPtr spCurler;
	RdKafka::Conf *pKafkaConf = 0;
	AbstractConfig::ShPtr spConfig;

	Curler::startup();
	try {
		spConfig = ConfigFactory::getConfigByFile(std::string("/etc/notifier.json"));
		spCurler = Curler::ShPtr(new Curler(spConfig));
		pKafkaConf = KafkaConf::get(spConfig.get(), 0);
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

