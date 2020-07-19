template <typename T> struct matrix {
private:
	int n;
	T* mat;
	const static T matrix_MOD = 1e9+7;

public:
	matrix(int num) : n(num), mat(new T[n*n]) {
		memset(mat, 0, n*n*sizeof(T));
	}

	matrix(std::initializer_list<T> l) : n(1) {
		while (n*n < l.size()) ++n;
		assert(l.size() == n*n);
		mat = new T[n*n];
		std::copy(l.begin(), l.end(), mat);
	}

	matrix(const std::vector <std::vector <T> >& v) : n(v.size()), mat(new T[n*n]) {
		for (int i = 0; i < n; ++i) {
			assert(v[i].size() == n);
			std::copy(v[i].begin(), v[i].end(), &mat[n*i]);
		}
	}

	~matrix() {
		delete[] mat;
	}

	T& get(int row, int col) {
		return (this->mat[row*n + col]);
	}

	void operator*= (matrix<T>& other) {
		T res[n][n];
		memset(res, 0, n*n*sizeof(T));
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				for (int k = 0; k < n; ++k) {
					res[i][j] += (this->mat[i*n + k] * other.get(k, j))%matrix_MOD;
					res[i][j] %= matrix_MOD;
				}
			}
		}
		memcpy(this->mat, res, n*n*sizeof(T));
	}

	void exp(long long int p) {
		matrix<T> res(n);
		for (int i = 0; i < n; ++i) res.get(i, i) = 1;
		for (p; p > 0; p >>= 1) {
			if (p&1) res *= *this;
			*this *= *this;
		}
		memcpy(this->mat, &res.get(0, 0), n*n*sizeof(T));
	}
};

