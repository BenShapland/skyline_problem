.ONESHELL:

BINARIES = cpu gpuglobal gpuconstant gpuman gpushared
SCRIPTS = *.cpp *.hpp *.cu

data: 
	g++ data_generator.cpp -o data

cpu:
	g++ -Wall -O3 -std=c++17 -mavx -march=native -fopenmp solution_cpu.cpp -o cpu


gpuglobal:
	nvcc -O3  global_gpu_sol.cu -o gpuglobal


gpuconstant:
	nvcc -O3  constant_gpu_sol.cu -o gpuconstant


gpuman:
	nvcc -O3 manhattan_gpu_sol.cu -o gpuman


gpushared:
	nvcc -O3  shared_gpu_sol.cu -o gpushared


clean:
	rm $(BINARIES)


sterile: clean
	rm test-data.hpp






