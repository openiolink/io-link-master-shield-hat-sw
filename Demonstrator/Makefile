.PHONY : all clean

all: Demonstrator

LIBS=-lwiringPi

ODIR=obj
_OBJ = BalluffBus0023.o BalluffBni0088.o Demonstrator_V1_0.o HardwareRaspberry.o IOLGenericDevice.o IOLMasterPort.o IOLMasterPortMax14819.o main.o Max14819.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

Demonstrator: $(OBJ)
	g++ -o $@.elf $^ $(LIBS)

$(ODIR)/%.o: src/%.cpp
	@mkdir -p $(ODIR)
	g++ -c -o $@ $<
clean:
	rm -rf $(ODIR)/*.o
	rm -rf Demonstrator
