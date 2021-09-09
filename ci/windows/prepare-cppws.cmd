@echo off
SETLOCAL EnableDelayedExpansion

REM If websocketpp directory does not exist, clone the git repo
if not exist %CPPWSPath% (
	echo websocketpp directory does not exist
	git clone --recursive https://github.com/zaphoyd/websocketpp --branch 0.8.2 %CPPWSPath%
)

REM If asio directory does not exist, clone the git repo
if not exist %AsioPath% (
	echo asio directory does not exist
	git clone --recursive https://github.com/chriskohlhoff/asio --branch asio-1-19-2 %AsioPath%
)
