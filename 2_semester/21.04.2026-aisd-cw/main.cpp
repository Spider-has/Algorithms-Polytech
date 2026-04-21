#include <cstddef>
#include <cstdint>
#include <iostream>
#include <tuple>
#include <utility>

template < class T > struct BiTree
{
  T val;
  BiTree< T > *lt, *rt, *parent;
};

enum Dir : std::uint8_t
{
  fall_left,
  parent
};

template < class T > std::pair< size_t, BiTree< T > * > fallLeft(BiTree< T > *root)
{
  size_t path = 0;
  while (root->lt)
  {
    root = root->lt;
    path++;
  }
  return {path, root};
}

template < class T > std::pair< size_t, BiTree< T > * > Parent(BiTree< T > *root)
{
  if (!root)
  {
    return {0, nullptr};
  }
  size_t path = 0;
  BiTree< T > *parent = root->parent;
  while (parent && parent->lt != root)
  {
    root = parent;
    parent = root->parent;
    path++;
  }
  return {path, parent};
}

template < class T > std::tuple< Dir, size_t, BiTree< T > * > nextStruct(BiTree< T > *root)
{
  if (root->rt)
  {
    auto result = fallLeft(root->rt);
    return std::tuple< Dir, size_t, BiTree< T > * >(Dir::fall_left, result.first, result.second);
  }
  auto result = Parent(root);
  return std::tuple< Dir, size_t, BiTree< T > * >(Dir::fall_left, result.first, result.second);
}

template < class T > bool isEqualStruct(BiTree< T > *lhs, BiTree< T > *rhs)
{
  auto lhs_begin = fallLeft(lhs);
  auto rhs_begin = fallLeft(rhs);
  if (lhs_begin.first != rhs_begin.first)
  {
    return false;
  }
  auto ln = nextStruct(lhs_begin.second);
  auto rn = nextStruct(rhs_begin.second);
  while (std::get< 0 >(ln) == std::get< 0 >(rn) && std::get< 1 >(ln) == std::get< 1 >(rn) && std::get< 2 >(ln) &&
         std::get< 2 >(rn))
  {
    ln = nextStruct(std::get< 2 >(ln));
    rn = nextStruct(std::get< 2 >(rn));
  }
  return ln == rn;
}

template < class T > bool includedStructStart(BiTree< T > *lhs_root, BiTree< T > *pattern)
{
  auto next_pattern = nextStruct(pattern);
  std::pair< Dir, BiTree< T > * > next_lhs;
  if (std::get< 0 >(next_pattern) == Dir::fall_left)
  {
    next_lhs = fallLeft(lhs_root);
  }
  else
  {
    next_lhs = Parent(lhs_root);
  }
  while (std::get< 1 >(next_pattern) == next_lhs.first && next_lhs.second && std::get< 2 >(next_pattern))
  {
    next_pattern = nextStruct(std::get< 2 >(next_pattern));
    if (std::get< 0 >(next_pattern) == Dir::fall_left)
    {
      if (next_lhs.second->rt)
      {
        next_lhs = fallLeft(next_lhs.second->rt);
      }
      else
      {
        return false;
      }
    }
    else
    {
      next_lhs = Parent(lhs_root);
    }
  }
  return std::get< 1 >(next_pattern) == next_lhs.first && std::get< 2 >(next_pattern) == nullptr;
}

template < class T > bool inlcludedStruct(BiTree< T > *lhs, BiTree< T > *pattern)
{
}

int main()
{
  BiTree< int > *A = new BiTree< int >{1, nullptr, nullptr, nullptr};
  BiTree< int > *ALeft = new BiTree< int >{2, nullptr, nullptr, A};
  A->rt = ALeft;

  BiTree< int > *B = new BiTree< int >{4, nullptr, nullptr, nullptr};
  BiTree< int > *BLeft = new BiTree< int >{3, nullptr, nullptr, B};
  B->lt = BLeft;

  std::cout << isEqualStruct< int >(A, B) << "\n";
}
