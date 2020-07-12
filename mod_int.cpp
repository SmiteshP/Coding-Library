// Using int and mod operations instead will be 2-3 times faster
template <typename T = int> class mInt {
private:
	T val;

public:
	static const T MOD = 1e9+7;

	mInt() : val(0) {}

	mInt(T n) : val((n%MOD+MOD)%MOD) {}

	inline mInt operator+ (const mInt<T>& other) const {
		return (this->val + other.val)%MOD;
	}

	inline mInt operator- (const mInt<T>& other) const {
		return ((this->val - other.val)%MOD + MOD)%MOD;
	}

	inline mInt operator* (const mInt<T>& other) const {
		return (this->val * other.val)%MOD;
	}

	inline mInt operator/ (const mInt<T>& denominator) const {
		return (*this) * denominator.mmi();
	}

	inline mInt& operator= (T n) {
		this->val = (n%MOD + MOD)%MOD;
		return *this;
	}

	inline mInt& operator= (const mInt<T>& other) {
		this->val = other.val;
		return *this;
	}

	inline bool operator== (T n) const {
		return this->val == n;
	}

	inline bool operator== (mInt<T>& other) const {
		return this->val == other.val;
	}

	inline bool operator!= (T n) const {
		return this->val != n;
	}

	inline bool operator!= (mInt<T>& other) const {
		return this->val != other.val;
	}

	inline bool operator< (T n) const {
		return this->val < n;
	}

	inline bool operator< (mInt<T>& other) const {
		return this->val < other.val;
	}

	inline bool operator> (T n) const {
		return this->val > n;
	}

	inline bool operator> (mInt<T>& other) const {
		return this->val > other.val;
	}

	inline bool operator<= (T n) const {
		return this->val <= n;
	}

	inline bool operator<= (mInt<T>& other) const {
		return this->val <= other.val;
	}

	inline bool operator>= (T n) const {
		return this->val >= n;
	}

	inline bool operator>= (mInt<T>& other) const {
		return this->val >= other.val;
	}

	inline friend std::ostream& operator<<(std::ostream& os, mInt<T> a) {
		os << a.val;
		return os;
	}

	inline friend std::istream& operator>>(std::istream& is, mInt<T>& a) {
		is >> a.val;
		return is;
	}

	mInt exp(int p) const {
		int ans = 1;
		T x = this->val;

		if (x == 0) return 0;

		while (p > 0) {
			if (p&1) {
				ans = (ans*x)%MOD;
			}

			p /= 2;
			x = (x*x)%MOD;
		}

		return mInt(ans);
	}

	// Modular multiplicative inverse
	// Extended Euclid algoritm - a and MOD must be coprime;
	mInt mmi() const {
		T a = this->val;
		T m = MOD;
		T y = 0;
		T x = 1;

		if (MOD == 1) return mInt(0);

		while (a > 1) {
			T q = a/m;
			T t = m;

			m = a%m;
			a = t;
			t = y;

			y = x - q*y;
			x = t;
		}

		if (x < 0) {
			x += MOD;
		}

		return mInt(x);
	}
};

