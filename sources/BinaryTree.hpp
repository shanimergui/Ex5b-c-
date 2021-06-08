#pragma once
#include <stdio.h>
#include <memory>
#include <queue>
using namespace std;

namespace ariel
{
    template <typename T> class BinaryTree{

    private:

      struct Vertex
      {
          T value;
          Vertex *left;
          Vertex *right;
          Vertex(const T &vertex) : value(vertex), left(nullptr), right(nullptr){}
      };


      void copy(Vertex * v, Vertex * other_v)
      {
          if (other_v->right!=nullptr)
          {
              v->right = new Vertex(other_v->right->value);
              copy(v->right, other_v->right);
          }

          if (other_v->left!=nullptr)
          {
              v->left = new Vertex(other_v->left->value);
              copy(v->left, other_v->left);
          }

      }

      void remove_the_tree()
      {
          if (!root)
          {
              for (auto it = begin(); it != end(); ++it)
              {
                  Vertex * del = it.getVertex();
                  delete del;
              }
          }
      }

      Vertex * find(T value)
      {
          if (root)
          {
              for (auto it = begin(); it != end(); ++it)
              {
                  if (*it == value)
                  {
                      return it.getVertex();
                  }
              }
          }
          return nullptr;
      }

      Vertex * root;

    public:
        BinaryTree() : root(nullptr){}
        ~BinaryTree() = default;
        BinaryTree(const BinaryTree &other)
        {
            remove_the_tree();
            if (other.root)
            {
                root = new Vertex(other.root->value);
                copy(root, other.root);
            }
        }

        BinaryTree(BinaryTree &&other) noexcept
        {
            root = other.root;
            other.root = nullptr;
        }

        BinaryTree &operator=( BinaryTree other)
        {
            if (this != &other)
            {
                remove_the_tree();
                if (other.root)
                {
                    root = new Vertex(other.root->value);
                    copy(root, other.root);
                }
            }
            return *this;
        }

        BinaryTree &operator=(BinaryTree &&other) noexcept
        {
            root = other.root;
            other.root = nullptr;
            return *this;
        }

        BinaryTree<T>& add_root(T value)
        {
            if (!root){ root = new Vertex(value); }
            else { root->value = value; }
            return *this;
        }

        BinaryTree<T>& add_left(T parent,const T lchild)
        {
            Vertex * l_child_found = find(parent);
            if (!l_child_found)
            {
                remove_the_tree();
                throw std::invalid_argument("Not have parent");
            }
            if (!l_child_found->left)
            {
                l_child_found->left = new Vertex(lchild);
            }
            else
            {
                (l_child_found->left)->value = lchild;
            }
            return *this;
        }

        BinaryTree<T>& add_right(T parent, const T rchild)
        {
          Vertex * r_child_found = find(parent);
          if (!r_child_found)
          {
              remove_the_tree();
              throw std::invalid_argument("Not have parent");
          }
          if (!r_child_found->right)
          {
              r_child_found->right = new Vertex(rchild);
          }
          else
          {
              (r_child_found->right)->value = rchild;
          }
          return *this;
        }

        friend ostream &operator<<(ostream &out, const BinaryTree &tree)
        {
            return out;
        }



        class iterator
        {
        private:

          void preorder(Vertex *root, queue<Vertex *> &q)
          {
              if (!(root))
              {
                  return;
              }
              q.push(root);
              preorder(root->left, q);
              preorder(root->right, q);
          }

          void inorder(Vertex *root, queue<Vertex *> &q)
          {
              if (!(root))
              {
                  return;
              }
              inorder(root->left, q);
              q.push(root);
              inorder(root->right, q);
          }

          void postorder(Vertex *root, queue<Vertex *> &q)
          {
              if (!(root))
              {
                  return;
              }
              postorder(root->left, q);
              postorder(root->right, q);
              q.push(root);
          }

            Vertex * ptr;
            queue<Vertex *> q;

        public:

            iterator(Vertex * current,int type) : ptr(current)
            {
                if(type == 1){
                  preorder(ptr, q);
                }
                if(type == 2){
                  inorder(ptr, q);

                }
                if(type == 3){
                  postorder(ptr, q);
                }
                q.push(nullptr);
                ptr = q.front();
                q.pop();
            }

            iterator &operator++()
            {
                ptr = q.front();
                q.pop();
                return *this;
            }

            iterator operator++(int)
            {
                iterator itr = *this;
                ptr = q.front();
                q.pop();
                return itr;
            }

            T &operator*() const
            {
                return ptr->value;
            }

            T *operator->() const
            {
                return &(ptr->value);
            }

            bool operator==(const iterator &other) const
            {
                return ptr == other.ptr;
            }

            bool operator!=(const iterator &rhs) const
            {
                return ptr != rhs.ptr;
            }

            Vertex *getVertex()
            {
                return ptr;
            }
        };


        iterator begin_preorder() const
        {
            return iterator{root,1};
        }
        iterator end_preorder() const
        {
            return iterator{nullptr,0};
        }
        iterator begin_inorder() const
        {
            return iterator{root,2};
        }
        iterator end_inorder() const
        {
            return iterator{nullptr,0};
        }
        iterator begin() const
        {
            return iterator{root,2};
        }
        iterator end() const
        {
            return iterator{nullptr,0};
        }
        iterator begin_postorder() const
        {
            return iterator{root,3};
        }
        iterator end_postorder() const
        {
            return iterator{nullptr,0};
        }
    };

}
