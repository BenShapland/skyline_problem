.ONESHELL:

BINARIES = cpu gpuglobal gpuconstant gpuman gpushared
c_script = *.cpp *.hpp *.cu

N=5000
blocks=5
threads=1000
Script= ../run.sh

data: 
	g++ data_generator.cpp -o data

cpu:
	g++ -Wall -O3 -std=c++17 -mavx -march=native -fopenmp solution_cpu.cpp -o cpu


gpuglobal:
	$(Script) $(N) $(blocks) $(threads) global_gpu_sol.cu
	nvcc -O3  global_gpu_sol.cu -o gpuglobal


gpuconstant:
	$(Script) $(N) $(blocks) $(threads) constant_gpu_sol.cu
	nvcc -O3  constant_gpu_sol.cu -o gpuconstant


gpuman:
	$(Script) $(N) $(blocks) $(threads) manhattan_gpu_sol.cu
	nvcc -O3 manhattan_gpu_sol.cu -o gpuman


gpushared:
	$(Script) $(N) $(blocks) $(threads) shared_gpu_sol.cu
	nvcc -O3  shared_gpu_sol.cu -o gpushared


test:
	$(Script) $(N) $(blocks) $(threads) test.cu
	nvcc -O3  test.cu -o test


clean:
	rm $(BINARIES)





