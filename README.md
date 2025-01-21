# PDE_Pricer

This project is an **options pricer** developed in C++. It uses the **explicit finite difference method** to solve partial differential equations (PDEs) and compute the prices of various options, including both vanilla and exotic ones.

## Features
- **Vanilla options:**
  - European Call
  - European Put
- **Exotic options:**
  - Asset-Or-Nothing Call
  - Barrier Knock-Out Call

## Compilation and Execution
### Compilation
To compile the pricer, run the following command in your terminal:
```bash
g++ -std=c++11 Pricer.cpp src/Payoff.cpp src/Option.cpp src/EDP.cpp src/MDF.cpp -o Pricer
```
### Execution
To run the pricer, use the command:
```bash
./Pricer
```
The results will be displayed in the terminal and also exported as CSV files in the output/ folder. These files contain the results for each time and space step.

## Vizualisation of Results
The project includes Python scripts to generate graphs from the results produced by the pricer. To run the scripts, use the following commands:
- **European Call:**
```bash
python python_scripts/Call.py
```
- **European Put:**
```bash
python python_scripts/Put.py
```
- **Asset-Or-Nothing Call:**
```bash
python python_scripts/AssetOrNothing.py
```
- **Barrier Knock-Out Call:**
```bash
python python_scripts/Barrier_CallKO.py
```

## Project Structure
- `src/` : Contains the C++ source files for the pricer.
- `output/` : Contains the CSV files generated after execution.
- `python_scripts/` : Contains Python scripts for visualizing the results.
- `Pricer.cpp` : The main file to execute the pricer.

## Requirements
- **C++ compiler :** `g++` or equivalent (supporting `-std=c++11`).
- **Python3.x :** With the following libraries installed:
  - `matplotlib`
  - `numpy`
  - `pandas`
You can install these libraries using:
```bash
pip install matplotlib numpy pandas
```

## Authors
This project was developed by Samuel Alvarez, Simon Duong, and Lucas Leproult, students at ENSAE.
