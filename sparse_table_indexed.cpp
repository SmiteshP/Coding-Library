class sparse_table {
private:
	int n, p;
	int* data;
	int* index_table;
	int* logbase2;

	int func(int x, int y) const {
		if (data[x] <= data[y]) {
			return x;
		} else {
			return y;
		}
	}

public:
	sparse_table(const std::vector <int>& v) : n(v.size()) {
		logbase2 = new int[n+1];
		logbase2[0] = logbase2[1] = 0;
		for (int i = 2; i <= n; ++i) {
			logbase2[i] = logbase2[i/2]+1;
		}

		p = logbase2[n];

		data = new int[n];
		memcpy(data, &v[0], n*sizeof(int));

		index_table = new int[(p+1)*n];
		std::iota(index_table, index_table+n, 0);

		for (int i = 1; i <= p; ++i) {
			int rng_len = (1<<i);
			for (int j = 0; j+rng_len <= n; ++j) {
				index_table[i*n + j] = func(index_table[(i-1)*n + j], index_table[(i-1)*n + j+(rng_len/2)]);
			}
		}
	}

	sparse_table(const sparse_table& other) = delete;

	void operator= (const sparse_table& other) = delete;

	~sparse_table() {
		delete[] logbase2;
		delete[] index_table;
		delete[] data;
	}

	// [l, r]
	int queryIndex(int l, int r) const {
		int tpow = logbase2[r-l+1];
		return func(index_table[tpow*n + l], index_table[tpow*n + r - (1<<tpow) + 1]);
	}

	int queryData(int l, int r) const {
		return data[queryIndex(l, r)];
	}
};

