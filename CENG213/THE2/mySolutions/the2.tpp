#pragma once

#include "LTree.tpp"

// *** You can add additional headers/functions/variables as necessary. ***

// *** Implement the functions below. ***

template<typename T>
LTree<T>::Node * LTree<T>::pushBack(const T & value)
{
    // *** IMPLEMENT THIS ***

    if(this->mRoot==nullptr)
    {
        Node* new_node=new Node(value);
        this->mRoot=new_node;
        this->mTail=new_node;
        return new_node;
    }
    else
    {

    
    Node* node=this->tail();
    Node* new_node=new Node(value);
    
    if(node->mParent==nullptr)
    {
        node->mLeft=new_node;
        new_node->mParent=node;
        node->mNext=new_node;
        new_node->mPrev=node;
        this->mTail=new_node;
        return new_node;
    }
    else
    {

    Node* parent_prev=node->parent();

    if(parent_prev->mRight==nullptr)
    {
        
        parent_prev->mRight=new_node;
        new_node->mParent=parent_prev;
        new_node->mPrev=node;
        node->mNext=new_node;


    }
    else
    {
        Node* new_parent=parent_prev->mNext;
        new_parent->mLeft=new_node;
        new_node->mParent=new_parent;
        new_node->mPrev=node;
        node->mNext=new_node;
    }
    this->mTail=new_node;
    return new_node;
    }

    }
}

template<typename T>
void LTree<T>::popBack()
{
    // *** IMPLEMENT THIS ***
    Node* node=this->tail();
    
    if(node->mParent==nullptr && node->mNext==nullptr && node->mLeft==nullptr && node->mRight==nullptr)
    {
        node->mParent=nullptr;
        node->mPrev=nullptr;
        node->mNext=nullptr;
        node->mLeft=nullptr;
        node->mRight=nullptr;
        this->mRoot=nullptr;
        this->mTail=nullptr;
        delete node;
    }
    else{

    
    Node* parent=node->parent();
    Node* prev=node->prev();
    if(parent->mRight==nullptr)
    {
        
        parent->mLeft=nullptr;
        prev->mNext=nullptr;
        node->mParent=nullptr;
        node->mPrev=nullptr;
        this->mTail=prev;
        
        delete node;
    }
    else
    {
        parent->mRight=nullptr;
        prev->mNext=nullptr;
        node->mParent=nullptr;
        node->mPrev=nullptr;
        this->mTail=prev;
        
        delete node;
    }
    }
    



}

