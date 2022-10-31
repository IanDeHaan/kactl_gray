/**
 * Author: Ian DeHaan
 * Date: 2022-10-31
 * License: CC0
 * Source: folklore
 * Description: Inefficient recursive lazy segment tree.
 * Only use in emergency. Kactl's is much faster.
 */

#pragma once

struct RageTree {
	int n, t[4*MAXN];
    bool marked[4*MAXN];
    int action[4*MAXN];

    int combine(int x, int y) {
        return x + y;
    }

    void init(int a[], int N) {
        n = N;
        memset(t, 0, sizeof t);
        memset(marked, false, sizeof marked);
        build(a, 1, 0, n - 1);
    }

    void build(int a[], int v, int tl, int tr) {
        if (tl == tr) {
            // we are at a leaf
            t[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            t[v] = combine(t[v*2], t[v*2+1]);
        }
    }

    void pushAction(int v, int tl, int tr) {
        if (!marked[v]) return;
        marked[v] = false;

        // action is to set everything underneath to action[v]
        int tm = (tl + tr) / 2;
        t[v*2] = action[v]*(tm+1-tl);
        t[v*2+1] = action[v]*(tr-tm);
        marked[v*2] = true;
        marked[v*2+1] = true;
        action[v*2] = action[v];
        action[v*2+1] = action[v];
    }

    void update(int l, int r, int new_val, int v = 1, int tl = 0, int tr = -1) {
        if (tr == -1) tr = n - 1;

        if (l > r) {
            return;
        }

        if (tl == l && tr == r) {
            // exactly this vertex
            t[v] = new_val*(r-l+1);
            marked[v] = true;
            action[v] = new_val;
        } else {
            pushAction(v, tl, tr);
            int tm = (tl + tr) / 2;
            update(l, min(r, tm), new_val, v*2, tl, tm);
            update(max(l, tm+1), r, new_val, v*2+1, tm+1, tr);
            t[v] = t[v*2] + t[v*2+1];
        }
    }

    int sum(int l, int r, int v = 1, int tl = 0, int tr = -1) {
        if (tr == -1) tr = n - 1;
        if (l > r) {
            return 0; // nothing to get
        }
        if (l == tl && r == tr) {
            return t[v]; // we're exactly this node
        }
        int tm = (tl + tr) / 2;
        pushAction(v, tl, tr);
        return sum(l, min(r, tm), v*2, tl, tm) + sum(max(l, tm+1), r, v*2+1, tm+1, tr);
    }
};