all: compile run

compile:
	mkdir -p build
	cd ${CURDIR}/build && cmake .. && make

run:
	cd ${CURDIR}/build && ./TcpServerSimulator
