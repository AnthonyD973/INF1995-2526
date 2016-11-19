
.PHONY: all clean

PRJNAME:=gas
PRJSRC:=main.cpp gas.cpp
GENDIR:=build
SRCDIR:=.
INC=.

OBJDEPS:=$(patsubst %.cpp,$(GENDIR)/%.o,$(strip $(filter %.cpp, $(PRJSRC))))

all: $(GENDIR) $(OBJDEPS)
	g++ -lm -I. -o $(PRJNAME) $(OBJDEPS) -std=c++11 -Wall

clean:
	rm -rf $(GENDIR)
	rm -rf $(PRJNAME)

# +----------------+
# | AUTRES TARGETS |
# +----------------+

$(GENDIR):
	mkdir $(GENDIR)

# Production des fichiers objet
# De C++ à objet
$(GENDIR)/%.o: $(SRCDIR)/%.cpp $(GENDIR)
	g++ -I. -o $@ -c $< -std=c++11 -Wall