# asteroids
Asteroids with C++ and SFML

<br/>
<img src="https://i.postimg.cc/K8BhSrds/asteroids.jpg" />
<br/>

How to start:
1. **`python -m pip install -U pip`**
2. **`pip install --force-reinstall -v "conan==1.59.0"`**

3. **`mkdir build`**
4. **`cd build`**

5. For latest MSVC compiler:
    - Debug:
        - **`conan install .. -s compiler.version=17 -s compiler.toolset=v143 --build=missing -s build_type=Debug`**
    - Release:
        - **`conan install .. -s compiler.version=17 -s compiler.toolset=v143 --build=missing -s build_type=Release`**

   For default installation:
    - Debug:
        - **`conan install .. --build=missing -s build_type=Debug`**
    - Release:
        - **`conan install .. --build=missing -s build_type=Release`**

6. **`cmake build -S ..`**
