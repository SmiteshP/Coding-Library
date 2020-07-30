// vertex indexing expected from 0
// input format  : adjacency list
// output format : empty vector if cycle exists else toposort order
std::vector <int> topological_sort(std::vector <std::vector <int> >& edges) {
	int num_vertex = edges.size();
	std::vector <int> in_degree(num_vertex);
	for (std::vector <int>& children : edges) {
		for (int child : children) {
			++in_degree[child];
		}
	}
	std::vector <int> tsort;
	tsort.reserve(num_vertex);
	std::queue <int> process_queue;
	for (int i = 0; i < num_vertex; ++i) {
		if (!in_degree[i]) process_queue.push(i);
	}
	while (process_queue.size() != 0) {
		int curr_vertex = process_queue.front();
		process_queue.pop();
		tsort.emplace_back(curr_vertex);
		for (int child : edges[curr_vertex]) {
			--in_degree[child];
			if (!in_degree[child]) process_queue.push(child);
		}
	}
	if (tsort.size() == (long unsigned int)num_vertex) {
		return tsort;
	} else {
		return {};
	}
}

