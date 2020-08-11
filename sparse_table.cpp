class sparse_table {
private:
	int n, p;
	int (*func)(int, int);
	int* table;
	int* logbase2;

public:
	sparse_table(const std::vector <int>& v, int(*_func)(int, int)) : n(v.size()), func(_func) {
		logbase2 = new int[n+1];
		logbase2[0] = logbase2[1] = 0;
		for (int i = 2; i <= n; ++i) {
			logbase2[i] = logbase2[i/2]+1;
		}

		p = logbase2[n];

		table = new int[(p+1)*n];
		memcpy(table, &v[0], n*sizeof(int));

		for (int i = 1; i <= p; ++i) {
			int rng_len = (1<<i);
			for (int j = 0; j+rng_len <= n; ++j) {
				table[i*n + j] = func(table[(i-1)*n + j], table[(i-1)*n + j+(rng_len/2)]);
			}
		}
	}

	sparse_table(const std::vector <int>& v) : sparse_table(v, [](int x, int y) -> int {return std::min(x, y);}) {}

	sparse_table(const sparse_table& other) = delete;

	void operator= (const sparse_table& other) = delete;

	~sparse_table() {
		delete[] logbase2;
		delete[] table;
	}

	// [l, r]
	int query(int l, int r) const {
		int tpow = logbase2[r-l+1];
		return func(table[tpow*n + l], table[tpow*n + r - (1<<tpow) + 1]);
	}
};

