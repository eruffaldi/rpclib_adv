


# Registry

The rpccore provides a service for registering services with a simple approach: just a string. Only one service is registered associating ip address and port.

registerService
unregisterService
lookupService
listServices

TODO:
- environment spec of the port and IP, like in ROS
- change in rpclib to support change of state in server-client on server side

Note: ROS uses the term api to specify the URI. In our case the URI is tcp://address:port or simply (address,port)

# Publisher Subscriber (TODO)
http://wiki.ros.org/ROS/Slave_API
http://wiki.ros.org/ROS/Technical%20Overview

Protocol on each client:
	publisherUpdate topic publishers (invoked by master)
	requestTopic topic protocols (requested by subscriber)
	getPublications
	getSubscriptions
	getBusInfo
	getBusStats

Protocol on core:
	registerSubscriber topic topictype callerapi
	unregisterSubscriber topic callerapi
	registerPublisher
	unregisterPublisher
	getPublishedTopics
	getTopicTypes
	getSystemState

Protocol of Publisher to Subscriber: the subscriber is a server that is invoked on a given (even anonymous) callback without response:
	rpc::this_handler().disable_response()


# Parameter Server (TODO)
http://wiki.ros.org/ROS/Parameter%20Server%20API

Client:
	paramUpdate key value

Server:
	deleteParam
	setParam
	getParam
	searchParam
	subscribeParam
	unsubscribeParam
	hasParam
	getParamNames

# Additional Services a-la ROS (TODO)
http://wiki.ros.org/ROS/Master_API

Client:
	shutdown of client
	getpid
	getMasterUri

Master:
	lookupNode
	getUri

