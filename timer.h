struct Timer {
	using namespace std;

	Timer() {
		startTimepoint = chrono::high_resolution_clock::now();
	}

	~Timer() {
		stop();
	}

	void stop() {
		auto endTimepoint = chrono::high_resolution_clock::now();

		auto start = chrono::time_point_cast<chrono::microseconds>(startTimepoint).time_since_epoch().count();
		auto end = chrono::time_point_cast<chrono::microseconds>(endTimepoint).time_since_epoch().count();

		auto duration = end - start;

		cout << duration*0.001 << " ms" << endl;
	}

private:
	chrono::time_point<chrono::high_resolution_clock> startTimepoint;
};

