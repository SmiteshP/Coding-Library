struct segment_data {
	int val;

	segment_data() : val(0) {}
	segment_data(int num) : val(num) {}

	static segment_data combine(const segment_data& a, const segment_data& b) {
		return segment_data(a.val+b.val);
	}
};

// Range update, Point query
class segment_tree {
private:
	int size;
	segment_data* st;

	void push_updates() {
		for (int i = 1; i < size; ++i) {
			st[i<<1] = segment_data::combine(st[i<<1], st[i]);
			st[i<<1|1] = segment_data::combine(st[i<<1|1], st[i]);
			st[i] = segment_data();
		}
	}

public:
	segment_tree(std::vector<segment_data>& v) : size(v.size()), st(new segment_data[2*size]) {
		std::copy(v.begin(), v.end(), st+size);
	}

	segment_tree(const segment_tree& other) : size(other.size), st(new segment_data[2*size]) {
		memcpy(st, other.st, 2*size*sizeof(segment_data));
	}

	segment_tree operator= (const segment_tree& other) = delete;

	~segment_tree() {
		delete[] st;
	}

	void update(int l, int r, const segment_data& val) {
		for (l += size, r += size; l < r; l >>= 1, r >>= 1) {
			if (l&1) st[l++] = segment_data::combine(st[l], val);
			if (r&1) st[r] = segment_data::combine(val, st[--r]);
		}
	}

	segment_data query(int idx) {
		segment_data ans;
		for (idx += size; idx > 0; idx >>= 1) ans = segment_data::combine(ans, st[idx]);
		return ans;
	}

	segment_data* inspect() {
		push_updates();
		return &st[size];
	}
};

