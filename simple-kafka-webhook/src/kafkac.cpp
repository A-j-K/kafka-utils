
#include <stdio.h>
#include <sys/time.h>

#include "kafka.hpp"
#include "kafkac.hpp"

#ifdef __cplusplus
extern "C" {
#endif

void kafka_logger(const rd_kafka_t *pkafka, int level, 
	const char *pfacility, const char *pbuf)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	fprintf(stdout, "%u.%03u RDKAFKA-%i-%s: %s: %s\n",
		(int)tv.tv_sec, (int)(tv.tv_usec / 1000),
		level, pfacility, rd_kafka_name(pkafka), pbuf);
}

void 
kafka_rebalance(rd_kafka_t *pKafka,
	rd_kafka_resp_err_t err,
	rd_kafka_topic_partition_list_t *ppartitions,
	void *popaque)
{
	Kafka *pKafkaClass = reinterpret_cast<Kafka*>(popaque);
	switch(err) {
	case RD_KAFKA_RESP_ERR__ASSIGN_PARTITIONS:
		fprintf(stdout, "Consumer group rebalanced: assigned\n");
		rd_kafka_assign(pKafka, ppartitions);
		pKafkaClass->setWaitEof(
			pKafkaClass->getWaitEof() + ppartitions->cnt);
		break;
	case RD_KAFKA_RESP_ERR__REVOKE_PARTITIONS:
		fprintf(stdout, "Consumer group rebalanced: revoked\n");
		rd_kafka_assign(pKafka, NULL);
		pKafkaClass->setWaitEof(0);
		break;
	default:
		fprintf(stdout, "Consumer group rebalanced: failed: %s\n",
			rd_kafka_err2str(err));
		rd_kafka_assign(pKafka, NULL);
		break;
	}
}

#ifdef __cplusplus
}
#endif

