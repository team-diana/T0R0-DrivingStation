all: compile run

compile:
	mkdir build
	cd ${CURDIR}/build && cmake .. && make

run:
	cd ${CURDIR}/build/bin && ./TcpServerSimulator
