uint64_t  gcd( uint64_t a, uint64_t b )
{
    if( a == 0 )   return b;
    if( b == 0 )   return a;
  
    auto  shift = __builtin_ctzll( a | b );
    a >>= __builtin_ctz( a );
    do  {
        b >>= __builtin_ctzll( b );
        if( a > b )    std::swap( a, b );
        b -= a;
    }  while( b != 0 );
    return  a << shift;
}
  
class  RNG 
{
  private:
    mt19937_64  mt;
  
  public:
    RNG() : mt( chrono::steady_clock::now().time_since_epoch().count() ) {}
  
    int64_t operator () ( int64_t L, int64_t R )  {
        uniform_int_distribution<int64_t>  dist( L, R - 1 );
        return  dist( mt );
    }
  
    int64_t operator () ( int64_t r )  { return (*this)( 0, r ); }
}  rng;
  
class  MMint     // MONTGOMERY FORM
{
  private:
    using i64  = int64_t;
    using u64  = uint64_t;
    using u128 = __uint128_t;
  
    static u64  mod;
    static u64  r;       // mod*r ≡ 1  MOD 2^64
    static u64  n2;      // 2^128  MOD mod
  
    u64  x;
  
    static u64  reduce( const u128 &b )
    { return ( b + u128( u64( b ) * u64( -r ) ) * mod ) >> 64; }
     
  public:
    MMint() : x( 0 ) {}
  
    MMint( int64_t b ) : x( reduce( ( u128( b ) + mod ) * n2 ) ) {}
  
    static u64  get_r()  {
        u64  ret = mod;
        for( size_t i=0 ; i<5 ; ++i )  ret *= 2 - mod * ret;
        return  ret;
    }
  
    static u64  get_mod()  { return mod; }
     
    u64  get() const  {
        u64  ret = reduce( x );
        return  ret >= mod ? ret - mod : ret;
    }
     
    static void  set_mod( u64 m )  {
        assert( m < (1LL << 62) );
        assert( (m & 1) == 1 );
        mod = m;
        n2 = -u128( m ) % m;
        r = get_r();
        assert( r * mod == 1 );
    }
  
    MMint &operator += ( const MMint &p )  {
        if( i64( x += p.x + 2*mod ) < 0 )   x += 2 * mod;
        return  *this;
    }
    MMint &operator -= ( const MMint &p )  {
        if( i64( x -= p.x ) < 0 )   x += 2 * mod;
        return  *this;
    }
    MMint &operator *= ( const MMint &p )  {
        x = reduce( u128( x ) * p.x );
        return  *this;
    }
    MMint &operator /= ( const MMint &p )  {
        *this *= p.inverse();
        return  *this;
    }
    MMint &operator ++ ()  { return *this += MMint( 1 ); }
    MMint operator ++ ( int )  {
        MMint  tmp = *this;
        ++*this;
        return  tmp;
    }
    MMint &operator -- ()  { return *this -= MMint( 1 ); }
    MMint operator -- ( int )  {
        MMint  tmp = *this;
        --*this;
        return  tmp;
    }
  
    MMint operator + ( const MMint &p ) const { return MMint(*this) += p; };
    MMint operator - ( const MMint &p ) const { return MMint(*this) -= p; };
    MMint operator * ( const MMint &p ) const { return MMint(*this) *= p; };
    MMint operator / ( const MMint &p ) const { return MMint(*this) /= p; };
  
    bool operator == ( const MMint &p ) const
    { return (x >= mod ? x - mod : x) == (p.x >= mod ? p.x - mod : p.x); };
    bool operator != ( const MMint &p ) const
    { return (x >= mod ? x - mod : x) != (p.x >= mod ? p.x - mod : p.x); };
  
    MMint  inverse()  const {
        u64  g = mod,  r = (*this).x,  x = 0,  y = 1;
        while( r != 0 )  {
            u64  q = g / r;
            g %= r;    swap( g, r );
            x -= q*y;  swap( x, y );
        }
        return  x < 0 ? x + mod : x;
    }
  
    MMint  pow( int64_t k ) const  {
        MMint  now = *this,  ret = 1;
        for( ; k > 0 ; k >>= 1, now *= now )  {
            if( k & 1 )  ret *= now;
        }
        return ret;
    }
  
    friend ostream &operator << ( ostream &os, const MMint &p )  { 
        return  os << p.get(); 
    }
    friend istream &operator >> ( istream &is, MMint &p )  {
        int64_t  a;
        is >> a;
        p = MMint( a );
        return  is;
    }
};
  
using  u32 = uint32_t;
using  u64 = uint64_t;
  
// NONCONSTANT STATIC CLASS MEMBERS MUST HAVE GLOBAL SCOPE
typename  MMint::u64  MMint::mod,  MMint::r,  MMint::n2;
  
