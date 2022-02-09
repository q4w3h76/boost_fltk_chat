# boost_fltk_chat
How to compiled(You should install boost and FLTK):
```
git clone --recursive https://github.com/q4w3h76/boost_fltk_chat
cd boost_fltk_chat/boost_chat_server
mkdir build
cd build
cmake ..
cmake --build .
cd ../../boost_chat_client
mkdir build
cd build
cmake ..
cmake --build .
```
How to use:
1. Run server(located in the boost_chat_server/build)
2. In another terminals, run several clients(enter your name and IP of server, as arguments)
