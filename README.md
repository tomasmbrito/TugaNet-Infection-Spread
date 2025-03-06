# TugaNet-Infection-Spread
Graph-based analysis to determine the maximum infection spread in a social network.

# TugaNet Infection Spread 🦠🔗

This project implements an algorithm to analyze the spread of an infection through the **TugaNet** social network, calculating the worst-case scenario by determining the longest possible chain of transmissions between individuals.

The solution was developed in **C++** as part of the **Algorithm Analysis and Design** course at **Instituto Superior Técnico (IST)**.

---

## 🧩 Problem Overview

To simulate the spread of a disease, we model the TugaNet network as a **directed graph** where:
- Nodes represent individuals.
- Edges represent directed relationships (i.e., person `x` knows person `y`).

The goal is to calculate the **maximum number of hops** a disease can make through the network, assuming that direct or indirect contact results in immediate infection.

---

## 🚀 Features

- Efficient graph traversal to handle directed and potentially cyclic graphs.
- Longest path computation to determine the maximum infection chain.
- Iterative algorithm to avoid stack overflow in large datasets.

---

## 📥 Input

The program reads from standard input:
1. Two integers `n` and `m`, representing the number of individuals and the number of relationships.
2. `m` lines with two integers each, where `x y` means person `x` knows person `y`.

### Example:

<img width="288" alt="image" src="https://github.com/user-attachments/assets/bb53803a-93ab-46ea-9310-6260f7ab6b79" />

input:
```
7 8
3 4
3 2
4 6
4 5
6 2
6 5
5 7
2 7
```

---

## 📤 Output

The program outputs a single integer: the maximum number of hops a disease can take through the network.

### Example:
```
4
```

---

## ⚙️ How to Run

### Compile:
```bash
g++ -std=c++11 -O3 -Wall tuga_net.cpp -o tuga_net
```

### Execute:
```bash
./tuga_net < input.txt
```

---

## 🧰 Technologies

- **Language:** C++
- **Libraries:** Standard Template Library (`vector`, `queue`, etc.) for graph representation and traversal.

  
