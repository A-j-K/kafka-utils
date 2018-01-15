<?php

namespace AJK;

class Zookeeper
{
	private static $instance = null;
	private $zoo = null;
	private $endpoint = null;
	private function __construct($in_endpoint = null) {
		if(defined("ZOOKEEPER_ENDPOINT")) $zkep = ZOOKEEPER_ENDPOINT;
		else $zkep = getenv("ZOOKEEPER_ENDPOINT");
		$this->endpoint = $zkep === false ? $in_endpoint : $zkep;
		if(!is_null($this->endpoint)) {
			$this->zoo = new \Zookeeper($this->endpoint);
		}
		else {
			throw new \Exception("Invalid Zookeeper endpoint");
		}
	}
	static public function instance($in_endpoint = null) {
		if(is_null(self::$instance)) {
			self::$instance = new \AJK\Zookeeper($in_endpoint);
		}
		return self::$instance;
	}
	public function kafka_brokers() {
		$brokers = array();
		if(!is_object($this->zoo)) {
			return $brokers;
		}
		$children = $this->zoo->getchildren("/brokers/ids");
		foreach($children as $key => $id) {
			$result = $this->zoo->get("/brokers/ids/$id");
			$arr = json_decode($result, true);
			if(isset($arr['host']) && isset($arr['port'])) {
				$brokers[] = $arr['host'].':'.$arr['port'];
			}
			return $brokers;
		}
	}
}

