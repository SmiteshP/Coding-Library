// Dinitz Algorithm
class flow_network {
public:
	struct Edge {
		int from, to;
		const long long int cap;
		long long int flow;

		Edge(int _from, int _to, long long int _cap) : from(_from), to(_to), cap(_cap), flow(0) {}
	};

	const long long int FN_INF = 1e18 + 5;
	std::vector <Edge> edges;
	std::vector <std::vector<int>> adjList;
	std::vector <int> levelGraph;

	int num_vertex, num_edges;
	int sourceIdx = 0, sinkIdx;
	long long int maxFlow = 0;

	flow_network (int _num_vertex, int _num_edges) : num_vertex(_num_vertex), num_edges(_num_edges), sinkIdx(num_vertex-1) {
		adjList.resize(num_vertex);
		levelGraph.resize(num_vertex);
		edges.reserve(2*num_edges);
	}

	flow_network(int _num_vertex) : flow_network(_num_vertex, 2*_num_vertex) {}

	void addEdge(int _from, int _to, long long int _cap) {
		int idx = edges.size();
		edges.emplace_back(_from, _to, _cap);
		edges.emplace_back(_to, _from, 0);
		adjList[_from].emplace_back(idx);
		adjList[_to].emplace_back(idx+1);
	}

	bool bfs() {
		std::fill(levelGraph.begin(), levelGraph.end(), -1);
		levelGraph[sourceIdx] = 0;
		std::queue <int> q;
		q.push(sourceIdx);
		while (!q.empty()) {
			int curr = q.front();
			q.pop();
			for (int idx : adjList[curr]) {
				Edge& e = edges[idx];
				if (e.cap - e.flow > 0 && levelGraph[e.to] == -1) {
					levelGraph[e.to] = levelGraph[curr]+1;
					q.push(e.to);
				}
			}
		}
		return levelGraph[sinkIdx] != -1;
	}

	long long int dfs(int curr, std::vector<int>& SAarr, long long int flow) {
		if (curr == sinkIdx) return flow;
		int nedges = adjList[curr].size();
		for (int& i = SAarr[curr]; i < nedges; ++i) {
			Edge& e = edges[adjList[curr][i]];
			if (e.cap - e.flow > 0 && levelGraph[e.to] == levelGraph[curr]+1) {
				long long int bottleNeck = dfs(e.to, SAarr, std::min(flow, e.cap - e.flow));
				if (bottleNeck > 0) {
					e.flow += bottleNeck;
					edges[adjList[curr][i]^1].flow -= bottleNeck;
					return bottleNeck;
				}
			}
		}
		return 0;
	}

	void flow() {
		std::vector <int> SAarr(num_vertex);
		while(bfs()) {
			std::fill(SAarr.begin(), SAarr.end(), 0);
			for (long long int flow = dfs(sourceIdx, SAarr, FN_INF); flow != 0; flow = dfs(sourceIdx, SAarr, FN_INF)) {
				maxFlow += flow;
			}
		}
	}
};

