# asteroids
Asteroids with C++ and SFML

<br/>
<img src="https://i.postimg.cc/K8BhSrds/asteroids.jpg" />
<br/>

How to run:
- **mkdir build**
- **cd build**
- **pip install conan**
- **conan install .. [-s build_type={Debug | Release}]**
- **cmake build -S ..**

*For latest MSVC compiler:
- **conan install .. [-s build_type={Debug | Release}] -s compiler.version=17 --build=missing**
