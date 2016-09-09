make: 
	@echo ""
	@echo "----Makefile Description----"
	@echo "all: for all versions"
	@echo "clean: to erase executables"
	@echo ""

all: main

main:
	g++ main.cpp -o peaks -lrt -ffast-math -std=c++11 -O3 


info:
	@echo ""
	@echo "$$ make (no_)post {PC/Pi2/Cust} {filename} {header lines}"
	@echo ""
	@echo "{filename} is required only for {Cust}"
	@echo "only input the name of the file without the file extension"
	@echo "This must be a file in the Test_Data folder and must be a .csv file"
	@echo ""
	@echo "{header_lines} is the number of lines at the top of te .csv to ignore"
	@echo ""

clean:
	-rm peaks
