struct Timer {
	Timer() {
		startTimepoint = std::chrono::high_resolution_clock::now();
	}

	~Timer() {
		stop();
	}

	void stop() {
		auto endTimepoint = std::chrono::high_resolution_clock::now();

		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(startTimepoint).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

		auto duration = end - start;

		std::cout << duration*0.001 << " ms" << std::endl;
	}

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> startTimepoint;
};

