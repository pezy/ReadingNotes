#include <iostream>
#include <thread>

void hello()
{
	while (1)
		std::cout << "Hello, Corrent world!" << std::endl;
}

int main()
{
	std::thread t(hello);
	t.join();
}