template<typename T>
void LTree<T>::exchange(LTree<T>::Node *a, LTree<T>::Node *b)
{
    Node* node_root=this->mRoot;
    bool check_a=0;
    bool check_b=0;
    if(a->mParent==b)
    {
        if (b->mRight==a)
        {
            Node* a_next=   a->mNext;
            Node* a_left=   a->mLeft;
            Node* a_right=  a->mRight;
            Node* a_parent= a->mParent;
            Node* a_prev=   a->mPrev;

            Node* b_next=   b->mNext;
            Node* b_left=   b->mLeft;
            Node* b_right=  b->mRight;
            Node* b_parent= b->mParent;
            Node* b_prev=   b->mPrev;

            if(b_parent!=nullptr && b_parent->mLeft==b)
            {
                b_parent->mLeft=a;
            }
            else if (b_parent!=nullptr && b_parent->mRight==b)
            {
                b_parent->mRight=a;
            }
            if(b_prev!=nullptr)
            {
                b_prev->mNext=a;
            }
            b_next->mPrev=a;
            b_left->mParent=a;
            

            if(a_left!=nullptr)
            {
                a_left->mParent=b;
            }
            if(a_right!=nullptr)
            {
                a_right->mParent=b;
            }
            if(a_next!=nullptr)
            {
                a_next->mPrev=b;
            }
            a_prev->mNext=b;


            a->mNext=b_next;
            a->mRight=b;
            a->mLeft=b_left;
            a->mParent=b_parent;
            a->mPrev=b_prev;
            b->mPrev=a_prev;
            b->mParent=a;
            b->mNext=a_next;
            b->mRight=a_right;
            b->mLeft=a_left;

            if(this->mTail==a)
            {
                this->mTail=b;
            }
            if(this->mRoot==b)
            {
                this->mRoot=a;
            }

        }
        else if(b->mLeft==a)
        {
            if (b->mNext==a) //bitti
            {
                Node* temp=a->mNext;
                Node* mleft=a->mLeft;
                Node* mright=a->mRight;
                Node* bright=b->mRight;

                if(bright!=nullptr)
                {
                bright->mParent=a;
                }
                if(temp!=nullptr)
                {
                temp->mPrev=b;
                }
                if(mleft!=nullptr)
                {
                    mleft->mParent=b;
                }
                if(mright!=nullptr)
                {
                    mright->mParent=b;
                }


                a->mNext=b;
                a->mLeft=b;
                a->mRight=bright;
                a->mParent=nullptr;
                a->mPrev=nullptr;
                b->mPrev=a;
                b->mParent=a;
                b->mNext=temp;
                b->mRight=mright;
                b->mLeft=mleft;
                this->mRoot=a;
                if(this->mTail==a)
                {
                    this->mTail=b;
                }
            }
            else
            {
                Node* a_next=   a->mNext;
                Node* a_left=   a->mLeft;
                Node* a_right=  a->mRight;
                Node* a_parent= a->mParent;
                Node* a_prev=   a->mPrev;

                Node* b_next=   b->mNext;
                Node* b_left=   b->mLeft;
                Node* b_right=  b->mRight;
                Node* b_parent= b->mParent;
                Node* b_prev=   b->mPrev;

                
                if(b_parent!=nullptr && b_parent->mLeft==b)
                {
                    b_parent->mLeft==a;
                }
                else if (b_parent!=nullptr && b_parent->mRight==b)
                {
                    b_parent->mRight==a;
                }
                if(b_prev!=nullptr)
                {
                    b_prev->mNext=a;
                }
                b_next->mPrev=a;
                b_right->mParent=a;


                if(a_left!=nullptr)
                {
                    a_left->mParent=b;
                }
                if(a_right!=nullptr)
                {
                    a_right->mParent=b;
                }
                if(a_next!=nullptr)
                {
                    a_next->mPrev=b;
                }
                a_prev->mNext=b;


                a->mNext=b_next;
                a->mLeft=b;
                a->mRight=b_right;
                a->mParent=b_parent;
                a->mPrev=b_prev;
                b->mPrev=a_prev;
                b->mParent=a;
                b->mNext=a_next;
                b->mRight=a_right;
                b->mLeft=a_left;

                if(this->mTail==a)
                {
                    this->mTail=b;
                }


            }
        }
    }
    else if (b->mParent==a)
    {
        if (a->mRight==b)
        {
            Node* a_next=   a->mNext;
            Node* a_left=   a->mLeft;
            Node* a_right=  a->mRight;
            Node* a_parent= a->mParent;
            Node* a_prev=   a->mPrev;

            Node* b_next=   b->mNext;
            Node* b_left=   b->mLeft;
            Node* b_right=  b->mRight;
            Node* b_parent= b->mParent;
            Node* b_prev=   b->mPrev;


            if(a_parent!=nullptr && a_parent->mLeft==a)
            {
                a_parent->mLeft=b;
            }
            else if (a_parent!=nullptr && a_parent->mRight==a)
            {
                a_parent->mRight=b;
            }
            if(a_prev!=nullptr)
            {
                a_prev->mNext=b;
            }
            a_next->mPrev=b;
            a_left->mParent=b;
            

            if(b_left!=nullptr)
            {
                b_left->mParent=a;
            }
            if(b_right!=nullptr)
            {
                b_right->mParent=a;
            }
            if(b_next!=nullptr)
            {
                b_next->mPrev=a;
            }
            b_prev->mNext=a;

            a->mNext=b_next;
            a->mRight=b_right;
            a->mLeft=b_left;
            a->mParent=b;
            a->mPrev=b_prev;
            b->mPrev=a_prev;
            b->mParent=a_parent;
            b->mNext=a_next;
            b->mRight=a;
            b->mLeft=a_left;

            if(this->mTail==b)
            {
                this->mTail=a;
            }
            if(this->mRoot==a)
            {
                this->mRoot=b;
            }
        }
        else if(a->mLeft==b)
        {
            if (a->mNext==b) //bitti
            {
                Node* temp=b->mNext;
                Node* mleft=b->mLeft;
                Node* mright=b->mRight;
                Node* aright=a->mRight;


                if(aright!=nullptr)
                {
                aright->mParent=b;
                }
                if(temp!=nullptr)
                {
                temp->mPrev=a;
                }
                if(mleft!=nullptr)
                {
                    mleft->mParent=a;
                }
                if(mright!=nullptr)
                {
                    mright->mParent=a;
                }


                b->mNext=a;
                b->mLeft=a;
                b->mRight=aright;
                b->mParent=nullptr;
                b->mPrev=nullptr;
                a->mPrev=b;
                a->mParent=b;
                a->mNext=temp;
                a->mRight=mright;
                a->mLeft=mleft;
                this->mRoot=b;
                if(this->mTail==b)
                {
                    this->mTail=a;
                }
            }
            else
            {
                Node* a_next=   a->mNext;
                Node* a_left=   a->mLeft;
                Node* a_right=  a->mRight;
                Node* a_parent= a->mParent;
                Node* a_prev=   a->mPrev;

                Node* b_next=   b->mNext;
                Node* b_left=   b->mLeft;
                Node* b_right=  b->mRight;
                Node* b_parent= b->mParent;
                Node* b_prev=   b->mPrev;


                if(a_parent!=nullptr && a_parent->mLeft==a)
                {
                    a_parent->mLeft=b;
                }
                else if (a_parent!=nullptr && a_parent->mRight==a)
                {
                    a_parent->mRight=b;
                }
                if(a_prev!=nullptr)
                {
                    a_prev->mNext=b;
                }
                a_next->mPrev=b;
                a_right->mParent=b;


                if(b_left!=nullptr)
                {
                    b_left->mParent=a;
                }
                if(b_right!=nullptr)
                {
                    b_right->mParent=a;
                }
                if(b_next!=nullptr)
                {
                    b_next->mPrev=a;
                }
                b_prev->mNext=a;


                a->mNext=b_next;
                a->mLeft=b_left;
                a->mRight=b_right;
                a->mParent=b;
                a->mPrev=b_prev;
                b->mPrev=a_prev;
                b->mParent=a_parent;
                b->mNext=a_next;
                b->mRight=a_right;
                b->mLeft=a;

                if(this->mTail==b)
                {
                    this->mTail=a;
                }
            }
        }
    }
    else
    {
        if(a->mNext==b)
        {
            Node* a_next=   a->mNext;
            Node* a_left=   a->mLeft;
            Node* a_right=  a->mRight;
            Node* a_parent= a->mParent;
            Node* a_prev=   a->mPrev;

            Node* b_next=   b->mNext;
            Node* b_left=   b->mLeft;
            Node* b_right=  b->mRight;
            Node* b_parent= b->mParent;
            Node* b_prev=   b->mPrev;


            if(a_left!=nullptr)
            {
                a_left->mParent=b;
            }
            if(a_right!=nullptr)
            {
                a_right->mParent=b;
            }
            if(b_left!=nullptr)
            {
                b_left->mParent=a;
            }
            if(b_right!=nullptr)
            {
                b_right->mParent=a;
            }
            if(a_parent!=nullptr&& a_parent->mLeft==a)
            {
                a_parent->mLeft=b;
                a_parent->mRight=a;
            }
            else if(a_parent!=nullptr&& a_parent->mRight==a)
            {
                a_parent->mRight=b;
                b_parent->mLeft=a;
            }
            if(b_next!=nullptr)
            {
                b_next->mPrev=a;
            }
            a_prev->mNext=b;

            

            a->mNext=b_next;
            a->mLeft=b_left;
            a->mRight=b_right;
            a->mParent=b_parent;
            a->mPrev=b;
            b->mPrev=a_prev;
            b->mParent=a_parent;
            b->mNext=a;
            b->mRight=a_right;
            b->mLeft=a_left;

            if(this->mTail==b)
            {
                this->mTail=a;
            }
        }
        else if (b->mNext==a)
        {
            Node* a_next=   a->mNext;
            Node* a_left=   a->mLeft;
            Node* a_right=  a->mRight;
            Node* a_parent= a->mParent;
            Node* a_prev=   a->mPrev;

            Node* b_next=   b->mNext;
            Node* b_left=   b->mLeft;
            Node* b_right=  b->mRight;
            Node* b_parent= b->mParent;
            Node* b_prev=   b->mPrev;


            if(a_left!=nullptr)
            {
                a_left->mParent=b;
            }
            if(a_right!=nullptr)
            {
                a_right->mParent=b;
            }
            if(b_left!=nullptr)
            {
                b_left->mParent=a;
            }
            if(b_right!=nullptr)
            {
                b_right->mParent=a;
            }
            if(a_parent!=nullptr&& a_parent->mLeft==a)
            {
                a_parent->mLeft=b;
                
            }
            else if(a_parent!=nullptr&& a_parent->mRight==a)
            {
                a_parent->mRight=b;
                
            }
            if(b_parent!=nullptr&& b_parent->mLeft==b)
            {
                b_parent->mLeft=a;
                
            }
            else if(b_parent!=nullptr&& b_parent->mRight==b)
            {
                b_parent->mRight=a;
                
            }
            if(a_next!=nullptr)
            {
                a_next->mPrev=b;
            }
            b_prev->mNext=a;
            a->mNext=b;
            a->mLeft=b_left;
            a->mRight=b_right;
            a->mParent=b_parent;
            a->mPrev=b_prev;
            b->mPrev=a;
            b->mParent=a_parent;
            b->mNext=a_next;
            b->mRight=a_right;
            b->mLeft=a_left;

            if(this->mTail==a)
            {
                this->mTail=b;
            }
        }
        else
        {
            Node* a_next=   a->next();
            Node* a_left=   a->left();
            Node* a_right=  a->right();
            Node* a_parent= a->parent();
            Node* a_prev=   a->prev();

            Node* b_next=   b->next();
            Node* b_left=   b->left();
            Node* b_right=  b->right();
            Node* b_parent= b->parent();
            Node* b_prev=   b->prev();


            if(a_left!=nullptr)
            {
                a_left->mParent=b;
            }
            if(a_right!=nullptr)
            {
                a_right->mParent=b;
            }
            if(b_left!=nullptr)
            {
                b_left->mParent=a;
            }
            if(b_right!=nullptr)
            {
                b_right->mParent=a;
            }
            if(a_parent!=nullptr&& a_parent->mLeft==a)
            {
                a_parent->mLeft=b;
                
            }
            else if(a_parent!=nullptr&& a_parent->mRight==a)
            {
                a_parent->mRight=b;
                
            }
            if(b_parent!=nullptr&& b_parent->mLeft==b)
            {
                b_parent->mLeft=a;
                
            }
            else if(b_parent!=nullptr&& b_parent->mRight==b)
            {
                b_parent->mRight=a;
                
            }
            if(a_next!=nullptr)
            {
                a_next->mPrev=b;
            }
            if(b_next!=nullptr)
            {
                b_next->mPrev=a;
            }
            if(b_prev!=nullptr)
            {
                b_prev->mNext=a;
            }
            if(a_prev!=nullptr)
            {
                a_prev->mNext=b;
            }
            a->mNext=b_next;
            a->mLeft=b_left;
            a->mRight=b_right;
            a->mParent=b_parent;
            a->mPrev=b_prev;
            b->mPrev=a_prev;
            b->mParent=a_parent;
            b->mNext=a_next;
            b->mRight=a_right;
            b->mLeft=a_left;

            if(this->mTail==b)
            {
                this->mTail=a;
            }
            else if (this->mTail==a)
            {
                this->mTail=b;
            }
            if(this->mRoot==b)
            {
                this->mRoot=a;
            }
            else if (this->mRoot==a)
            {
                this->mRoot=b;
            }
        }
        
    }
}

