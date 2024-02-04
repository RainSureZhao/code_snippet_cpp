mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
cout << rng() << "\n";

mt19937_64 mt{random_device()()};

int get(int l, int r)
{
    uniform_int_distribution t(l, r);
    return t(mt);
}