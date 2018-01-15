<?php

namespace AJK;

class Kafka
{
	private static $instance = null;
	private $broker = null;
	private $topic = null;
	private function __construct($in_zk_endpoint = null, $in_topic = "test") {
		$zk = \AJK\Zookeeper::instance($in_zk_endpoint);
		$brokers = $zk->kafka_brokers();
		if(count($brokers) > 0) {
			$list = implode(",", $brokers);
			$this->broker = new \RdKafka\Producer();
			$this->broker->addBrokers($list);
			$this->topic = $this->broker->newTopic($in_topic);
		}
	}
	static public function instance($in_zkep = null, $in_topic = "test") {
		if(is_null(self::$instance)) {
			self::$instance = new \AJK\Kafka($in_zkep, $in_topic);
		}
		return self::$instance;
	}
	public function produce($in_msg, $in_part = RD_KAFKA_PARTITION_UA, $in_block = 0) {
		if(!is_null($this->topic)) {
			$this->topic->produce($in_part, 0, $in_msg);
			$this->broker->poll(0);
			while($in_block && $this->broker->getOutQLen() > 0) {
				$this->broker->poll($in_block);
			}
			return true;
		}
		return false;
	}
}