template<typename T>
void LTree<T>::split(LTree<T> **outLeft, LTree<T> **outRight)
{
    // *** IMPLEMENT THIS ***
    
    Node* root_node=this->mRoot;
    Node* deneme=this->mRoot;
    
    if(root_node->mRight==nullptr&&root_node->mLeft==nullptr)
    {

        LTree<T>* final_left= new LTree<T>();
        LTree<T>* final_right= new LTree<T>();
        final_right->mRoot=root_node->mRight;
        final_right->mTail=root_node->mRight;
        *outRight=final_right;
        final_left->mRoot=root_node->mLeft;
        final_left->mTail=root_node->mLeft;
        *outLeft=final_left;
        root_node->mNext=nullptr;
        root_node->mPrev=nullptr;
        root_node->mRight=nullptr;
        root_node->mLeft=nullptr;
        root_node->mParent=nullptr;
        this->mRoot=root_node;
        this->mTail=root_node;
    }
    else if(root_node->mRight==nullptr&&root_node->mLeft!=nullptr)
    {
        LTree<T>* final_left= new LTree<T>();
        LTree<T>* final_right= new LTree<T>();
        final_right->mRoot=root_node->mRight;
        final_right->mTail=root_node->mRight;
        *outRight=final_right;
        Node* left_node=root_node->mLeft;
        left_node->mPrev=nullptr;
        left_node->mParent=nullptr;
        final_left->mRoot=left_node;
        final_left->mTail=left_node;
        *outLeft=final_left;
    
        root_node->mNext=nullptr;
        root_node->mLeft=nullptr;
        this->mRoot=root_node;
        this->mTail=root_node;
    }
    else
    {

    LTree<T>* final_left= new LTree<T>();
    Node* left_node=root_node->mLeft;
    left_node->mParent=nullptr;
    left_node->mPrev=nullptr;
    final_left->mRoot=left_node;

    LTree<T>* final_right= new LTree<T>();
    Node* right_node=root_node->mRight;
    right_node->mParent=nullptr;
    right_node->mPrev=nullptr;
    final_right->mRoot=right_node;

    Node* test_left=left_node;
    Node* test_node=left_node->mLeft;
    bool check=0;
    while(test_node!=nullptr)
    {
        
        test_node->mPrev=test_left;
        test_left->mNext=test_node;

        test_node=test_node->mLeft;
        if(test_left->mRight==nullptr)
        {
            check=1;
            break;
        }
        test_left=test_left->mRight;
    }
    if(!check)
    {
        final_left->mTail=test_left;
        test_left->mNext=nullptr;
    }
    else
    {
        final_left->mTail=this->mTail;
    }


    Node* test_right=right_node;
    test_node=right_node->mLeft;
    bool check1=0;
    while(test_node!=nullptr)
    {
        
        test_node->mPrev=test_right;
        test_right->mNext=test_node;

        test_node=test_node->mLeft;
        if(test_right->mRight==nullptr)
        {
            check1=1;
            break;
        }
        test_right=test_right->mRight;
    }
    if(!check1)
    {
        test_right->mNext=nullptr;
        final_right->mTail=test_right;
    }
    else
    {
        final_right->mTail=this->mTail;
    }
    *outLeft=final_left;
    *outRight=final_right;
    deneme->mNext=nullptr;
    deneme->mPrev=nullptr;
    deneme->mRight=nullptr;
    deneme->mLeft=nullptr;
    deneme->mParent=nullptr;
    this->mRoot=deneme;
    this->mTail=deneme;
    }
}
