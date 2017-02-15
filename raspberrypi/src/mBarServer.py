#!/usr/bin/python

import hashlib
import os.path
from os import urandom
import re
import signal
import socket
import sys
#import RPi.GPIO as GPIO

DEBUG = 1

'''
	We use a very simple protocol for communication:
	---------------------------------------------
	|	msg_type	|	msg_len		|	msg		|
	---------------------------------------------
	|	1 byte		|	2 bytes	    |	n bytes	|
	---------------------------------------------
'''

class NeXTGarageServer:

	#the keys to the dictionary are msg_type
	#the values are a 2-tuple: a string explaining
	#its function, and msg_len for this msg_type
	msg_types = {
					0 : ('makeDrink', 1), #client asks to connect
				}
	
	def __init__(self, portNumber):
		self.__portNumber = portNumber
		self.__listenSocket = None
		self.__clientSocket = None
		self.__clientAddress = None

		#register signal handler for nice cleanup
		signal.signal(signal.SIGINT, self.__cleanup)
	
	#return False if any errors were encountered
	def start(self):
		print "Starting microBar Server on port " + str(self.__portNumber) + "..."

		self.__listenSocket = socket.socket()
		self.__listenSocket.bind(('', self.__portNumber))

		self.__listenSocket.listen(0)

		#TODO: investigate if clientSocket needs to be explicity set to
		#blocking? socket documentation claims it is by default
		while True:
			self.__clientSocket, self.__clientAddress = self.__listenSocket.accept()
			self.__genericDebug("Got connection from " + self.__clientAddress[0] + ":" + str(self.__clientAddress[1]));
			

            #now handle client's requests
			self.__serveClient()

			#cleanup stuff associated with last client
			if(self.__clientSocket != None):
				self.__clientSocket.close()
			self.__clientSocket = None
			self.__clientAddress = None


	#serve client's requests until they quit or connection
	#is interrupted
	def __serveClient(self):
		cS = self.__clientSocket
		cA = self.__clientAddress

		while(True):
			msgType, msgLen, msg = self.__getMessage(cS, cA)
		
			#this means we read 0 bytes, so the socket has been closed	
			if(msgType == None):
				self.__genericDebug("Client " + cA[0] + " closed the connection")
				break
            
			#garage door status
			if msgType == 0:
				self.makeDrink(msg)

	def makeDrink(self,data):
		print "In make drink function..."
		print data
		if data == 1:
			print "recieved data of 0!"
            

    #TODO:	could make msg type a string instead? would be nicer
	#			for calling this and __sendMessage
	#get a message from the client
	#should return an int for msg type, int for msg length,
	#and bytearray for msg.  if only msg type is returned,
	#msg length was not sent correctly.  if only msg type and
	#msg length are returned, msg was not sent correctly.
	def __getMessage(self, clientSocket, clientAddress):

		tmp, bytesRead = self.__getBytes(clientSocket, 1)
		if(bytesRead != 1):
			return None, None, None

		msgType = tmp[0]
		
		tmp, bytesRead = self.__getBytes(clientSocket, 2)
		if(bytesRead != 2):
			return msgType, None, None

		msgLen = (tmp[0] << 8) | tmp[1]
		try:
			if(msgLen != self.msg_types[msgType][1]):
				return msgType, None, None
		except(KeyError):
			return msgType, None, None

		self.__debugGetMessage(msgType, msgLen, clientAddress)

		#just return a size 0 bytearray if msgLen == 0
		if(msgLen == 0):
			return msgType, msgLen, bytearray(0)

		msg, bytesRead = self.__getBytes(clientSocket, msgLen)

		if(bytesRead != msgLen):
			return msgType, msgLen, None

		return msgType, msgLen, msg[0]
	
	#send a message to client, msg is a bytearray
	def __sendMessage(self, clientSocket, clientAddress, msgType, msg):
	
		try:	
			msgLen = self.msg_types[msgType][1]
		except(KeyError):
			return -1

		#minimum size is 3
		toSend = bytearray(3 + msgLen)
		toSend[0] = msgType
		toSend[1] = (msgLen & 0xFF00) >> 8
		toSend[2] = (msgLen & 0x00FF)

		#copy msg in
		for i in range(0, msgLen):
			toSend[i + 3] = msg[i]

		bytesSent = self.__putBytes(clientSocket, toSend)

		self.__debugSendMessage(msgType, msgLen, clientAddress)

		return bytesSent

	#wrap Python's socket.recv to return bytearray, bytes read
	def __getBytes(self, clientSocket, numBytes):
		myList = bytearray(numBytes)
		myBuf = memoryview(myList)

		bytesRead = clientSocket.recv_into(myBuf, numBytes)
		return myList, bytesRead

	#wrap Python's socket.send to send bytearray, return bytes sent
	def __putBytes(self, clientSocket, toSend):
		bytesSent = clientSocket.send(toSend)
		return bytesSent

	#cleanup any open sockets
	def __cleanup(self, signal, frame):
		if(self.__clientSocket != None):
			self.__clientSocket.close()

		if(self.__listenSocket != None):
			self.__listenSocket.close()			

		#make sure we actually get out
		sys.exit(0)


	def __debugGetMessage(self, msgType, msgLen, clientAddress):
		if(DEBUG == 0):
			return

		sys.stdout.write("DEBUG:\t")
		try:
			sys.stdout.write("Got message of type " + self.msg_types[msgType][0]);
		except(KeyError):
			print "Got unknown message type (" + str(msgType) + ")"

		try:
			sys.stdout.write(" with")
			if(msgLen == self.msg_types[msgType][1]):
				sys.stdout.write(" length")
			else:
				sys.stdout.write(" incorrect length")
		except(KeyError):
			pass
			
		print " " + str(msgLen) + " from " + clientAddress[0] + ":" + str(clientAddress[1])

	def __debugSendMessage(self, msg_type, msg_len, clientAddress):
		if(DEBUG == 0):
			return
		sys.stdout.write("DEBUG:\t")
		print "Sent message of type " + self.msg_types[msg_type][0] + " with length " + str(msg_len) + " to " + clientAddress[0] + ":" + str(clientAddress[1])

	def __genericDebug(self, string):
		if(DEBUG == 0):
			return
		sys.stdout.write("DEBUG:\t")
		print string




a = NeXTGarageServer(int(sys.argv[1]))
a.start()
