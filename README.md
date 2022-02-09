# boost_fltk_chat
How to compiled:
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
2. In another terminals, run several clients

While there are problems client completion(returned Aborted core dumped) and I don't know, they will be solved
