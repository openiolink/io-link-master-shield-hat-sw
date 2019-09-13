.PHONY : all clean

all: Demonstrator

Demonstrator:	BallufBus0023.o BalluffBni0088.o Demonstrator_V1_0.o HardwareRaspberry.o IOLGenericDevice.o IOLMasterPort.o IOLMasterPortMax14819.o main.o Max14819.o
	g++ -o $@ $^ -lwiringPi

BallufBus0023.o: BallufBus0023.cpp

BalluffBni0088.o: BalluffBni0088.cpp

Demonstrator_V1_0.o: Demonstrator_V1_0.cpp

HardwareRaspberry.o: HardwareRaspberry.cpp

IOLGenericDevice.o: IOLGenericDevice.cpp

IOLMasterPort.o: IOLMasterPort.cpp

IOLMasterPortMax14819.o: IOLMasterPortMax14819.cpp

main.o: main.cpp

Max14819.o: Max14819.cpp

clean:
	rm -rf *.o
	rm -rf Demonstrator
