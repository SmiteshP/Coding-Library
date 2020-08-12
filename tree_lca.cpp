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

class tree_lca {
private:
	int num_nodes;
	const std::vector <std::vector <int>>& tree;
	std::vector <int> ntt_map;		// node to euler_tour map
	std::vector <int> depth_map;
	std::vector <int> euler_tour;
	sparse_table* st;

	void dfs(int node, int depth, int parent) {
		ntt_map[node] = euler_tour.size();
		euler_tour.emplace_back(node);
		depth_map.emplace_back(depth);

		if (tree[node].empty()) {
			return;
		} else {
			for (int n : tree[node]) {
				if (n != parent) {
					dfs(n, depth+1, node);
					ntt_map[node] = euler_tour.size();
					euler_tour.emplace_back(node);
					depth_map.emplace_back(depth);
				}
			}
		}
	}

public:
	// Input : zero indexed tree, adjacency list
	tree_lca(int root, int _num_nodes, const std::vector <std::vector <int>>& _tree) : num_nodes(_num_nodes), tree(_tree), ntt_map(num_nodes, -1) {
		euler_tour.reserve(2*num_nodes-1);
		depth_map.reserve(2*num_nodes-1);

		dfs(root, 0, -1);

		st = new sparse_table(depth_map);
	}

	tree_lca(const tree_lca& other) = delete;

	void operator= (const tree_lca& other) = delete;

	~tree_lca() {
		delete st;
	}

	int lca(int node1, int node2) {
		node1 = ntt_map[node1];
		node2 = ntt_map[node2];
		if (node1 > node2) std::swap(node1, node2);
		return euler_tour[st->queryIndex(node1, node2)];
	}
};

