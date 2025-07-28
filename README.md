📜 Overview
This project implements a simplified version of Shamir's Secret Sharing algorithm to reconstruct a secret from polynomial roots using Lagrange interpolation. Given n shares and a threshold k, the program finds the constant term (c) of the polynomial representing the secret.

The shares are provided in JSON format with values encoded in various bases. The program:

Parses the JSON input

Decodes share values from different bases

Uses all possible combinations of k shares from n to compute candidate secrets

Determines the most frequent secret to identify the correct one

Detects and reports corrupt/wrong shares that lead to inconsistent secrets

🚀 Features
Supports any base encoding for share values (up to base 36)

Uses Lagrange interpolation with modular arithmetic for secret recovery

Automatically identifies corrupt shares by analyzing all k-combinations

Reads input from JSON files to handle multiple test cases

Implemented in C++17 with the powerful nlohmann/json library for JSON parsing

🛠️ Getting Started
Prerequisites
C++17 compatible compiler (g++ recommended)

nlohmann/json single-header included in the project folder

MinGW or equivalent (for Windows users)

JSON test case files (provided)

Clone the repository
git clone https://github.com/yourusername/secret-sharing.git
cd secret-sharing
Compile
g++ -std=c++17 main.cpp -o secret
Run
./secret
The program will process the test cases (testcase1.json, testcase2.json) and print:

The correct secret for each test case

List of corrupt shares if any

📂 Repository Structure
Secret_Sharing/
│── main.cpp           # Main source code
│── json.hpp           # JSON parser header
│── testcase1.json     # Sample test case 1
│── testcase2.json     # Sample test case 2
│── README.md          # This file
🔍 How It Works
Input Parsing: Reads JSON files to extract n, k, and share data.

Decoding: Converts encoded share values from their respective bases to decimal under modulo arithmetic.

Combination Checking: Generates all combinations of k shares from n.

Secret Computation: Uses Lagrange interpolation to find the secret from each combination.

Majority Voting: Selects the secret with the highest frequency as the correct secret.

Corrupt Share Detection: Flags shares that never appear in any combination yielding the correct secret.

