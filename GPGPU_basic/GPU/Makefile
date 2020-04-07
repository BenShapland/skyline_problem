.ONESHELL:

BINARIES = data cpu gpu
SCRIPTS = *.cpp *.hpp *.cu

data: 
	g++ data_generator.cpp -o data



cpu:
	g++ -Wall -O3 -std=c++17 -mavx -march=native -fopenmp solution_cpu.cpp -o cpu



gpu:
	nvcc -O3  solution_gpu.cu -o gpu


clean:
	rm $(BINARIES)


sterile: clean
	rm test-data.hpp






