template <typename T> class fenwickTree {
// Zero based Indexing
private:
	vector <T> ft;
	int N;
public:
	fenwickTree(vector <T>& v) {
		this->N = v.size();
		this->ft = vector <T> (N, 0);

		for (int i = 0; i<N; i++) {
			add(i, v[i]);
		}
	}

	void add(int idx, T del) {
		for (idx; idx<N; idx=(idx|(idx+1))) {
			ft[idx] += del;
		}
	}

	T sum(int idx) {
		idx = min(N-1, idx);
		T ans = 0;
		for (idx; idx>=0; idx=(idx&(idx+1))-1) {
			ans += ft[idx];
		}
		return ans;
	}

	T sum(int l, int r) {
		// number at index l NOT in sum
		return sum(r) - sum(l);
	}
};

