/**
 * Author: Dilhan Salgado (based on description by defnotmee)
 * Date: 2025
 * Source: Sleator
 * Description: Skew Heap.
 * Mergeable Heaps. To make 'persistent' update merge function to return *new* SkewHeap
 */

 using T = int;
 struct SkewHeap {
   SkewHeap *l = 0, *r = 0;
   T val;
   SkewHeap (T v) : val(v) {}
   static SkewHeap* merge (SkewHeap* a, SkewHeap* b) {
     if (a == 0) return b;
     if (b == 0) return a;
     if (a->val > b->val) swap(a, b);
 
     auto x = a->r;
     a->r = SkewHeap::merge(a->l, b);
     a->l = x;
     return a;
   };
 };
 
 T pop (SkewHeap* &a) {
   T out = a->val;
   a = SkewHeap::merge(a->l, a->r);
   return out;
 };
 
 void insert (SkewHeap* &a, T v) {
   a = SkewHeap::merge(a, new SkewHeap(v));
 }