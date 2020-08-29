// Zero indexed
class disjoint_set {
private:
	int N;
	int* forest;
	int* t_size;
	int* track;

public:
	disjoint_set(int n_obj) : N(n_obj), forest(new int[N]), t_size(new int[N]), track(new int[N]) {
		std::iota(forest, forest+n_obj, 0);
		std::fill(t_size, t_size+n_obj, 1);
	}

	disjoint_set(const disjoint_set& other) = delete;
	void operator= (const disjoint_set& other) = delete;

	~disjoint_set() {
		delete[] forest;
		delete[] t_size;
		delete[] track;
	}

	int groupID(int i) {
		int n_elems = 0;
		while (forest[i] != i) {
			track[n_elems] = i;
			++n_elems;
			i = forest[i];
		}
		while (n_elems--) {
			forest[track[n_elems]] = i;
		}
		return i;
	}

	bool join(int a, int b) {
		int ga = groupID(a);
		int gb = groupID(b);
		if (ga == gb) {
			return false;
		} else {
			if (t_size[ga] > t_size[gb]) std::swap(ga, gb);
			forest[ga] = gb;
			t_size[gb] += t_size[ga];
			return true;
		}
	}

	int groupSize(int nodeID) {
		return t_size[groupID(nodeID)];
	}

	int size() const {
		return N;
	}
};

