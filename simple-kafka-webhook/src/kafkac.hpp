#pragma once

/*****************************************
Defines the pure C librdkafka callbacks.
*****************************************/

#include <librdkafka/rdkafka.h>

#ifdef __cplusplus
extern "C" {
#endif

void kafka_logger(const rd_kafka_t *pkafka, int level, 
	const char *pfacility, const char *pbuf);

void 
kafka_rebalance(rd_kafka_t *pKafka,
	rd_kafka_resp_err_t err,
	rd_kafka_topic_partition_list_t *ppartitions,
	void *popaque);

#ifdef __cplusplus
}
#endif

