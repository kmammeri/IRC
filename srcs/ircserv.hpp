#pragma once

// using namespace std;
#define DEBUG

#define LEN_MAX	1024
#define QUEUE_MAX 5
#define SERVER_NAME "42irc"

enum ChannelMode {
	PUBLIC = 0,
	PRIVATE = 1,
	INVITE_ONLY = 2,
	PRIVATE_WITH_INVITE = 3,
};

enum StateServer {
	UP,
	DOWN
};