#!/usr/bin/env python
import msgpackrpc

client = msgpackrpc.Client(msgpackrpc.Address("127.0.0.1", 12345))
print client.call("listServices")

