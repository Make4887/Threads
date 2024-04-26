#include <iostream>
#include <thread>
#include <shared_mutex>

std::shared_mutex mtx;
int value = 0;

void Write() {
    for (int i = 0; i < 10; i++) {
        std::unique_lock lock(mtx);
        value = i;
        std::cout << "Write: " << value << std::endl;
        lock.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void Read() {
    for (int i = 0; i < 10; i++) {
        std::shared_lock lock(mtx);
        std::cout << "Read: " << value << std::endl;
        lock.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int main() {
    std::thread write(Write);
    std::thread read(Read);

    write.join();
    read.join();

    return 0;
}
