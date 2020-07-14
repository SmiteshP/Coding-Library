struct segment_data {
	int val;

	segment_data() : val(0) {}
	segment_data(int num) : val(num) {}

	static segment_data combine(const segment_data& a, const segment_data& b) {
		return segment_data(a.val+b.val);
	}
};

class segment_tree {
private:
	segment_data* st = nullptr;
	int size;
public:
	segment_tree(std::vector<segment_data>& v) {
		size = v.size();

		st = new segment_data[2*size];
		std::copy(v.begin(), v.end(), st+size);

		for (int i = size-1; i > 0; i--) {
			st[i] = segment_data::combine(st[2*i], st[2*i+1]);
		}
	}

	segment_tree(const segment_tree& other) : size(other.size) {
		st = new segment_data[2*size];
		memcpy(st, other.st, 2*size*sizeof(segment_data));
	}

	segment_tree operator= (const segment_tree& other) = delete;

	~segment_tree() {
		delete[] st;
	}

	void update(int idx, const segment_data& val) {
		idx += size;
		st[idx] = val;
		idx >>= 1;
		for (idx; idx > 0; idx >>= 1) {
			st[idx] = segment_data::combine(st[idx<<1], st[idx<<1|1]);
		}
	}

	segment_data query(int l, int r) const {
		segment_data ans_l, ans_r;
		for (l += size, r += size; l < r; l >>= 1, r >>= 1) {
			if (l&1) ans_l = segment_data::combine(ans_l, st[l++]);
			if (r&1) ans_r = segment_data::combine(st[--r], ans_r);
		}
		return segment_data::combine(ans_l, ans_r);
	}

	segment_data query(int idx) const {
		return st[idx+size];
	}
};