bool  millerRabin( u64 n, vector<u64> as )  {
    if( MMint::get_mod() != n )  MMint::set_mod( n );
     
    u64  d = n - 1;
    while( !(d & 1) )  d >>= 1;
     
    MMint  e = 1,  rev = n - 1;
     
    for( u64 a : as )  {
        if( n <= a )  break;
        u64  t = d;
        MMint  y = MMint( a ).pow ( t );
        while( t != n - 1  &&  y != e  &&  y != rev )  {
            y *= y;
            t <<= 1;
        }
        if( y != rev  &&  !(t & 1) )  return false;
    }
    return true;
}
  
bool  isPrime( u64 n )  {
    if( !(n & 1) )  return n == 2;
    if (n <= 1 )    return false;
    if( n < (1LL << 30) )  return  millerRabin( n, { 2, 7, 61 } );
    return  millerRabin (n, { 2, 325, 9375, 28178, 450775, 9780504, 1795265022 } );
}
  
u64  pollardRho( u64 n )  {
    if( !( n & 1 ) )    return  2;
    if( isPrime( n ) )  return  n;
     
    if( MMint::get_mod() != n )  MMint::set_mod( n );
        
    MMint  R,  one = 1;
    auto  f   = [&]( MMint x ) { return x * x + R; };
    auto  rnd = [&]()  { return rng( n - 2 ) + 2; };
     
    while( true )  {
        MMint  x,  y,  ys,  q = one;
        R = rnd(),  y = rnd();
        u64  g = 1;
        int  m = 128;
         
        for( u64 r=1 ; g==1 ; r<<=1ULL )  {
            x = y;
            for( size_t i=0 ; i<r ; ++i )  y = f( y );
            for( size_t k=0 ; g==1 && k<r ; k += m )  {
                ys = y;
                for( size_t i=0 ; i<m && i<r-k ; ++i )  q *= x - ( y = f ( y ) );
                g = gcd( q.get(), n );
            }
        }
         
        if( g == n )
            do  { g = gcd( ( x - ( ys = f(ys) ) ).get(), n ); }  while( g == 1 );
         
        if( g != n )  return g;
    }
    return 0;
}
  
vector<u64>  _factorize( u64 n )  { 
    if( n <= 1 )  return {};
     
    u64  p = pollardRho( n );
    if( p == n )  return { n };
     
    auto  l = _factorize( p );
    auto  r = _factorize( n / p );
     
    copy( begin( r ), end( r ), back_inserter( l ) );
    return  l;
}
map<u64, vector<u64>> ___mp;
int _ltt[7] = {2, 3, 5, 7, 11, 13, 17};
vector<u64>  factorize( u64 n )  { // 返回有序质数
    if(___mp.count(n)) return ___mp[n];
    int __n = n;
    vector<u64> ret;
    auto add = [&](int x){
        if(x <= 1) return;
        while(n % x == 0){
            ret.push_back(x);
            n /= x;
        }       
    };
    for(int i = 0;i < 7; i++) add(_ltt[i]);
    u64 m1 = (u64)sqrtl(n);
    auto ck = [](u64 x){
        long long mm = pow(x, 1.0 / 3.0);
        for(u64 i = max(mm - 2, 0ll);i <= (u64)mm + 2;i++){
            if(i * i * i == x) return i;
        }
        return u64(0);
    };
    u64 mm = ck(n);
    //add(m1);add(mm);
    auto pp = _factorize(n);
    for(auto x : pp) ret.push_back(x);
    sort(ret.begin(), ret.end());
    if(___mp.size() <= 1000)
        return  ___mp[__n] = ret;
    return ret;
}
  
vector<pair<u64, u32>>  primeFactor(u64 n){ // 返回一个存二元组的vector，first是质数的值，second是该质数的数量 
    auto  pf = factorize( n );
    vector< pair<u64, u32> >  ret;
    for( auto &e : pf )  {
        if(!ret.empty() && ret.back().first == e )  ++ret.back().second;
        else   ret.emplace_back( e, 1 );
    }
    return  ret;
}
vector<long long> get_divisor(long long n) { // 求所有约数，包括1和n
    std::vector<long long> ret;
    auto vp = primeFactor(n);
    function<void(int, long long)> dfs = [&](int idx, long long res){
        if(idx == (int)vp.size()) {
            ret.push_back(res);
            return;
        }
        long long x = vp[idx].first, tmp = res;
        for(int i = 0;i <= (int)vp[idx].second; i++){
            dfs(idx + 1, tmp);
            tmp *= x;
        }
    };
    dfs(0, 1);
    sort(ret.begin(), ret.end());
    return ret;
}