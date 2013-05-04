mkdir build -p

g++ -o build/client ola-client.cpp $(pkg-config --cflags --libs libola)

g++ -o build/monitor ola-monitor.cpp $(pkg-config --cflags --libs libola)
