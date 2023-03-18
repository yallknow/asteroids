# asteroids
Asteroids with C++ and SFML

<br/>
<img src="https://i.postimg.cc/K8BhSrds/asteroids.jpg" />
<br/>

How to run:
- **python -m pip install -U pip**
- **pip install --force-reinstall -v "conan==1.59.0"**

- **mkdir build**
- **cd build**

- **conan install .. [-s build_type={Debug | Release}]**
- **cmake build -S ..**

*For latest MSVC compiler:
- **conan install .. -s compiler.version=17 -s compiler.toolset=v143 --build=missing [-s build_type={Debug | Release}]**
