
.PHONY: clean

PRJNAME:=gas
PRJSRC:=main.cpp gas.cpp
GENDIR:=build
SRCDIR:=.

OBJDEPS:=$(patsubst %.cpp,$(GENDIR)/%.o,$(strip $(filter %.cpp, $(PRJSRC))))

all: $(GENDIR) $(OBJDEPS)
	g++ -o $(PRJNAME) $(OBJDEPS) -std=c++11 -Wall

# Pour tester GAS, effectuer la commande suivante:
# $ make && ./gas input.txt output.txt; hexdump output.txt -v -e '/1 "%02X "'; echo

clean:
	rm -rf $(GENDIR)
	rm -rf $(PRJNAME)

# +----------------+
# | AUTRES TARGETS |
# +----------------+

$(GENDIR):
	mkdir $(GENDIR)

$(GENDIR)/%.o: $(SRCDIR)/%.cpp $(GENDIR)
	g++ -o $@ -c $< -std=c++11 -Wall

docs:
	doxygen doxygen/Doxyfile
	rm -rf doxygen/latex/