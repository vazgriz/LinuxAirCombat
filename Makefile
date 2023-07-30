OBJS=3ds.o aiobject.o audio.o cockpit.o common.o conf.o dirs.o effects.o fileloader.o FlightModel.o gl.o glland.o land.o loader_tga.o main.o mathtab.o menu.o mission.o model.o NetworkApi.o object.o objload.o pilots.o vertexarray.o

CXX=g++ -Ofast -g0 -fPIE

LIBS= -lglut -lGLU -lSDL -lSDL_mixer -L/lib64 -lGL

Lac09p15: $(OBJS)
	mkdir -p ~/.LAC
	cp DefaultHeightMap.LAC ~/.LAC/DefaultHeightMap.LAC 
	g++ -o Lac09p15 $(LIBS) $(OBJS)
	cp Lac09p15 bin/Release/Lac09p15
	chmod +x bin/Release/Lac09p15
clean:
	@rm -f *.o
	@rm -f Lac09p15
