//===========================KDTree====================
const int KDTmaxp = 5; //最大维度
const int KDTmaxn = 100005; //最大节点数
const int KDTinf = 0x7fffffff; //最大dist值
int P;
struct KDT_Point
{
	int xy[KDTmaxp], num, dist;
};
struct KDT_Node
{
	KDT_Point p;
	int max[KDTmaxp], min[KDTmaxp], l, r;
	KDT_Node(KDT_Point k)
	{
		l = r = 0;
		p = k;
		for (int i = 0; i < KDTmaxp; ++i)
			max[i] = min[i] = k.xy[i];
	}
	KDT_Node() {}
};
bool operator<(KDT_Point a, KDT_Point b)
{
	return a.xy[P] < b.xy[P];
}
struct KD_Tree
{
private:
	KDT_Node t[KDTmaxn];
	int n, tot, root, KDTp;
	int sqr(int a)
	{
		return a * a;
	}
	void up(int now)
	{
		for (int i = 0; i < KDTp; ++i)
		{
			if (t[now].l)
				t[now].max[i] = max(t[now].max[i], t[t[now].l].max[i]),
				                t[now].min[i] = min(t[now].min[i], t[t[now].l].min[i]);
			if (t[now].r)
				t[now].max[i] = max(t[now].max[i], t[t[now].r].max[i]),
				                t[now].min[i] = min(t[now].min[i], t[t[now].r].min[i]);
		}
	}
	int build(int l, int r, KDT_Point K[], int p)
	{
		if (l > r) return 0;
		int now = ++tot;
		P = p;
		sort(K + l, K + r + 1);
		int mid = (l + r) / 2;
		t[now] = KDT_Point(K[mid]);
		t[now].l = build(l, mid - 1, K, (p + 1) % KDTp);
		t[now].r = build(mid + 1, r, K, (p + 1) % KDTp);
		up(now);
		return now;
	}
	void ins(int now, KDT_Point k, int p)
	{
		if (t[now].p.xy[p] > k.xy[p])
		{
			if (!t[now].l)
			{
				t[now].l = ++tot;
				t[tot] = KDT_Point(k);
			}
			else ins(t[now].l, k, (p + 1) % KDTp);
		}
		else
		{
			if (!t[now].r)
			{
				t[now].r = ++tot;
				t[tot] = KDT_Point(k);
			}
			else ins(t[now].r, k, (p + 1) % KDTp);
		}
		up(now);
	}
	void re_min(int now, KDT_Point &a, KDT_Point ans[], int k)
	{
		int i = k;
		int di = dist(t[now].p, a);
		t[now].p.dist = di;
		for (; i >= 1 && ans[i].dist >= di; --i);
		if (i == k) return;
		++i;
		for (int j = k; j > i; --j) ans[j] = ans[j - 1];
		ans[i] = t[now].p;
	}
	void qy_min(int now, KDT_Point &a, KDT_Point ans[], int k, int p)
	{
		if (!now) return;
		KDT_Point P;
		for (int i = 0; i < KDTp; ++i)
			P.xy[i] = (a.xy[i] <= t[now].max[i] && a.xy[i] >= t[now].min[i]) ? a.xy[i]
			          : (abs(t[now].max[i] - a.xy[i]) < abs(t[now].min[i] - a.xy[i])
			             ? t[now].max[i] : t[now].min[i]);
		if (dist(P, a) > ans[k].dist) return;
		re_min(now, a, ans, k);
		if (a.xy[p] > t[now].p.xy[p])
		{
			qy_min(t[now].r, a, ans, k, (p + 1) % KDTp);
			qy_min(t[now].l, a, ans, k, (p + 1) % KDTp);
		}
		else
		{
			qy_min(t[now].l, a, ans, k, (p + 1) % KDTp);
			qy_min(t[now].r, a, ans, k, (p + 1) % KDTp);
		}
	}
	void re_max(int now, KDT_Point &a, KDT_Point ans[], int k)
	{
		int i = k;
		int di = dist(t[now].p, a);
		t[now].p.dist = di;
		for (; i >= 1 && (ans[i].dist < di || (ans[i].dist == di && ans[i].num > t[now].p.num)); --i);
		if (i == k) return;
		++i;
		for (int j = k; j > i; --j) ans[j] = ans[j - 1];
		ans[i] = t[now].p;
	}
	void qy_max(int now, KDT_Point &a, KDT_Point ans[], int k, int p)
	{
		if (!now) return;
		KDT_Point P;
		for (int i = 0; i < KDTp; ++i)
			P.xy[i] = abs(t[now].max[i] - a.xy[i]) > abs(t[now].min[i] - a.xy[i])
			          ? t[now].max[i] : t[now].min[i];
		if (dist(P, a) < ans[k].dist) return;
		re_max(now, a, ans, k);
		if (a.xy[p] < t[now].p.xy[p])
		{
			qy_max(t[now].r, a, ans, k, (p + 1) % KDTp);
			qy_max(t[now].l, a, ans, k, (p + 1) % KDTp);
		}
		else
		{
			qy_max(t[now].l, a, ans, k, (p + 1) % KDTp);
			qy_max(t[now].r, a, ans, k, (p + 1) % KDTp);
		}
	}
public:
	void create(int N, KDT_Point K[], int p) //表示一共有n个节点要预先建树 节点信息存在k[]里 下标0~n-1 维度为p
	{
		n = N;
		KDTp = p;
		root = build(0, n - 1, K, 0);
	}
	void insert(KDT_Point k) //往KD_Tree里插入节点k
	{
		ins(root, k, 0);
	}
	void query_max(KDT_Point &a, KDT_Point ans[], int k) //返回离点a的k远点 写在ans[]里
	{
		for (int i = 0; i <= k; ++i)
			ans[i].dist = -KDTinf;
		qy_max(root, a, ans, k, 0);
	}
	void query_min(KDT_Point &a, KDT_Point ans[], int k) //回离点a的k近点 写在ans[]里
	{
		for (int i = 0; i <= k; ++i)
			ans[i].dist = KDTinf;
		qy_min(root, a, ans, k, 0);
	}
	int dist(KDT_Point a, KDT_Point b) //回点a、b的距离
	{
		int ans = 0;
		for (int i = 0; i < KDTp; ++i)
			ans += sqr(a.xy[i] - b.xy[i]);
		return ans;
	}
	void clear() //清空KDT
	{
		n = tot = root = KDTp = 0;
		memset(t, 0, sizeof(t));
	}
};
//===========================KDTree====================
