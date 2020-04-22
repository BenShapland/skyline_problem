.ONESHELL:


parallel:
	chmod +x benchmark.sh
	g++ -Wall -O3 -std=c++17 -mavx -march=native -fopenmp parallel_solution.cpp -o parallel

parallelperf:
	chmod +x benchmark.sh
	g++ -Wall -O3 -std=c++17 -mavx -march=native -fopenmp parallel_solution_perf.cpp -o parallelperf

clean:
	rm parallel