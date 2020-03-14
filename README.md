# skyline_problem
[Pareto optimality](https://en.wikipedia.org/wiki/Pareto_efficiency) is a concept that originated in Economics to describe a game theoretic strategy that *dominates* all alternatives; i.e., no matter the circumstances, it is the best choice. Many data analysis tasks can also be thought of as game theoretic; e.g., selecting a product from an online shop/aggregator (such as Amazon or Skyscanner) is a game theoretic problem of determining the best trade-off of quality and price relative to an adversary (the retailer or service provider) who is also involved in the transaction but has the opposing pay-off. [The skyline problem](http://delab.csd.auth.gr/papers/IISA2015tpm.pdf) is to select all the points from a dataset that offer the maximisation of *some* trade-off. Depending on the amount of correlation in the data, it can reduce reduce a dataset to just a few points or only by half.

Interm Report 1 - editable from link
https://docs.google.com/document/d/1wsWvpQUKmiKB0Odzt9YEmOPK0mVC1a3SuqWjgiESaeM/edit?usp=sharing

Interm Report 2 - editable from link
https://docs.google.com/document/d/1zMy0XRLxMfB9fp2gygNS8Z-aWCYBne-WlXbtq5mYruY/edit?usp=sharing

BAD copy:
https://docs.google.com/document/d/1YMiDLCQd3QnpE150zXRuKwICiOqGe3Sxm3DOrDqNndQ/edit?usp=sharing

AoS

    Node.h
    solution.hpp
    bechmarking.cpp 
    timing.hpp
    original_node.cpp
  

SoA-hot_and_cold_data_split

    Node.h
    solution.hpp
    bechmarking.cpp 
    timing.hpp
    original_node.cpp


Usage:
```
    cd AoS OR
    cd hot_and_cold_data_split 
    g++ -Wall -Og -std=c++17 benchmarking.cpp -o bench 
    ./bench
```
