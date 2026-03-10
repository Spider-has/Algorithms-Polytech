template < class T > struct List
{
  T val;
  List< T > *next, *prev;
};

template < class T > bool has_common(const List< T > *h1, const List< T > *h2)
{
  const List< T > *head = h1;
  while (head->prev)
  {
    head = head->prev;
  }
  while (head)
  {
    if (head == h2)
    {
      return true;
    }
    head = head->next;
  }
  return false;
}

template < class T > bool no_common(const List< const List< T > * > *h)
{
  const List< List< T > * > *head = h;
  const List< List< T > * > *curr = nullptr;
  while (head)
  {
    curr = head->next;
    while (curr)
    {
      if (has_common(head->val, curr->val))
      {
        return false;
      }
      curr = curr->next;
    }
    head = head->next;
  }
  return true;
}

template < class T > struct MList
{
  T val;
  MList< T > *next, *prev, *ref;
};

template < class T > bool has_common(const MList< T > *h1, const MList< T > *h2)
{
  const List< T > *head = h1;
  while (head->prev)
  {
    head = head->prev;
  }
  while (head)
  {
    if (head == h2)
    {
      return true;
    }
    head = head->next;
  }
  return false;
}

template < class T > bool self_refed(MList< T > *h)
{
  while (h)
  {
    if (h->ref)
    {
      if (!has_common(h->ref, h))
      {
        return false;
      }
    }
    h = h->next;
  }
  return true;
}

template < class T > bool has_ref(MList< T > *list, MList< T > *node)
{
  while (list)
  {
    if (list->ref == node)
    {
      return true;
    }
    list = list->next;
  }
  return false;
}

template < class T > List< const MList< T > * > *no_refs(const MList< T > *h)
{
  List< const MList< T > * > dummy_head{nullptr, nullptr, nullptr};
  List< const MList< T > * > tail = &dummy_head;
  List< const MList< T > * > prev = nullptr;
  MList< T > *inner = h;
  while (inner)
  {
    if (!has_ref(h, inner))
    {
      try
      {
        tail->next = new List< const MList< T > * >{inner, nullptr, prev};
        tail = tail->next;
        prev = tail;
      }
      catch (...)
      {
        while (tail->prev)
        {
          List< const MList< T > * > tmp = tail.prev;
          delete tail;
          tail = tmp;
        }
        throw;
      }
    }
    inner = inner->next;
  }
  return dummy_head.next;
}

#include <cstddef>

template < class T > List< const MList< T > * > *most_refs(const MList< T > *h)
{
  size_t count = 0;
  const MList< T > *cp = h;
  while (cp)
  {
    cp = cp->next;
    count++;
  }
  size_t *ref_sizes = new size_t[count];
  cp = h;
  const MList< T > *curr = cp;
  size_t max = 0;
  for (size_t i = 0; i < count; ++i)
  {
    size_t refs = 0;
    while (cp)
    {
      if (cp->ref == curr)
      {
        refs++;
      }
      cp = cp->next;
    }
    cp = h;
    ref_sizes[i] = refs;
    curr = curr->next;
    if (refs > max)
    {
      max = refs;
    }
  }

  List< const MList< T > * > *ans = nullptr;
  List< const MList< T > * > *tail = ans;
  if (max)
  {
    try
    {
      cp = h;
      for (size_t i = 0; i < count; ++i)
      {
        if (ref_sizes[i] == max)
        {
          if (!ans)
          {
            ans = new List< const MList< T > * >{cp, nullptr, nullptr};
            tail = ans;
          }
          else
          {
            tail->next = new List< const MList< T > * >{cp, tail, nullptr};
            tail = tail->next;
          }
        }
        cp = cp->next;
      }
    }
    catch (...)
    {
      delete[] ref_sizes;
      while (ans)
      {
        List< const MList< T > * > *n = ans->next;
        delete ans;
        ans = n;
      }
      throw;
    }
  }
  delete[] ref_sizes;
  return ans;
}
