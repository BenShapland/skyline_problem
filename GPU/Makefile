
.ONESHELL:

BINARIES = cpu gpuglobal gpuconstant gpuman gpushared
c_script = *.cpp *.hpp *.cu

N=5000
blocks=5
threads=1000
Script= ../run.sh

data: 
	cd data
	g++ data_generator.cpp -o data

gpuglobal:
	chmod +x $(Script)
	$(Script) $(N) $(blocks) $(threads) global_gpu_sol.cu
	nvcc -O3  global_gpu_sol.cu -o gpuglobal

gpuglobalbranch:
	chmod +x $(Script)
	$(Script) $(N) $(blocks) $(threads) global_gpu_sol_branch.cu
	nvcc -O3  global_gpu_sol_branch.cu -o gpuglobalbranch

gpuconstant:
	chmod +x $(Script)
	$(Script) $(N) $(blocks) $(threads) constant_gpu_sol.cu
	nvcc -O3  constant_gpu_sol.cu -o gpuconstant

gpuconstantbranch:
	chmod +x $(Script)
	$(Script) $(N) $(blocks) $(threads) constant_gpu_sol_branch.cu
	nvcc -O3  constant_gpu_sol_branch.cu -o gpuconstantbranch


gpuman:
	chmod +x $(Script)
	$(Script) $(N) $(blocks) $(threads) manhattan_gpu_sol.cu
	nvcc -O3 manhattan_gpu_sol.cu -o gpuman


gpushared:
	chmod +x $(Script)
	$(Script) $(N) $(blocks) $(threads) shared_gpu_sol.cu
	nvcc -O3  shared_gpu_sol.cu -o gpushared

test:
	chmod +x $(Script)
	$(Script) $(N) $(blocks) $(threads) test.cpp
	g++ -Wall -O3 -std=c++17 -mavx -march=native -fopenmp test.cpp -o test


clean:
	rm -f $(BINARIES)


