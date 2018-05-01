struct node {
    node* l,* r;
    ll sum;

    node() {
        l = r = nullptr;
        sum = 0;
    }

    node(ll val) {
        l = r = nullptr;
        sum = val;
    }

    node(node* x, node* y) {
        l = x;
        r = y;
        sum = 0;
        if (l) {
            sum += l->sum;
        }
        if (r) {
            sum += r->sum;
        }
    }
};

node * build(int tl, int tr) {
    if (tl == tr) {
        return new node(a[tl]);
    }
    int tm = (tl + tr) >> 1;
    return new node(build(tl, tm), build(tm + 1, tr));
}

ll get(node * t, int tl, int tr, int l, int r) {
    if (l > r) {
        return 0;
    }
    if (l == tl && r == tr) {
        return t->sum;
    }
    int tm = (tl + tr) >> 1;
    return get(t->l, tl, tm, l, min(r, tm)) +
    get(t->r, tm + 1, tr, max(l, tm + 1), r);
}

node * update(node * t, int tl, int tr, int pos, ll val) {
    if (tl == tr) {
        return new node(val);
    }
    int tm = (tl + tr) >> 1;
    if (pos <= tm) {
        return new node(update(t->l, tl, tm, pos, val), t->r);
    } else {
        return new node(t->l, update(t->r, tm + 1, tr, pos, val));
    }
}
