class tree_binary_lifting {
private:
	// Binary Lift Power : ceil(log2(max_number_of_nodes))
	static const int BLP = 20;

	struct tree_node {
		int blift[BLP];
		tree_node() {
			memset(blift, -1, BLP*sizeof(int));
		}
	};

	tree_node* tn_list;
	int* depth_map;

public:
	tree_binary_lifting(std::vector <std::vector <int>>& tree, int root) : tn_list(new tree_node[tree.size()]), depth_map(new int[tree.size()]) {
		depth_map[root] = 0;
		std::stack <int> stk;
		stk.push(root);
		while (!stk.empty()) {
			int parent = stk.top();
			stk.pop();
			for (int cur : tree[parent]) {
				if (cur == tn_list[parent].blift[0]) continue;
				stk.push(cur);
				depth_map[cur] = depth_map[parent]+1;
				tn_list[cur].blift[0] = parent;
				for (int j = 1; j < BLP; ++j) {
					if (tn_list[cur].blift[j-1] != -1) {
						tn_list[cur].blift[j] = tn_list[tn_list[cur].blift[j-1]].blift[j-1];
					} else {
						break;
					}
				}
			}
		}
	}

	~tree_binary_lifting() {
		delete[] tn_list;
		delete[] depth_map;
	}

	int lifter(int node, int height) {
		if (node == -1) {
			return -1;
		} else if (height == 0) {
			return node;
		}

		while (node != -1 && height > 0) {
			int tpow = 0;
			int tpval = 1;
			while (height > 2*tpval) {
				tpow++;
				tpval *= 2;
			}
			node = tn_list[node].blift[tpow];
			height -= tpval;
		}

		return node;
	}

	int lca(int node1, int node2) {
		if (node1 == -1 || node2 == -1) {
			return -1;
		}

		int dn1 = depth_map[node1];
		int dn2 = depth_map[node2];

		if (dn1 > dn2) {
			node1 = lifter(node1, dn1-dn2);
			dn1 = dn2;
		} else if (dn1 < dn2) {
			node2 = lifter(node2, dn2-dn1);
			dn2 = dn1;
		}

		while (node1 != node2) {
			int mxup = 0;
			while (tn_list[node1].blift[mxup+1] != tn_list[node2].blift[mxup+1]) {
				++mxup;
			}
			node1 = tn_list[node1].blift[mxup];
			node2 = tn_list[node2].blift[mxup];
		}

		return node1;
	}

	int node_depth(int node) {
		return depth_map[node];
	}
};

