 Copyright @ Nathan Greenfield
 
# CS20A P05 - Fall 2025 #

## Student information... ##
Name: Mayssa  Boughazi

Email: BOUGHAZI_MAYSSA@STUDENT.SMC.EDU

Platform: PC

### Notes ###

 # Assignment Build & Test Script

This repository contains the build and test automation script provided for **CS Assignment 5**.  
The original template and testing setup were created by **Professor Nathan Greenfield** (see copyright in the script).  

---

## 📌 About the Program
The script is a **bash automation tool** that:
1. **Downloads graded test files** from Google Drive.  
2. **Extracts** the files into the working directory.  
3. **Configures the project** using `cmake` with `clang` and `clang++`.  
4. **Compiles the code** inside a `build/` directory.  
5. **Runs the graded tests** with a timeout to ensure execution doesn’t hang.  

This process ensures that student submissions are automatically built and tested in a consistent environment.

---

## 🛠️ How It Works
- `wget ... -O p5.tar.gz` → Downloads the test archive.  
- `tar xzf p5.tar.gz` → Extracts the tests.  
- `mkdir build && cd build` → Creates a build folder for compilation.  
- `CC=clang CXX=clang++ cmake ..` → Configures the project with Clang.  
- `make` → Compiles the project.  
- `timeout 30 build/tests/tests [graded] -r=github` → Runs the test suite with a 30-second limit.  

---

## ✍️ My Contributions
While the test script was provided by the professor, my contributions involve:  
- Implementing the required C++ code that the script builds and tests.  
- Debugging and ensuring my program passes all provided test cases.  
- Learning how to use `cmake`, `make`, and bash scripting in a real project workflow.  

---

⚠️ **Note:** This repository includes educational material and automation scripts originally authored by Professor Nathan Greenfield.  
I am sharing my completed version here for learning and portfolio purposes.  
