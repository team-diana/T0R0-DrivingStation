all: delete download update compile

download:
	mkdir -p temp
	cd ${CURDIR}/temp && git clone https://github.com/team-diana/TcpSocket.git
	# DOWNLOAD COMPLETED

update:
	# Delete TcpServer inside ,main project folder and then update
	cd ${CURDIR}/../../ && rm -f TcpServer.h TcpServer.cpp
	cd ${CURDIR}/temp/TcpSocket/TcpServer && cp TcpServer.h ../../../../../TcpServer.h && cp TcpServer.cpp ../../../../../TcpServer.cpp
	# Delete TcpClient inside ,main project folder and then update
	cd ${CURDIR}/../../ && rm -f TcpClient.h TcpClient.cpp
	cd ${CURDIR}/temp/TcpSocket/TcpClient && cp TcpClient.h ../../../../../TcpClient.h && cp TcpClient.cpp ../../../../../TcpClient.cpp
	# Delete TcpServer inside TcpServerSimulator folder and then update
	cd ${CURDIR}/../TcpServerSimulator && rm -f TcpServer.h TcpServer.cpp
	cd ${CURDIR}/temp/TcpSocket/TcpServer && cp TcpServer.h ../../../../TcpServerSimulator/TcpServer.h && cp TcpServer.cpp ../../../../TcpServerSimulator/TcpServer.cpp
	# UPDATE ENDED

delete:
	cd ${CURDIR} && rm -rf temp
	# REMOVE TEMP FOLDER COMPLETED

compile:
	# Compile other tools
	cd ${CURDIR}/../TcpServerSimulator && make compile
	# COMPILE ENDED
